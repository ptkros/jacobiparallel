The project aims to design and implement a feasible parallel implementation of the Jacobi iterative method to solve a system of linear equations. The proposed solution has been implemented using the parallel programming framework [FastFlow](https://github.com/fastflow/fastflow) and targeting the [Intel Xeon PHI r720-phi](https://www.intel.com/content/dam/www/public/us/en/documents/pdf/true-scale-xeon-phi-coprocessor-overview.pdf) coprocessor. Detailed information can be found [here](https://drive.google.com/file/d/1kl55s-oYZdovRLXkU2PJFGvlY8-GyRaQ/view).

# How to build

In order to compile and run the application a copy of the files on a machine with Intel Xeon Phi coprocessor is required. There are two ways on how to compile the application:
  * *make* to get executable files for the host machine;
  * make phi: to get executable files for the Xeon Phi coprocessor.
For all compilation options the executable files obtained are:
• jacobip_ORIG: it is the original version;
• jacobip_VRED: it is the vectorization version.
In order to run the program a set of parameters are required:
• nworkers: the number of workers;
• chunk: the iteration chunks;
• lsyspathname|lsysdim: the (path)name of the input file containing the
linear system or the desired dimension of the linear system for a random
generation;
• version:
o p: to execute the parallel version;
o l: to execute the sequential version;
• errtolerance: it is the desired error tolerance of the vector solutions.
Optional.

