#include "moveobj.h"

TMoveObject::~TMoveObject()
{
	TObject::~TObject();
}

TMoveObject::TMoveObject(EType_Objects t) : TObject(t)
{
	Counter=0;
	Delay=100;
	Destroying=-10;

	Default_Mess=Mess_None;

	Random_Move=0;

	Stop=1;
	Direct=Up_Direct;
}

void TMoveObject::ChangeDirect(EDirection d)
{
if (d==Stop_Direct)
	Stop=1;
else
	{
	Stop=0;
	Direct=d;
	}
}

void TMoveObject::Move()
{
	if (Destroying)
		{
		Destroy();
		if (Destroying==0)
			{
			Clear();
			Show();
			}
		return;
		}
	if (Random_Move)
		if (random(100)>95)
			{
			Direct=EDirection(random(4));
			Stop=random(100)>=95;
			}
	if (Stop)
		return;

	Clear();

	Old_Left=Left;
	Old_Top=Top;

	int Step=2;
	if (Direct==Left_Direct)
		{
		Left=Left-Step;
		}
	else if (Direct==Right_Direct)
		{
		Left=Left+Step;
		}
	else if (Direct==Up_Direct)
		{
		Top=Top-Step;
		}
	else if (Direct==Down_Direct)
		{
		Top=Top+Step;
		}
	Show();
	if (Default_Mess!=Mess_None)
		SendMessage(this, Default_Mess);
}


void TMoveObject::Refresh()
{
if (Counter++>Delay)
	{
	Move();
	Counter=0;
	}
}
