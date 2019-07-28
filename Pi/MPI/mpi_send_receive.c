#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#define SEED 326172

int main(int argc, char* argv[]) {
	long iterations = 100000000;			
	int pid, numberOfNodes, i, error, count=0;
	double x, y, z, pi, begin, end;														
	
	MPI_Status status;


	error = MPI_Init(&argc, &argv);						
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);				
	MPI_Comm_size(MPI_COMM_WORLD, &numberOfNodes);
	begin = MPI_Wtime();

	int counts[numberOfNodes];				// contains all processes circle point counts
	int temp;								// temp buffer to store incoming count messages on node 0

	srand(SEED + pid);							

	for(i = 0; i < iterations; i++) {
		x= ((double)rand()) / RAND_MAX;			
		y =((double)rand()) / RAND_MAX;			
		z = x*x + y*y;		

		if (z <= 1)
		{
			count++;				
		}
	
	}

	if(pid != 0) /* Everyone sends their contribution to node 0 */
	{
		MPI_Send(&count, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
	}

	else /* Node 0 needs to receive a message from everyone else */
	{
		/* Put root's count in place */
		counts[0] = count;
		for(i = 0; i < numberOfNodes-1; i++)
		{
			/* We don't know who will be done first, so we need to post an MPI_ANY_SOURCE receieve */
			MPI_Recv(&temp, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);
			/* Find out who this MPI_Recv() message came from */
			counts[status.MPI_SOURCE] = temp;
		}
	}

	end = MPI_Wtime();

	/* Ok, root has everyone's contributions; add them up and calculate Pi */
	if (pid == 0)	
	{      
		int sum = 0;
		for(i = 0; i < numberOfNodes; ++i)
		{
			sum += counts[i];
		}

		long total_iterations = numberOfNodes * iterations;
		pi = ((double)sum / (double)total_iterations) * 4.0;	
		printf("Processors = %2d;    Iterations = %ld    Time = %f s;    PI = %0.10f\n", numberOfNodes, total_iterations, end-begin, pi);
	}

	error = MPI_Finalize();
	return 0;
}