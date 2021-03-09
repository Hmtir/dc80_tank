
#include "video.h"
#include "resource.h"

#include <conio.h>
#include <dos.h>
#include <stdio.h>
#include <assert.h>

struct tagButtons {
 int x,y;
 char *Normal_shape;
 char *HiLight_shape;
} btns[3]={ {80,100,SHP_PLAY_N,SHP_PLAY_A},
	   {90,120,SHP_CREDIT_N,SHP_CREDIT_A},
	   {100,140,SHP_EXIT_N,SHP_EXIT_A} };

#define MAX_BTN  2
#define MIN_BTN  0

void SplashScreen()
{
unsigned char w,h;
FILE *in;

 _VIDEO_CLEAR_SCREEN();
 in=fopen("SPLASH.PAL","rb");
 assert(in!=0);
 char *mempal=new char [256*3];
 assert(mempal!=0);
 fread(mempal,256*3,1,in);
 fclose(in);

 in=fopen("SPLASH.DAT","rb");
 assert(in!=0);

 fread(&w,1,1,in);
 fread(&h,1,1,in);
 char *mempic=new char[2+w*h];
 assert(mempic!=0);
 rewind(in);
 fread(mempic,w*h+2,1,in);
 fclose(in);

 _VIDEO_SET_PAL(mempal);
 _VIDEO_MEM2SCREEN(320/2-w/2,20,mempic);
 delete mempic;
 delete mempal;
getch();
 _VIDEO_CLEAR_SCREEN();
}

int MainMenu()
{
unsigned char w,h;
FILE *in;

 _VIDEO_CLEAR_SCREEN();
 in=fopen("RMENU.PAL","rb");
 assert(in!=0);
 char *mempal=new char [256*3];
 assert(mempal!=0);
 fread(mempal,256*3,1,in);
 fclose(in);

 in=fopen("RMENU.DAT","rb");
 assert(in!=0);

 fread(&w,1,1,in);
 fread(&h,1,1,in);
 char *mempic=new char[2+w*h];
 assert(mempic!=0);
 rewind(in);
 fread(mempic,w*h+2,1,in);
 fclose(in);

 _VIDEO_SET_PAL(mempal);
 for(int i=320;i>=320-147;i--)
 {
  _VIDEO_MEM2SCREEN(i,0,mempic);
//  delay(10);
 }

 for(i=0;i<=80;i++)
 {
  _VIDEO_MEM2SCREEN(i,100,SHP_PLAY_N);
  _VIDEO_MEM2SCREEN(i+10,120,SHP_CREDIT_N);
  _VIDEO_MEM2SCREEN(i+20,140,SHP_EXIT_N);
  delay(5);
 }

 delay(500);
 _VIDEO_MEM2SCREEN(80,100,SHP_PLAY_A);

 int cur=0; // Current selected button
 int key;
 do
 {
  key=getch();
  if(!key) key=256+getch();

  if (key==336) //Down Arrow
  {
   _VIDEO_MEM2SCREEN(btns[cur].x,btns[cur].y,btns[cur].Normal_shape);
   if (++cur>MAX_BTN)
    cur=MIN_BTN;
   _VIDEO_MEM2SCREEN(btns[cur].x,btns[cur].y,btns[cur].HiLight_shape);
  }

  if (key==328) //Up Arrow
  {
   _VIDEO_MEM2SCREEN(btns[cur].x,btns[cur].y,btns[cur].Normal_shape);
   if (--cur<MIN_BTN)
    cur=MAX_BTN;
   _VIDEO_MEM2SCREEN(btns[cur].x,btns[cur].y,btns[cur].HiLight_shape);
  }

 }while(key!=27 && key!=13 && key!=32);
 _VIDEO_CLEAR_SCREEN();
 delete mempic;
 delete mempal;
 if (key==27)
  return MAX_BTN;

 return cur;
}

void Credit()
{
unsigned char w,h;
FILE *in;

 _VIDEO_CLEAR_SCREEN();
 in=fopen("CREDIT.PAL","rb");
 assert(in!=0);
 char *mempal=new char [256*3];
 assert(mempal!=0);
 fread(mempal,256*3,1,in);
 fclose(in);

 in=fopen("CREDIT.DAT","rb");
 assert(in!=0);

 fread(&w,1,1,in);
 fread(&h,1,1,in);
 char *mempic=new char[2+w*h];
 assert(mempic!=0);
 rewind(in);
 fread(mempic,w*h+2,1,in);
 fclose(in);

 _VIDEO_FADE_IN(320/2-w/2,200-h-1,mempic,mempal);
 if (!getch()) getch();
 _VIDEO_FADE_OUT(mempal);

 delete mempic;
 delete mempal;
 _VIDEO_CLEAR_SCREEN();
}
