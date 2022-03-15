HYPAMAS: HYbrid PArallel MAtrix Solver for linear systems
=======
The package HYPAMAS is a thread-safe, high-performance, robust software for solving large sparse unsymmetric linear systems of equations A*X=b using either the direct method or the iterative method on shared memory machines. HYPAMAS is implemented in pure C using POSIX threads for parallel executions, and hand-code BLAS for effective numerical calculation. So you use HYPAMAS easily without linking other software packages.

In the direct method, HYPAMAS contains three numerical kernels to update LU factorization:
>1) sparse left-looking LU factorization based on sparse BLAS-1.  
>2) sparse left-looking LU factorization based on sparse BLAS-1 and standard dense BLAS-2.  
>3) sparse left-right looking LU factorization based on sparse BLAS-1, standard dense BLAS-2, and BLAS-3.  
In the direct method, HYPAMAS can use sequential/parallel forward elimination and backward substitution. To be suitable for Newton-Raphson iteration, HYPAMAS supports a re-factorization to perform A=LU without numerical pivoting permutation.

In the iterative method, HYPAMAS uses incomplete LU(ILU) factorization as the right-preconditioner for GMRES. It also supports versatile ILU algorithms:
>1) sparse left-looking ILU factorization based on threshold dropping(ILUT).
>2) sparse left-looking ILU factorization based on threshold dropping with partial pivoting(ILUTP).  
  
- 👋 Hi, I’m @Hypamas
- 👀 I’m interested in high performance computation, especially in matrix solver.
- 🌱 I’m currently learning direct & iterative matrix solver.
- 💞️ I’m looking to collaborate on a nice team.
- 📫 You can contact me by [email](mailto:hypamas@outlook.com).

<!---
Hypamas/Hypamas is a ✨ special ✨ repository because its `README.md` (this file) appears on your GitHub profile.
You can click the Preview link to take a look at your changes.
--->
