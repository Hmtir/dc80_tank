TButton::TButton(int pwnd):TWindow(pwnd)
{
	strcpy(classname,"TButton");
}

void TButton::Paint(int tcolor,int bkcolor)
{
	int x1,y1,x2,y2;
	visible=true;
	Mouse.hide();
	textcolor=tcolor;
	backcolor=bkcolor;
	x1=pos.left;
	x2=pos.left+pos.width;
	y1=pos.top;
	y2=pos.top+pos.height;
	if (wstyle==1) tcolor=15;
	setcolor(tcolor);
	rectangle(pos.left,pos.top,pos.left+pos.width,pos.top+pos.height);
	setfillstyle(SOLID_FILL,bkcolor);
	floodfill(pos.left+1,pos.top+1,tcolor);
	floodfill(pos.left+1,pos.top+pos.height-1,tcolor);
	switch (wstyle)
	{
		case 0: setcolor(15);
			line(x1,y1,x2-1,y1);
			line(x1,y1,x1,y2-1);
			setcolor(8);
			line(x1+1,y2-1,x2-1,y2-1);
			line(x2-1,y1+1,x2-1,y2-1);
			break;
		case 1: setcolor(0);
			line(x1,y1,x2,y1);
			line(x1,y1,x1,y2);
			break;

	}
	Mouse.show();
	this->active=false;
}

void TButton::SetCaption(char *caption,int color)
{
	int x,y;
	textcolor=color;
	setcolor(backcolor);
	rectangle(pos.left+1,pos.top+1,pos.left+pos.width-2,pos.top+pos.height-2);
	setfillstyle(SOLID_FILL,backcolor);
	floodfill(pos.left+1,pos.top+1,backcolor);
	y=(pos.top+(pos.height/2)-(textheight(caption)/2))+1;
	x=(pos.left+(pos.width/2)-(textwidth(caption)/2))+1;
	setcolor(color);
	outtextxy(x,y,caption);
}
