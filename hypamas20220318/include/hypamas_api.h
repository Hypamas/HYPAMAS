/*used to define api and control parameter*/
/*last modified: Mar 18, 2022*/
/*author: Penguin*/

#ifndef __HYPAMAS_API__
#define __HYPAMAS_API__

#define IN__
#define OUT__
#define INOUT__

#ifdef __cplusplus
extern "C"
{
#endif

    /*Initialize the Hypamas. It must be called at first.*/
    /*This routine have to be performed ONLY ONCE.*/
    int HypamasInit(
        INOUT__ void **handler,
        INOUT__ int **iparm,
        INOUT__ double **dparm);

    /*Destroy the Hypamas and free all memories. It must be called in the last*/
    int HypamasFinalize(
        INOUT__ void *handler);

    /*Pre-processing, including ordering and static pivoting.*/
    /*This routine have to be performed ONLY ONCE.*/
    int HypamasAnalyze(
        INOUT__ void *handler,
        IN__ int n,
        IN__ double *ax,
        IN__ int *ap,
        IN__ int *ai);

    /*Create threads for parallel factoriztion, re-factorization or in-factorization.*/
    /*This routine have to be performed ONLY ONCE.*/
    int HypamasInitThreads(
        INOUT__ void *handler,
        IN__ int threads);

    /*LU factorization, with partial pivoting.*/
    /*Before called, HypamasAnalyze must be called.*/
    int HypamasFactorize(
        INOUT__ void *handler,
        IN__ double *ax,
        IN__ int threads);

    /*LU factorization, without partial pivoting.*/
    /*Before called, HypamasFactorize must be called at least once.*/
    int HypamasReFactorize(
        INOUT__ void *handler,
        IN__ double *ax,
        IN__ int threads);

    /*Solve the linear system Ax=b after LU or ILU factorization.*/
    /*If x is NULL, b will be overwritten by the solution on output. Otherwise b is not changed and x return the solution on output.*/
    int HypamasSolve(
        INOUT__ void *handler,
        INOUT__ double *rhs,
        OUT__ double *sol,
        IN__ int threads);

    /*Incomplete LU factorization, inculde ILUT and ILUTP.*/
    /*Before called, HypamasAnalyze must be called.*/
    int HypamasInFactorize(
        INOUT__ void *handler,
        IN__ double *ax,
        IN__ int threads);

    /*Solve nonsymmetric linear systems Ax=b using krylov method, based on the generalized minimal residual method.*/
    /*Before called, HypamasInFactorize must be called.*/
    int HypamasGMRES(
        INOUT__ void *handler,
        IN__ double *ax,
        IN__ int *ap,
        IN__ int *ai,
        IN__ double *rhs,
        INOUT__ double *sol);

    /*Refine the linear systems Ax=b using residual error or backward error. This routine does not always work well.*/
    int HypamasRefine(
        INOUT__ void *handler,
        IN__ double *ax,
        IN__ int *ap,
        IN__ int *ai,
        IN__ double *rhs,
        OUT__ double *sol);

    /*Memory used by hypamas, in MBytes.*/
    /*This routine estimates an approximate value.*/
    int HypamasEstimateMemoryUsage(
        IN__ void *handler,
        OUT__ double *memuse);

    /*calculate the residual error, rerr = |b-A*x| or rerr = |b-A_T*x|, fast but maybe overflow:*/
    /*rerr0: L1-norm of the residual vector.*/
    /*rerr1: L2-norm of the residual vector, also known as Frobenius norm.*/
    /*rerr2: Loo-norm of the residual vector.*/
    int HypamasResidualNorm(
        IN__ void *handler,
        IN__ double *ax,
        IN__ int *ap,
        IN__ int *ai,
        IN__ double *sol,
        IN__ double *rhs,
        OUT__ double *rerr0,
        OUT__ double *rerr1,
        OUT__ double *rerr2);

    /*******************************************************************************/

    /*Esitmate matrix type.*/
    int Hypamas_EstimateMatrixType(
        IN__ int *n,
        IN__ double *ax,
        IN__ int *ap,
        IN__ int *ai,
        OUT__ int *mtype);

    /*Check matrix consistency.*/
    int Hypamas_CheckMatrix(
        IN__ int n,
        IN__ int nnz,
        IN__ int *ap,
        IN__ int *ai);

    /*This routine is more stable but slower.*/
    /*When mode=0, it calculates residual error = |b-A*x|.*/
    /*When mode=1, it calculates residual error = |b-A_T*x|.*/
    /*rerr0: L1-norm of the residual vector.*/
    /*rerr1: L2-norm of the residual vector, also known as Frobenius norm.*/
    /*rerr2: Loo-norm of the residual vector.*/
    int Hypamas_SparseResidual(
        IN__ int n,
        IN__ double *ax,
        IN__ int *ap,
        IN__ int *ai,
        IN__ double *sol,
        IN__ double *rhs,
        IN__ int mode,
        OUT__ double *rerr0,
        OUT__ double *rerr1,
        OUT__ double *rerr2);

    /*Write a matrix to a file formatted by the matrix market format(CSC format).*/
    /*While for mode, zero denotes ax & ap & ai is CSR formatted, otherwise stored by CSC format.*/
    /*Matrix(ax & ap & ai) is based zero, but data in output file is based one. If ap is NULL and ai is NULL,*/
    /*ax will be a vector based zero, in general, right hand side.*/
    int Hypamas_WriteMatrixMarketFile(
        IN__ char *file,
        IN__ int n,
        IN__ int nnz,
        IN__ double *ax,
        IN__ int *ap,
        IN__ int *ai,
        IN__ int mode);

    /*Read a matrix from a file formatted by the matrix market format(CSC format)*/
    /*While for mode, zero denotes ax & ap & ai is CSR formatted, otherwise stored by CSC format.*/
    /*Matrix(ax & ap & ai) is based zero, but data in input file is based one. If ap is NULL and ai is NULL,*/
    /*ax will be a vector based zero, in general, right hand side*/
    int Hypamas_ReadMatrixMarketFile(
        IN__ char *file,
        OUT__ int *n,
        OUT__ int *nnz,
        OUT__ double **ax,
        OUT__ int **ap,
        OUT__ int **ai,
        IN__ int mode);

#ifdef __cplusplus
}
#endif

/**
 * @brief Integer control parameters
 */
enum HypamasIparm
{
    kIparmTimer,                 /* Enable timer for performace profile                              Default: 0                                  [IN]        */
    kIparmAutoParallelOff,       /* Automatical parallelization                                      Default: 0                                  [IN]        */
    kIparmSolveTranspose,        /* Solve with transpose matrix                                      Default: 0                                  [IN]        */
    kIparmStaticScaling,         /* Static scaling                                                   Default: 0                                  [IN]        */
    kIparmDynamicScaling,        /* Dynamic scaling method                                           Default: kDynamicScalingOff                 [IN]        */
    kIparmThreadNumber,          /* Number of the native threads, exclude hyper threads              Default: -                                  [OUT]       */
    kIparmThreadCreated,         /* Number of the created threads                                    Default: 1                                  [OUT]       */
    kIparmThreadUsed,            /* Number of the actually used threads                              Default: 1                                  [OUT]       */
    kIparmSupernodeMaxRow,       /* Maximum number of the consecutive row for a supernode            Default: 56                                 [IN]        */
    kIparmSupernodeRelaxation,   /* Maximum number of the relaxation row for a supernode [1, 16]     Default: 8                                  [IN]        */
    kIparmSupernodeMinColumn,    /* Minimum number of the column consisting of a supernode           Default: 0                                  [IN]        */
    kIparmPanelSize,             /* Size of the panel                                                Default: 16                                 [IN]        */
    kIparmRowBlock,              /* Minimum size of row block in panel supernode                     Default: 32                                 [IN]        */
    kIparmColumnBlock,           /* Minimum size of column block in panel supernode                  Default: 200                                [IN]        */
    kIparmSupernodeNumber,       /* Number of supernode in factorization                             Default: 0                                  [OUT]       */
    kIparmInFactAlgorithm,       /* Selected algorithm for incomplete factorization                  Default: kCfgInFactColumnSILUTP             [IN]        */
    kIparmKrylovDimension,       /* Krylov subspace dimension                                        Default: 50                                 [IN]        */
    kIparmKrylovMaxIter,         /* Maximum iteration number of GMRES                                Default: 300                                [IN]        */
    kIparmStagnationStep,        /* Max number of stagnation step in Krylov subspace                 Default: 25                                 [IN]        */
    kIparmIterNum,               /* Number of the used iterative refinement                          Default: -                                  [OUT]       */
    kIparmRefineMaxIter,         /* Maximum iteration number of refinement                           Default: 3                                  [IN]        */
    kIparmRefineMetric,          /* Metric about refinement using residual error or backward error   Default: kCfgRefineResidualError            [IN]        */
    kIparmSingularRow,           /* Index of singular row, based on zero                             Default: -1                                 [OUT]       */
    kIparmEntryNumberAnalyzed,   /* Number of non-zero estimated in phase analysis                   Default: 0                                  [OUT]       */
    kIparmOffDiagonalPivotNum,   /* Number of off-pivoting occured in factorization                  Default: 0                                  [OUT]       */
    kIparmLowerEntryNumFactored, /* Number of non-zero in L including diag in factorization          Default: 0                                  [OUT]       */
    kIparmUpperEntryNumFactored, /* Number of non-zero in U including diag in factorization          Default: 0                                  [OUT]       */
    kIparmEntryNumberFactored,   /* Number of non-zero counted in factorization                      Default: 0                                  [OUT]       */
    kIparmFastOff,               /* Disable fast method for factorization using previous symbolic    Default: 0                                  [IN]        */
    kIparmSortOrderOff,          /* Disable sort order for refactorization                           Default: 0                                  [IN]        */
    kIparmMapLinkOff,            /* Disable map link for refactorization                             Default: 1                                  [IN]        */
    kIparmAMDFlipFlag,           /* Flip flag for AMD                                                Default: 1                                  [IN]        */

};

/**
 * @brief Double control parameters
 */
enum HypamasDparm
{

    kDparmPivotTolerance,       /* Partial pivoting tolerance threshold                             Default: 0.001                              [IN]        */
    kDparmAMDDense,             /* Threshold of detecting dense row for AMD                         Default: 10                                 [IN]        */
    kDparmLoadBalance,          /* Coefficient used to control loading balance                      Default: 0.95                               [IN]        */
    kDparmILUDropTolerance,     /* Dropping tolerance for incomplete factorization                  Default: 1e-6                               [IN]        */
    kDparmGMRESMetricTolerance, /* Relative stopping tolerance for GMRES                            Default: 1e-10                              [IN]        */
    kDparmRefineEpsilon,        /* EPSILON for iterative refinment                                  Default: 1e-10                              [IN]        */
    kDparmAnalyzeTime,          /* Time used for analyzing matrix                                   Default: -                                  [OUT]       */
    kDparmFactTime,             /* Time used for symbolic & numeric (incomplete) factorization      Default: -                                  [OUT]       */
    kDparmSolveTime,            /* Time used for direct & iterative solving                         Default: -                                  [OUT]       */
    kDparmGFlopsAnalyzed,       /* GFlops(10^9) estimated in phase analysis                         Default: -                                  [OUT]       */

};

/**
 * @brief Dynamic scaling method
 */
enum HypamasDynamicScaling
{
    kDynamicScalingOff = 0, /* Dynamic scaling: no*/
    kDynamicScalingMax = 1, /* Dynamic scaling: max-scaling*/
    kDynamicScalingSum = 2  /* Dynamic scaling: sum-scaling*/
};

/**
 * @brief Algorithm for incomplete LU factorization
 */
enum HypamasCfgInFact
{
    kCfgInFactPreconditionerOff = 0, /* No preconditioner*/
    kCfgInFactColumnSILUTP = 1,      /* Sequential ILUTP based on column*/
    kCfgInFactColumnSILUT = 2,       /* Sequential ILUT based on column*/
    kCfgInFactColumnPILUTP = 3,      /* Parallel ILUTP based on column*/
    kCfgInFactColumnPILUT = 4,       /* Parallel ILUT based on column*/
    kCfgInFactSupernodeSILUTP = 5,   /* Sequential ILUTP based on supernode*/
};

/**
 * @brief Cfg of stopping criterion for refinement
 */
enum HypamasCfgRefineMetric
{
    kCfgRefineResidualError = 0, /* Using residual error as stopping criterion*/
    kCfgRefineBackwardError,     /* Using backward error as stopping criterion*/
};

/**
 * @brief Matrix type in hypamas
 */
enum HypamasMatrixType
{
    kMTypeGeneral = 0,            /* General matrix, nonsymmetric matrix*/
    kMTypeStructualSymmetric = 1, /* Structural symmetric matrix*/
    kMTypeNumericSymmetric = 2,   /* Symmetric but non positive definite matrix */
    kMTypePositiveDefinite = 3,   /* Positive definite matrix*/
};

/**
 * @brief return warning & error code in Hypamas
 */
enum HypamasReturnValues
{
    kHypamasOK = 0,
    kErrorGeneralFail = -1,
    kErrorInvalidArgument = -2,
    kErrorOutOfMemory = -3,
    kErrorOpenFileFail = -4,
    kErrorMatrixStructuralSingular = -5,
    kErrorMatrixNumericSingular = -6,
    kErrorMatrixConsistencyCheck = -7,
    kErrorMatrixDuplicatedEntry = -8,
    kErrorThreadInitializeFail = -9,
    kErrorThreadNotInitialized = -10,
    kErrorPhaseNotInitialized = -11,
    kErrorPhaseNotAnalyzed = -12,
    kErrorPhaseNotFactorized = -13,
    kErrordOverflow = -14,
    kErrorMapInitializeFail = -15,
    kErrorAlgorithmInvalid = -16,
    kWarningThreadBindFail = +1,
    kWarningMaxIterationAchieved = +2,
    kWarningIterationConvergeSlowly,
    kWarningIterationConvergeFail,
    kWarningNoPreconditioner,
    kWarningMatrixNotSorted,
};

#define OK(code) ((code) >= kHypamasOK)
#define FAIL(code) ((code) < kHypamasOK)
#define WARNING(code) ((code) > kHypamasOK)
#define EXCEPT(code) ((code) != kHypamasOK)

#endif
