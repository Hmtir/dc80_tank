
#include "video.h"

#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <mem.h>
#include <assert.h>

void _VIDEO_INIT_DEVICE()
{
 _AX=0x0013;
 __int__(0x10);
}

void _VIDEO_DEINIT_DEVICE()
{
 _AX=0x0003;
 __int__(0x10);
}

void _VIDEO_CLEAR_SCREEN()
{
 for(unsigned i=0;i<=320U*200;i++)
  pokeb(0xa000,i,0);
}


void _VIDEO_SCREEN2MEM(int x1,int y1,int x2,int y2,char *mem)
{
 int dx=x2-x1,dy=y2-y1;
 assert(mem!=0);

 mem[0]=dx;
 mem[1]=dy;
 int p=2;
 for(int x=0;x<dx;x++)
  for(int y=0;y<dy;y++)
   mem[p++]=peekb(0xa000,(x+x1)+(y+y1)*320);
}

void _VIDEO_MEM2SCREEN(int x1,int y1,char *mem)
{
 int dx,dy;
 assert(mem!=0);

 outport(0x3ce,0x0003);
 dx=mem[0];
 dy=mem[1];
 int p=2;
 for(int x=0;x<dx;x++)
  for(int y=0;y<dy;y++)
   if ((x+x1<320) && (y+y1<200) &&
       (x+x1>=0)  && (y+y1>=0) )
    pokeb(0xa000,(x+x1)+(y+y1)*320,mem[p++]);
}

void _VIDEO_MEM2FILE(const char *mem,char *fname)
{
FILE *out=fopen(fname,"wt");
 int p=2,lp=0;
 fprintf(out,"char SHP_TMP[]={ %d,%d,\n",mem[0],mem[1]);
 for(int y=0;y<mem[1];y++)
  for(int x=0;x<mem[0];x++)
  {
   fprintf(out,"0x%02x,",mem[p++]);
   if (lp++>20)
   {
    fprintf(out,"\n");
    lp=0;
   }
  }
 fprintf(out,"\n0};\n");
 fclose(out);
}

void _VIDEO_PAL2FILE(char pal[],char *fname)
{
FILE *out=fopen(fname,"wt");
 int p=0,lp=0;
 fprintf(out,"char PAL_TMP[]={ \n");
 for(int i=0;i<=256*3;i++)
 {
  fprintf(out,"0x%02x,",pal[p++]);
  if (lp++>10)
  {
   fprintf(out,"\n");
   lp=0;
  }
 }
 fprintf(out,"\n0};\n");
 fclose(out);
 _VIDEO_SET_PAL(pal);

}

void _VIDEO_SET_PAL(char pal[])
{
 outportb(0x3c8,0);
 for(int i=0;i<=256*3;i++)
  outportb(0x3c9,pal[i]);
}

void _VIDEO_FADE_IN(int x,int y,char *pic,char pal[])
{
char FD[256*3];
 memset(FD,0,sizeof(FD));
 _VIDEO_SET_PAL(FD);
 _VIDEO_MEM2SCREEN(x,y,pic);

 for(int i=0;i<=63;i++)
 {
  for(int j=0;j<256*3;j++)
    if (FD[j]<pal[j])
     FD[j]++;
  _VIDEO_SET_PAL(FD);
  delay(10);
 }
}

void _VIDEO_FADE_OUT(char pal[])
{
char FD[256*3];
 memcpy(FD,pal,sizeof(FD));
 _VIDEO_SET_PAL(FD);

 for(int i=0;i<=63;i++)
 {
  for(int j=0;j<256*3;j++)
    if (FD[j]>0)
     FD[j]--;
  _VIDEO_SET_PAL(FD);
  delay(20);
 }
}

struct BMP_HEADER
{
char magic[2];
long FileLenght;
long Reserved;
long DataOffset;
long HeadLenght;
long BitMapX, BitMapY;
unsigned FarbEbenen,BitsProPixel;
long Compressing,
     PictureSize,
     BiXPelsPM,
     BiYPelsPM,
     BenColors,
     WiColors;
};

struct BMP_PALETTE
{
 unsigned char b,g,r;
 unsigned char reserved;
};

void _VIDEO_LOAD_BITMAP(const char*fname)
{
BMP_HEADER header;
BMP_PALETTE pal[256];
char mypal[256*3];

FILE *in=fopen(fname,"rb");
 fread(&header,sizeof(BMP_HEADER),1,in);
 fread(pal,4*256,1,in);

 int p=0;
 outportb(0x3c8,0);
 for(int i=0;i<=256;i++)
 {
  outportb(0x3c9,mypal[p++]=pal[i].r>>2);
  outportb(0x3c9,mypal[p++]=pal[i].g>>2);
  outportb(0x3c9,mypal[p++]=pal[i].b>>2);
 }

 int size=header.BitMapX*header.BitMapY;

 fseek(in,header.DataOffset,SEEK_SET);
 for(int y=0;y<=header.BitMapY;y++)
  for(int x=0;x<=header.BitMapX;x++)
  {
   unsigned char i;
   fread(&i,1,1,in);
   pokeb(0xa000,(x)+(header.BitMapY-y)*320,i);
  }
 fclose(in);
 char *data=new char[size];
 assert(data!=0);
 _VIDEO_SCREEN2MEM(0,1,header.BitMapX,header.BitMapY,data);
 getch();
 _VIDEO_CLEAR_SCREEN();
 _VIDEO_MEM2SCREEN(150,0,data);
 getch();
 _VIDEO_SET_PAL(mypal);
 _VIDEO_MEM2FILE(data,"rmenu.rc");
 _VIDEO_PAL2FILE(mypal,"rmenu.pal");
}