#include "app.h"

TApplication::TApplication()
{
	Desktop=new TDesktop;
}

TApplication::~TApplication()
{
	delete Desktop;
}

void TApplication::Initialize()
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

void TApplication::Run()
{
	int ck=0,ock;

	Desktop->SetLevel();
	//Desktop->Show();

	while (1)
	{
		ock=ck;
		ck=0;
		ck=inp(0x60);
		if (Desktop->Refresh())
			break;

		if (ck==ock)
			continue;

		while(kbhit())
			getch();

		/*
		asm{
			mov ah,0x0c
			mov al,0
			int 0x21
			}
		*/
		if (ck==1)	//ESC for exit
			if (ShowMessage("Cancel Game ?",3))
				break;
			else
				Desktop->Show();

		switch (ck)
			{
			case 72:
				Desktop->Tank->ChangeDirect(Up_Direct);
				break;
			case 80:
				Desktop->Tank->ChangeDirect(Down_Direct);
				break;
			case 77:
				Desktop->Tank->ChangeDirect(Right_Direct);
				break;
			case 75:
				Desktop->Tank->ChangeDirect(Left_Direct);
				break;
			case 170:
			case 205:
			case 200:
			case 203:
			case 208:
				Desktop->Tank->ChangeDirect(Stop_Direct);
				break;
			case 57:		//Space
				Desktop->Shooting=1;
				break;
			case 185:
				Desktop->Shooting=0;
				break;
			}
	}
}
