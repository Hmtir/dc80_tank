#include "things.h"
#include "tank.h"

TListThings *TThings::All_Things=NULL;

TThings::TThings() : TObject(Type_Things)
{
	Destroying=0;
	Life=1;

	TListThings *tmp;
	tmp=new TListThings;
	tmp->Link=All_Things;
	tmp->Data=this;
	All_Things=tmp;
}

TThings::~TThings()
{
	//Clear();
	SendMessage(this,Mess_Refresh);
	TListThings *tmp;
	tmp=TThings::All_Things;
	if (tmp->Data==this)
		{
		TThings::All_Things=tmp->Link;
		delete tmp;
		}
	else
		{
		while (tmp->Link)
			{
			if (tmp->Link->Data==this)
				{
				TListThings *tmp2;
				tmp2=tmp->Link;
				tmp->Link=tmp2->Link;
				delete tmp2;
				break;
				}
			tmp=tmp->Link;
			}
		}
	TObject::~TObject();
}

void TThings::Show()
{
	Clear();
	if (Destroying>=Life)
		return;
	int color=0;

	if (Type_Thing>Stone)
		{
		if (Life==MAX_THINGS_LIFE)
			SetColor();
		setcolor(Color);
		settextstyle(1,0,2);
		rectangle(Left,Top,Left+Width,Top+Height);
		switch(Type_Thing)
			{
			case Food_NumTank:
				outtextxy(Left+4,Top+2,"NT");
				break;
			case Food_SpeedTank:
				outtextxy(Left+4,Top+2,"ST");
				break;
			case Food_NumShot:
				outtextxy(Left+4,Top+2,"NS");
				break;
			case Food_SpeedShot:
				outtextxy(Left+5,Top+2,"SS");
				break;
			case Food_Radar:
				outtextxy(Left+10,Top+2,"R");
				break;
/*			case Food_EnemyRadar:
				outtextxy(Left+3,Top+2,"ER");
				break;*/
			}
		return;
		}

	if (Type_Thing==Brick)
		{
		color=6;
		}
	else if (Type_Thing==Stone)
		{
		color=15;
		}
	setcolor(color);
	setfillstyle(9,color);
	rectangle(Left,Top,Left+Width,Top+Height);
	floodfill(Left+1,Top+1,color);
	setfillstyle(EMPTY_FILL,1);
	setcolor(0);
	int i;
	srand(100);
	for (i=0; i<Destroying*Width*Height/Life*1.5; i++)
		putpixel(random(Width+1)+Left,random(Height+1)+Top,0);
	//setcolor(0);
	//for (i=0; i<Destroying*Width*Height/Life/5; i++)
	//	circle(random(Width+1)+Left,random(Height+1)+Top,3);
	randomize();
}

void TThings::SetColor()
{
	switch(Type_Thing)
		{
		case Food_NumTank:
			Color=10;
			break;
		case Food_SpeedTank:
			Color=10;
			break;
		case Food_NumShot:
			Color=13;
			break;
		case Food_SpeedShot:
			Color=13;
			break;
		case Food_Radar:
			Color=4;
			break;
		}
		return;

}

EMessage TThings::Proccess(TObject *Sender, EMessage Mess)
{
	switch(Mess)
		{
		case Mess_Explode:
			if (Type_Thing!=Stone)
				if (++Destroying>=Life)
					{
					Clear();
					delete this;
					return Mess_Explode;
					}
			Show();
			SendMessage(this, Mess_Refresh);
			break;
		case Mess_ShotPosition:
			if (HasContact(Sender))
				{
				if (Type_Thing<=Stone)
					return SendMessage(this, Mess_Contact, Sender);
				else
					Show();
				}
			break;
		case Mess_Refresh:
			if ((HasContact(Sender)) && (Sender!=this) )
				Show();
			break;
		case Mess_TankPosition:
			if (HasContact(Sender))
				{
				if (Type_Thing<=Stone)
					{
					SendMessage(this, Mess_Contact, Sender);
					Show();
					SendMessage(this, Mess_Refresh);
					return Mess_NoMove;
					}
				else
					{
					//if ( ((TTank *)Sender)->Random_Move==0)
					//	{
						Clear();
						Tag=((TMoveObject *)Sender)->Random_Move;
						if (Type_Thing==Food_NumTank)
							SendMessage(this, Mess_Food);
						else
							SendMessage(this, Mess_Food,Sender);
						delete this;
						return Mess_Food;
					//	}
					//else
					//	Show();
					}
				}
			break;
		}

	return Mess_None;

}
