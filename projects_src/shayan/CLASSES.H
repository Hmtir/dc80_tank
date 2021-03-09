
#ifndef __CLASSES_INCLUDED
#define __CLASSES_INCLUDED

enum DRCT
{
 dirNone=0,
 dirLeft,
 dirRight,
 dirUp,
 dirDown
};

enum MSG
{
 msgGAMEOVER,
 msgNEXTLEVEL,

 msgKEYB,

 msgMOVECOMPLETE,
 msgCOLLISIONTO,
 msgCOLLISIONFROM
};

typedef unsigned long CLSID;

// option bits:

#define OPT_NONE		0
#define OPT_KEY_PROCESSOR	1
#define OPT_GAME_OVER_ON_DIE	1<<1
#define OPT_PAINT_WITH_MASK	1<<2

//////////////////////////////////////////////////////////////////////////
class TBackground; // forward decl.

#define TOBJECT_CLASS_ID   0x4e8a234f
class TObject
{
public:

 virtual void destroy()=0;
 virtual CLSID getClassId() { return TOBJECT_CLASS_ID; }

public:
 unsigned int options;
protected:
 TBackground *owner;
 int id;
friend class TBackground;
};

//////////////////////////////////////////////////////////////////////////
#define TFRAMEDOBJ_CLASS_ID   0x99fc7f13
class TFramedObj:public TObject
{
public:
 TFramedObj(int x1=0,int y1=0,int x2=10,int y2=10);
 ~TFramedObj();
 virtual CLSID getClassId() { return TFRAMEDOBJ_CLASS_ID; }
 void destroy();

 virtual void draw();
 void show();
 void hide();
 void BackBuffering(int on);

 int intersect(TFramedObj& obj);
 int willIntersect(TFramedObj& obj,int x,int y);
 int getWidth();
 int getHeight();

 virtual int messageHandler(MSG msg,void *obj)=0;

 int x1,y1,x2,y2;
protected:
 int visible;
 int bbf;  // Back Buffering
private:
 char *BackBuff;
};

//////////////////////////////////////////////////////////////////////////
#define TMOVABLE_CLASS_ID   0x300ef3db
class TMovable:public TFramedObj
{
public:
 TMovable(int x1,int y1,int x2,int y2);
 virtual CLSID getClassId() { return TMOVABLE_CLASS_ID; }

 void moveDelta(int DeltaTop,int DeltaLeft);
 void moveTo(int x,int y);
 void getTarget(DRCT dir,int& x,int& y);
 void changeDir(DRCT dir);

protected:
 DRCT direction;
 DRCT drawdirection;  // Same as 'direction' unless 'direction' is dirNone.
		      // In that case 'drawdirection' holds latest direction
		      // for drawing purpose.
};

//////////////////////////////////////////////////////////////////////////
#define TSYNCMOVABLE_CLASS_ID   0x27832bad
class TSyncMovable:public TMovable
{
public:
 TSyncMovable(int x1,int y1,int x2,int y2);
 virtual CLSID getClassId() { return TSYNCMOVABLE_CLASS_ID; }

 virtual void update();
};

//////////////////////////////////////////////////////////////////////////
#define TTANK_CLASS_ID   0x5cda0f9f
class TTank:public TSyncMovable
{
public:
 TTank(int x1,int y1,int x2,int y2);
 virtual CLSID getClassId() { return TTANK_CLASS_ID; }
};

//////////////////////////////////////////////////////////////////////////
#define TMYTANK_CLASS_ID   0x1355fd00
class TMyTank:public TTank
{
public:
 TMyTank(int x1,int y1,int x2,int y2);
 virtual CLSID getClassId() { return TMYTANK_CLASS_ID; }

 virtual void draw();
 virtual int messageHandler(MSG msg,void *obj);
};

//////////////////////////////////////////////////////////////////////////
#define TENEMYTANK_CLASS_ID   0x8cd14321
class TEnemyTank:public TTank
{
public:
 TEnemyTank(int x1,int y1,int x2,int y2);
 virtual CLSID getClassId() { return TENEMYTANK_CLASS_ID; }

 virtual void draw();
 virtual int messageHandler(MSG msg,void *obj);
};

//////////////////////////////////////////////////////////////////////////
#define TBULET_CLASS_ID   0x8db35a19
class TBulet:public TSyncMovable
{
public:
 TBulet(int x1,int y1,int x2,int y2);
 ~TBulet();
 virtual CLSID getClassId() { return TBULET_CLASS_ID; }

 virtual void draw();
 virtual int messageHandler(MSG msg,void *obj);
};

//////////////////////////////////////////////////////////////////////////
#define TBACKGROUND_CLASS_ID   0x00000321
class TBackground:public TFramedObj
{
public:
 TBackground();
 virtual CLSID getClassId() { return TBACKGROUND_CLASS_ID; }

 int checkCollision(int id,int x,int y);

 virtual void draw();
 void own(TFramedObj* obj);
 void disown(TFramedObj* obj);

 virtual int messageHandler(MSG,void *)
 {
  return 0;
 }

private:
int getfreeslot();

private:
#define MAX_OBJECTS  100
static char Map[8][13];
TFramedObj *Childs[MAX_OBJECTS];
};

#endif

