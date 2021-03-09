#include "Shot.h"

TShot::TShot(TObject *p):TMoveObject(Type_Shot)
{
	Radar=0;
	Parent=p;
	Width=4;
	Height=4;
	Random_Move=0;
	Delay=90;
	Stop=1;
	Default_Mess=Mess_ShotPosition;
	Destroying=0;
	Color=14;
}

TShot::~TShot()
{
	TObject::~TObject();
}
void TShot::Show()
{
	setcolor(Color);
	setlinestyle(SOLID_LINE,0,3);
	rectangle(Left+1,Top+1,Left+Width-1,Top+Height-1);
	setlinestyle(SOLID_LINE,0,1);
//	rectangle(Left,Top,Left+Width,Top+Height);
}

EMessage TShot::Proccess(TObject *Sender, EMessage Mess)
{
	switch (Mess)
	{
	case Mess_Explode:
		sound(100);
		delay(5);
		nosound();
		Stop=1;
		Clear();
		break;
	case Mess_Contact:
		Clear();
		SendMessage(this,Mess_Refresh);
		Stop=1;
		return SendMessage(this, Mess_Explode, Sender);
	case Mess_ShotPosition:
		if (!Stop)
			if (HasContact(Sender))
				if (Sender->Parent!=this->Parent)
					{
					SendMessage(this, Mess_Contact, Sender);
					return Mess_NoMove;
					}
		break;
	}
	return Mess_None;
}

void TShot::Refresh()
{
	TMoveObject::Refresh();
}

void TShot::Destroy()
{
	Clear();
	Destroying=0;
}
