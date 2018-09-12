The project aims to design and implement a feasible parallel implementation of the Jacobi iterative method to solve a system of linear equations. The proposed solution has been implemented using the parallel programming framework [FastFlow](https://github.com/fastflow/fastflow) and targeting the [Intel Xeon PHI r720-phi](https://www.intel.com/content/dam/www/public/us/en/documents/pdf/true-scale-xeon-phi-coprocessor-overview.pdf) coprocessor. Detailed information can be found [here](https://drive.google.com/file/d/1kl55s-oYZdovRLXkU2PJFGvlY8-GyRaQ/view).

# How to build

In order to compile and run the application a copy of the files on a machine with Intel Xeon Phi coprocessor is required. There are two ways on how to compile the application:
 * *make*: to get executable files for the host machine;
 * *make phi*: to get executable files for the Xeon Phi coprocessor.
For all compilation options the executable files obtained are:
 * *jacobip_ORIG*: it is the original version;
 * *jacobip_VRED*: it is the vectorization version.
In order to run the program a set of parameters are required:
 * *nworkers*: the number of workers;
 * *chunk*: the iteration chunks;
 * *lsyspathname|lsysdim*: the (path)name of the input file containing the linear system or the desired dimension of the    linear system for a random generation;
 * version:
   * *p*: to execute the parallel version;
   * *l*: to execute the sequential version;
 * errtolerance: it is the desired error tolerance of the vector solutions. Optional.
If version *l* is chosen, the first two parameters are not considered but necessary.

# How to use

Use the lsys500.txt as a test input file. Below, some examples of usage:

*./jacobip_ORIG 5 0 lsys500.txt p*
*./jacobip_VRED 10 0 lsys500.txt p 0.0001*
*./jacobip_ORIG 5 50 lsys500.txt p*
*./jacobip_VRED 50 5 lsys500.txt p 0.0001*
*./jacobip_ORIG 100 0 1500 p*
*./jacobip_VRED 100 200 3000 p*
*./jacobip_ORIG 1 0 lsys500.txt l*
*./jacobip_VRED 1 0 750 l 0.0001*


