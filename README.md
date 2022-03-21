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
>1) HYPAMAS can automatically control thread to determine whether using parallel computation. This feature can be turned off in parameter `iparm[kIparmAutoParallelOff]` then HYPAMAS will execute the program by the given number of used threads.
>2) Forward elimination(L*y=b) and backward substitution(U*x=y) performs much fewer floating-point operations per second(FLOPS) than a numerical LU factorization, it is not guaranteed that parallelization of triangular solves can gain performance improvements. So it is always recommended that triangular solves are sequential.
>3) HYPAMAS only supports the sparse matrix A stored in a compressed sparse row format[(CSR)](https://en.wikipedia.org/wiki/Sparse_matrix). If the sparse matrix given is stored in a compressed sparse column(CSC), HYPAMAS should solve A<sup>T</sup>*x=b instead of A*x=b. This option is controled in parameter `iparm[kIparmSolveTranspose]`.

Benchmark:
=========
From the top-level directory of HYPAMAS, type:
>1) cd demo
>2) make
>3) ./benchmark rajat19.mtx 8  

This series of commands solve the matrix `rajat19.mtx` based on LU factorization with the used number of threads equal to `8`.  
It is available to download the benchmark test set from the website [SuiteSparse Matrix Collection](https://sparse.tamu.edu/)[<sup>[12]</sup>](#refer_anchor_12).   HYPAMAS is deliberately well-devised to solve the matrix obtained from the `Newton-Raphson` iteration, e.g. Circuit Simulation Problem typically in `SPICE-like` simulators. It is worth mentioning that HYPAMAS only temporarily supports the [Matrix Market](https://math.nist.gov/MatrixMarket/formats.html) exchange format, not the `MATLAB` and the [Rutherford Boeing](https://people.math.sc.edu/Burkardt/data/rb/rb.html) format.

Requirements:
===========
OS: linux  
CPU: AVX Instruction Set  
gcc: 8.4  

References:
==========
<div id = "refer_anchor_1" ></div>
[1] J. R. Gilbert and T. Peierls. Sparse partial pivoting in time proportional to arithmetic operations. SIAM J. Scientific and Statistical Computing, 9:862-874, 1988.  
<div id = "refer_anchor_2" ></div>
[2] S. C. Eisenstat and J. W. H. Liu. Exploiting structural symmetry in a sparse partial pivoting code. SIAM J. Scientific and Statistical Computing, 14:253-257, 1993.  
<div id = "refer_anchor_3" ></div>
[3] Xiaoye S. Li. Sparse gaussian elimination on high performance computers. EECS Department, University of California, Berkeley, 1996.  
<div id = "refer_anchor_4" ></div>
[4] T. A. Davis and E. P. Natarajan. Algorithm 907: KLU, a direct sparse solver for circuit simulation problems. ACM Trans. Mathematical Software. 37(3), 36:1-36:17, 2010.  
<div id = "refer_anchor_5" ></div>
[5] X. Chen, Y. Wang and H. Yang. NICSLU: An adaptive sparse matrix solver for parallel circuit simulation. IEEE Trans. Computer-Aided Design of Integrated Circuits and Systems. 32(2), 261-274, 2013.  
<div id = "refer_anchor_6" ></div>
[6] I. S. Duff and J. Koster. On algorithms for permuting large entries to the diagonal of a sparse matrix. SIAM J. Matrix Analysis and Applications. 22(4), 973-996, 2000.  
<div id = "refer_anchor_7" ></div>
[7] P. R. Amestoy, T. A. Davis and I. S. Duff. Algorithm 837: AMD, an approximate minimum degree ordering algorithm. ACM Trans. Mathematical Software. 30(3), 381-388, 2004.  
<div id = "refer_anchor_8" ></div>
[8] Y. Saad. ILUT: A dual threshold incomplete LU factorization. Numerical Linear Algebra with Applications, 1(4), 387–402, 1994.  
<div id = "refer_anchor_9" ></div>
[9] Xiaoye S. Li and M. Shao. A supernodal approach to incomplete LU factorization with partial pivoting. ACM Trans. Mathematical Software. 37(4), 43:1-43:20, 2011.  
<div id = "refer_anchor_10" ></div>
[10] Y. Saad and M. H. Schultz. GMRES: A generalized minimal residual algorithm for solving nonsymmetric linear systems. SIAM J. Scientific and Statistical Computing, 7(3), 856-869, 1986.  
<div id = "refer_anchor_11" ></div>
[11] Y. Saad. Iterative methods for sparse linear systems. 2nd Edition. SIAM. 2003.  
<div id = "refer_anchor_12" ></div>
[12] T. A. Davis and Y. Hu. The University of Florida Sparse Matrix Collection. ACM Trans. Mathematical Software. 38(1) 1:1-1:25, 2011.



  
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
