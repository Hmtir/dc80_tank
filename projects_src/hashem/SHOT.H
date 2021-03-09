#ifndef __Shot
#define __Shot

#include <dos.h>

#include "Moveobj.h"

class TShot:public TMoveObject
{
private:

protected:
	EMessage Proccess(TObject *Sender, EMessage Mess);

public:
	int Radar;

	TShot(TObject *p);
	~TShot();
	void Show();
	void Refresh();
	void Destroy();
};

#endif