#include "Menu.h"
#include <Conio.h>
#include <string.h>

TMenu::~TMenu()
{
}

TMenu::TMenu()
{
	Left=120;
	Top=100;
	Distance=50;

	CurItem=1;
	strcpy(Items[0],"Start Game");
	strcpy(Items[1],"Set Levels");
	strcpy(Items[2],"Help");
	strcpy(Items[3],"Exit");
}

void TMenu::Show()
{
	int i;

	Flag=new TTank;
	Flag->Random_Move=0;
	Flag->Left=Left;
	Flag->Top=Top+(CurItem-1)*Distance+10;
	Flag->Direct=Right_Direct;
	Flag->Stop=1;
	Flag->Destroying=0;
	Flag->Delay=6000;
	Flag->Show();
	Flag->Color=10;

	settextstyle(10,0,1);
	for (i=0; i<MAXITEM; i++)
		{
		setcolor(4);
		outtextxy(Left+Flag->Width+20+2,Top+i*Distance+2,Items[i]);
		setcolor(12);
		outtextxy(Left+Flag->Width+20+1,Top+i*Distance+1,Items[i]);
		setcolor(14);
		outtextxy(Left+Flag->Width+20,Top+i*Distance,Items[i]);
		}

	rectangle (Left-10,Top-10,Left+400, Top+Distance*MAXITEM+5);

}

int TMenu::Get()
{
	int ck;
	while(1)

		{
		Flag->Show();
		ck=getch();
		if (!ck)	ck=-getch();

		switch(ck)
			{
			case -72:		//Up
				if (CurItem>1)
					{
					Move_Flag(Up_Direct);
					CurItem--;
					}
				break;
			case -80:		//Down
				if (CurItem<MAXITEM)
					{
					Move_Flag(Down_Direct);
					CurItem++;
					}
				break;
			case 13:
				Destroy();
				return CurItem;
			case 27:
				Destroy();
				return 0;
			}

		}
}

void TMenu::Destroy()
{
	delete Flag;
	cleardevice();
}

void TMenu::Move_Flag(EDirection Dir)
{
int nt;
nt=Flag->Top+(Dir==Down_Direct)*2*Distance-Distance;
Flag->Direct=Dir;
Flag->Stop=0;

while(abs(Flag->Top-nt)>1)
	Flag->Refresh();

Flag->Top=nt;
Flag->Stop=1;
Flag->Direct=Right_Direct;
Flag->Clear();
}
