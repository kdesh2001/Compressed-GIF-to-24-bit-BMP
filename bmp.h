#pragma pack(1)
/* Bitmap File Header */
struct bmpfheader{
    char bfType[2];    /*2 bytes*/
    unsigned int bfSize;       /* 4 bytes */
    unsigned short bfReserved1;  /* 2 bytes */
    unsigned short bfReserved2;  /*2 bytes*/ 
    unsigned int bfOffBits;    /* 4 bytes */
};

/*Bitmap image header*/
struct bmpimgheader{
    int biSize;          /* 4 bytes */
    int biWidth;         /* 4 bytes */
    int biHeight;        /* 4 bytes */
    unsigned short biPlanes; /* 2 bytes */
    unsigned short biBitCount;/* 2 bytes */
    int biCompression; /* 4 bytes */
    unsigned int biSizeImage;     /* 4 bytes */
    int biXPixPerMeter;  /* 4 bytes */
    int biYPixPerMeter;  /* 4 bytes */
    int biClrUsed;       /* 4 bytes */
    int biClrImportant;  /* 4 bytes */
};

struct bmpfheader fheader(int ps);
struct bmpimgheader imgheader(int w, int h);
void pixeldata(char *pcd, char *fpd, int w, int h);
