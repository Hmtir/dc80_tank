position lpos;
void *bufhint;
TObject *lobj=NULL;
TWindow *DeskTop=NULL;
TTaskBar *TaskBar=NULL;
TButton *Task=NULL,*StartButton=NULL;
TMouse Mouse;
TApplication Application;
TForm1 *TankFrame=NULL;
TForm2 *TestObj=NULL;
Start_Menu *SMenu=NULL;
HookList *hook=NULL;
_ShoutDown *s=NULL;
TObject *Deragobj=NULL;
position Deragpos;
TLable *lbl1;
TBomb *bomb;
char flag,test=0;
void *DeragBuf1,*DeragBuf2,*DeragBuf3,*DeragBuf4;


TApplication::TApplication(void){
   int gdriver = DETECT, gmode, errorcode;
   initgraph(&gdriver, &gmode, "");
   errorcode = graphresult();
   if (errorcode != grOk)
   {
      printf("Graphics error: %s\n", grapherrormsg(errorcode));
      printf("Press any key to halt:");
      getch();
      exit(1);
   }
   lobj=NULL;
   list=NULL;
   hook=NULL;
}

void TApplication::SetHint(position Pos,TObject *obj)
{
	unsigned size;
	int x1,y1,x2,y2,poly[10];
	if (obj->allowup==false) return;
	if (lobj!=obj) flag=1;
	if (flag==0) return;
	if ((obj->allowhint==false)&&(lobj==obj))
	{
		x1=lpos.x;
		y1=lpos.y;
		Mouse.hide();
		putimage(x1,y1,bufhint,0);
		Mouse.show();
		free(bufhint);
		flag=0;
		lobj=obj;
		return;
	}
	if ((lobj!=NULL)&&(lobj->allowhint==true)){
		if (lobj==obj) return;
		x1=lpos.x;
		y1=lpos.y;
		Mouse.hide();
		putimage(x1,y1,bufhint,0);
		Mouse.show();
		free(bufhint);
	} else if (lobj!=NULL) lobj->allowhint=true;

	x1=Pos.x-3;
	if ((obj->pos.top+obj->pos.height) > getmaxy()-50){
		y1=obj->pos.top-6-textheight(obj->hint)-3;
		y2=obj->pos.top-6+3;
	}
	else{
		y1=(obj->pos.top+obj->pos.height)+10;
		y2=(obj->pos.top+obj->pos.height)+textheight(obj->hint)+6+10;
	}
	x2=Pos.x+textwidth(obj->hint)+3;
	if (x2>getmaxx()){
		x1=x1-(x2-getmaxx());
		x2=getmaxx();
	}
	if (obj->showhint==true){
		size=imagesize(x1,y1,x2,y2);
		bufhint=malloc(size);
		Mouse.hide();
		getimage(x1,y1,x2,y2,bufhint);
		poly[0]=x1;
		poly[1]=y1;
		poly[2]=x2-1;
		poly[3]=y1;
		poly[4]=x2-1;
		poly[5]=y2-1;
		poly[6]=x1;
		poly[7]=y2-1;
		poly[8]=x1;
		poly[9]=y1;
		setcolor(0);
		setfillstyle(1,15);
		fillpoly(4,poly);
		rectangle(x1,y1,x2-1,y2-1);
		outtextxy(x1+3,y1+3,obj->hint);
		Pos.y=y1;
		Pos.x=x1;
		lpos=Pos;
		lobj=obj;
		test++;
		Mouse.show();
	}else lobj=NULL;
};

void TApplication::TestHotKey(int key)
{
	char ch;
//	zorder *t;
	key>>=8;
	for(int i=0;i<26;i++)
		if (ChCode[i][1]==key) exit(0); /*{ ch=ChCode[i][0]; break;}*/
/*	t=start;
	while (t!=NULL){
		for(i=0;i<t->object->h_index;i++)
			if (ch==t->object->HotKey[i]){ t->object->Do_Operation(ch);return;};
		t=t->l_link;
	}
/*	for(i=0;i<=index;i++)
		if (HotKey[i]==ch) break;
	if (i<=index){
		GroupBox1->SetIndex(ch);
	}*/
}

int TApplication::PushZ(TObject *pointer,zorder **StartPoint)
{
	zorder *t,*b;
	t=*StartPoint;
	int handle;
	handle=InsertList(pointer);
	t=new zorder;
	t->link=*StartPoint;
	t->object=pointer;
	*StartPoint=t;
	return handle;
}

int TApplication::InsertList(TObject *pointer)
{
	objectlist *l1,*l2;
	int hwnd;
	l1=list;
	l2=l1;
	hwnd=0;
	if (l1==NULL){
		l1=new objectlist;
		l1->handle=200;
		l1->object=pointer;
		l1->link=NULL;
		hwnd=200;
		list=l1;
	}
	else{
	      while (l1->link!=NULL) l1=l1->link;
	      hwnd=l1->handle + 1;
	      l2=new objectlist;
	      l1->link=l2;
	      l2->link=NULL;
	      l2->handle=hwnd;
	      l2->object=pointer;
	}
	return hwnd;
}

bool TApplication::ValidWindow(int handle)
{
	objectlist *a;
	a=list;
	while (a!=NULL)
	{
		if (a->object->Handle()==handle) return true;
		a=a->link;
	}
	return false;
}

void TApplication::Run(void){
	int key,tmp,handle,mkey,lobj;
	Rect loc;
	loc.top=0;
	loc.left=0;
	loc.width=getmaxx();
	loc.height=getmaxy()-26;

	DeskTop = new TWindow(0);
	DeskTop->SetName("DeskTop");
	DeskTop->SetClassname("TDeskTop");
	DeskTop->pos=loc;
	DeskTop->wstyle=1;

	DeskTop->Paint(9,9);
	Mouse.show();
	TaskBar = new TTaskBar(0);

/*	flag=1;
	loc.top=100;
	loc.left=200;
	loc.height=200;
	loc.width=300;

	Form1 = new TForm(0,"Form1");
	Form1->pos=loc;
	Form1->SetClassname("TForm");
	Form1->PaintForm(0,7,0);
	SetActiveWindow(Form1);*/
	Mouse.MousePos();
	lobj=MouseOnWindow(start,Mouse.pos);
	mkey=Mouse.pos.key;
	for (;;) //Alt + F4
	{
		TaskBar->SetClock();
		Mouse.MousePos();
/*		setcolor(9);
		char st[20];
		char oname[30];
		outtextxy(10,5,"лллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллл");*/
		handle=MouseOnWindow(start,Mouse.pos);
		SendMessage(handle,MW_MOUSEMOVE,Mouse.pos);
		if ((lobj!=0)&&(lobj!=handle)){
			if (Mouse.pos.key==1){
				if (ValidWindow(lobj)==false) handle=lobj=MouseOnWindow(start,Mouse.pos);
				if (lobj!=0)
					SendMessage(lobj,MW_MOUSEUP,Mouse.pos);
				lobj=0;
			}
			else if (Mouse.pos.key!=0){
				SendMessage(handle,MW_MOUSECLICK,Mouse.pos);
				lobj=handle;
			}
		}
		if (Mouse.pos.key!=0){
			SendMessage(handle,MW_MOUSECLICK,Mouse.pos);
			lobj=handle;
		}
		else if (Mouse.pos.key!=mkey){
			SendMessage(handle,MW_MOUSEUP,Mouse.pos);
			lobj=handle;
		}
		mkey=Mouse.pos.key;
/*		setcolor(0);
		itoa(handle,st,10);
		outtextxy(10,5,st);
		itoa(Mouse.pos.x,st,10);
		outtextxy(60,5,st);
		itoa(Mouse.pos.y,st,10);
		outtextxy(100,5,st);
		strcpy(oname,Application.start->object->name);
		outtextxy(150,5,oname);*/
		if (bioskey(1)){
			key=bioskey(0);
			tmp=bioskey(2);
			int tm;
			tm=tmp;
			tmp&=8;
			tmp>>=3;
			if (tmp==1){
				TestHotKey(key);
				continue;
			}
			else
			{
				position pos;
				pos.x=key;
				pos.y=tm;
				SendMessage(GetActiveWindow(),MW_KEYPRESS,pos);
			}
		}
	}
}

void TApplication::showzorder(zorder *z)
{
	if (z==NULL) return;
	showzorder(z->link);
	printf("%s  %s  %d  %d \n",z->object->name,z->object->classname,z->object->Handle(),z->object->P_Handle());
	delete z->object;
}

int TApplication::MouseOnWindow(zorder *StartPoint,position pos)
{
	static position p;
	int handle;
	int h1;
	char test;
	zorder *t;
	int x1,y1,x2,y2;
	TObject *cl;
	p=pos;
	t=StartPoint;
	test=0;
	while (t!=NULL)
	{
		cl=t->object;
		if (cl->visible==false){
			t=t->link;
			continue;
		}
		handle=cl->Handle();
		x1=(cl->pos.left);
		x2=(cl->pos.left+cl->pos.width);
		y1=(cl->pos.top);
		y2=(cl->pos.top+cl->pos.height);
		if (((x1<=p.x)&&(x2>=p.x))&&
		   (y1<=p.y)&&(y2>=p.y))
		    {
			   if (cl->Handle()==200){
				t=t->link;
				test=1;
				continue;
			   }
			   h1=0;
			   if (cl->selfZ!=NULL)
				h1=MouseOnWindow(cl->selfZ,Mouse.pos);
			   if (h1!=0) handle=h1;
			   return handle;
		    }
		t=t->link;
	}
	if (test==1) return 200;
	else return 0;
}

void TApplication::SendMessage(int handle,int Message,position pos,Rect rec,int para2)
{
	TObject *obj;
	HookList *h;
	obj=GetObject(handle);
	h=hook;
	if (((TWindow *) obj)->visible==false) return;
	switch (Message){
	      case MW_MOUSEMOVE: if (Deragobj!=NULL) DeragObject(obj,pos);
				 if (Deragobj!=NULL) break;
				 SetHint(pos,obj);
				 while (h!=NULL){
					if (h->OnMouseMove!=NULL)
						(h->OnMouseMove)(pos,h->obj,obj);
					h=h->link;
				 }
				 if (obj->OnMouseMove==NULL) break;
					(obj->OnMouseMove)(pos,obj);
				break;
	      case MW_MOUSECLICK:if (Deragobj!=NULL) break;
				 obj->allowhint=false;
				 if ((obj->Handle()!=GetActiveWindow())&&(Deragobj==NULL))
				 {
					if (GetActiveWindow()==204)
					{
					    obj->allowhint=obj->allowhint;
					}
					SetActiveWindow(obj);
				 }
				 DeragObject(obj,pos);
				 SetHint(pos,obj);
				 ((TWindow *)obj)->Click();
				 while (h!=NULL){
					if (h->OnMouseClick!=NULL)
						(h->OnMouseClick)(pos,h->obj,obj);
					h=h->link;
				 }
				 if (obj->OnMouseClick==NULL) break;
					(obj->OnMouseClick)(pos,obj);
				break;
	      case MW_MOUSEUP   : ((TWindow *)obj)->UnClick();
				 if (Deragobj!=NULL)  DeragObject(obj,pos);
				 if (obj->OnMouseUp==NULL) break;
					(obj->OnMouseUp)(pos,obj);
				break;
	      case MW_REFRESH   :((TWindow *)obj)->refresh(rec.left,rec.top,rec.left+rec.width,rec.top+rec.height);
				 ((TWindow *)obj)->OnRefresh(rec);
				break;
	      case MW_KEYPRESS  :if (obj->OnKeyPress!=NULL)
					obj->OnKeyPress(pos.x,pos.y);
				break;
	}
	para2=para2;
}

TObject *TApplication::GetObject(int handle)
{
	objectlist *obj;
	obj=list;
	while (obj!=NULL){
		if (obj->object->Handle()==handle) break;
		obj=obj->link;
	}
	return obj->object;
}

void TApplication::Hook(TObject *obj,int Event,void (*event)(position,TObject *,TObject *))
{
	HookList *h,*b;
	h=hook;
	b=h;
	while (h!=NULL){
		b=h;
		h=h->link;
	}
	h=new HookList;
	h->obj=obj;
	h->OnMouseMove=NULL;
	h->OnMouseUp=NULL;
	h->OnMouseClick=NULL;
	switch (Event){
	      case	EV_MOUSEMOVE: h->OnMouseMove=event;
				      break;
	      case	EV_MOUSEUP:   h->OnMouseUp=event;
				      break;
	      case	EV_MOUSECLICK:h->OnMouseClick=event;
				      break;
	}
	h->link=NULL;
	if (hook==NULL) hook=h;
	else b->link=h;
}

void TApplication::UnHook(int handle)
{
	HookList *h,*b;
	h=hook;
	b=h;
	while (h!=NULL){
		if (h->obj->Handle()==handle)
		   if (h==hook){
			hook=h->link;
			delete h;
		   }
		   else{
			b->link=h->link;
			delete h;
		   }
		b=h;
		h=h->link;
	}
}

/*void TApplication::DestroyWindow(int handle,zorder **StartPoint)
{
	zorder *t,*b;
	t=*StartPoint;
	b=t;
	while (t!=NULL){
		if (t->object->P_Handle()==handle)
		{
		    b=t->link;
		    DestroyWindow(t->object->Handle(),StartPoint);
		    t=b=start;
		}
		else
		{
		    b=t;
		    t=t->link;
		}
	}
	t=start;
	b=t;
	while (t!=NULL)
	{
		if (t->object->Handle()==handle){
			if (t==start){
				start=start->link;
				delete(t);
				t=start;
				break;
			}
			else
			{
				b->link=t->link;
				delete(t);
				t=b->link;
				break;
			}
		}
		b=t;
		t=t->link;
	}

}*/

void TApplication::DeleteObjectList(int handle)
{
	objectlist *t,*b;
	t=list;
	b=t;
	while (t!=NULL){
		if ((t->object->P_Handle()==handle)||(t->object->Handle()==handle))
			if (t==list){
				list=list->link;
				delete t;
				t=b=list;
			}
			else{
				b->link=t->link;
				delete t;
				t=b;
			}
		b=t;
		t=t->link;
	}
}

void TApplication::Terminated(void)
{
	exit(1);
}

void TApplication::DeragObject(TObject *obj,position pos)
{
	int x1,y1,x2,y2,size;
	static lx1,lx2,ly1,ly2;
	Rect rec;
	static position lpos;
	if (pos.key==0){
		if (Deragobj!=NULL){
			Mouse.hide();
			rec.left=lx1;
			rec.top=ly1;
			rec.height=ly2-ly1;
			rec.width=lx2-lx1;
			putimage(lx1,ly1,DeragBuf1,0);
			putimage(lx2,ly1,DeragBuf2,0);
			putimage(lx1,ly2,DeragBuf3,0);
			putimage(lx1,ly1,DeragBuf4,0);
			((TWindow *)Deragobj)->MoveWindow(lx1,ly1);
			if (obj->OnEndDrag!=NULL)
				obj->OnEndDrag(Deragobj);
			Mouse.show();
			free(DeragBuf1);
			free(DeragBuf2);
			free(DeragBuf3);
			free(DeragBuf4);
			Deragobj=NULL;
			return;
		}
	}
	if (Deragobj!=NULL){
		if ((lpos.x!=pos.x)||(lpos.y!=pos.y))
		{
			int avgx,avgy;
			avgx=pos.x-Deragpos.x;
			avgy=pos.y-Deragpos.y;

			x1=Deragobj->pos.left+avgx;
			x2=Deragobj->pos.left+Deragobj->pos.width+avgx;
			y1=Deragobj->pos.top+avgy;
			y2=Deragobj->pos.top+Deragobj->pos.height+avgy;

			if ((x1<=0)||(x2>=getmaxx())||(y1<=0)||(y2>=getmaxy()-25)){
				Mouse.SetMousePos(lpos.x,lpos.y);
				return;
			}
			Mouse.hide();
			putimage(lx1,ly1,DeragBuf1,0);
			putimage(lx2,ly1,DeragBuf2,0);
			putimage(lx1,ly2,DeragBuf3,0);
			putimage(lx1,ly1,DeragBuf4,0);

			lx1=x1;
			lx2=x2;
			ly1=y1;
			ly2=y2;

			getimage(x1,y1,x2,y1,DeragBuf1);
			getimage(x2,y1,x2,y2,DeragBuf2);
			getimage(x1,y2,x2,y2,DeragBuf3);
			getimage(x1,y1,x1,y2,DeragBuf4);

			setlinestyle(1,2,0);
			setcolor(8);
			rectangle(x1,y1,x2,y2);
			setlinestyle(0,0,0);
			Mouse.show();
			lpos=pos;
		}
	}
	else{
		lx1=x1=obj->pos.left;
		lx2=x2=obj->pos.left+obj->pos.width;
		ly1=y1=obj->pos.top;
		ly2=y2=obj->pos.top+obj->pos.height;
		if (obj->allowderag==false){
			Deragobj=NULL;
			return;
		}
		if ((pos.x>=x1+4)&&(pos.x<=x2-30)&&(pos.y>=y1+4)&&(pos.y<=y1+20))
		{
			if (obj->OnStartDrag!=NULL)
				obj->OnStartDrag(obj);
			size=imagesize(x1,y1,x2,y1);
			DeragBuf1=malloc(size);
			getimage(x1,y1,x2,y1,DeragBuf1);

			size=imagesize(x2,y1,x2,y2);
			DeragBuf2=malloc(size);
			getimage(x2,y1,x2,y2,DeragBuf2);

			size=imagesize(x1,y2,x2,y2);
			DeragBuf3=malloc(size);
			getimage(x1,y2,x2,y2,DeragBuf3);

			size=imagesize(x1,y1,x1,y2);
			DeragBuf4=malloc(size);
			getimage(x1,y1,x1,y2,DeragBuf4);

			Deragpos=pos;
			lpos=pos;
			Deragobj=obj;
		}else Deragobj=NULL;
	}
//-------------
	rec=rec;
//-------------
}

HWND TApplication::GetActiveWindow(zorder *z)
{
	if (z==NULL) return start->object->Handle();
	else  return z->object->Handle();
}

void TApplication::SetActiveWindow(TObject *obj)
{
	zorder *s,*t,*b,*k;
	zorder *ch;
	TObject *p,*m;
	bool key=false;
	HWND _handle=obj->Handle();
	p=NULL;
	if (obj==NULL) return;
	if (obj->P_Handle()==0)
		s=Application.start;
	else{
		p=GetObject(obj->P_Handle());
		s=p->selfZ;
	}
	p=obj;
	while (p->P_Handle()!=0)
	{
		p=GetObject(p->P_Handle());
		s=p->selfZ;
		b=t=s;
		if  (s->object->Handle()!=_handle)
		{
			while (s!=NULL)
			{
				if (s->object->Handle()==_handle)
				{
					t->link=b;
					k=b->link;
					b->link=s->link;
					s->link=k;
					b=s;
					break;
				}
				t=s;
				s=s->link;
			}
			p->selfZ=b;
		}
		_handle=p->P_Handle();
	}
	b=s=t=start;
	if (s->object->Handle()==_handle)
	{
		if (s->object->active!=true)
		{
			s->object->active=true;
			m=s->object;
			((TWindow *)m)->ActiveWindow();
		}
	}
	else
	while (s!=NULL)
	{       if (s->object->Handle()==_handle)
		{
			t->link=b;
			b->object->active=false;
			m=b->object;
			((TWindow *)m)->DeActiveWindow();
			k=b->link;
			b->link=s->link;
			s->link=k;
			s->object->active=true;
			m=s->object;
			((TWindow *)m)->ActiveWindow();
			b=s;
			break;
		}
		t=s;
		s=s->link;
	}
	start=b;
/*	if (obj->Handle()==s->object->Handle()){
		if (obj->active==false){
			SetActiveWindow(GetObject(obj->P_Handle()));
			obj->active=true;
			if (s->link!=NULL)
			{
				TObject *ob=s->link->object;
				((TWindow *)ob)->DeActiveWindow();
				ch=ob->selfZ;
				while (ch!=NULL)
				{
					ch->object->active=false;
					ch=ch->link;
				}
			}
			((TWindow *)obj)->ActiveWindow();
			ch=obj->selfZ;
			while (ch!=NULL)
			{
				ch->object->active=true;
				ch=ch->link;
			}
		}
		return;
	}
	t=s;
	while (t!=NULL)
	{
		if (t->object->Handle()==obj->Handle()){
			key=true;
			break;
		}
		t=t->link;
	}
	if (key==false) return;
	b=t=s;
	while (t!=NULL)
	{
		if (t->object->Handle()==obj->Handle()){
			b->link=t->link;
			break;
		};
		b=t;
		t=t->link;
	}
	t->link=s;
	TObject *o;
	o=s->object;
	o->active=false;
//	((TWindow *)o)->GetPicture();
	((TWindow *)o)->DeActiveWindow();
	ch=o->selfZ;
	while (ch!=NULL)
	{
		ch->object->active=false;
		ch=ch->link;
	}
	o=t->object;
	o->active=true;
	ch=o->selfZ;
	while (ch!=NULL)
	{
		ch->object->active=true;
		ch=ch->link;
	}
	((TWindow *)o)->ActiveWindow();
	RefreshWindow(o);
	if (p==NULL)
	{
		Application.start=t;
	}
	else
	{
		SetActiveWindow(p);
		GetObject(obj->P_Handle())->selfZ=t;
	}*/
	key=key;
}
void TApplication::RefreshWindow(TObject *obj)
{
	zorder *z;
	int x1,y1,x2,y2,x3,y3,x4,y4,dx1,dx2,dy1,dy2;
	if (obj->P_Handle()!=0) return;
	if (obj->Handle()==200) return;
	TObject *top;
	if (obj->Handle()==204)
	{
		int i=0;
		i++;
	}
	x1=obj->pos.left;
	y1=obj->pos.top;
	x2=obj->pos.left+obj->pos.width;
	y2=obj->pos.top+obj->pos.height;
	if (obj->P_Handle()!=0)
		z=GetObject(obj->P_Handle())->selfZ;
	else
		z=Application.start;
	while ((z->object->Handle()!=obj->Handle())&&(z!=NULL))
	{
		x3=z->object->pos.left;
		y3=z->object->pos.top;
		x4=z->object->pos.left+z->object->pos.width;
		y4=z->object->pos.top+z->object->pos.height;
		if ((y3<=y2)&&(y4>=y1))
		{
			dy1=y3-y1;
			dy2=y4-y1;
			if (dy1<0) dy1=0;
			if (dy2>(y2-y1+1)) dy2=y2-y1+1;
		}
		if ((x3<=x1)&&(x4>=x1))
		{
			dx1=x3-x1;
			dx2=x4-x1;
			if (dx1<0) dx1=0;
			if (dx2>(x2-x1+1)) dx2=x2-x1+1;
		}
		((TWindow *)obj)->refresh(dx1,dy1,dx2,dy2);
		z=z->link;
	}
}

void  TApplication::Refresh2(int x1,int y1,int x2,int y2,zorder *z,TObject *obj)
{
	int X1,Y1,X2,Y2,dx1=0,dx2=0,dy1=0,dy2=0,dX1=0,dX2=0,dY1=0,dY2=0;
	bool key=false;
	if ((x1>=x2)||(y1>=y2)) return;
	if (z==NULL) return;
	if (z->object->Handle()==obj->Handle())
	{
		Refresh2(x1 , y1 , x2 , y2 , z->link,obj);
		return;
	}
	X1=z->object->pos.left;
	X2=z->object->pos.left+z->object->pos.width;
	Y1=z->object->pos.top;
	Y2=z->object->pos.top+z->object->pos.height;
	if ( (y1>=Y2)||(y2<=Y1) )
	{
		Refresh2(x1,y1,x2,y2,z->link,obj);
		return;
	}
	else
	{
		dy1=y1-Y1;
		dy2=y2-Y1;
		if (dy1<0) dy1=0;
		if (dy2>(Y2-Y1)) dy2=Y2-Y1;
		key=true;
		if ( (x1>=X2)||(x2<=X1) )
		{
			Refresh2(x1,y1,x2,y2,z->link,obj);
			return;
		}
		else
		{
			dx1=x1-X1;
			dx2=x2-X1;
			if (dx1<0) dx1=0;
			if (dx2>(X2-X1)) dx2=X2-X1;
			key=true;
		}
	}
	dY1=Y1+dy1;
	dY2=Y1+dy2+1;
	dX1=X1+dx1;
	dX2=X1+dx2;
	Refresh2( x1 ,  y1 , dX1 ,  y2 , z->link,obj);
	Refresh2(dX2 ,  y1 , x2 ,  y2 , z->link,obj);
	Refresh2(dX1 ,  y1 , dX2 , dY1 , z->link,obj);
	Refresh2(dX1 , dY2 , dX2 ,  y2 , z->link,obj);
	if (key==true)
	{
		TObject *obj1=z->object;
		Rect rec;
		rec.left=dx1;
		rec.top=dy1;
		rec.width=dx2-dx1;
		rec.height=dy2-dy1;
		SendMessage(obj1->Handle(),MW_REFRESH,NullPos,rec);
	}
}

TApplication::~TApplication(void){
	closegraph();
	zorder *z;
	z=start;
	while (z!=NULL)
	{
	printf("%s  %s  %d  %d \n",z->object->name,z->object->classname,z->object->Handle(),z->object->P_Handle());
	z=z->link;
	}
//   printf("\n %d",GetActiveWindow(Form1));
//   showzorder(start);
//   showzorder(TaskBar->selfZ);
	///must be free object's mem
}

bool TApplication::getbmp(int x1,int y1,int x2,int y2,char *filename)
{
	unsigned size;
	int x,y;
	FILE *f;
	void *buf;
	size=imagesize(x1,y1,x2,y2);
	buf=malloc(size);
	getimage(x1,y1,x2,y2,buf);
	f=fopen(filename,"wb");
	if (f==NULL){
		free(buf);
		return false;
	}
	fwrite(&size,1,2,f);
	x=x2-x1;
	y=y2-y1;
	fwrite(&x,1,2,f);
	fwrite(&y,1,2,f);
	fwrite(buf,1,size,f);
	fclose(f);
	free(buf);
	return true;
}

void TApplication::RemoveChild(TObject *obj,HWND _handle)
{
	zorder *z,*b,*p;
	b=z=GetObject(_handle)->selfZ;
	while (z!=NULL)
	{
		b=z->link;
		delete z->object;
		delete z;
		z=b;
	}
	if (obj==NULL) p=start;
	else	p=obj->selfZ;
	z=b=p;
	while (z!=NULL)
	{
		if (z->object->Handle()==_handle)
			if (z==p)
			{
				if (obj==NULL) start=start->link;
				else	obj->selfZ=obj->selfZ->link;
				delete z;
				break;
			}
			else
			{
				b->link=z->link;
				delete z;
				break;
			}
		b=z;
		z=z->link;
	}
/*	if (obj==NULL) p=start;
	else	p=obj->selfZ;
	SetActiveWindow(p->object);*/
}
