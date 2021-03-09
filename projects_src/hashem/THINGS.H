#ifndef __Things
#define __Things

#include "Basic.h"

#define NUM_FOOD 5
#define MAX_THINGS_LIFE 32000

//enum EType_Things {None=0, Brick=1, Stone=2, Food_NumTank=9, Food_SpeedTank=10, Food_NumShot=15, Food_SpeedShot=13, Food_Radar=12, Food_EnemyRadar=4};
enum EType_Things {None=0, Brick=1, Stone=2, Food_NumTank, Food_SpeedTank, Food_NumShot, Food_SpeedShot, Food_Radar, Food_EnemyRadar};

class TThings;

struct TListThings
{
	TThings *Data;
	TListThings *Link;
};

class TThings:public TObject
{
private:
	int Destroying;
	void SetColor();
protected:
public:
	int Life;
	static TListThings *All_Things;
	TThings();
	~TThings();
	EType_Things Type_Thing;
	void Show();
	EMessage Proccess(TObject *Sender, EMessage Mess);
};

#endif