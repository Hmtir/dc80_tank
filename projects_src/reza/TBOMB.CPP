TBomb::TBomb(int _dir,int x,int y,int pwnd):TObject(pwnd)
{
	int *poly;
	int x1,y1,x2,y2;
	TObject *obj=Application.GetObject(P_Handle());

	pos.top=y-2;
	pos.left=x;
	pos.height=2;
	pos.width=2;

	x1=pos.left;
	y1=pos.top;
	x2=pos.left;
	y2=pos.top;
	dir=_dir;
	y1=y1+pos.height-(obj->pos.top+21);
	y1=y1/37;
	x1=x1+pos.width-(obj->pos.left+4);
	x1=x1/37;
	y2=y2+pos.height-(obj->pos.top+21);
	y2=y2/37;
	x2=x2+pos.width-(obj->pos.left+4);
	x2=x2/37;
	if (y1==10) y1=9;
	if (x1==10) x1=9;
	if (y2==10) y2=9;
	if (x2==10)  x2=9;
	allowdraw=true;
	switch (dir)
	{
		case 1: if ( (y1==0)||(TankFrame->block[y1-1][x1]=='b') )
			{
				allowdraw=false;
				return;
			}
			break;
		case 2: if ( (y2==9)||(TankFrame->block[y2+1][x1]=='b') )
			{
				allowdraw=false;
				return;
			}
			break;
		case 3: if ( (x1==0)||(TankFrame->block[y1][x1]=='b') )
			{
				allowdraw=false;
				return;
			}
			break;
		case 4: if ( (x2==9)||(TankFrame->block[y1][x2]=='b') )
			{
				allowdraw=false;
				return;
			}
	}
	visible=false;
	bool mouse=Mouse.OnWindow(this);
	if (mouse==true)
		Mouse.hide();
	poly=fillpol(pos.left,pos.top,pos.left+pos.width,pos.top+pos.height);
	box(poly,14,14,1);
	if (mouse==true)
		Mouse.show();
	this->x=100;
	TankFrame->bombindex++;
	TankFrame->bomblist[TankFrame->bombindex]=this;
	((TForm1 *)obj)->SetBombLoc(this);
	strcpy(classname,"TBomb");
	SetName("Bomb");
};

void TBomb::MoveBomb(int step)
{
       int *poly;
       bool mouse=Mouse.OnWindow(this);
       if ( (pos.width>3)||(pos.height>3)||(pos.left<0)||(pos.top<0) ) return;
       if (mouse==true)
	       Mouse.hide();
       poly=fillpol(pos.left,pos.top,pos.left+pos.width+1,pos.top+pos.height+1);
       box(poly,0,0,1);
       switch (dir)
       {
	case 1:pos.top-=step;
		break;
	case 2:pos.top+=step;
		break;
	case 3:pos.left-=step;
		break;
	case 4:pos.left+=step;
		break;
       }
       poly=fillpol(pos.left,pos.top,pos.left+pos.width,pos.top+pos.height);
       box(poly,14,14,1);
       if (mouse==true)
	       Mouse.show();
       setcolor(0);
}

TBomb::~TBomb()
{
	int *poly;
	if ( (pos.width>3)||(pos.height>3)||(pos.left<0)||(pos.top<0) ) return;
	if (allowdraw==true)
	{
		bool mouse=Mouse.OnWindow(this);
		tank->index--;
		poly=fillpol(pos.left,pos.top,pos.left+pos.width+1,pos.top+pos.height+1);	poly=fillpol(pos.left,pos.top,pos.left+pos.width+1,pos.top+pos.height+1);
		if (mouse==true)
			Mouse.show();
		box(poly,0,0,1);
		if (mouse==true)
			Mouse.hide();
	}
	setcolor(0);
	if (Handle()==0) return;
}
