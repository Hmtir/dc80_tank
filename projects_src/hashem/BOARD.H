#ifndef __ScoreBoard
#define __ScoreBoard

#include "Basic.h"


class TScoreBoard:public TObject
{
private:
	int Score;

public:
	int Live;
	TScoreBoard();
	~TScoreBoard();
	void ShowLevel(char *);
	void ShowScore(int s);
	void ShowTank(int l);
	void Show();
};

#endif