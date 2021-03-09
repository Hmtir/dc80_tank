void TImage::TImage(int phwnd):TWindow(phwnd)
{
	allowdown=false;
	x=-1;
	index=-1;
	kill=2;
}

bool TImage::LoadFromFile(char *fname)
{
	FILE *f;
	unsigned size1;
	bool mouse=Mouse.OnWindow(this);
	int x,y;
	void *buf;
	f=fopen(fname,"rb");
	if (f==NULL) return false;
	setcolor(0);
	fread(&size1,1,2,f);
	fread(&x,1,2,f);
	fread(&y,1,2,f);
	buf=malloc(size1);
	fread(buf,1,size1,f);
	pos.width=x;
	pos.height=y;
	if (mouse==true)
		Mouse.hide();
	putimage(pos.left,pos.top,buf,2);
	if (mouse==true)
		Mouse.show();
	free(buf);
	size=size1;
	fclose(f);
	return true;
};

void TImage::Move(int x,int y)
{
	void *buf;
	int *poly;
	if ((x==0)&&(y==0)) return;
	bool mouse=Mouse.OnWindow(this);
	if (mouse==true)
		Mouse.hide();
	setcolor(0);
	buf=malloc(size);
	getimage(pos.left,pos.top,pos.left+pos.width,pos.top+pos.height,buf);
	poly=fillpol(pos.left,pos.top,pos.left+pos.width,pos.top+pos.height+1);
	setfillstyle(1,0);
	fillpoly(4,poly);
	free(poly);
	pos.left+=y;
	pos.top+=x;
	putimage(pos.left,pos.top,buf,0);
	if (mouse==true)
		Mouse.show();
	free(buf);
}

void TImage::Clear(void)
{
	int *poly;
	bool mouse=Mouse.OnWindow(this);
	setcolor(0);
	setbkcolor(0);
	if (mouse==true)
		Mouse.hide();
	poly=fillpol(pos.left,pos.top,pos.left+pos.width,pos.top+pos.height+1);
	setfillstyle(1,0);
	fillpoly(4,poly);
	if (mouse==true)
		Mouse.show();
	free(poly);
}

void TImage::Bombing(blocktank tanklist[10][10])
{
	register int i;
	int x1,y1;
	if (index>=0) return;
	TObject *obj=Application.GetObject(P_Handle());
	x1=pos.left+pos.width-(obj->pos.left+4)-5;
	y1=pos.top+pos.height-(obj->pos.top+21)-5;
	x1/=37;
	y1/=37;
	if (x1==10) x1=9;
	if (y1==10) y1=9;
	switch (state)
	{
		case 1:for (i=y-1;i>=0;i--)
			    if ( (tanklist[i][x].state=='e')||(TankFrame->block[i][x]=='b') )
				break;
			    else
			    if (tanklist[i][x].state=='m')
			    {
				  Fire();
				  break;
			    }
		       break;
		case 2:for (i=y1+1;i<=9;i++)
			    if ( (tanklist[i][x].state=='e')||(TankFrame->block[i][x]=='b') )
				break;
			    else
			    if (tanklist[i][x].state=='m')
			    {
				  Fire();
				  break;
			    }
		       break;
		case 3:for (i=x-1;i>=0;i--)
			    if ( (tanklist[y][i].state=='e')||(TankFrame->block[y][i]=='b') )
				break;
			    else
			    if (tanklist[y][i].state=='m')
			    {
				  Fire();
				  break;
			    }
		       break;
		case 4:for (i=x1+1;i<=9;i++)
			    if ( (tanklist[y][i].state=='e')||(TankFrame->block[y][i]=='b') )
				break;
			    else
			    if (tanklist[y][i].state=='m')
			    {
				  Fire();
				  break;
			    }
		       break;
	};
}

void TImage::Fire(void)
{
	int x1,y1;
	TObject *obj=Application.GetObject(P_Handle());
	x1=pos.left+pos.width-(obj->pos.left+4)-5;
	y1=pos.top+pos.height-(obj->pos.top+21)-5;
	x1/=37;
	y1/=37;
	if (x1==10) x1=9;
	if (y1==10) y1=9;
	switch (state)
	{
		case 1: if (y==0) return;
			bomb = new TBomb(1,pos.left+10,pos.top-2,P_Handle());
			break;
		case 2: if (y1==9) return;
			bomb = new TBomb(2,pos.left+10,pos.top+pos.height+2,P_Handle());
			break;
		case 3: if (x==0) return;
			bomb = new TBomb(3,pos.left-4,pos.top+12,P_Handle());
			break;
		case 4: if (x1==9) return;
			bomb = new TBomb(4,pos.left+pos.width+2,pos.top+12,P_Handle());
			break;
	}
	if (bomb->allowdraw==true)
	{
		bomb->tank=this;
		index++;
	}
	else
	delete bomb;
}