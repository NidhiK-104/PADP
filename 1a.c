#include<omp.h>
#include<stdio.h>
#include<stdlib.h>
#define SEED 35791246

void main()
{
	int t = 0, n;
	for(t=1; t<=8; t=t*2){
		for(n=500; n<=2000; n+=500){
			int i, count=0;
			double z,pi,x,y;
			srand(SEED);
			double t1 = omp_get_wtime();
			omp_set_num_threads(t);
			#pragma omp parallel for 
				for(int i = 0; i < n; i++)
				{
					x = (double)rand()/RAND_MAX;
					y = (double)rand()/RAND_MAX;
					z = x*x + y*y;
					if(z<=1)
						count++;
				}
				pi = (double)count/n*4;
				double t2 = omp_get_wtime();
				printf("%d Trials, %d Threads, Pi = %g, Time taken = %lf\n",n,t,pi, t2-t1);
			}
			printf("\n");
		}
}
