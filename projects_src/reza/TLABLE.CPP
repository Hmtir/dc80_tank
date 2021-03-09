TLable::TLable(int phwnd):TObject(phwnd)
{
	strcpy(classname,"TLable");
	caption[0]='\x0';
	textcolor=0;
	backcolor=8;
	t=0;
}

void TLable::SetCaption(char *cap)
{
	bool mouse;
	if (caption[0]=='\x0')
	{
		pos.left=pos.left+Application.GetObject(P_Handle())->pos.left;
		pos.top=pos.top+Application.GetObject(P_Handle())->pos.top;
		mouse=Mouse.OnWindow(this);
		if (mouse==true) Mouse.hide();
		setcolor(backcolor);
		outtextxy(pos.left,pos.top,caption);
	}else
	{
		mouse=Mouse.OnWindow(this);
		if (mouse==true) Mouse.hide();
		setcolor(parentcolor);
		outtextxy(pos.left,pos.top,caption);
	}
	pos.height=textheight(caption);
	pos.width=textwidth(caption);
	strcpy(caption,cap);
	setcolor(textcolor);
	outtextxy(pos.left,pos.top,caption);
	if (mouse==true) Mouse.show();
}

void TLable::SetColor(int tcolor)
{
	bool mouse=Mouse.OnWindow(this);
	if (mouse==true) Mouse.hide();
	textcolor=tcolor;
	setcolor(textcolor);
	outtextxy(pos.left,pos.top,caption);
	if (mouse==true) Mouse.show();
}