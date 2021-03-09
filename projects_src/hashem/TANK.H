#ifndef __Tank
#define __Tank

#include "basic.h"
#include "shot.h"

class TTank;

struct TListTank
{
	TTank *Data;
	TListTank *Link;
};

class TTank : public TMoveObject
{
protected:
	EMessage TTank::Proccess(TObject *Sender, EMessage Mess);
public:
	static TListTank *All_Tanks;
	int Num_Shot;
	TShot *Shot[5];

	TTank();
	~TTank();
	void Show();
	void Shoot();
	void Refresh();
	void Destroy();
	int IsNear(TObject *Sender, int dis);
};
#endif