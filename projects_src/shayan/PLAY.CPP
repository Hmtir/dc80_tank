
#include "classes.h"

#include "resource.h"
#include "video.h"

#include <conio.h>
#include <dos.h>
#include <stdlib.h>

void GoPlay()
{
 _VIDEO_SET_PAL(PAL_GAME);
// randomize();
 srand(0);

 TBackground gnd;
 gnd.BackBuffering(0);

 TTank *t0=new TEnemyTank(120,84,120+24,84+23);
 TTank *t1=new TEnemyTank(120,24,120+24,24+23);
 TTank *t2=new TEnemyTank(120,120,120+24,120+23);
 TTank *t3=new TMyTank(192,110,192+24,110+23);
 gnd.own(t0);
 gnd.own(t1);
 gnd.own(t2);
 gnd.own(t3);


 gnd.show();
 t0->show();
 t1->show();
 t2->show();
 t3->show();

 t0->changeDir(dirUp);
 t1->changeDir(dirRight);
 t2->changeDir(dirUp);
 t3->changeDir(dirNone);

 int key=0;
 do
 {
  if (kbhit())
  {
   key=getch();
   if (!key) key=256+getch();
   t3->messageHandler(msgKEYB,&key);
  }

  t0->update();
  t1->update();
  t2->update();
  t3->update();
  delay(10);
 } while (key!=27);
/*
*/
 _VIDEO_CLEAR_SCREEN();
 delete t0;
 delete t1;
 delete t2;
 delete t3;
}

