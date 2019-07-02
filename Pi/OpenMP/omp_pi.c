
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include<time.h>

int main(int argc, char* argv[])
{
  int iterations = 100000;         //number of iterations per FOR loop
  double x, y, z;                  //x,y value for the random coordinate. z is used to check if x^2+y^2<=1            
  int count=0;                     //count holds all the number of how many good coordinates
  double pi;                       //holds approx value of pi
  int numthreads = 16;
  int i;

  #pragma omp parallel firstprivate(x, y, z, i) reduction(+:count) num_threads(numthreads)
  {
    srand48((int)time(NULL) ^ omp_get_thread_num());  //Give random() a seed value
    for (i = 0; i<iterations; ++i)         
    {
      x = (double)drand48();
      y = (double)drand48();
      z = ((x * x) + (y * y));
      
      if (z <= 1)
        ++count;
    }
  } 

  pi = ((double)count / (double)(iterations * numthreads)) * 4.0;
  printf("Estimated Pi: %f\n", pi);
  
  return 0;
}