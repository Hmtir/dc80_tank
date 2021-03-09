#ifndef __MoveObject
#define __MoveObject

#include "Basic.h"

enum EDirection {Up_Direct, Down_Direct, Left_Direct, Right_Direct ,Stop_Direct};

class TMoveObject:public TObject
{
private:
	int Counter;
protected:
	int Old_Left,Old_Top;
	EMessage Default_Mess;
public:
	EDirection Direct;
	int Stop;
	int Delay;
	int Random_Move;
	int Destroying;

	TMoveObject(EType_Objects t);
	~TMoveObject();
	void ChangeDirect(EDirection d);
	void Move();
	void Refresh();
	virtual void Show()=0;
	virtual void Destroy()=0;
};

#endif