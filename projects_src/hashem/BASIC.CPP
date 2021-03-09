#include <dos.h>
#include <conio.h>
#include "basic.h"

int TObject::Max_Id=0;
TListObject *TObject::All_Objects=NULL;

TObject::TObject(EType_Objects t)
{
	Color=random(15)+1;
	Type=t;
	//Set an Unique Id
	Id=Max_Id++;

	// add this object to link list
	TListObject *tmp;
	tmp=new TListObject;
	tmp->Link=All_Objects;
	tmp->Data=this;
	All_Objects=tmp;

	Left=Top=10;
	//Width=620;
	//Height=450;
	Width=620;
	Height=400;

	Tag=0;
}

TObject::~TObject()
{
	//for don't Destroyinf Object that has been destroied perviously.
	if (Id==-1)
		return;
	Id=-1;
	//Clear();
	//Remove this object from link list
	TListObject *tmp;
	tmp=All_Objects;
	if (tmp->Data==this)
		{
		All_Objects=tmp->Link;
		delete tmp;
		}
	else
		{
		while (tmp->Link)
			{
			//Finding this object in the list
			if (tmp->Link->Data==this)
				{
				//Remove it
				TListObject *tmp2;
				tmp2=tmp->Link;
				tmp->Link=tmp2->Link;
				delete tmp2;
                break;
				}
			tmp=tmp->Link;
			}
		}
}

TObject *TObject::FindObject(int id)
{
	TListObject *tmp;
	tmp=All_Objects;
	while (tmp)
		{
		if (tmp->Data->Id==id)
			return tmp->Data;
		tmp=tmp->Link;
		}
	return NULL;
}

EMessage TObject::SendMessage(TObject *Sender, EMessage Mess, TObject *Receiver)
{
	if (!Receiver)
		{
		EMessage ms;
		TListObject *tmp, *tmp2;
		tmp=All_Objects;
		while (tmp)
			{
			tmp2=tmp->Link;
			ms=tmp->Data->Proccess(Sender, Mess);
			if (ms!=Mess_None)
				  return ms;
			tmp=tmp2;
			}
		return Mess_None;
		}
	return Receiver->Proccess(Sender, Mess);
}

int TObject::HasContact(TObject *Sender)
{
	if (
	   (
			( (Left>=Sender->Left) && (Left<=Sender->Left+Sender->Width) )
		|| 	( (Sender->Left>=Left) && (Sender->Left<=Left+Width) )
	   )
	   &&
	   (
			( (Top>=Sender->Top) && (Top<=Sender->Top+Sender->Height) )
		||  ( (Sender->Top>=Top) && (Sender->Top<=Top+Height) )
	   )
	   )
	   return 1;
	return 0;
}

int TObject::IsIn(TObject *Sender)
{
	if (
	   (
			( (Sender->Left>Left) && (Sender->Left<Left+Width) )
		&& 	( (Sender->Left+Sender->Width>Left) && (Sender->Left+Sender->Width<Left+Width) )
	   )
	   &&
	   (
			( (Sender->Top>Top) && (Sender->Top<Top+Height) )
		&&  ( (Sender->Top+Sender->Height>Top) && (Sender->Top+Sender->Height<Top+Height) )
	   )
	   )
	   return 1;
	return 0;
}

void TObject::Clear()
{
	//viewporttype old;
	//getviewsettings(&old);
	setviewport(Left, Top, Left+Width, Top+Height, 0);
	clearviewport();
	setviewport(0,0,getmaxx(),getmaxy(),0);
	//setviewport(old.left, old.top, old.right, old.bottom, old.clip);
}


int TMessageBox::Show(char *Mess, int Animate)
{
	int i;

	if (Animate)
		{
		setcolor(11);
		for (i=0; i<=Height/2; i++)
			{
			rectangle(Left+Width/2,Top+Height/2-i,Left+Width/2,Top+Height/2+i);
			delay(6);
			}
		for (i=0; i<=Width/2; i++)
			{
			rectangle(Left+Width/2-i,Top,Left+Width/2+i,Top+Height);
			delay(2);
			}
		}

	setcolor(8);
	rectangle(Left+1, Top+1, Left+Width-1, Top+Height-1);
	setcolor(15);
	rectangle(Left, Top, Left+Width, Top+Height);
	setcolor(1);
	settextstyle(7,0,Font_Size);
	outtextxy(Left+Width/2-textwidth(Mess)/2,Top+Height/2-textheight(Mess)/1.5,Mess);
	int ck=0;
	while ((ck=inp(0x60))!=28)  // Until Enter Key Pressed
		if (ck==1) break;
	while (kbhit())
		getch();
	return (ck==28);
}

void TMessageBox::Hide()
{
	setviewport(Left, Top, Left+Width, Top+Height, 0);
	clearviewport();
	setviewport(0,0,getmaxx(),getmaxy(),0);
}

int ShowMessage(char *mess,int font_size)
{
	int r;
	TMessageBox Mess;
	settextstyle(7,0,font_size);
	Mess.Width =textwidth(mess)+20;
	Mess.Height=textheight(mess)+20;
	Mess.Left  =(getmaxx()-Mess.Width)/2;
	Mess.Top   =(getmaxy()-Mess.Height)/2;
	Mess.Font_Size=font_size;
	r=Mess.Show(mess,1);
	Mess.Hide();
	return r;
}