#ifndef __App
#define __App

#include <stdio.h>

#include "Desktop.h"

class TApplication
{
private:
	TDesktop *Desktop;
public:
	TApplication();
	~TApplication();
	void Initialize();
	void Run();
};

#endif