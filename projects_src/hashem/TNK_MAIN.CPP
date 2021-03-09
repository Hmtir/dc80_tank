#include "app.h"
#include "app_lvl.h"
#include "menu.h"

void splash()
{
	int i;
	setbkcolor(3);
	setcolor(9);
	settextstyle(10,0,7);
/*	float t,x=0,y=0;
	for (t=-3.1415; t<0; t+=.05)
		{
		x=cos(t)*t*50;
		y=sin(t)*t*50;
		setcolor(12);
		outtextxy(213+x,83+y,"Tank");
		delay(1);
		setcolor(11);
		outtextxy(213+x,83+y,"Tank");
		}*/
//    cleardevice();
 //	setcolor(3);
//	outtextxy(211,81,"Tank");
	setcolor(8);
	outtextxy(211,81,"Tank");
	setcolor(10);
	outtextxy(210,80,"Tank");

	setcolor(4);
	settextstyle(5,0,1);
	outtextxy(234,230,"CopyRight (C) 2002");
	settextstyle(6,0,1);
	outtextxy(252,260,"By Hashem Tatari");
	settextstyle(0,0,1);
	outtextxy(180,300,"Shahid Bahonar University of Kerman");


	setcolor(14);
	for (i=0; i<220; i++)
		{
		circle(210+i,100,2);
		circle(430-i,220,2);
		delay(4);
		}

	TTank Tank;
	Tank.Left=560;
	Tank.Top=380;
	Tank.Color=14;
	Tank.Destroying=0;
	Tank.Random_Move=0;
	Tank.Delay=500;
	Tank.ChangeDirect(Left_Direct);
	Tank.Show();

	while (!kbhit())
		{
		Tank.Refresh();
		if (Tank.Left<40)
			Tank.Direct=Right_Direct;
		else if (Tank.Left>560)
			Tank.Direct=Left_Direct;
		}
	while (kbhit())
		getch();

	setcolor(1);
	setfillstyle(1,1);
/*	for (i=0; i<1000; i++)
		{
		circle(random(640),random(480),1);
		fillellipse(random(640),random(480),5,5);
		//delay(1);
		}
*/
	setbkcolor(1);
}

void showhelp()
{
	char mess[ 7][80]={"Brick       : You can Destroy this Object by shooting to it.",
					   "Stone       : You can't Destroy this Object.",
					   "Num Tank    : Get more tank.",
					   "Speed Tank  : Increase tank speed.",
					   "Num Shot    : Get more shot",
					   "Speed Shot  : Increase shot speed.",
					   "Radar       : Tank's Shot can follow enemy tank."
					   };
	int i;

	TThings tmp1;
	tmp1.Left=50;
	tmp1.Width=30;
	tmp1.Height=30;
	tmp1.Color=14;

	for (i=1; i<=NUM_FOOD+2; i++)
		{
		tmp1.Type_Thing=EType_Things(i);
		tmp1.Top=i*50;
		tmp1.Show();
		settextstyle(2,0,5);
		setcolor(15);
		outtextxy(110,i*50+7,mess[i-1]);
		//outtextxy(200,i*50+20,"lkjkl");
		}

    setcolor(10);
	rectangle(40,40,580,400);
	setcolor(13);
	outtextxy(40,400,"Press any key to see next page...");
	setcolor(12);
	settextstyle(4,1,1);
	outtextxy(580,280,"Hashem Tatari");

	getch();
	cleardevice();

	settextstyle(2,0,5);
	setcolor(15);
	outtextxy(50,50,"The keys that used in the game are:");
	outtextxy(80,70,"Move Tank : Up ,Down ,Left ,Right ");
	outtextxy(80,90,"Shoot     : Space");
	outtextxy(50,140,"The keys that used in the Set Level:");
	outtextxy(80,160,"Move Cursor  : Up ,Down ,Left ,Right ");
	outtextxy(80,180,"Move 1 pixel : Ctrl Up ,Ctrl Down ,Ctrl Left ,Ctrl Right ");
	outtextxy(80,200,"Cursor Size  : +  , -   ,Ctrl +  ,Ctrl -");
	outtextxy(80,220,"Stone/Brick  : Space");
	outtextxy(80,240,"Put thing    : Enter");
	outtextxy(80,260,"Delete thing : Del");
	outtextxy(80,280,"Change Level : Page Up ,Page Down");
	outtextxy(80,300,"New Level    : Ctrl Ins");
	outtextxy(80,320,"Save Level   : F2");
	outtextxy(80,340,"Exit         : ESC");

	setcolor(10);
	rectangle(40,40,580,400);
	line(50,120,550,120);
	setcolor(13);
	outtextxy(40,400,"Press any key to continue...");
	setcolor(12);
	settextstyle(4,1,1);
	outtextxy(580,280,"Hashem Tatari");

	getch();

}

void Initialize()
{
   int gdriver = VGA, gmode=2, errorcode;
   initgraph(&gdriver, &gmode, "");
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

void main()
{
	TMenu *Menu;
	Menu =new TMenu;

	TApplication *App;
	TApp_lvl *App_lvl;

	Initialize();

	splash();

	int m=1;

	while ((m!=0) && (m!=4))
		{
		while (kbhit())
			getch();
		cleardevice();
		Menu->Show();
		m=Menu->Get();
		switch(m)
			{
			case 1:
				App=new TApplication;
				App->Run();
				delete App;
				break;
			case 2:
				App_lvl=new TApp_lvl;
				App_lvl->Run();
				delete App_lvl;
				break;
			case 3:
				showhelp();
				break;
			}
		}
	delete Menu;
    closegraph();

}
