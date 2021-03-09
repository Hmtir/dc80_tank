#include "Desktop.h"

TDesktop::~TDesktop()
{
	delete Board;
	Destroy_Tanks();
	Destroy_Things();
	TObject::~TObject();
}

TDesktop::TDesktop():TObject(Type_Desktop)
{
	Delay=50;
	Shooting=0;
	Num_Tank=0;
	Max_Tank=15;
	Level=1;
	Live=3;

	Color=15;
	Left=9;
	Top=50;
	Width=622;
	Height=420;

	Board=new TScoreBoard;

	CreateTank();
}

void TDesktop::Show(int NotThings)
{
	//setviewport(0,0,getmaxx(),getmaxy(),0);

/*	if (!NotThings)
		{
		cleardevice();
		setfillstyle(9,4);
		floodfill(320,200,4);
		setfillstyle(0,0);
		Clear();
		}*/
/*	setcolor(8);
	rectangle(Left,Top,Left+Width,Top+Height);
	setcolor(Color);
	rectangle(Left-1,Top-1,Left+Width+1,Top+Height+1);
	*/

	setcolor(8);
	rectangle(Left,Top,Left+Width+1,Top+Height+1);
	setcolor(Color);
	rectangle(Left-1,Top-1,Left+Width,Top+Height);

	//setviewport(Left,Top,Left+Width,Top+Height,0);

	TListThings *tmp;
	tmp=TThings::All_Things;
	if (!NotThings)
		{
		while(tmp)
			{
			tmp->Data->Show();
			tmp=tmp->Link;
			}
		Board->Show();
		Board->ShowTank(Live);
		}
	Tank->Show();
}

void TDesktop::SetLevel(int NoBox)
{
	char levelname[4]="";
	char filename[10]="";
	itoa(Level,levelname,10);
	strcpy(filename,levelname);
	strcpy(filename,strcat(filename,".lvl"));

	Num_Tank=0;

	lvl_file.open(filename);
	if (!lvl_file)
		{
		Level=1;
		strcpy(filename,"1.lvl");
		lvl_file.open(filename);
		if (!lvl_file)
			exit(1);
		itoa(Level,levelname,10);
		}

	Clear();

	char mess[20]="Level ";
	strcat(mess,levelname);

	if (!NoBox)
		ShowMessage(mess,5);

	Destroy_Things();

	CreateTank(0);

	do
		{
		int a;
		int x,y,w,h,l;
		lvl_file >> a;
		if (lvl_file.eof())
			break;
		lvl_file >> x >> y;
		lvl_file >> w >> h;
		lvl_file >> l;

		TThings *tmp;
		tmp=new TThings;

		tmp->Type_Thing=EType_Things(a);
		tmp->Left=x;
		tmp->Top=y;
		tmp->Width=w;
		tmp->Height=h;
		tmp->Life=l;

		} while (!lvl_file.eof());
	lvl_file.close();
	Show();
	Board->ShowLevel(mess);
}

int TDesktop::Refresh()
{
static long int tc=0,tc2=0;
static pos=600;

if (Counter++>Delay)
	{
	if (Live<=0)
		{
		ShowMessage("Game Over",3);
		return 1;  // Means Game Over
		}

	int Tank_Count=0;

	if (Shooting)
		{
		if ( (tc2--<=0) || ( (Tank->Shot[0]->Stop) && (tc2/Tank->Num_Shot/20<=50)) )
			{
			Tank->Shoot();
			tc2=Tank->Shot[0]->Delay*70+20*Tank->Num_Shot;
			if (tc2<0)	tc2=10000000;
			}
		}
	else
		tc2=0;

	TListTank *tmp,*tmp2;
	tmp=Tank->All_Tanks;
	while(tmp)
		{
		Tank_Count++;
		tmp2=tmp->Link;
		tmp->Data->Refresh();
		tmp=tmp2;
		}

	TListThings *tmp3,*tmp4;
	tmp3=TThings::All_Things;
	while(tmp3)
		{
		tmp4=tmp3->Link;
		if (tmp3->Data->Type_Thing>Stone)
			{
			tmp3->Data->Life--;
			if (!tmp3->Data->Life)
				{
				tmp3->Data->Clear();
				delete tmp3->Data;
				//Show();
				}
			}
		tmp3=tmp4;
		}

/*	if ( (random(1000)>998) && (random(1000)>998) && !((Tank_Count==1) && (Num_Tank>=Max_Tank) ))
		{
		TThings *tmp;
		tmp=new TThings;

		tmp->Type_Thing=EType_Things(random(NUM_FOOD)+3);
		tmp->Width=30;
		tmp->Height=30;
		tmp->Left=random(Width-1-tmp->Width)+Left+1;
		tmp->Top=random(Height-1-tmp->Height)+Top+1;
		tmp->Life=MAX_THINGS_LIFE;
		tmp->Show();
		}
*/
	Counter=0;
	if ( (Num_Tank<Max_Tank) && (tc--<=0) )
		{
		TTank *tmp;
		tmp=new TTank;
		tmp->Random_Move=1;
		pos=pos>500 ? 50: pos+250;
		tmp->Left=pos;
		tmp->Top=Top+2;
		tmp->Direct=EDirection(random(4));
		tmp->Stop=random(100)>=95;
		tmp->Delay=random(100)+50-Level*5;
		if (tmp->Delay<15) tmp->Delay=15;
		tmp->Num_Shot=log(random(100)+Level*1);
		if (tmp->Num_Shot>5) tmp->Num_Shot=5;
		tmp->Tag=tmp->Num_Shot*1000/tmp->Delay;	//Score of this tank

		for (int i=0; i<tmp->Num_Shot; i++)
			{
			tmp->Shot[i]->Delay=tmp->Delay/1.4;
			tmp->Shot[i]->Color=tmp->Color;
			}
		tc=30000;
		}
	if ( (Tank_Count==1) && (Num_Tank>=Max_Tank) )
		{
		if (tc++>40000)
			{
			Level++;
			SetLevel();
			tc=0;
			}
		if (tc==0)
			Shooting=0;
		return 0;
		}

	}
return 0;
}

EMessage TDesktop::Proccess(TObject *Sender, EMessage Mess)
{
	switch(Mess)
		{
		case Mess_ShotPosition:
			if (!IsIn(Sender))
				{
				SendMessage(this, Mess_Contact, Sender);
				( (TMoveObject *)Sender)->Stop=1;
				//if (!HasContact(Sender))
				//	Show();
				//else
					Show(1);
				}
			break;
		case Mess_TankPosition:
			if (!IsIn(Sender))
				{
				SendMessage(this, Mess_Contact, Sender);
				Show(1);
				return Mess_NoMove;
				}
			break;
		case Mess_TankCreate:
			if (((TMoveObject *)Sender)->Random_Move)
				Num_Tank++;
			return Mess_EnemyBorn;

		case Mess_TankExplode:
			if (((TMoveObject *)Sender)->Random_Move)
				{
				Board->ShowScore(Sender->Tag);
				int r=Level;
				r*=10;
				if (r>80) r=80;
				if (random(100)>r)
				{
					TThings *tmp;
					tmp=new TThings;

					tmp->Type_Thing=EType_Things(random(NUM_FOOD)+3);
					tmp->Width=30;
					tmp->Height=30;
					tmp->Left=random(Width-1-tmp->Width)+Left+1;
					tmp->Top=random(Height-1-tmp->Height)+Top+1;
					tmp->Life=MAX_THINGS_LIFE;
					tmp->Show();
				}
				}
			else
				{
				Live--;
				Board->ShowTank(Live);
				CreateTank();
				}
			return Mess_GetScore;
		case Mess_Food:
			switch( ((TThings *)Sender)->Type_Thing)
				{
				case Food_NumTank:
					if (Sender->Tag==0)
						{
						Live++;
						Board->ShowTank(Live);
						}
					else
						{
						Max_Tank++;
						}
					break;
				}
			return Mess_Food;
		}

	return Mess_None;
}

void TDesktop::CreateTank(int Create)
{
	int i;
	if (Live<=0)
		return;
	if (Create)
		{
		Tank=new TTank;
		Tank->Delay=70;
		Tank->Color=11;
		for (i=0; i<5; i++)
			{
			Tank->Shot[i]->Delay=40;
			Tank->Shot[i]->Color=Tank->Color;
			}
		}
	Tank->Left=320-Tank->Width/2;
	Tank->Top=Top+Height-Tank->Width-5;
	Tank->Stop=1;
    Shooting=0;
	for (i=0; i<5; i++)
		Tank->Shot[i]->Stop=1;
}

void TDesktop::SaveLevel()
{
	ofstream lvl_file;
	char levelname[4]="";
	char filename[10]="";
	itoa(Level,levelname,10);
	strcpy(filename,levelname);
	strcpy(filename,strcat(filename,".lvl"));

	Num_Tank=0;

	lvl_file.open(filename);

	TListThings *tmp,*tmp2;
	tmp=TThings::All_Things;
	while(tmp)
		{
		tmp2=tmp->Link;
		lvl_file << tmp->Data->Type_Thing << "\t";
		lvl_file << tmp->Data->Left << "\t";
		lvl_file << tmp->Data->Top << "\t";
		lvl_file << tmp->Data->Width << "\t";
		lvl_file << tmp->Data->Height << "\t";
		lvl_file << tmp->Data->Life << "\n";
		tmp=tmp2;
		}
}

void TDesktop::Destroy_Things()
{
	TListThings *tmp,*tmp2;
	tmp=TThings::All_Things;
	while(tmp)
		{
		tmp2=tmp->Link;
		delete tmp->Data;
		tmp=tmp2;
		}
	TThings::All_Things=NULL;
}

void TDesktop::Destroy_Tanks()
{
	TListTank *tmp,*tmp2;
	tmp=TTank::All_Tanks;
	while(tmp)
		{
		tmp2=tmp->Link;
		delete tmp->Data;
		tmp=tmp2;
		}
	TTank::All_Tanks=NULL;
}