void StartMenu(position ,TObject *);
void HideMenu(position ,TObject *,TObject *);
void StartMenuMouseMove(position,TObject *,TObject *);
void Start_MenuClick(position,TObject *);

TTaskBar::TTaskBar(int pwnd):TWindow(pwnd)
{
	visible=true;
	wstyle=1;
	Mouse.hide();
	selfZ=NULL;
	Rect loc;
	pos.left=0;
	pos.top=getmaxy()-25;
	pos.width=getmaxx();
	pos.height=25;
	strcpy(name,"TaskBar");
	strcpy(classname,"TTaskBar");
	Paint(8,7);
	setcolor(15);
	line(pos.left,pos.top,pos.width,pos.top);
	loc.top=getmaxy()-22;
	loc.left=getmaxx()-47;
	loc.width=44;
	loc.height=19;

	Task = new TButton(Handle());
	Task->SetName("Task");
	Task->pos=loc;
	Task->SetClassname("TButton");
	Task->wstyle=1;
	Task->Paint(0,7);

	loc.top=getmaxy()-22;
	loc.left=3;
	loc.width=50;
	loc.height=19;

	StartButton = new TButton(Handle());
	StartButton->SetName("StartButton");
	StartButton->SetClassname("TButton");
	StartButton->pos=loc;
//	StartButton->p_handle=0;
	StartButton->wstyle=0;
	StartButton->Paint(0,7);

	StartButton->SetHint("Click Me!");
	StartButton->OnMouseClick=StartMenu;
	Application.Hook(StartButton,EV_MOUSECLICK,HideMenu);
//	Application.PushZ(StartButton,&selfZ,Handle());

	setcolor(8);
	line(loc.left+loc.width+3,loc.top-1,loc.left+loc.width+3,loc.top+loc.height+1);
	setcolor(15);
	line(loc.left+loc.width+4,loc.top-1,loc.left+loc.width+4,loc.top+loc.height+1);
	StartButton->SetCaption("  GO!",0);
	WINDOW(7,12,460,465,8,RED,1);
	WINDOW(13,18,460,465,8,GREEN,1);
	WINDOW(7,12,466,471,8,BLUE,1);
	WINDOW(13,18,466,471,8,YELLOW,1);

	Mouse.show();
	this->active=false;
	Application.SetActiveWindow(this);
}

void TTaskBar::SetClock(void)
{
	static min;
	struct  time ti;
	static char hu[3],mi[3],c,cap[14],tmp[5];
	struct date d;
	gettime(&ti);
	if (ti.ti_min==min) return;
	if (c==2)
	{
		setcolor(7);
		outtextxy(595,463,hu);
		outtextxy(618,463,mi);
	}
	c=2;
	setcolor(0);
	outtextxy(595,463,"  :  ");
	min=ti.ti_min;
	itoa(ti.ti_hour,hu,10);
	if (hu[1]=='\x0'){
		hu[2]=hu[1];
		hu[1]=hu[0];
		hu[0]='0';
	}
	outtextxy(595,463,hu);
	itoa(ti.ti_min,mi,10);
	if (mi[1]=='\x0'){
		mi[2]=mi[1];
		mi[1]=mi[0];
		mi[0]='0';
	}
	getdate(&d);
	itoa(d.da_mon,cap,10);
	strcat(cap,"/");
	itoa(d.da_day,tmp,10);
	strcat(cap,tmp);
	strcat(cap,"/");
	itoa(d.da_year,tmp,10);
	strcat(cap,tmp);
	Task->SetHint(cap);
	outtextxy(618,463,mi);
}

