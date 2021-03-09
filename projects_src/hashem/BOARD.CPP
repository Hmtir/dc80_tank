#include "board.h"
#include "tank.h"

TScoreBoard::~TScoreBoard()
{
	TObject::~TObject();
}

TScoreBoard::TScoreBoard() : TObject(Type_ScoreBoard)
{
	Left=10;
	Top=10;
	Width=620;
	Height=33;
	Color=11;
	Live=0;
	Score=0;
}

void TScoreBoard::Show()
{
	setviewport(Left, Top, Left+Width, Top+Height, 1);
	clearviewport();
	setfillstyle(1,3);
	floodfill(2,2,15);

	setcolor(8);
	//rectangle(Left,Top,Left+Width+1,Top+Height+1);
	rectangle(0,0,Width+1,Height+1);
	setcolor(Color);
	//rectangle(Left-1,Top-1,Left+Width,Top+Height);
	rectangle(0,0,Width,Height);
	settextstyle(1,0,2);
	setcolor(4);
	outtextxy(10,1,"Score :");
	//outtextxy(Left+10,Top+1,"Score :");

	ShowScore(0);
	//ShowLevel("Level 1");
}

void TScoreBoard::ShowTank(int l)
{
	setviewport(Left+210, Top+2, Left+Width-100, Top+Height-2, 1);
	clearviewport();
	setfillstyle(1,3);
	floodfill(2,2,15);
	setviewport(0,0,getmaxx(),getmaxy(),0);

	TTank tmp;
	l--;
	if (l>10) l=10;
	for (int i=0; i<l; i++)
		{
		tmp.Left=Left+Width-i*30-120;
		tmp.Top=Top+7;
		tmp.Width=20;
		tmp.Height=20;
		tmp.Color=11;
		tmp.Destroying=0;
		tmp.Random_Move=1;
		tmp.Show();
		}
}

void TScoreBoard::ShowLevel(char *l)
{
	setviewport(Left+Width-90, Top+3, Left+Width-5, Top+Height-2, 1);
	clearviewport();
	setfillstyle(1,3);
	floodfill(2,2,15);

	settextstyle(8,0,1);
	setcolor(4);
	outtextxy(1,1,l);
	setviewport(0,0,getmaxx(),getmaxy(),0);
}

void TScoreBoard::ShowScore(int tank_score)
{
	Score+=tank_score;
	char s[10]="";
	itoa(Score,s,10);
	setviewport(Left+100, Top+1, Left+200, Top+25, 1);
	clearviewport();
	setfillstyle(1,3);
	floodfill(2,2,15);
	settextstyle(1,0,2);
	setcolor(4);
	outtextxy(1,1,s);
	setviewport(0,0,getmaxx(),getmaxy(),0);
}

