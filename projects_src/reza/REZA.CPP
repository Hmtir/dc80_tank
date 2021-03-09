#include <alloc.h>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <bios.h>
#include <dos.h>
#include "declar.h"
#include "app.h"
#include "app.cpp"
#include "object.cpp"
#include "mouse.cpp"
#include "Window.cpp"
#include "Button.cpp"
#include "Form.cpp"
#include "Taskbar.cpp"
#include "Startmnu.cpp"
#include "quit.cpp"
#include "TPanel.cpp"
#include "TLable.cpp"
#include "TnkFrame.cpp"
#include "TImage.cpp"
#include "TBomb.cpp"
#include "TPBar.cpp"
#include "Form2.cpp"

void main(void)
{
	randomize();
	Application.Run();
}

void Form1_OnKeyPress(int key,int tmp)
{
	char sp;
	bool result=true;
	sp=TankFrame->Image1->speed;
	tmp=tmp;
	if (key==15872) //F4
	{
		if ( (TankFrame->end==true)&&(TankFrame->Image1->visible==true) )
		{
			TankFrame->retry=false;
			TankFrame->StartNextMission();
		}
		if ( (TankFrame->end==true)&&(TankFrame->Image1->visible==false) )
		{
			TankFrame->retry=true;
			TankFrame->StartNextMission();
		}
	}
	if (TankFrame->end==true) return;
	if (key==15360) //F2
	{
		TankFrame->start=true;
		TankFrame->Lable6->SetColor(7);
		return;
	}
	if (key==15616) //F3
	{
		TankFrame->start=false;
		TankFrame->Lable6->parentcolor=7;
		TankFrame->Lable6->SetCaption(" Press F2 For Resume Game ...");
		TankFrame->Lable6->SetColor(0);
		return;
	}
	if (TankFrame->start==false) return;
	switch (key){
		case 18432:sp=TankFrame->SetStep(TankFrame->Image1->speed,TankFrame->Image1->pos,1);   //up
			   if ( TankFrame->CanDo(TankFrame->Image1,1,&sp) == false ) break;
			   if ( (TankFrame->Image1->state!=1)&&(sp!=0) )
			   {
				TankFrame->Image1->Clear();
				position location=TankFrame->SetLocation(1,TankFrame->Image1->state,TankFrame->Image1);
				TankFrame->Image1->pos.left=location.x;
				TankFrame->Image1->pos.top=location.y;
				if (TankFrame->Image1->y!=9)
					TankFrame->Image1->pos.top-=sp;
				TankFrame->Image1->LoadFromFile("image\\uptank.gbf");
				TankFrame->Image1->state=1;
			   }
			   else TankFrame->Image1->Move(-sp,0);
			   break;
		case 20480:sp=TankFrame->SetStep(TankFrame->Image1->speed,TankFrame->Image1->pos,2);   //down
			   if ( TankFrame->CanDo(TankFrame->Image1,2,&sp) == false ) break;
			   if ( (TankFrame->Image1->state!=2)&&(sp!=0) )
			   {
				TankFrame->Image1->Clear();
				position location=TankFrame->SetLocation(2,TankFrame->Image1->state,TankFrame->Image1);
				TankFrame->Image1->pos.left=location.x;
				TankFrame->Image1->pos.top=location.y;
				if (TankFrame->Image1->y!=8)
					TankFrame->Image1->pos.top+=sp;
				TankFrame->Image1->LoadFromFile("image\\downtank.gbf");
				TankFrame->Image1->state=2;
			   }
			   else TankFrame->Image1->Move(sp,0);
			   break;
		case 19200:sp=TankFrame->SetStep(TankFrame->Image1->speed,TankFrame->Image1->pos,3);   //left			   if ( TankFrame->CanDo(TankFrame->Image1,3,&sp) == false ) break;
			   if ( TankFrame->CanDo(TankFrame->Image1,3,&sp) == false ) break;
			   if ( (TankFrame->Image1->state!=3)&&(sp!=0) )
			   {
				TankFrame->Image1->Clear();
				position location=TankFrame->SetLocation(3,TankFrame->Image1->state,TankFrame->Image1);
				TankFrame->Image1->pos.left=location.x;
				TankFrame->Image1->pos.top=location.y;
				if (TankFrame->Image1->x!=0)
					TankFrame->Image1->pos.left-=sp;
				TankFrame->Image1->LoadFromFile("image\\lefttank.gbf");
				TankFrame->Image1->state=3;
			   }
			   else TankFrame->Image1->Move(0,-sp);
			   break;
		case 19712:sp=TankFrame->SetStep(TankFrame->Image1->speed,TankFrame->Image1->pos,4);   //right
			   if ( TankFrame->CanDo(TankFrame->Image1,4,&sp) == false ) break;
			   if ( (TankFrame->Image1->state!=4)&&(sp!=0) )
			   {
				TankFrame->Image1->Clear();
				position location=TankFrame->SetLocation(4,TankFrame->Image1->state,TankFrame->Image1);
				TankFrame->Image1->pos.left=location.x;
				TankFrame->Image1->pos.top=location.y;
				TankFrame->Image1->pos.left+=sp;
				TankFrame->Image1->LoadFromFile("image\\righttank.gbf");
				TankFrame->Image1->state=4;
			   }
			   else TankFrame->Image1->Move(0,sp);
			   break;
		case 14624:if (TankFrame->Image1->index>=0) break;
			   switch (TankFrame->Image1->state)
			   {
				case 1: bomb = new TBomb(1,TankFrame->Image1->pos.left+10,TankFrame->Image1->pos.top-2,TankFrame->Handle());
					if (bomb->allowdraw==false)
						result=false;
					break;
				case 2: //if (TankFrame->Image1->y==9) return;
					bomb = new TBomb(2,TankFrame->Image1->pos.left+10,TankFrame->Image1->pos.top+TankFrame->Image1->pos.height+2,TankFrame->Handle());
					if (bomb->allowdraw==false)
						result=false;
					break;
				case 3: //if (TankFrame->Image1->x==0) return;
					bomb = new TBomb(3,TankFrame->Image1->pos.left-4,TankFrame->Image1->pos.top+12,TankFrame->Handle());
					if (bomb->allowdraw==false)
						result=false;
					break;
				case 4: //if (TankFrame->Image1->x==9) return;
					bomb = new TBomb(4,TankFrame->Image1->pos.left+TankFrame->Image1->pos.width+2,TankFrame->Image1->pos.top+12,TankFrame->Handle());
					if (bomb->allowdraw==false)
						result=false;
					break;
			   }
			   if (result==true)
			   {
				bomb->tank=TankFrame->Image1;
				TankFrame->Image1->index++;
			   }
			   else delete bomb;
			   break;
		case 7777:  for (int i=0;i<=2;i++)
				TankFrame->enemy[i]=NULL;
			   break;
	}
	if (TankFrame->SetTankPos(TankFrame->Image1)==true)
	{
		TankFrame->Image1->pbar->Go(99);
		TankFrame->DestroyTank(TankFrame->Image1);
		TankFrame->EndMission();
	}
}

void Form1_Action(position pos,TObject *Me,TObject *obj)
{
	if (TankFrame->start==false) return;
	for (int i=0;i<=TankFrame->bombindex;i++)
		TankFrame->BombAction(TankFrame->bomblist[i]);
	TankFrame->MoveEnemyTank();
	if ( (TankFrame->end==true)&&(TankFrame->Image1->visible==true) )
	{
		TankFrame->Lable6->SetColor(0);
		TankFrame->Lable6->parentcolor=7;
		TankFrame->Lable6->SetCaption("Press F4 For Start Next Mission");
	}
	if ( (TankFrame->end==true)&&(TankFrame->Image1->visible==false) )
	{
		TankFrame->Lable6->SetColor(0);
		TankFrame->Lable6->parentcolor=7;
		TankFrame->Lable6->SetCaption("Press F4 For Play This Mission");
	}
	pos=pos;
	Me=Me;
	obj=obj;
}

void TestObjSub(position pos,TObject *Me,TObject *obj)
{
	char handle[5];
	TObject *o=Application.GetObject(Application.GetActiveWindow());
	if (o->Handle()!=Me->Handle()) return;
	itoa(obj->Handle(),handle,10);
	if ( strcmp(((TForm2 *)Me)->Lable14->GetCaption(),handle) )
		((TForm2 *)Me)->Lable14->SetCaption(handle);
	if ( strcmp(((TForm2 *)Me)->Lable13->GetCaption(),obj->name) )
		((TForm2 *)Me)->Lable13->SetCaption(obj->name);
	if ( strcmp(((TForm2 *)Me)->Lable15->GetCaption(),obj->classname) )
		((TForm2 *)Me)->Lable15->SetCaption(obj->classname);
	itoa(obj->p_handle,handle,10);
	if ( strcmp(((TForm2 *)Me)->Lable16->GetCaption(),handle) )
		((TForm2 *)Me)->Lable16->SetCaption(handle);
	itoa(obj->pos.left,handle,10);
	if ( strcmp(((TForm2 *)Me)->Lable17->GetCaption(),handle) )
		((TForm2 *)Me)->Lable17->SetCaption(handle);
	itoa(obj->pos.top,handle,10);
	if ( strcmp(((TForm2 *)Me)->Lable18->GetCaption(),handle) )
		((TForm2 *)Me)->Lable18->SetCaption(handle);
	itoa(obj->pos.width,handle,10);
	if ( strcmp(((TForm2 *)Me)->Lable19->GetCaption(),handle) )
		((TForm2 *)Me)->Lable19->SetCaption(handle);
	itoa(obj->pos.height,handle,10);
	if ( strcmp(((TForm2 *)Me)->Lable20->GetCaption(),handle) )
		((TForm2 *)Me)->Lable20->SetCaption(handle);
	itoa(pos.x,handle,10);
	if ( strcmp(((TForm2 *)Me)->Lable21->GetCaption(),handle) )
		((TForm2 *)Me)->Lable21->SetCaption(handle);
	itoa(pos.y,handle,10);
	if ( strcmp(((TForm2 *)Me)->Lable22->GetCaption(),handle) )
		((TForm2 *)Me)->Lable22->SetCaption(handle);

}

void StartMenu(position pos,TObject *obj)
{
	if (pos.key!=1) return;
	if (obj->allowup==false) return;
	SMenu = new Start_Menu(0);
	Application.Hook(SMenu,EV_MOUSEMOVE,StartMenuMouseMove);
	SMenu->OnMouseClick=Start_MenuClick;
	pos=pos;
}

void HideMenu(position pos,TObject *Me,TObject *obj)
{
	if (Me->allowup==true) return;
	if (obj->Handle()==Me->Handle()){
		Application.SetActiveWindow(SMenu);
		return;
	}
	if (obj->Handle()==SMenu->Handle()) return;
	delete SMenu;
	SMenu=NULL;
	pos=pos;
}

void StartMenuMouseMove(position pos,TObject *Me,TObject *obj)
{
	int y,dv,md,*poly,st;
	if (obj->Handle()!=Me->Handle()){
		SMenu->SetMenu();
		SMenu->l_md=SMenu->l_dv=-1;
		return;
	}
	if ((pos.x<29)||(pos.y>452)) return;
	y=pos.y;
	y=453-y;
	md=(y/26);
	dv=(y%26);
	if (md>SMenu->items) {
		SMenu->SetMenu();
		SMenu->l_md=SMenu->l_dv=-1;
		return;
	}
	if (SMenu->l_md==md) return;
	if ((dv>3)&&(dv<=23)) {
		Mouse.hide();
		SMenu->SetMenu();
		setcolor(1);
		if (md==0){
			st=51;
			line(29,453-(md*26)-23,29,453-(((md)*26)+3));
		}
		else st=29;
		poly=fillpol(st,453-(md*26)-23,SMenu->len-2,453-(((md)*26)+3));
		setfillstyle(1,1);
		fillpoly(4,poly);
		free(poly);
		setcolor(15);
		outtextxy(55,453-(md*26)-16,SMenu->Item[md]);
		SMenu->l_md=md;
		SMenu->l_dv=dv;
		SMenu->itemindex=md;
	}
	else{
		SMenu->SetMenu();
		SMenu->l_md=SMenu->l_dv=-1;
	}
	Mouse.show();
}

void Start_MenuClick(position pos,TObject *obj)
{
	if ((pos.x<=24)&&(pos.y>=239)&&(pos.y<=453)) return;
	delete SMenu;
	SMenu=NULL;
	obj=obj;
}

void shoutdown(void)
{
	s = new _ShoutDown(0);
	s->PaintForm(0,7,1);
}

void CloseForm(position pos,TObject *obj)
{
	pos=pos;
	obj=obj;
/*	TObject *obj1;
//	obj1=Application.GetObject(obj->P_Handle());
//	delete (TForm*)obj1;
	pos=pos;*/
}
void Form1_OnStartDrag(TObject *obj)
{
	((TWindow *)obj)->GetPicture();
}