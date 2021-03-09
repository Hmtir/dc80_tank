void TMouse::TMouse(void)
{
	pos=MousePos();
	asm{
		pusha
		pushf
		mov ax,0
		int 33h
		popf
		popa
	}
}
void TMouse::show(void)
{

	asm{
		pusha
		pushf
		mov ax,1
		int 33h
		popf
		popa
	}
}
void TMouse::hide(void){
	asm{
		pusha
		pushf
		mov ax,2
		int 33h
		popf
		popa
	}
}

position TMouse::MousePos(void)
{
	position p;
	int b,c,d;
	asm{
		pusha
		pushf
		mov ax,03h
		int 33h
		mov b,bx
		mov c,cx
		mov d,dx
		popf
		popa
	}
	p.key=b;
	p.x=c;
	p.y=d;
	if (b==1){
		d=d;
	}
	pos=p;
	return p;
}

void TMouse::MouseMove(void)
{
	static char x[4],y[4],na[30],*r="Right click",*n="No click",*l="Left clcik",d;
	position p;
	p=Mouse.MousePos();
	if ((pos.x==p.x)&&(pos.y==p.y)&&(pos.key==p.key)) return ;
	setcolor(DeskTop->backcolor);
	switch (d) {
	       case 	0:outtextxy(100,5,n);
		  break;
	       case 	2:outtextxy(100,5,r);
		  break;
	       case	1:outtextxy(100,5,l);
	};
	outtextxy(300,5,na);
	outtextxy(0,5,x);
	outtextxy(50,5,y);
	itoa(p.x,x,10);
	itoa(p.y,y,10);
	setcolor(0);
	outtextxy(0,5,x);
	outtextxy(50,5,y);
	d=p.key;
	switch (d){
	       case 	0:outtextxy(100,5,n);
		  break;
	       case 	2:outtextxy(100,5,r);
		  break;
	       case	1:outtextxy(100,5,l);
	};
	pos=p;
////////////////////////////////////////////////////
	zorder *t;
	int x1,y1,x2,y2;
	TObject *cl;
	t=Application.start;
	while (t!=NULL)
	{
		cl=t->object;
		x1=(cl->pos.left);
		x2=(cl->pos.left+cl->pos.width);
		y1=(cl->pos.top);
		y2=(cl->pos.top+cl->pos.height);
		if (((x1<=p.x)&&(x2>=p.x))&&
		   (y1<=p.y)&&(y2>=p.y))
		    {
			   outtextxy(300,5,cl->name);
			   strcpy(na,cl->name);
			   break;
		     }
		t=t->link;
	}
/////////////////////////////////////////////////////
}

void TMouse::SetMousePos(int x,int y)
{
	asm{
		pusha
		pushf
		mov ax,04h
		mov cx,x
		mov dx,y
		int 33h
		popf
		popa
	}
}

bool TMouse::OnWindow(TObject *obj)
{
	position pos;
	pos=MousePos();
	if ( (pos.x>=obj->pos.left)&&(pos.x<=obj->pos.left+obj->pos.width)
	   &&(pos.y>=obj->pos.top)&&(pos.y<=obj->pos.top+obj->pos.height) )
		return true;
	else
		return false;
}