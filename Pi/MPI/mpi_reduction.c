#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
	int pid, numberOfNodes, i, sum, error, count = 0, iterations = 100000000;								
	double x, y, z, pi, begin, end;																

	/* 
    	1. Get process ID
    	2. Get processes number
    	3. Synchonize all processes
    	4. Get begin time
    */
	error = MPI_Init(&argc, &argv);						
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);		
	MPI_Comm_size(MPI_COMM_WORLD, &numberOfNodes);
	begin = MPI_Wtime();

	srand48(time(NULL) + pid);

	for(i = 0; i < iterations; i++) {
		x = (double)drand48();					
		y = (double)drand48();					
		z = ((x*x)+(y*y));						
		
		if (z <= 1)
		{
			count++;							
		}	
	}

	/* Now we can reduce the values to master */

	MPI_Reduce(&count, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	end = MPI_Wtime();

	long total_iterations = iterations * numberOfNodes;

	if (pid == 0)								//if root process
	{      
		pi = ((double)sum / (double)total_iterations) * 4.0;	
		printf("Processors = %2d;    Iterations = %ld    Time = %f s;    PI = %0.10f\n", numberOfNodes, total_iterations, end-begin, pi);			
	}
	
	error = MPI_Finalize();								//Close the MPI instance
	return 0;
}