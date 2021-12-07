#include <stdio.h>
#include <gd.h>
#include <error.h>
#include <omp.h>
int main(int argc, char *argv[])
{
	int nt = 8, chnk;
	//printf("Enter chunk size:\n");
	//scanf("%d",&chnk);
	int tid,h,w;
	h=w=0;
	char *iname =NULL;
	char *oname = NULL;
	gdImagePtr img;
	FILE *fp={0};
	if(argc!=3)
		error(1,0,"format : object_file input.png output.png");
	else
	{
		iname = argv[1];
		oname = argv[2];
	}
	for(chnk=10; chnk<=100; chnk+=20){	
	if((fp=fopen(iname,"r"))==NULL)
		error(1,0,"error : fopen : %s",iname);
	else
	{
		img = gdImageCreateFromPng(fp);
		w=gdImageSX(img);
		h=gdImageSY(img);
	}
	double t=omp_get_wtime();
	omp_set_num_threads(nt);
	int x,y;
	//#pragma omp parallel for collapse(2) private(x,y) 	//here change the type of scheduling - static, dynamic, guided
	//#pragma omp parallel for collapse(2) private(x,y) schedule(guided,chnk)
	//#pragma omp parallel for collapse(2) private(x,y) schedule(static,chnk)
	#pragma omp parallel for collapse(2) private(x,y) schedule(dynamic,chnk)
	for(x=0;x<w;x++)
		for(y=0;y<h;y++)
		{
			int color=gdImageGetPixel(img,x,y);
			int red=gdImageRed(img,color);
			int green=gdImageGreen(img,color);
			int blue=gdImageBlue(img,color);
			int tmp=(red+green+blue)/3;
			red=green=blue=tmp;
			color=gdImageColorAllocate(img,red,green,blue);
			gdImageSetPixel(img,x,y,color);
		}	
	t=omp_get_wtime()-t;
	printf("\nTime taken : %lf Chunksize : %d\n",t,chnk);
	if((fp=fopen(oname,"w"))==NULL)
		error(1,0,"error : fopen : %s",oname);
	else
	{
		gdImagePng(img,fp);
		fclose(fp);
	}	
	gdImageDestroy(img);
	}
	return 0;
}
