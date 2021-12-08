#include<stdio.h>
#include "bmp.h"
//Making the bmp file header
struct bmpfheader fheader(int ps){
    struct bmpfheader fh; 
    fh.bfType[0]='B'; fh.bfType[1]='M';
    fh.bfSize=54+ps; fh.bfReserved1=0; fh.bfReserved2=0;
    fh.bfOffBits=54;
    return fh;
}
//Making bmp image header
struct bmpimgheader imgheader(int w, int h){
    struct bmpimgheader ih;
    ih.biSize=40;
    ih.biWidth=h; ih.biHeight=-w; //-ve indicates top to bottom
    ih.biPlanes=1; ih.biBitCount=24; ih.biCompression=0;
    ih.biSizeImage=0; ih.biXPixPerMeter=0; ih.biYPixPerMeter=0;
    ih.biClrUsed=0; ih.biClrImportant=0;
    return ih;
}
//Null padding the pixel data
void pixeldata(char *pcd, char *fpd, int w, int h){
    int loci=0, locf=0, reqb=4-((3*w)%4);
    if(w%4==0)
        reqb = 0;
    
    for(int mn=0;mn<h;mn++){
        for(int uv=0;uv<3*w;uv++){
            fpd[locf++]=pcd[loci++];
        }
        for(int uv=0;uv<reqb;uv++){
            fpd[locf++]='\0';
        }
    }
    
}