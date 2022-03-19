HYPAMAS: Hybrid Parallel Matrix Solver for Linear Systems
=======
The package HYPAMAS is a thread-safe, high-performance, robust software for solving large sparse nonsymmetric linear systems of equations A*X=b using an either direct or iterative method on shared-memory machines with a multi-core processor. HYPAMAS is implemented in pure C using POSIX threads for parallelization, and hand-code BLAS for efficient numerical calculation. So it is straightforward to use HYPAMAS without linking other software packages.

In the direct method, HYPAMAS contains three numerical kernels to update LU factorization:
>1) sparse left-looking LU factorization based on sparse BLAS-1.  
>2) sparse left-looking LU factorization based on sparse BLAS-1 and standard dense BLAS-2.  
>3) sparse left-right looking LU factorization based on sparse BLAS-1, standard dense BLAS-2, and BLAS-3.  
  
In the direct method, HYPAMAS can use sequential/parallel forward elimination and backward substitution. To be suitable for Newton-Raphson iteration, HYPAMAS supports a re-factorization to perform A=LU without numerical pivoting permutation.

In the iterative method, HYPAMAS uses incomplete LU(ILU) factorization as the right preconditioner for the generalized minimal residual method(GMRES). It also supports versatile ILU algorithms:
>1) sparse left-looking ILU factorization based on threshold dropping(ILUT) based on sparse BLAS-1 and standard dens BLAS-2.
>2) sparse left-looking ILU factorization based on threshold dropping with partial pivoting(ILUTP) based on sparse BLAS-1 and standard dens BLAS-2.  
  
GMRES is temporarily only in sequential implementation, and ILU has the parallel feature.
  
HYPAMAS has the following improvement features:
>1) Automatical thread control.
>2) Adaptive algorithm selection.
>3) Advanced acceleration technology.
>4) Accurate and attractive preconditioner.

Details:
=======
>1) HYPAMAS can automatically control thread to determine whether using parallel computation. This feature can be turned off in parameter iparm[kIparmAutoParallelOff] then HYPAMAS will execute the program by threads that the user gives.
>2) Forward elimination(L*y=b) and backward substitution(U*x=y) performs much fewer floating-point operations per second(FLOPS) than a numerical LU factorization, it is not guaranteed that parallelization of triangular solves can gain performance improvements. So it is always recommended that triangular solves are sequential.
>3) HYPAMAS only supports the sparse matrix A stored in a compressed sparse row format[(CSR)](https://en.wikipedia.org/wiki/Sparse_matrix). If the sparse matrix given is stored in a compressed sparse column(CSC), HYPAMAS should solve A<sup>T</sup>*x=b instead of A*x=b. This option is controled in parameter iparm[kIparmSolveTranspose].

Requirements:
===========
OS: linux  
CPU: AVX Instruction Set  
gcc: 8.4  

References:
==========
[1] J. R. Gilbert and T. Peierls. Sparse partial pivoting in time proportional to arithmetic operations. SIAM J. Scientific and Statistical Computing, 9:862-874, 1988.  
[2] S. C. Eisenstat and J. W. H. Liu. Exploiting structural symmetry in a sparse partial pivoting code. SIAM J. Scientific and Statistical Computing, 14:253-257, 1993.
  
Authors:
=======
- 👋 Hi, I’m Penguin.
- 👀 I’m interested in high-performance computation, especially in matrix solvers.
- 🌱 I’m currently learning direct & iterative matrix solvers.
- 💞️ I’m looking to collaborate on a nice team.
- 📫 You can contact me by [email](mailto:hypamas@outlook.com).

<!---
Hypamas/Hypamas is a ✨ special ✨ repository because its `README.md` (this file) appears on your GitHub profile.
You can click the Preview link to take a look at your changes.
--->
