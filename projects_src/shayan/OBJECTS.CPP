
#include "classes.h"
#include "video.h"

#include "resource.h"

#include <dos.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <conio.h>

/*************************************************************************/
/*  TFramedObj
*/

TFramedObj::TFramedObj(int x1,int y1,int x2,int y2) :
	 x1(x1),y1(y1),x2(x2),y2(y2),visible(0),
	 BackBuff(0),bbf(1)
{
 owner=0;
 BackBuff=new char[(x2-x1)*(y2-y1)];
}

TFramedObj::~TFramedObj()
{
 destroy();
 if (!BackBuff)
  delete BackBuff;
 if (owner!=0)
  owner->disown(this);
}

void TFramedObj::show()
{
 if (bbf)
  _VIDEO_SCREEN2MEM(x1,y1,x2,y2,BackBuff);

 draw();
 visible=1;
}

void TFramedObj::draw()
{
 if (visible)
  _VIDEO_MEM2SCREEN(x1,y1,_PIC_dummy);
}

void TFramedObj::hide()
{
 if (bbf)
  _VIDEO_MEM2SCREEN(x1,y1,BackBuff);

 visible=0;
}

void TFramedObj::BackBuffering(int on)
{
 bbf=on;
 if (bbf==0)
  if (BackBuff!=0)
   delete BackBuff;
 if (bbf==1)
  BackBuff=new char[getWidth()*getHeight()];
}

void TFramedObj::destroy()
{
 if (visible)
  hide();
}

int TFramedObj::intersect(TFramedObj&)
{
return 0;
}

int TFramedObj::willIntersect(TFramedObj& obj,int x,int y)
{
int willx1=x, willx2=x+(x2-x1)-1;
int willy1=y, willy2=y+(y2-y1)-1;

 if (!obj.visible || !this->visible)
  return 0;

 if ( (obj.y1>willy2) ||
      (obj.y2<willy1) ||
      (obj.x1>willx2) ||
      (obj.x2<willx1) )
   return 0;

return 1;
}

int TFramedObj::getWidth()
{
 return (x2-x1);
}

int TFramedObj::getHeight()
{
 return (y2-y1);
}


/*************************************************************************/
/*  TMovable
*/

TMovable::TMovable(int x1,int y1,int x2,int y2) :
	 TFramedObj(x1,y1,x2,y2),direction(dirNone),drawdirection(dirUp)
{
}

void TMovable::changeDir(DRCT dir)
{
 direction=dir;
 if (dir!=dirNone)
  drawdirection=dir;
}

void TMovable::moveDelta(int DeltaTop,int DeltaLeft)
{
int oldvis=visible; // another variable is required,
		    // 'visible' will change during hide()
 if (oldvis)
  hide();

 x1+=DeltaLeft;
 y1+=DeltaTop;
 x2+=DeltaLeft;
 y2+=DeltaTop;

 if (oldvis)
  show();
}

void TMovable::moveTo(int x,int y)
{
 moveDelta(y-y1,x-x1);
}

void TMovable::getTarget(DRCT dir,int& x,int& y)
{
 int dx=1;
 int dy=1;
 switch(dir)
 {
  case dirRight:
   x=x1+dx; y=y1;
   break;

  case dirLeft:
   x=x1-dx; y=y1;
   break;

  case dirDown:
   x=x1; y=y1+dy;
   break;

  case dirUp:
   x=x1; y=y1-dy;
   break;
 }
}

/*************************************************************************/
/*  TSyncMovable
*/
TSyncMovable::TSyncMovable(int x1,int y1,int x2,int y2) :
     TMovable(x1,y1,x2,y2)
{
}

void TSyncMovable::update()
{
int trgx,trgy;
 if (direction!=dirNone)
 {
  getTarget(direction,trgx,trgy);
  if (owner!=0)
   if (owner->checkCollision(id,trgx,trgy))
    moveTo(trgx,trgy);
 }
}

/*************************************************************************/
/*  TTank
*/

TTank::TTank(int x1,int y1,int x2,int y2) :
	 TSyncMovable(x1,y1,x2,y2)
{
}

/*************************************************************************/
/*  TBulet
*/

TBulet::TBulet(int x1,int y1,int x2,int y2) :
	 TSyncMovable(x1,y1,x2,y2)
{
}

TBulet::~TBulet()
{
 if (owner!=0)
  owner->disown(this);
}


void TBulet::draw()
{
 switch(drawdirection)
 {
  case dirNone:
  case dirDown:
   _VIDEO_MEM2SCREEN(x1,y1,SHP_BULET_D);
   break;
  case dirUp:
   _VIDEO_MEM2SCREEN(x1,y1,SHP_BULET_U);
   break;
  case dirLeft:
   _VIDEO_MEM2SCREEN(x1,y1,SHP_BULET_L);
   break;
  case dirRight:
   _VIDEO_MEM2SCREEN(x1,y1,SHP_BULET_R);
   break;
 }
}

int TBulet::messageHandler(MSG,void *)
{
 return 0;
}

/*************************************************************************/
/*  TBackground
*/
char TBackground::Map[8][13]={ {'K',' ','K',' ',' ','K','K','K','K','K','K','K','K'},
			       {'K','G','K',' ',' ',' ','K',' ',' ',' ','K','G','K'},
			       {' ',' ','K',' ',' ',' ','K',' ',' ',' ','K','G','K'},
			       {' ',' ','K',' ',' ',' ','K',' ',' ',' ','K',' ','K'},
			       {'K',' ','K',' ',' ',' ',' ',' ',' ','K','K',' ','K'},
			       {' ',' ',' ',' ','K',' ',' ',' ',' ',' ',' ',' ','K'},
			       {'K',' ',' ','K','K','K','K',' ',' ',' ',' ',' ',' '},
			       {'K','K',' ','K','K','K',' ',' ',' ',' ',' ',' ',' '} };

TBackground::TBackground() : TFramedObj(0,0,320,200)
{
 for(int i=0;i<MAX_OBJECTS;++i)
  Childs[i]=0;
}

void TBackground::draw()
{
 for (int y=0;y<=7;y++)
  for (int x=0;x<=12;x++)
   if (Map[y][x]=='K')
    _VIDEO_MEM2SCREEN(x*24,y*24, SHP_FBLOCK);
   else
   if (Map[y][x]=='G')
    _VIDEO_MEM2SCREEN(x*24,y*24, SHP_FLAG);
}

int TBackground::checkCollision(int id,int x,int y)
{
 assert(Childs[id]!=0);
 int w=Childs[id]->getWidth();
 int h=Childs[id]->getHeight();

 if ( x<0 || x>319-w ||
      y<0 || y>199-h )
 {
  Childs[id]->messageHandler(msgCOLLISIONTO,this); // collision to walls or
						   // screen corners assumed
						   // as collision to TBackground
  return 0;
 }

 if (Map[y/24][x/24]=='K' ||
     Map[(y+h-1)/24][(x+w-1)/24]=='K' ||
     Map[(y+h-1)/24][x/24]=='K' ||
     Map[y/24][(x+w-1)/24]=='K')
 {
  Childs[id]->messageHandler(msgCOLLISIONTO,this);
  return 0;
 }

 int i;
/*
 gotoxy(1,10);
 for(i=0;i<MAX_OBJECTS;++i)
  if (Childs[i]!=0)
   printf("%d:(%d,%d)-(%d,%d)  \n",i,Childs[i]->x1,Childs[i]->y1,
			     Childs[i]->x2,Childs[i]->y2);

*/
 for(i=0;i<MAX_OBJECTS;++i)
  if (id!=i)
   if (Childs[i]!=0)
    if (Childs[id]->willIntersect(*Childs[i],x,y))
    {
     Childs[id]->messageHandler(msgCOLLISIONTO,Childs[i]);
     Childs[i]->messageHandler(msgCOLLISIONFROM,Childs[id]);
     return 0;
    }

 return 1;
}

int TBackground::getfreeslot()
{
 for(int i=0;i<MAX_OBJECTS;++i)
  if (Childs[i]==0)
   return i;
 abort();
 return (-1);
}

void TBackground::own(TFramedObj* obj)
{
 assert(obj!=0);
 obj->owner=this;
 int id=getfreeslot();
 Childs[id]=obj;
 obj->id=id;
}

void TBackground::disown(TFramedObj* obj)
{
 Childs[obj->id]=0;
}

/*************************************************************************/
/*  TMyTank
*/
TMyTank::TMyTank(int x1,int y1,int x2,int y2) :
	 TTank(x1,y1,x2,y2)
{
}

int TMyTank::messageHandler(MSG msg,void *obj)
{
 if (msg==msgCOLLISIONTO)
  switch( ( (TObject *)obj )->getClassId()  )
  {
   case TENEMYTANK_CLASS_ID:
   case TMYTANK_CLASS_ID:
   case TBACKGROUND_CLASS_ID:
    changeDir(dirNone);
    break;

   case TBULET_CLASS_ID:
    break;
   }
 if (msg==msgKEYB)
  switch(*((int *)obj))
  {
   case 336:      // Down Arrow
    changeDir(dirDown);
    break;
   case 328:      // Up Arrow
    changeDir(dirUp);
    break;
   case 331:      // Left Arrow
    changeDir(dirLeft);
    break;
   case 333:     // Right Arrow
    changeDir(dirRight);
    break;

   case 32:      // Space (FIRE)
    TBulet *b=new TBulet(x1,y1,x1+10,y1+9);
    b->changeDir(direction);
    owner->own(b);
    break;
  }
return 1;
}

void TMyTank::draw()
{
 switch(drawdirection)
 {
  case dirNone:
  case dirDown:
   _VIDEO_MEM2SCREEN(x1,y1,SHP_MY_TANK_D);
   break;
  case dirUp:
   _VIDEO_MEM2SCREEN(x1,y1,SHP_MY_TANK_U);
   break;
  case dirLeft:
   _VIDEO_MEM2SCREEN(x1,y1,SHP_MY_TANK_L);
   break;
  case dirRight:
   _VIDEO_MEM2SCREEN(x1,y1,SHP_MY_TANK_R);
   break;
 }
}

/*************************************************************************/
/*  TEnemyTank
*/
TEnemyTank::TEnemyTank(int x1,int y1,int x2,int y2) :
	 TTank(x1,y1,x2,y2)
{
}

void TEnemyTank::draw()
{
 switch(drawdirection)
 {
  case dirNone:
  case dirDown:
   _VIDEO_MEM2SCREEN(x1,y1,SHP_TANK_D);
   break;
  case dirUp:
   _VIDEO_MEM2SCREEN(x1,y1,SHP_TANK_U);
   break;
  case dirLeft:
   _VIDEO_MEM2SCREEN(x1,y1,SHP_TANK_L);
   break;
  case dirRight:
   _VIDEO_MEM2SCREEN(x1,y1,SHP_TANK_R);
   break;
 }
}

int TEnemyTank::messageHandler(MSG msg,void *obj)
{
 if (msg==msgCOLLISIONTO)
  switch( ( (TObject *)obj )->getClassId()  )
  {
   case TBACKGROUND_CLASS_ID:
    DRCT newdir;
    do
    {
     newdir=(DRCT)(random(4)+1); // 1..4
    } while(newdir==direction);
    changeDir(newdir);
    break;

   case TENEMYTANK_CLASS_ID:
   case TMYTANK_CLASS_ID:
    if (direction==dirUp) changeDir(dirDown);
    else
    if (direction==dirDown) changeDir(dirUp);
    else
    if (direction==dirRight) changeDir(dirLeft);
    else
    if (direction==dirLeft) changeDir(dirRight);
    break;

   case TBULET_CLASS_ID:
    break;
  }
return 1;
}
