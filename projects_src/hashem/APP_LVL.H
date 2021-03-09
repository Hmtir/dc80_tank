#ifndef __App_lvl
#define __App_lvl

#include <stdio.h>

#include "Desktop.h"

class TApp_lvl
{
private:
	TDesktop *Desktop;
public:
	TApp_lvl();
	~TApp_lvl();
	void Initialize();
	void Run();
};

class TCursor:public TObject
{
public:
	TCursor();
	void Show();
	void Hide();
};

#endif