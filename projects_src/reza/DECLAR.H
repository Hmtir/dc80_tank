#define MW_MOUSEMOVE 0x01
#define MW_MOUSECLICK 0x02
#define MW_MOUSEUP 0x03
#define MW_REFRESH 0x04
#define MW_KEYPRESS 0x05


#define EV_MOUSEMOVE 0x01
#define EV_MOUSEUP 0x02
#define EV_MOUSECLICK 0x03
#define EV_TIMER 0x04


typedef int HWND;

typedef struct Rect{
	int top;
	int left;
	int width;
	int height;
};

typedef struct position{
		int x;
		int y;
		int key;
};

typedef struct objectlist{
		class TObject *object;
		int handle;
		objectlist *link;
};

typedef enum bool {false=0,true=1};

typedef struct HookList{
		class TObject *obj;
		void (*OnMouseClick)(position,TObject *,TObject *);
		void (*OnMouseUp)(position,TObject *,TObject *);
		void (*OnMouseMove)(position,TObject *,TObject *);
		HookList *link;
};

typedef	struct zorder{
		class TObject  *object;
		zorder *link;
};

typedef	struct blocktank{
		char state;
		class TImage *tank;
};

char ChCode[26][2]={{'A',30},{'B',48},{'C',46},{'D',32},{'E',18},{'F',33},
		    {'G',34},{'H',35},{'I',23},{'J',36},{'K',37},{'L',38},
		    {'M',50},{'N',49},{'O',24},{'P',25},{'Q',16},{'R',19},
		    {'S',31},{'T',20},{'U',22},{'V',47},{'W',17},{'X',45},
		    {'Y',21},{'Z',44}};

position NullPos;
Rect NullRect;

void WINDOW(int x1,int x2,int y1,int y2,int tcolor,int bkcolor,int style)
{
	Rect pos;
	pos.left=x1;
	pos.width=x2-x1+1;
	pos.top=y1;
	pos.height=y2-y1+1;
	if (style!=1) tcolor=15;
	setcolor(tcolor);
	rectangle(pos.left,pos.top,pos.left+pos.width,pos.top+pos.height);
	setfillstyle(SOLID_FILL,bkcolor);
	floodfill(pos.left+1,pos.top+1,tcolor);
	floodfill(pos.left+1,pos.top+pos.height-1,tcolor);
}

int *fillpol(int x1,int y1,int x2,int y2)
{
	int *poly;
	poly=(int *)malloc(20);
	poly[0]=x1;
	poly[1]=y1;
	poly[2]=x2;
	poly[3]=y1;
	poly[4]=x2;
	poly[5]=y2;
	poly[6]=x1;
	poly[7]=y2;
	poly[8]=x1;
	poly[9]=y1;
	return poly;
}

void box(int *poly,int tcolor,int bcolor,int style)
{
//	setbkcolor(bcolor);
	setcolor(tcolor);
	setfillstyle(style,bcolor);
	fillpoly(4,poly);
	free(poly);
}
