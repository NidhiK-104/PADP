#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
	int n,i,j,k;
	for(int n=500; n<=2000; n+=500)
	{
		printf("\nSize: %d\n", n);
		int *arr1[n],*arr2[n];
		
		for(i=0;i<n;i++)
			arr1[i] = (int *)malloc(n*sizeof(int));
		
		for(i=0;i<n;i++)
			arr2[i] = (int *)malloc(n*sizeof(int));
			
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
				arr1[i][j] = rand()%10;
				
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
				arr2[i][j] = rand()%10;
		
		int *arr3[n];
		for(i=0;i<n;i++)
			arr3[i] = (int *)malloc(n*sizeof(int));
		
		int l;
		for(l=1;l<=8;l=l<<1) {
			double x = omp_get_wtime();
			omp_set_num_threads(l);
			#pragma omp parallel for private(j,k) 
			for(i=0;i<n;i++)
				for(j=0;j<n;j++)
				{
					arr3[i][j] = 0;
					for(k=0;k<n;k++)
						arr3[i][j] += arr1[i][k] * arr2[k][j];
				}
				
			double y = omp_get_wtime();
			if(l==1)
				printf("%d thread - %lf seconds\n", l, y-x);
			else
				printf("%d threads - %lf seconds\n", l, y-x);

		}
	}
	return 0;
}
