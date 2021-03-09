void CloseForm(position pos,TObject *obj);

TForm::TForm(int phwnd,char *Name):TWindow(phwnd)
{
	TButton *b1;
	Rect loc;
	int x1,y1,x2,y2;
	strcpy(name,Name);
	strcpy(classname,"TForm");
	strcpy(caption,name);
	maximize=minimize=close=true;
	allowdown=false;
	allowderag=true;

	b1=new TButton(Handle());
	b1->SetHint("Close");
	b1->SetName("Close");
	b1->OnMouseClick=CloseForm;
	b1->wstyle=0;

	b1=new TButton(Handle());
	b1->SetHint("Maximize");
	b1->SetName("Maximize");
	b1->wstyle=0;

	b1=new TButton(Handle());
	b1->SetHint("Minimize");
	b1->SetName("Minimize");
	b1->wstyle=0;
}

void TForm::PaintForm(int tcolor,int bkcolor,char st)
{
	int x1,y1,x2,y2,Y;
	int *poly;
	FILE *f;
	void *buf;
	this->size=imagesize(pos.left,pos.top,pos.left+pos.width,pos.top+pos.height);
	zorder *z;
	Rect loc;
	visible=true;
	Mouse.hide();
	textcolor=tcolor;
	backcolor=bkcolor;
	x1=pos.left;
	x2=pos.left+pos.width;
	y1=pos.top;
	y2=pos.top+pos.height;
	setcolor(15);
	rectangle(x1,y1,x2,y2);
	setcolor(8);
	line(x1+1,y2-1,x2-1,y2-1);
	line(x2-1,y1+1,x2-1,y2-1);
	setcolor(15);
	line(x1+1,y1+1,x1+1,y2-2);
	line(x1+1,y1+1,x2-2,y1+1);
	setcolor(0);
	line(x1,y2,x2,y2);
	line(x2,y1,x2,y2);
	setfillstyle(1,7);
	poly=fillpol(x1+2,y1+2,x2-2,y2-1);
	fillpoly(5,poly);
	free(poly);
	setfillstyle(1,bkcolor);
	if (st==0)
		Y=y2-3;
	else{
		Y=y2-22;
		setcolor(8);
		rectangle(x1+4,Y+2,x2-4,y2-4);
		setcolor(15);
		line(x1+4,y2-4,x2-4,y2-4);
		line(x2-4,Y+2,x2-4,y2-4);
		setcolor(bkcolor);
	}
	poly=fillpol(x1+4,y1+21,x2-4,Y);
	fillpoly(4,poly);
	free(poly);
	poly=fillpol(x1+4,y1+4,x2-4,y1+20);
	setfillstyle(1,1);
	fillpoly(4,poly);
	free(poly);
	setcolor(15);
	settextstyle(11,HORIZ_DIR,1);
	outtextxy(x1+8,y1+9,caption);
	z=selfZ;
	while (z!=NULL)
	{
		if (strcmp(z->object->name,"Close")==0){
			loc.width=13;
			loc.height=12;
			loc.top=y1+6;//pos.top+50;
			loc.left=x2-19;//pos.left+10;
			z->object->pos=loc;
			((TButton *)z->object)->Paint(0,7);
			((TButton *)z->object)->visible=true;
			setcolor(0);
			line(x2-15,y1+10,x2-10,y1+15);
			line(x2-14,y1+10,x2-10,y1+14);
			line(x2-15,y1+15,x2-9,y1+10);
			line(x2-15,y1+14,x2-10,y1+10);
		}
		if (strcmp(z->object->name,"Maximize")==0){
			loc.width=13;
			loc.height=12;
			loc.top=y1+6;//pos.top+50;
			loc.left=x2-37;
			z->object->pos=loc;
			((TButton *)z->object)->Paint(0,7);
			((TButton *)z->object)->visible=true;
			setcolor(0);
			rectangle(x2-34,y1+8,x2-27,y1+15);
			line(x2-34,y1+9,x2-27,y1+9);
		}
		if (strcmp(z->object->name,"Minimize")==0){
			loc.width=13;
			loc.height=12;
			loc.top=y1+6;//pos.top+50;
			loc.left=x2-53;
			z->object->pos=loc;
			((TButton *)z->object)->Paint(0,7);
			((TButton *)z->object)->visible=true;
			setcolor(0);
			line(x2-50,y1+14,x2-44,y1+14);
			line(x2-50,y1+15,x2-44,y1+15);
		}
		z=z->link;
	}
//---------------Save form--------------
	GetPicture();
	Mouse.show();
	this->active=false;
	Application.SetActiveWindow(this);
}

void TForm::ActiveWindow(void)
{
	int *poly,x1,y1,x2;
	Mouse.hide();
	setcolor(1);
	x1=pos.left;
	x2=pos.left+pos.width;
	y1=pos.top;
	poly=fillpol(x1+4,y1+4,x2-54,y1+19);
	setfillstyle(1,1);
	fillpoly(4,poly);
	free(poly);
	line(x2-54,y1+4,x2-5,y1+4);
	line(x2-54,y1+5,x2-5,y1+5);
	line(x2-54,y1+19,x2-5,y1+19);
	line(x2-39,y1+4,x2-39,y1+19);
	line(x2-38,y1+4,x2-38,y1+19);
	line(x2-23,y1+4,x2-23,y1+19);
	line(x2-22,y1+4,x2-22,y1+19);
	line(x2-21,y1+4,x2-21,y1+19);
	line(x2-20,y1+4,x2-20,y1+19);
	line(x2-5,y1+4,x2-5,y1+19);
	line(x2-4,y1+4,x2-4,y1+19);
	setcolor(15);
	settextstyle(11,HORIZ_DIR,1);
	outtextxy(x1+8,y1+9,caption);
	Mouse.show();
}

void TForm::DeActiveWindow(void)
{
	int *poly,x1,y1,x2;
	Mouse.hide();
	GetPicture();
	setcolor(8);
	x1=pos.left;
	x2=pos.left+pos.width;
	y1=pos.top;
	poly=fillpol(x1+4,y1+4,x2-54,y1+19);
	setfillstyle(1,8);
	fillpoly(4,poly);
	free(poly);
	line(x2-54,y1+4,x2-5,y1+4);
	line(x2-54,y1+5,x2-5,y1+5);
	line(x2-54,y1+19,x2-5,y1+19);
	line(x2-39,y1+4,x2-39,y1+19);
	line(x2-38,y1+4,x2-38,y1+19);
	line(x2-23,y1+4,x2-23,y1+19);
	line(x2-22,y1+4,x2-22,y1+19);
	line(x2-21,y1+4,x2-21,y1+19);
	line(x2-20,y1+4,x2-20,y1+19);
	line(x2-5,y1+4,x2-5,y1+19);
	line(x2-4,y1+4,x2-4,y1+19);
	setcolor(15);
	settextstyle(11,HORIZ_DIR,1);
	outtextxy(x1+8,y1+9,caption);
	Mouse.show();
}

void TForm::OnRefresh(Rect rec)
{
	if (active==false) DeActiveWindow();
	rec=rec;
}
