# Monte Carlo Simulation for Pi
Contains the following:
  1. A serial approach to the estimation of Pi using the Monte Carlo Method (C++)
  2. A Multithreaded estimation of Pi based on the Monte Carlo Method (C++)
  3. Using matplotlib, plots the estimated value of Pi using Monte Carlo Method (Python)
  4. A parallel computing version that estimates Pi using the Monte Carlo Method in OpenMP (C)
  5. A parallel computing version that estimates Pi using the Monte Carlo Method in MPI (C)
  
### To use MPI

The best performance is achieved when the number of nodes is equal to number of cores. E.g.:
'''
> $HOME/opt/usr/local/bin/mpicc -o pi ./mpi_pi.c
> $HOME/opt/usr/local/bin/mpirun -np 4 ./pi 
'''

You can change the number '4' to equal the number of cores you have.

