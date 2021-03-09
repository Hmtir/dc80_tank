#ifndef __Menu
#define __Menu

#include "Tank.h"
#define MAXITEM 4

class TMenu
{
private:
	int Distance;
	TTank *Flag;
	void Move_Flag(EDirection Dir);
	void Destroy();
	char Items[MAXITEM][20];
	int CurItem;
public:
	int Left,Top;
	TMenu();
	~TMenu();
	void Show();
	int Get();
};

#endif