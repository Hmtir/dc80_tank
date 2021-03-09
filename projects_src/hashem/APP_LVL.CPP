#include <dir.h>

#include "app_lvl.h"
#include "Things.h"

TApp_lvl::TApp_lvl()
{
	Desktop=new TDesktop;
}
TApp_lvl::~TApp_lvl()
{
	delete Desktop;
}

void TApp_lvl::Initialize()
{
   int gdriver = VGA, gmode=2, errorcode;
   initgraph(&gdriver, &gmode, "\\language\\bc3_1\\bgi");
   errorcode = graphresult();

   if (errorcode != grOk)  /* an error occurred */
   {
	  printf("Graphics error: %s\n", grapherrormsg(errorcode));
	  printf("Press any key to halt:");
	  exit(1);             /* return with error code */
   }
   randomize();
   setbkcolor(1);
}

void TApp_lvl::Run()
{
	int ck=0;

	TThings *tmp;
	TListThings *tmp_t;

	Desktop->SetLevel(1);
	TCursor Cursor;
	Cursor.Color=12;

	while (1)
		{
		Cursor.Show();
		ck=getch();
		if (!ck)
			ck=-getch();
		Cursor.Hide();

		tmp_t=TThings::All_Things;
		while(tmp_t)
			{
			if (Cursor.HasContact(tmp_t->Data))
				tmp_t->Data->Show();
			tmp_t=tmp_t->Link;
			}

		switch(ck)
			{
			case 43:		//+
				if (Cursor.Left+Cursor.Width+1<Desktop->Left+Desktop->Width)
					Cursor.Width++;
				break;
			case -144:		//Ctrl +
				if (Cursor.Top+Cursor.Height+1<Desktop->Top+Desktop->Height)
					Cursor.Height++;
				break;
			case 45:		//-
				if (Cursor.Width>1)
					Cursor.Width--;
				break;
			case -142:		//Ctrl -
				if (Cursor.Height>1)
					Cursor.Height--;
				break;

			case 27:
				if (ShowMessage("Are You Want To Exit ?",2))
					return;
				Desktop->Show();
				break;
			case -141:		//Ctrl+Up
				if (Cursor.Top-1>Desktop->Top)
					Cursor.Top-=1;
				break;
			case -145:		//Ctrl+Down
				if (Cursor.Top+Cursor.Height+1<Desktop->Top+Desktop->Height)
					Cursor.Top+=1;
				break;
			case -116:		//Ctrl+Right
				if (Cursor.Left+Cursor.Width+1<Desktop->Left+Desktop->Width)
					Cursor.Left+=1;
				break;
			case -115:		//Ctrl+Left
				if (Cursor.Left>Desktop->Left)
					Cursor.Left-=1;
				break;
			case -72:		//Up
				if (Cursor.Top-Cursor.Height>Desktop->Top)
					Cursor.Top-=Cursor.Height+1;
				break;
			case -80:		//Down
				if (Cursor.Top+2*Cursor.Height<Desktop->Top+Desktop->Height)
					Cursor.Top+=Cursor.Height+1;
				break;
			case -77:		//Right
				if (Cursor.Left+2*Cursor.Width<Desktop->Left+Desktop->Width)
					Cursor.Left+=Cursor.Width+1;
				break;
			case -75:		//Left
				if (Cursor.Left-Cursor.Width>Desktop->Left)
					Cursor.Left-=Cursor.Width+1;
				break;
			case -83:		//Del -->  Remove things
				tmp_t=TThings::All_Things;
				while(tmp_t)
					{
					if (Cursor.HasContact(tmp_t->Data))
						{
						tmp_t->Data->Clear();
						delete tmp_t->Data;
						break;
						}
					tmp_t=tmp_t->Link;
					}
				break;
			case -60:		//F2  -->  Save
				Desktop->SaveLevel();
				break;
			case -63:       //F5  -->  Refresh
				cleardevice();
				Desktop->Show();
				break;
			case 32:
				Cursor.Color=(Cursor.Color==7) ? 12 : 7;
				break;
			case 13:
				tmp_t=TThings::All_Things;
				while(tmp_t)
					{
					if (Cursor.HasContact(tmp_t->Data))
						{
						tmp_t->Data->Life++;
						break;
						}
					tmp_t=tmp_t->Link;
					}
				if (!tmp_t)
					{
					tmp= new TThings;
					tmp->Left=Cursor.Left;
					tmp->Top=Cursor.Top;
					tmp->Width=Cursor.Width;
					tmp->Height=Cursor.Height;
					tmp->Type_Thing=(Cursor.Color==7) ? Stone : Brick;
					tmp->Life=1;
					tmp->Show();
					}
				break;
			case -73:		//Page Up
				if (Desktop->Level>1)
					{
					Desktop->Level--;
					Desktop->SetLevel();
					}
				break;
			case -81:		//Page Down
				Desktop->Level++;
				Desktop->SetLevel();
				break;
			case -146:		//Ctrl + Ins  --> New Level
				//Find Last Level
				{
				char filename[10]="";
				struct ffblk ffblk;
				itoa(Desktop->Level,filename,10);
				strcpy(filename,strcat(filename,".lvl"));
				while (!findfirst(filename,&ffblk,0))
					{
					Desktop->Level++;
					itoa(Desktop->Level,filename,10);
					strcpy(filename,strcat(filename,".lvl"));
					}
				Desktop->Destroy_Things();
				Desktop->Clear();
				Desktop->Show();
				itoa(Desktop->Level,filename,10);
				char mess[20]="New ";
				strcat(mess,filename);
				Desktop->Board->ShowLevel(mess);
				break;
				}

			//default:
			//	printf("%d",ck);
			}
		}
}


void TCursor::TCursor() : TObject(Type_Cursor)
{
	Width=19;
	Height=9;
	Left=309;
	Top=220;
	Color=14;
}

void TCursor::Show()
{
	setcolor(Color);
	rectangle(Left,Top,Left+Width,Top+Height);
}

void TCursor::Hide()
{
	setcolor(0);
	rectangle(Left,Top,Left+Width,Top+Height);
}

