/*demo: used to do a benchmark*/
/*last modified: Mar 18, 2022*/
/*author: Penguin*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hypamas_api.h"

int main(int argc, char *argv[])
{
    int retval;
    void *handler;
    int *iparm;
    double *dparm;
    int n, nnz, i;
    double *ax;
    int *ap, *ai;
    double *rhs, *sol, rerr, memuse;

    if (argc < 3)
        return 0;

    ax = NULL;
    ai = NULL;
    ap = NULL;
    sol = NULL;

    // initialize Hypamas, call it only once
    retval = HypamasInit(&handler, &iparm, &dparm);
    if (FAIL(retval))
    {
        printf("initilization error = %d\n", retval);
        goto FINAL;
    }

    iparm[kIparmTimer] = 1; // turn on timer
    // iparm[kIparmAutoParallelOff] = 1; // turn off automatic thread control
    iparm[kIparmSolveTranspose] = 0; // solve A*x=b

    // read matrix from matrix market file
    retval = Hypamas_ReadMatrixMarketFile(argv[1], &n, &nnz, &ax, &ap, &ai, 0);
    if (FAIL(retval))
    {
        printf("read matrix market file error = %d\n", retval);
        goto FINAL;
    }

    sol = (double *)malloc(sizeof(double) * n * 2);
    rhs = sol + n;
    for (i = 0; i < n; ++i)
        rhs[i] = 1.;

    printf("\n==========\n");
    printf("N = %d, NNZ = %d\n", n, nnz);

    // pre-processing include sparse ordering and static pivoting
    retval = HypamasAnalyze(handler, n, ax, ap, ai);
    if (FAIL(retval))
    {
        printf("analysis error = %d\n", retval);
        goto FINAL;
    }
    printf("analysis time: %.8g\n", dparm[kDparmAnalyzeTime]);
    printf("estimated FLOPS(GFlops): %g\n", dparm[kDparmGFlopsAnalyzed]);
    printf("\n==========\n");

    // initialize thread, call it only once
    retval = HypamasInitThreads(handler, atoi(argv[2]));
    if (FAIL(retval))
    {
        printf("initilization thread error = %d\n", retval);
        goto FINAL;
    }

    // perform P*A=L*U with partial pivoting
    retval = HypamasFactorize(handler, ax, 0);
    if (FAIL(retval))
    {
        printf("factorization error = %d\n", retval);
        goto FINAL;
    }
    printf("1st fact time: %.8g\n", dparm[kDparmFactTime]);

    // perform forward elimination(L*y=b) and backward substitution(U*x=y)
    retval = HypamasSolve(handler, rhs, sol, 0);
    if (FAIL(retval))
    {
        printf("solve error = %d\n", retval);
        goto FINAL;
    }
    printf("solve time: %.8g\n", dparm[kDparmSolveTime]);

    // calculate the residual error |b-A*x|_F
    HypamasResidualNorm(handler, ax, ap, ai, sol, rhs, NULL, &rerr, NULL);
    printf("|b-A*x|_F: %.8g\n", rerr);
    printf("L = %d, U = %d\n", iparm[kIparmLowerEntryNumFactored], iparm[kIparmUpperEntryNumFactored]);
    printf("F = %d, Off-pivot = %d\n", iparm[kIparmEntryNumberFactored], iparm[kIparmOffDiagonalPivotNum]);

    printf("\n");

    retval = HypamasFactorize(handler, ax, 0);
    if (FAIL(retval))
    {
        printf("factorization error = %d\n", retval);
        goto FINAL;
    }
    printf("2nd fact time = %.8g\n", dparm[kDparmFactTime]);

    retval = HypamasSolve(handler, rhs, sol, 0);
    if (FAIL(retval))
    {
        printf("solve error = %d\n", retval);
        goto FINAL;
    }
    printf("solve time: %.8g\n", dparm[kDparmSolveTime]);

    HypamasResidualNorm(handler, ax, ap, ai, sol, rhs, NULL, &rerr, NULL);
    printf("|b-A*x|_F: %.8g\n", rerr);

    printf("\n==========\n");

    // perform A=L*U without partial pivoting
    retval = HypamasReFactorize(handler, ax, 0);
    if (FAIL(retval))
    {
        printf("refactorization error = %d\n", retval);
        goto FINAL;
    }
    printf("1st refact time: %.8g\n", dparm[kDparmFactTime]);

    retval = HypamasSolve(handler, rhs, sol, 0);
    if (FAIL(retval))
    {
        printf("solve error = %d\n", retval);
        goto FINAL;
    }
    printf("solve time: %.8g\n", dparm[kDparmSolveTime]);

    HypamasResidualNorm(handler, ax, ap, ai, sol, rhs, NULL, &rerr, NULL);
    printf("|b-A*x|_F: %.8g\n", rerr);

    printf("\n");

    retval = HypamasReFactorize(handler, ax, 0);
    if (FAIL(retval))
    {
        printf("refactorization error = %d\n", retval);
        goto FINAL;
    }
    printf("2nd refact time: %.8g\n", dparm[kDparmFactTime]);

    retval = HypamasSolve(handler, rhs, sol, 0);
    if (FAIL(retval))
    {
        printf("solve error = %d\n", retval);
        goto FINAL;
    }
    printf("solve time: %.8g\n", dparm[kDparmSolveTime]);

    HypamasResidualNorm(handler, ax, ap, ai, sol, rhs, NULL, &rerr, NULL);
    printf("|b-A*x|_F: %.8g\n", rerr);

    // refine solution using residual error as stopping criterion
    iparm[kIparmRefineMetric] = kCfgRefineResidualError;
    retval = HypamasRefine(handler, ax, ap, ai, rhs, sol);
    if (FAIL(retval))
    {
        printf("refinement error = %d\n", retval);
        goto FINAL;
    }
    HypamasResidualNorm(handler, ax, ap, ai, sol, rhs, NULL, &rerr, NULL);
    printf("number of iterative refinement = %d\n", iparm[kIparmIterNum]);
    printf("after refinement |b-A*x|_F: %.8g\n", rerr);

    printf("\n==========\n");

    iparm[kIparmStagnationStep] = 25;

    // using sequential incomplete factorization based on threshold dropping with partial pivoting without merging supernode
    iparm[kIparmInFactAlgorithm] = kCfgInFactColumnSILUTP;
    retval = HypamasInFactorize(handler, ax, 0);
    if (FAIL(retval))
    {
        printf("infactorization error = %d\n", retval);
    }

    dparm[kDparmILUDropTolerance] = 1e-4;     // set drop tolerance 1e-4
    dparm[kDparmGMRESMetricTolerance] = 1e-8; // set iterative stopping tolerance 1e-8

    memset(sol, 0, sizeof(double) * n);                   // set initial-guess zero
    retval = HypamasGMRES(handler, ax, ap, ai, rhs, sol); // GMRES with right-preconditioner
    if (FAIL(retval))
    {
        printf("GMRES error = %d\n", retval);
        goto FINAL;
    }
    printf("gmres preconditioning time: %.8g\n", dparm[kDparmFactTime]);
    printf("gmres iterating time: %.8g\n", dparm[kDparmSolveTime]);
    printf("gmres total time: %.8g\n", dparm[kDparmFactTime] + dparm[kDparmSolveTime]);
    printf("number of iterative refinement = %d\n", iparm[kIparmIterNum]);
    printf("L = %d, U = %d\n", iparm[kIparmLowerEntryNumFactored], iparm[kIparmUpperEntryNumFactored]);

    HypamasResidualNorm(handler, ax, ap, ai, sol, rhs, NULL, &rerr, NULL);
    printf("|b-A*x|_F: %.8g\n", rerr);

    HypamasEstimateMemoryUsage(handler, &memuse);
    printf("memory usage(MB): %g\n", memuse);

FINAL:

    HypamasFinalize(handler);
    if (NULL != sol)
        free(sol);

    return 0;
}
