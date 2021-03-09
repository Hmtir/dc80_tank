TProgressBar::TProgressBar(int phwnd):TObject(phwnd)
{
	allowdown=false;
}

void TProgressBar::Show(void)
{
	int *poly;
	pos.left=pos.left+Application.GetObject(Handle())->pos.left;
	pos.top=pos.top+Application.GetObject(Handle())->pos.top;
	poly=fillpol(pos.left,pos.top,pos.left+pos.width,pos.top+pos.height);
	box(poly,textcolor,backcolor,1);
}

void TProgressBar::Go(int per)
{
	int *poly;
	poly=fillpol(pos.left,pos.top,pos.left+pos.width,pos.top+pos.height);
	box(poly,textcolor,8,1);
	per=((per*pos.width)/100);
	poly=fillpol(pos.left,pos.top,pos.left+per+1,pos.top+pos.height);
	box(poly,textcolor,fillcolor,1);
	if (per<98){
		setcolor(textcolor);
		line(pos.left+pos.left+per,pos.top+1,pos.left+pos.left,pos.top+pos.height-2);
	}
}

void TProgressBar::Clear(void)
{
	int *poly;
	poly=fillpol(pos.left,pos.top,pos.left+pos.width,pos.top+pos.height);
	box(poly,textcolor,backcolor,2);
}