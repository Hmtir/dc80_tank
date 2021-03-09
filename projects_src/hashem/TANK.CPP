#include "Tank.h"
#include "Things.h"

int asgn (int a)
{
if (a)
	return (a>0)*2-1;
else
	return 0;
}

TListTank *TTank::All_Tanks=NULL;

TTank::TTank() : TMoveObject(Type_Tank)
{
	Num_Shot=1;
	Left=200;
	Top=200;
	Width=30;
	Height=30;
	Delay=100;
	Color=random(6)+9;
	Destroying=-5;

	Default_Mess=Mess_TankPosition;

	for (int i=0; i<5; i++)
		{
		Shot[i]=new TShot(this);
		//Shot[i]->Delay=100;
		}

	TListTank *tmp;
	tmp=new TListTank;
	tmp->Link=All_Tanks;
	tmp->Data=this;
	All_Tanks=tmp;
}

TTank::~TTank()
{
	for (int i=0; i<Num_Shot; i++)
		if (Shot[i])
			{
			if (!Shot[i]->Stop)
				Shot[i]->Clear();
			delete Shot[i];
			Shot[i]=NULL;
			}

	TListTank *tmp;
	tmp=All_Tanks;
	if (tmp->Data==this)
		{
		All_Tanks=tmp->Link;
		delete tmp;
		}
	else
		{
		while (tmp->Link)
			{
			if (tmp->Link->Data==this)
				{
				TListTank *tmp2;
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


void TTank::Show()
{
if (Destroying)
	return;

int w=5;

if ( (Direct==Up_Direct) || (Direct==Down_Direct) )
	{
	setcolor(Color);
	setfillstyle(5,Color);
	rectangle(Left,Top,Left+Width/w,Top+Height);
	floodfill(Left+1,Top+1,Color);
	rectangle(Left+Width-Width/w,Top,Left+Width,Top+Height);
	floodfill(Left+Width-Width/w+1,Top+1,Color);

	setfillstyle(0,Color);
	//fillellipse(Left+Width/2,Top+Height/2,(Width-2*Width/w)/2,Height/2);
	fillellipse(Left+Width/2,Top+Height/2+((Direct==Up_Direct)*4)-2,(Width-2*Width/w)/2,Height/2-2);
	setfillstyle(9,Color);
	fillellipse(Left+Width/2,Top+Height/2,(Width-2*Width/w)/4,Height/4);

	setlinestyle(SOLID_LINE,0,3);

	//line(Left+Width/2, Top+ ((Direct==Up_Direct)? -Height/4: Height/2 ), Left+Width/2, Top+ ((Direct==Up_Direct)? Height/2: Height+Height/4 ));
	line(Left+Width/2, Top+ ((Direct==Up_Direct)? 0: Height/2 ), Left+Width/2, Top+ ((Direct==Up_Direct)? Height/2: Height ));

	setlinestyle(SOLID_LINE,0,1);
	}
else if ( (Direct==Left_Direct) || (Direct==Right_Direct) )
	{
	setcolor(Color);
	setfillstyle(4,Color);
	rectangle(Left  ,Top  ,Left+Width,Top+Height/w);
	floodfill(Left+1,Top+1,Color);
	rectangle(Left  ,Top+Height-Height/w  ,Left+Width,Top+Height);
	floodfill(Left+1,Top+Height-Height/w+1,Color);

	setfillstyle(0,Color);
	fillellipse(Left+Width/2+((Direct==Left_Direct)*6)-3,Top+Height/2,Width/2-3,(Height-2*Height/w)/2);
	setfillstyle(9,Color);
	fillellipse(Left+Width/2,Top+Height/2,Width/4,(Height-2*Height/w)/4);

	setlinestyle(SOLID_LINE,0,3);

	line(Left+((Direct==Left_Direct)? 0: Width/2 ), Top+Height/2 , Left+((Direct==Left_Direct)? Width/2: Width ), Top+Height/2 );

	setlinestyle(SOLID_LINE,0,1);
	}
}

void TTank::Shoot()
{
for (int i=0; i<Num_Shot; i++)
	if (Shot[i]->Stop)
		{
		Shot[i]->Direct=Direct;
		Shot[i]->Stop=0;

		if (Direct==Right_Direct)
			Shot[i]->Left=Left+Width+1;
		else if (Direct==Left_Direct)
			Shot[i]->Left=Left-Shot[i]->Width-1;
		else
			Shot[i]->Left=Left+Width/2-1;

		if (Direct==Down_Direct)
			Shot[i]->Top=Top+Height+1;
		else if (Direct==Up_Direct)
			Shot[i]->Top=Top-Shot[i]->Width-1;
		else
			Shot[i]->Top=Top+Height/2-1;
		Shot[i]->Show();
		break;
		}
}

void TTank::Refresh()
{
	int i;
	if ((Random_Move) && (Destroying==0))
		if (random(30000)>29995)
			Shoot();

	for (i=0; i<Num_Shot; i++)
		Shot[i]->Refresh();

	TMoveObject::Refresh();
}

EMessage TTank::Proccess(TObject *Sender, EMessage Mess)
{
	int i;
	switch (Mess)
		{
		case Mess_Explode:
			sound(200);
			Stop=1;
			//Random_Move=0;
			//Clear();
			Destroying=1;
			nosound();
			return Mess_Explode;
		case Mess_ShotPosition:
			if (!Destroying)
				{
				if (HasContact(Sender))
					{
					if (((TMoveObject *)Sender->Parent)->Random_Move!=this->Random_Move)
						SendMessage(this, Mess_Contact, Sender);
					else
						Show();
					}
				else
					//if ( ( ((TShot *)Sender)->Radar) && (IsNear(Sender)) )
					if (IsNear(Sender,((TShot *)Sender)->Radar*5))

						if (Random_Move!=((TTank *)Sender->Parent)->Random_Move)
							{
							Sender->Clear();
							if ((((TShot *)Sender)->Direct==Down_Direct) || (((TShot *)Sender)->Direct==Up_Direct))
								Sender->Left+= asgn(Left+Width/2-Sender->Left)*(((TShot *)Sender)->Radar+5)/5;
								//Sender->Left+= asgn(Left+Width/2-Sender->Left)*1;
							else
								Sender->Top+= asgn(Top+Height/2-Sender->Top)*(((TShot *)Sender)->Radar+5)/5;
								//Sender->Top+= asgn(Top+Height/2-Sender->Top)*1;
							((TShot *)Sender)->Show();
							}
				}
			break;
		case Mess_Refresh:
			if ( (HasContact(Sender)) && (Sender!=this) )
				Show();
			break;
		case Mess_Contact:
			Clear();
			SendMessage(this,Mess_Refresh);
			Left=Old_Left;
			Top=Old_Top;
			Stop=1;
			Show();
			break;
		case Mess_TankPosition:
			if (HasContact(Sender))
				if (Sender!=this)
					{
					SendMessage(this, Mess_Contact, Sender);
					Show();
					return Mess_NoMove;
					}
			break;
		case Mess_Born:
			if (HasContact(Sender))
				if (Sender!=this)
					return Mess_Contact;
			break;
		case Mess_Food:
			switch( ((TThings *)Sender)->Type_Thing)
				{
				case Food_SpeedTank:
					if (Delay>15)
						Delay-=5;
					break;
				case Food_NumShot:
					if (Num_Shot<5)
						Num_Shot++;
					break;
				case Food_SpeedShot:
					if (Shot[0]->Delay>=15)
						for (i=0; i<5; i++)
							Shot[i]->Delay-=5;
					break;
				case Food_Radar:
					for (i=0; i<5; i++)
						{
						Shot[i]->Radar++;
						if (Random_Move)
							Shot[i]->Color=12;
						else
							Shot[i]->Color=13;
						}
					break;
				default:
					return Mess_None;
				}
			return Mess_Food;
		}
	return Mess_None;
}

void TTank::Destroy()
{
	Clear();
	setcolor(Color);
	if (Destroying>=Height/4)
		{
		SendMessage(this,Mess_TankExplode);
		delete this;
		return;
		}
	if (Destroying>0)
		ellipse(Left+Width/2, Top+Height/2, 0, 360, Width/4+Destroying, Height/4+Destroying );
	else
		{
		if (SendMessage(this,Mess_Born)==Mess_Contact)
			delete this;
		else
			ellipse(Left+Width/2, Top+Height/2,	0, 360,	Width/2+Destroying/5, Height/2+Destroying/5 );
		}
	Destroying++;
	if (!Destroying)
		SendMessage(this,Mess_TankCreate);
}

int TTank::IsNear(TObject *Sender,int dis)
{
	//int dis=Shot[1]->Radar*30;
	//int dis=30;
	if (
	   (
			( (Left>=Sender->Left-dis) && (Left<=Sender->Left+Sender->Width+dis) )
		|| 	( (Sender->Left>=Left-dis) && (Sender->Left<=Left+Width+dis) )
	   )
	   &&
	   (
			( (Top>=Sender->Top-dis) && (Top<=Sender->Top+Sender->Height+dis) )
		||  ( (Sender->Top>=Top-dis) && (Sender->Top<=Top+Height+dis) )
	   )
	   )
	   return 1;
	return 0;
}

