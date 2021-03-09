#ifndef __Basic
#define __Basic

#include <graphics.h>
#include <stdlib.h>

enum EMessage {	Mess_None
			   ,Mess_Destroy
			   ,Mess_Contact
			   ,Mess_Explode
			   ,Mess_ShotPosition
			   ,Mess_TankPosition
			   ,Mess_Born
			   ,Mess_NoMove
			   ,Mess_ShowLevel
			   ,Mess_GetScore
			   ,Mess_EnemyBorn
			   ,Mess_TankCreate
			   ,Mess_TankExplode
			   ,Mess_Food
			   ,Mess_FoodExplode
			   ,Mess_Refresh
			   };
enum EType_Objects {Type_Desktop
				   ,Type_Tank
				   ,Type_Shot
				   ,Type_Things
				   ,Type_ScoreBoard
				   ,Type_Cursor
					};

class TObject;

struct TListObject
{
	TObject *Data;
	TListObject *Link;
};

class TObject
{
private:
	static int Max_Id;
	int Id;
	EType_Objects Type;
	static TListObject *All_Objects;

protected:
	TObject *FindObject(int id);
	virtual EMessage Proccess(TObject *Sender, EMessage Mess){return Mess_None;};

public:
	int Color;
	int Tag;

	TObject *Parent;
	int Left,Top,Width,Height;
	TObject(EType_Objects t);
	~TObject();
	EMessage SendMessage(TObject *Sender, EMessage Mess, TObject *Receiver=NULL);
	int HasContact(TObject *Sender);
	int IsIn(TObject *Sender);
	void Clear();
};

class TMessageBox
{
public:
	int Left,Top,Width,Height;
	int Show(char *, int);
	int Font_Size;
	void Hide();
};

int ShowMessage(char *,int);

#endif