#include<stdio.h>
#pragma pack(1)
struct header
{
	char sgn[3];
	char ver[3];
};

struct lsd
{
	unsigned short int x;
	unsigned short int y;
	unsigned char pkd;
	unsigned char cindx;
	unsigned char asp;
};

struct gct
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

struct imgdes
{
	unsigned short l;
	unsigned short t;
	unsigned short w;
	unsigned short h;
	unsigned char pkd;
};

struct imgdata
{
	int code; int clrindx[12];
};

struct header getheader(FILE *fp);
struct lsd getlsd(FILE *fp);
struct gct gct(FILE *);
struct imgdes getimgdes(FILE *fp);
void rotate(int array[1000][1000],int r,int c,int rot[1000][1000]);