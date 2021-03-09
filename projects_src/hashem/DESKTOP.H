#ifndef __Desktop
#define __Desktop

#include <fstream.h>
#include <string.h>
#include <conio.h>
#include <math.h>

#include "tank.h"
#include "things.h"
#include "Board.h"

class TDesktop:public TObject
{
private:
	ifstream lvl_file;
	int Live;
	int Num_Tank;
	int Max_Tank;
	void CreateTank(int=1);
	void Destroy_Tanks();

public:
	TScoreBoard *Board;
	void Destroy_Things();
	TTank *Tank;
	int Level;
	int Delay;
	int Counter;
	int Shooting;

	TDesktop();
	~TDesktop();
	void Show(int NotThings=0);
	void SetLevel(int NoBox=0);
	void SaveLevel();
	int Refresh();
	EMessage Proccess(TObject *Sender, EMessage Mess);
};

#endif