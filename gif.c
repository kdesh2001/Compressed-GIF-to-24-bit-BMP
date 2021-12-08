#include<stdio.h>
#include "gif.h"

//Function to read header data of gif
struct header getheader(FILE * fp){
    struct header z;
    fread(&z,sizeof(struct header),1,fp);
    return z;
}
//Function to read logical screen descriptor
struct lsd getlsd(FILE *fp){
    struct lsd p;
    fread(&p,sizeof(struct lsd),1,fp);
    return p;
}
//Function to read and store global or local color table
struct gct gct(FILE *gif)
{
    struct gct gct;
    fread(&gct,sizeof(struct gct),1,gif);
    return gct;
}
//Function to read image descriptor
struct imgdes getimgdes(FILE *fp){
    struct imgdes im;
    fread(&im,sizeof(struct imgdes),1,fp);
    return im;
}
//Function to rotate the pixel data
void rotate(int array[1000][1000],int r,int c,int rot[1000][1000])
{
	int i,j,k;
	k=r;
	for (i=0;i<c;i++)
	{
		for(j=0;j<r;j++){
			rot[i][j]=*(*(array+(k-1-j))+i);
		}
	}
}