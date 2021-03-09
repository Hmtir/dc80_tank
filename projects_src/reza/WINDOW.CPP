TWindow::TWindow(int pwnd):TObject(pwnd)
{
	clicked=false;
	DeragCondition=false;
	visible=false;
}

void TWindow::SetClassname(char *Classname)
{
	strcpy(classname,Classname);
}

void TWindow::SetbkColor(int color)
{
	setcolor(15);
	setfillstyle(SOLID_FILL,color);
	floodfill(pos.left+1,pos.top+1,15);
}

void TWindow::GetPicture(void)
{
	FILE *f;
	void *buf;
	int bx,by,kx,ky,size,x1,y1,x2,y2,bazeh;
	strcpy(TempFileName,"Temp\\");
	strcat(TempFileName,name);
	strcat(TempFileName,".tmp");
	f=fopen(TempFileName,"wb");
	bazeh=pos.width / 32;
/*	if (Handle()==200) bazeh=20;
	else bazeh=8;*/
	kx=(pos.width) / bazeh;
	bx=(pos.width) % bazeh;
	ky=(pos.height) / bazeh;
	by=(pos.height) % bazeh;
	size=imagesize(0,0,kx,ky);
	buf=malloc(size);
	Mouse.hide();
	for (int j=0;j<bazeh;j++)
	{
		size=imagesize(0,0,kx,ky);
		for (int i=0;i<bazeh;i++)
		{
			x1=pos.left+(i*kx);
			y1=pos.top+(j*ky);
			x2=pos.left+((i+1)*kx);
			y2=pos.top+((j+1)*ky);
			getimage(x1,y1,x2,y2,buf);
			fwrite(buf,size,1,f);
		}
		if (bx!=0){
			size=imagesize(x2,y1,x2+bx,y2);
			getimage(x2,y1,x2+bx,y2,buf);
			fwrite(buf,size,1,f);
		}
	}
	if (by!=0){
		y1=y2;
		y2=y2+by;
		for (int i=0;i<bazeh;i++)
		{
			x1=pos.left+(i*kx);
			x2=pos.left+((i+1)*kx);
			size=imagesize(x1,y1,x2,y2);
			getimage(x1,y1,x2,y2,buf);
			fwrite(buf,size,1,f);
		}
		if (bx!=0){
			size=imagesize(0,0,bx,by);
			getimage(x2,y1,x2+bx,y1+by,buf);
			fwrite(buf,size,1,f);
		}
	}
	Mouse.show();
	fclose(f);
	free(buf);
}

void TWindow::Paint(int tcolor,int bkcolor)
{
	this->size=imagesize(pos.left,pos.top,pos.left+pos.width,pos.top+pos.height);
	Mouse.hide();
	visible=true;
	textcolor=tcolor;
	backcolor=bkcolor;
	if (wstyle!=1) tcolor=15;
	setcolor(tcolor);
	rectangle(pos.left,pos.top,pos.left+pos.width,pos.top+pos.height);
	setfillstyle(SOLID_FILL,bkcolor);
	floodfill(pos.left+1,pos.top+1,tcolor);
	floodfill(pos.left+1,pos.top+pos.height-1,tcolor);
	GetPicture();
	Mouse.show();
	this->active=false;
	Application.SetActiveWindow(this);
}

void TWindow::refresh(int x1,int y1,int x2,int y2)
{
	FILE *f;
	void *buf;
	char location[30][30];
	int bazeh;
	int kx,ky,bx,by,size,test,indx1=0,indy1=0,indx2,indy2;
	if ((x2<=x1)||(y2<=y1)) return;
	bazeh=pos.width / 32;
/*	if (Handle()==200) bazeh=20 ;
	else bazeh=8;*/
	indx2=indy2=bazeh;
	f=fopen(TempFileName,"rb");
	kx=(pos.width) / bazeh;
	bx=(pos.width) % bazeh;
	ky=(pos.height) / bazeh;
	by=(pos.height) % bazeh;
	for (int j=0;j<bazeh;j++)
	    for (int i=0;i<bazeh;i++)
		    location[i][j]=0;
//--------------------------------------------------
	test=kx;
	while (x1 >= test){
		test+=kx;
		indx1++;
	}
	test=pos.width-bx;

	while (x2 <= test)
	{
		test-=kx;
		indx2--;
	}
	test=ky;
	while (y1 >= test){
		test+=ky;
		indy1++;
	}
	test=pos.height-by;
	while (y2 <= test)
	{
		test-=ky;
		indy2--;
	}
	for (j=indy1;j<=indy2;j++)
		for (i=indx1;i<=indx2;i++)
			location[j][i]=1;

//--------------------------------------------------
	size=imagesize(0,0,kx,ky);
	buf=malloc(size);
	Mouse.hide();
	for (j=0;j<bazeh;j++)
	{
		size=imagesize(0,0,kx,ky);
		for (i=0;i<bazeh;i++)
		{
			x1=pos.left+(i*kx);
			y1=pos.top+(j*ky);
			x2=pos.left+((i+1)*kx);
			y2=pos.top+((j+1)*ky);
			fread(buf,size,1,f);
			if (location[j][i]==1)
				putimage(x1,y1,buf,0);
		}
		if (bx!=0){
			size=imagesize(0,0,bx,ky);
			fread(buf,size,1,f);
			if (location[j][bazeh]==1)
				putimage(x2,y1,buf,0);
		}
	}
	if (by!=0){
		y1=y2;
		y2=y2+by;
		size=imagesize(0,y1,kx,y2);
		for (i=0;i<bazeh;i++)
		{
			x1=pos.left+(i*kx);
			x2=pos.left+((i+1)*kx);
			fread(buf,size,1,f);
			if (location[bazeh][i]==1)
				putimage(x1,y1,buf,0);
		}
		if (bx!=0){
			size=imagesize(0,0,bx,by);
			fread(buf,size,1,f);
			if (location[bazeh][bazeh]==1)
				putimage(x2,y1,buf,0);
		}
	}
	free(buf);
	fclose(f);
	Mouse.show();
}

void TWindow::Click()
{
	if (Mouse.pos.key!=1) return;
	if (wstyle==1) return;
	if (clicked==true) return;
	if (allowdown==false) return;
	Mouse.hide();
	clicked=true;
	setcolor(15);
	line(pos.left,pos.top+pos.height,pos.left+pos.width,pos.top+pos.height);
	line(pos.left+pos.width,pos.top,pos.left+pos.width,pos.top+pos.height);
	setcolor(backcolor);
	line(pos.left,pos.top+pos.height-1,pos.left+pos.width-1,pos.top+pos.height-1);
	line(pos.left+pos.width-1,pos.top,pos.left+pos.width-1,pos.top+pos.height-1);
	setcolor(0);
	line(pos.left,pos.top,pos.left+pos.width,pos.top);
	line(pos.left,pos.top,pos.left,pos.top+pos.height);
	Mouse.show();
}

void TWindow::UnClick(void)
{
	if (allowup==false) return;
	if (wstyle==1) return;
	if (clicked==false) return;
	if (allowdown==false) return;
	Mouse.hide();
	clicked=false;
	setcolor(0);
	line(pos.left,pos.top+pos.height,pos.left+pos.width,pos.top+pos.height);
	line(pos.left+pos.width,pos.top,pos.left+pos.width,pos.top+pos.height);
	setcolor(8);
	line(pos.left,pos.top+pos.height-1,pos.left+pos.width-1,pos.top+pos.height-1);
	line(pos.left+pos.width-1,pos.top,pos.left+pos.width-1,pos.top+pos.height-1);
	setcolor(15);
	line(pos.left,pos.top,pos.left+pos.width-1,pos.top);
	line(pos.left,pos.top,pos.left,pos.top+pos.height-1);
	Mouse.show();
}

void TWindow::Hide(void)
{
	TObject *obj;
	zorder *z;
/*	if (obj!=NULL)
		Application.DestroyWindow(Handle(),&(obj->selfZ));
	else
		Application.DestroyWindow(Handle(),&(Application.start));*/
	obj=Application.GetObject(P_Handle());
	if (obj!=NULL)
		z=obj->selfZ;
	else
		z=Application.start;
/*	while (z->object->Handle()!=Handle())
		z=z->link;*/
	Application.Refresh2(pos.left,pos.top,pos.left+pos.width,pos.top+pos.height,z,Application.GetObject(Handle()));
	Application.SetActiveWindow(Application.start->object);
/*	FILE *f;
	void huge *buf;
	zorder *z;
	Mouse.hide();
	buf=malloc(size);
	f=fopen(TempFileName,"rb");
	fread((void *)buf,size,1,f);
	putimage(pos.left,pos.top,buf,0);
	Mouse.show();
	free((void *)buf);
	visible=false;
	z=selfZ;
	while (z!=NULL)
	{
		((TWindow *)z->object)->visible=false;
		z=z->link;
	}
	fclose(f);*/
}

void TWindow::MoveWindow(int avgx,int avgy)
{
	void *buf;
	FILE *f;
	int x,y;
	x=pos.left-avgx;
	y=pos.top-avgy;
	if ((avgx==pos.left)&&(avgy==pos.top)) return;
	Mouse.hide();
	DeskTop->refresh(pos.left,pos.top,pos.left+pos.width,pos.top+pos.height);
	pos.left-=x;
	pos.top-=y;

	refresh(0,0,pos.width,pos.height);
	visible=true;
	zorder *z;
	z=selfZ;
	while (z!=NULL){
		z->object->visible=true;
		z->object->pos.left-=x;
		z->object->pos.top-=y;
		z=z->link;
	}
	Mouse.show();
}

TWindow::~TWindow(void)
{
	remove(TempFileName);
}
