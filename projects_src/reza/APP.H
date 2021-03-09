class TObject{
	HWND handle;
public:
	HWND p_handle;
	bool showhint;
	char hint[30];
	bool allowhint;
	bool allowup;
	bool allowdown;
	bool allowderag;
	bool visible;
	bool active;
	zorder *selfZ;
	Rect pos;
	char name[30];
	char classname[30];
	void SetName(char *);
	void (*OnMouseMove)(position,TObject *);
	void (*OnMouseClick)(position,TObject *);
	void (*OnMouseUp)(position,TObject *);
	void (*OnKeyPress)(int key,int tm);
	void (*OnStartDrag)(TObject *);
	void (*OnEndDrag)(TObject *);
	HWND Handle(void);
	HWND P_Handle(void);
	TObject(int pwnd);
	~TObject(void);
	void SetHint(char *Hint);
};


class TApplication {
public:
      objectlist *list;
      zorder *start;
      TApplication(void);
      void Run(void);
      void TestHotKey(int key);
      int PushZ(TObject *pointer,zorder **StartPoint);
      void showzorder(zorder *z);
      bool ValidWindow(int handle);
      int InsertList(TObject *pointer);
      int MouseOnWindow(zorder *StartPoint,position);
      void SendMessage(int handle,int Messsage,position pos=NullPos,Rect rec=NullRect,int para2=0);
      void SetHint(position,TObject *);
      void Hook(TObject *obj,int Event,void (*event)(position,TObject *,TObject *));
      void UnHook(int handle);
      void DeleteObjectList(int handle);
      HWND GetActiveWindow(zorder *z=NULL);
      void SetActiveWindow(TObject *obj);
      void RemoveChild(TObject *obj,HWND handle);
      TObject *GetObject(int handle);
      void RefreshWindow(TObject *obj);
      void Refresh2(int x1,int y1,int x2,int y2,zorder *z,TObject *obj);
      void Terminated(void);
      void DeragObject(TObject *obj,position pos);
      bool getbmp(int x1,int y1,int x2,int y2,char *filename);
      ~TApplication(void);
};

class TWindow:public TObject{
public:
      bool DeragCondition;
      unsigned	size;
      char caption[30];
      char TempFileName[80];
      int textcolor;
      int backcolor;
      char wstyle;
      bool clicked;
      TWindow(int pwnd);
      void SetClassname(char *);
      void SetbkColor(int color);
      virtual void Paint(int tcolor,int bkcolor);
      void GetPicture(void);
      void Click(void);
      void UnClick(void);
      ~TWindow(void);
      void refresh(int x1,int y1,int x2,int y2);
      virtual void OnRefresh(Rect rec){rec=rec;};
      void Hide(void);
      virtual void ActiveWindow(void){ };
      virtual void DeActiveWindow(void){ };
      void MoveWindow(int avgx,int avgy);
};

class TTaskBar:public TWindow{
public:
      TTaskBar(int pwnd);
      void SetClock(void);
      ~TTaskBar(){};
};

class TButton:public TWindow{
public:
	TButton(int pwnd);
	virtual void Paint(int tcolor,int bkcolor);
	void SetCaption(char *caption,int color);
	~TButton(){};
};

class Start_Menu:public TWindow{
public:
	int itemindex;
	int items;
	int l_md,l_dv;
	char Item[10][30];
	int len;
	Start_Menu(int pwnd);
	~Start_Menu(void);
	void DoOperation(void);
	void SetMenu(void);
};

class TForm:public TWindow{
public:
      bool minimize;
      bool maximize;
      bool close;
      TForm(int phwnd,char *Name);
      ~TForm(void){};
      virtual void ActiveWindow(void);
      virtual void DeActiveWindow(void);
      virtual void OnRefresh(Rect rec);
      void PaintForm(int tcolor,int bkcolor,char st);
};

class TMouse{
public:
	position pos;
	TMouse(void);
	~TMouse(){};
	position MousePos(void);
	void show(void);
	void hide(void);
	void MouseMove(void);
	void SetMousePos(int x,int y);
	bool OnWindow(TObject *obj);
};

class _ShoutDown:public TForm{
public:
	class TLable *lable1;
	class TButton *b1,*b2;
	_ShoutDown(int pwnd);
	~_ShoutDown(){};
};

class TPanel:public TWindow
{
public:
      TPanel(int phwnd);
      ~TPanel(){};
};

class TLable:public TObject
{
	int textcolor;
	char caption[30],t;
public:
	int backcolor,parentcolor;
	TLable(int phwnd);
	~TLable(){};
	void SetCaption(char *cap);
	char *GetCaption(void){return caption;}
	void SetColor(int tcolor);
};

class TProgressBar:public TObject
{
public:
	int percent;
	int textcolor,backcolor,fillcolor;
	TProgressBar(int phwnd);
	~TProgressBar(){};
	void Go(int per);
	void Clear(void);
	void Show(void);
};

class TImage:public TWindow
{
	char FileName[80];
	int size;
public:
	TProgressBar *pbar;
	char id;
	int index;
	char kill;
	char state;
	char x,y;
//	char e_index;
	char speed;
	bool LoadFromFile(char *fname);
	void Bombing(blocktank tanklist[10][10]);
	void Fire(void);
	void Move(int x,int y);
	TImage(int phwnd);
	~TImage(){};
	void Clear(void);
};

class TBomb:public TObject
{
public:
	TImage *tank;
	char dir,allowdraw;
	char state;
	char x,y;
	void MoveBomb(int step);
	TBomb(int _dir,int x,int y,int pwnd);
	~TBomb();
};

class TForm1:public TForm
{
	blocktank tanklist[10][10];
	TBomb *bombloclist[10][10];
	char colorlist[5];
	char level;
public:
	bool end,start,retry;
	char block[10][10];
	TImage *enemy[3];
	int bombindex;
	TBomb *bomblist[50];
	TLable *Lable1,*Lable2,*Lable3,*Lable4,*Lable5,*Lable6,*Lable7;
	TPanel *Panel1;
	TImage *Image1,*Image2,*Image3,*Image4;
	TProgressBar *pbar1,*pbar2,*pbar3,*pbar4;
	position SetLocation(char state,char laststate,TObject *obj);
	void StartNextMission(void);
	void Init(void);
	void SetBombLoc(TBomb *bomb);
	void MoveBomb(TBomb *bomb);
	int SetStep(int step,Rect loc,char dir);
	bool SetTankPos(TImage *tank);
	bool CanDo(TImage *tank,char action,char *step);
	void BombAction(TBomb *bomb);
	void DeleteBomb(TBomb *bomb);
	void DrawBlock(void);
	void MoveEnemyTank(void);
	char CreatePath(TImage *tank,char step,int *sp);
	void EndMission(void);
	void DestroyTank(TImage *tank);
	void WinMission(void);
	virtual void OnRefresh(Rect rec);
	TForm1(void);
	~TForm1(void){};
};

class TForm2:public TForm
{
public:
     TLable *Lable1,*Lable2,*Lable3,*Lable4,*Lable5,*Lable6,*Lable7,*Lable8,
	    *Lable9,*Lable10,*Lable11,*Lable12,*Lable13,*Lable14,*Lable15,*Lable16,
	    *Lable17,*Lable18,*Lable19,*Lable20,*Lable21,*Lable22;
     TForm2(void);
     ~TForm2(void){};
};