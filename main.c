#include<stdio.h>
#include<math.h>
#include "gif.h"
#include "bmp.h"
struct imgdata table[5000];     //LZW code dictionary
int pixel(unsigned short int,int);
char pd[40000];                     //Color indexes for each pixel
void seti(int);
int i=0,n1,nc;                  //i tracks last element in dictionary
int main(int argc, char *argv[]){
    char *fname = argv[1], t; FILE *fp; unsigned short int x; unsigned char min, bsize, code, rem;
    fp = fopen(fname,"rb");
    printf("Starting conversion.....\n");
    //Getting header
    struct header h;
    h = getheader(fp);
    
    //Logical screen descriptor
    struct lsd lsd;
    lsd = getlsd(fp);
    
    int p;
    //Creating global color table if there is one
    struct gct gctm[256];
    if(lsd.pkd & 0x80 == 0x80){
        p= 3*pow(2,(lsd.pkd & 7)+1); nc=p/3;
        for(int a=0;a<p/3;a++){
            gctm[a]=gct(fp);
        }
    }
    for(int a=0;a<5000;a++){
        for(int j=0;j<12;j++){
            table[a].clrindx[j]=-1;
        }
    }
    for(int a=0;a<(p/3)+2;a++){
        table[a].code=a;
        table[a].clrindx[0]=a;
        
    }
    seti(p/3);
    t=0;
    //Finding image separator(always 0x2c)
    do
    {
        fread(&t,1,1,fp);
    } while(t!=0x2C);

    //Getting other things from img descriptor
    struct imgdes d;
    d = getimgdes(fp);
    //Getting local color table if there is one
    if(d.pkd & 0x80 == 0x80){
        p= 3*pow(2,(d.pkd & 7)+1); nc=p/3;
        for(int a=0;a<p/3;a++){
            gctm[a]=gct(fp);
        }
    }

    //LZW min code size
    fread(&min,1,1,fp);
    
    //Block size
    fread(&bsize,1,1,fp);
    
    
    n1=min+1;
    int n = min+1, rb=8,count=0, first=1,bytecount=1;
    if(n>=8){
        fread(&code,1,1,fp); bytecount++;
        
        unsigned short cdw=code; int max= pow(2,n-8)-1;
        fread(&code,1,1,fp); bytecount++;
        
        cdw += ((code & max)<<8);
        rem=(code>>(n-8));
        rb = 8-(n-8);
        first=0;
    }

    //Algorithm to scrap required no. of bits(i.e. LZW code)
    while(1){
        if(rb<n){
            if(n<=rb+8){
                fread(&code,1,1,fp); bytecount++;

                int nn;
                int max=pow(2,n-rb)-1;
                unsigned short cdv=code & max;
                unsigned short cd1=(cdv<<rb) + rem;
                if(cd1==nc+1)
                    break;
                nn = pixel(cd1, n);
                rem = code>>(n-rb);
                rb = 8-n+rb;
                
                n=nn;
                
            }
            else{
                fread(&code,1,1,fp); bytecount++;
                
                if(bytecount>bsize)
                    break;
                
                int nn;
                unsigned short cds = code;
                unsigned short cd1=(cds<<rb) + rem;
                fread(&code,1,1,fp); bytecount++;
                if(bytecount>bsize)
                    break;
                int max=pow(2,n-rb-8)-1;
                unsigned short cdu = (code & max);
                unsigned short cdt=(cdu<<(rb+8))+cd1;
                nn = pixel(cdt, n);
                rem = code>>(n-rb-8);
                rb = 8-(n-rb-8);
                n = nn;
            }
        }
        else{
            if(first){
                fread(&rem,1,1,fp);
                
            }
            int max=pow(2,n)-1,nn;
            if(!first){
                unsigned short cd2 =rem & max;
                nn = pixel(cd2, n);
            }
            rem = rem>>n;
            rb -= n;
            if(!first){
                n = nn;
            }
            first=0;
        }
        
        
    }
    //Storing the colour data as a 2D array
    int pd2[1000][1000], fg=0;
    for (int qr=0;qr<d.h;qr++){
        for(int st=0;st<d.w;st++){
            pd2[qr][st] = pd[fg];
            fg++;
        }
    }
    
    //Rotate by 90 degrees to right
    int pdr[1000][1000];    //Rotated pixel data
    rotate(pd2,d.h,d.w,pdr);

    //Getting pixel data in terms of RGB values using color table
    char pcdi[120000]; int ab=0;
    for (int qr=0;qr<d.w;qr++){
        for(int st=0;st<d.h;st++){
            pcdi[ab++]=gctm[pdr[qr][st]].b;
            pcdi[ab++]=gctm[pdr[qr][st]].g;
            pcdi[ab++]=gctm[pdr[qr][st]].r;
        }
    }

    //Making a BMP file
    int ps=(d.w)*(3*(d.h) + (4-((3*(d.h))%4)));     //Pixel data size for bmp including null padding to make a Dword
    if((d.h)%4==0)
        ps -= 4;
    
    FILE* fpb; char bmpname[]="destination_image.bmp";    //Name of the output file
    
    struct bmpfheader bmpfh;
    bmpfh = fheader(ps);
    struct bmpimgheader bmpih;
    bmpih= imgheader(d.w, d.h);

    char pcdf[120000];
    pixeldata(pcdi, pcdf, d.h, d.w);

    fpb=fopen(bmpname,"wb");
    fwrite(&bmpfh,sizeof(struct bmpfheader),1,fpb);//Writing file header
    fwrite(&bmpih,sizeof(struct bmpimgheader),1,fpb);//Writing image header 
    for(int op=0;op<ps;op++){
        fputc(pcdf[op],fpb);        //Writing all the pixel data
    }
    fclose(fpb);

    fclose(fp);
    printf("Successful. Please check the folder.\n");
    return 0;
}


int e=0,first=1; unsigned short prev;//e tracks adding position in pixel data
void seti(int t){
    i=t+2;
}

//LZW decoding
int pixel(unsigned short int t, int n){
    if((t==nc || i==4095) && !first){
        for(int q=nc+2;q<5000;q++){
            for(int j=0;j<12;j++){
                table[q].clrindx[j]=-1;
            }
        }
        i=nc+2;
        first=1;
        return n1;
    }
    int h=0,ti;
    for(int u=0;u<i;u++){
        if(table[u].code==t){
            h=1; ti=u; break;
        }
    }
    if(h){//If code is there in the dictionary
        for(int j=0;table[ti].clrindx[j]!=-1 && j<12;j++){
            pd[e++]=table[ti].clrindx[j];//Add the color indexes to pixel array
        }
        if(!first){//First code has different methods
            int k=table[ti].clrindx[0];
            int j=0; table[i].code=i;
            for(j=0;table[prev].clrindx[j]!=-1 && j<12;j++){
                table[i].clrindx[j]=table[prev].clrindx[j];
            }
            table[i].clrindx[j]=k;  //Adding new code to dictionary by making it using previous code value
            if((pow(2,n)-1)==i)
                n++;            //If the code added matches to the max value that can be stored in n bits
            i++;                //we increment n
        }
    }
    else{//If code is not in dictionary
        int k=table[prev].clrindx[0];
        int j=0;
        table[i].code=i;
        for(j=0;table[prev].clrindx[j]!=-1 && j<12;j++){    //Add it to the dictionary and pixel data
            table[i].clrindx[j]=table[prev].clrindx[j];
            pd[e++]=table[prev].clrindx[j];
        }
        pd[e++]=k; table[i].clrindx[j]=k;
        if((pow(2,n)-1)==i)
            n++;
        i++;
    }
    first=0;
    prev=t;
    return n;
}