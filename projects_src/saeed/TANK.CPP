#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <dos.h>
#include <bios.h>

#pragma warn -aus

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
#define    T_C      4
#define    WAY_W    34
#define    WAY_H    37
#define    TANK_HEIGHT WAY_H -7
#define    TANK_WIDTH  WAY_W -4

#define    LEVEL_SPEED_VAR   4
#define    TIMEOUT     150
#define    MOVE_PIXEL  4
#define    GRID_X 34
#define    GRID_Y 37
#define    TIR_SPEED  40
//**********************************************
typedef struct{
    char stat;
    char no;

} scr_stat;

//*************************************
int box_3d(int x1,int y1,int w,int h,int style=1,int color=7);
int box(int x1,int y1,int w,int h,int style,int color);

//**************************************
class link_list;
//***************************************
class menu{
private:
  int items;
public:
  int x,y,w,h,color;
  menu(int,int,int,int,int);
  void draw(void);
  void erase(void){box(x,y,w,h,0,1);};
};


//******************************************
class tir{
private:
  //static int counter;
public:
  char set_mask;
  char reset_mask;

  int handle;
  int speed;
  int x_pos,y_pos;
  int arrx_pos,arry_pos;
  int dir;
  int parent_tank_handle;

  class board *scr;

  //friend board;
  tir(board *,int,int,int,int);
  ~tir(void){erase();};
  void explode(void);
  void moveto(int ,int );
  void erase(void);
  void draw(void);
  void action(void);
};

//**************************************
class board{
  private:

  public:
      //int status[15][19];
      int  tir_counter,tank_counter;
      int  cur_level;
      int  colors[10];

      int tank_x,tank_y;
      scr_stat status[15][19];
      int key,key_stat;

      board(void);
      void set_pos_stat(class tank *,int,int);
      scr_stat get_pos_stat(int,int);
      int get_key(int);
      void draw(int color);
      void init(int);
      void sort_on_speed(void);
      void game_over(void);

      int con_x2arr(int );
      int con_y2arr(int );
      int is_cross(int,int);
      //int next_step_stat(class tank *,int ,int &,int &,int );
      scr_stat next_step_stat(class tank *,int ,int &,int &,int );
//      scr_stat next_step_stat(class tir *,int ,int &,int &,int );

      class tank *que[T_C];
      //friend class link_list;
      class link_list *tir_list;
      friend tir;
};
//********************************************
class link_list{
private:
   class node *root;
   class node *end;
public:
   link_list(void);

   void reset(void){current_node=root;};
   class node *current_node;

   class tir *find(int key);
   void add(class tir *);
   class tir *del(int key);
   class tir *next_tir(void);
   void erase_list(void);
};

//*******************************************
class tank{
protected:
     int w_style;//for whills
     //define tank color
     int color_set[5][6];
//     int step,wait;
  public:
     char set_mask;
     char reset_mask;

     int x_pos,arrx_pos;
     int y_pos,arry_pos;
     int width,height;
     int dir;
     int handle;
     class board *screen;
     int active_color;
     int tank_style;
     int speed;
     int tir_qty,max_tir_qty;
     int active;

     tank(class board *,int ,int ,int);
     int get_x(void);
     int get_y(void);
     int can_turn(int);
     void draw(void);
     void erase(void);
     void moveto(int x,int y);
     void fire(void);
     void explode(void);

     virtual void action(int);
     virtual void go(int);
     virtual void init(int level);

};

//*************************************
class enemy_tank:public tank{
public:
   virtual void init(int);
   virtual void action(int);
   virtual void go(int);
   enemy_tank(class board *,int x=100,int y=200 ,int color=2);

   int make_new_dir(void);
   int turn_allow(int,int *);
   int in_line_of_sight(void);
   void invert_dir(void);
//   Titled_TForm::Titled_TForm(unsigned char l_left=30,unsigned char l_top=10,unsigned char l_width=20,unsigned char l_height=5,int l_bgcolor=7,int l_txtcolor=14,char text[]="Title:"):TForm(l_left,l_top,l_width,l_height,l_bgcolor,l_txtcolor)

};
//*************************************
void board::game_over(void)
{
  int i=0;
  int s[10]={100,200,300,400,200,500,600,700,800,500};
  class menu m1(160,200,300,130,9);
  delay(1000);
  m1.draw();
  setcolor(1);
  settextstyle(10,0,3);
  outtextxy(m1.x +36 , m1.y +38,"GAME OVER");
/*  for(i=0;i<10;i++)
  {
    sound(s[i]);
    delay(150);
    nosound();
  } */

  delay(2000);
  getch();
  exit(0);
}
//--------------------------------------
board::board(void)
{
   int c[10]={0,1,4,9,8,14,10};

   for(int i=0;i<10;i++)
     colors[i]=c[i];

   tir_list=new link_list();

   cur_level=0;
   flushall();
   key=0,key_stat=0;
   init(0);
}
//-----------------------------------------
int board::is_cross(int x_pix,int y_pix)
{
   int cross=0;
   int x=con_x2arr(x_pix);
   int y=con_y2arr(y_pix);


   if(!(status[y][x+1].stat & 0x80))
     cross+=2;
   if(!(status[y][x-1].stat & 0x80))
     cross+=2;
   if(!(status[y-1][x].stat & 0x80))
     cross+=2;
   if(!(status[y+1][x].stat & 0x80))
     cross+=2;

   if( (!(status[y+1][x].stat & 0x80) && !(status[y-1][x].stat & 0x80))  ||
	    (!(status[y][x+1].stat & 0x80) && !(status[y][x-1].stat & 0x80)))
     cross--;
/*   if(status[y+1][x].stat & 0x80)
     cross++;
   if(status[y-1][x].stat & 0x80)
     cross++;
   if(status[y+1][x-1].stat & 0x80)
     cross++;
   if(status[y-1][x+1].stat & 0x80)
     cross++;*/
   return(cross);
}
//---------------------------------------
scr_stat board::get_pos_stat(int x,int y)
{
   int x_arr=con_x2arr(x);
   int y_arr=con_y2arr(y);
   return(status[y][x]);
}
//--------------------------------------
void board::set_pos_stat(class tank *obj,int new_x,int new_y)
{
   int px=obj->x_pos,py=obj->y_pos;
   int new_arrx_pos=con_x2arr(new_x);
   int new_arry_pos=con_y2arr(new_y);

//   if(py==new_y && px==new_x) return;

//this condition should be change to correct
   //if(new_arrx_pos==obj->arrx_pos && new_arry_pos==obj->arry_pos) return;

   obj->x_pos=new_x;
   obj->y_pos=new_y;
   obj->arrx_pos=new_arrx_pos;//con_x2arr(new_x);
   obj->arry_pos=new_arry_pos;//con_y2arr(new_y);
   if(obj->tank_style==1)
   {
      tank_x=obj->arrx_pos;
      tank_y=obj->arry_pos;
   }

   status[con_y2arr(py)][con_x2arr(px)].stat &=obj->reset_mask;
   status[con_y2arr(py + obj->height)][con_x2arr(px + obj->width)].stat &=obj->reset_mask;

   status[con_y2arr(py)][con_x2arr(px)].no=0;
   status[con_y2arr(py + obj->height)][con_x2arr(px + obj->width)].no=0;


   status[con_y2arr(new_y)][con_x2arr(new_x)].stat|=obj->set_mask;
   status[con_y2arr(new_y + obj->height)][con_x2arr(new_x + obj->width)].stat|=obj->set_mask;

   status[con_y2arr(new_y)][con_x2arr(new_x)].no=obj->handle;
   status[con_y2arr(new_y + obj->height)][con_x2arr(new_x + obj->width)].no=obj->handle;

}
//---------------------------------------
int board::con_x2arr(int x)
{
   if(x<0)
     return(0);
   else
     return(x/GRID_X + 1);
}
//----------------------------------------
int board::con_y2arr(int y)
{
   if(y<-4)
     return(0);
   //else if(y>480 && y<490)
     //return(13);
   else
     return(y/GRID_Y + 1);
}
//--------------------------------------
scr_stat board::next_step_stat(class tank *mobile_obj,int direction,int &next_x,int &next_y,int pix_step)
{
   int tx=con_x2arr(mobile_obj->get_x()),ty=con_y2arr(mobile_obj->get_y());
   next_x=mobile_obj->x_pos;
   next_y=mobile_obj->y_pos;
   // this function convert cordinate on pixel x,y to
   // cordinate on arr and puts them into tx,ty
   //dont forget fix last step

   if(direction<3 && direction >0)
   {
     if(direction==1)//up
     {
       ty=con_y2arr(mobile_obj->get_y() - pix_step);
       next_y=mobile_obj->y_pos - pix_step;
     }
     else //left
     {
       tx=con_x2arr(mobile_obj->get_x() - pix_step);
       next_x=mobile_obj->x_pos - pix_step;
     }
   }
   else if(direction>2 && direction<5)
   {
     if(direction==4)  //right
     {
	tx=con_x2arr(mobile_obj->get_x() + pix_step);//+TANK_WIDTH
	next_x=mobile_obj->x_pos + pix_step;
     }
     else  //down
     {
	ty=con_y2arr(mobile_obj->get_y()  + pix_step);//+WAY_H
	next_y=mobile_obj->y_pos + pix_step;
     }
   }
   return(status[ty][tx]);
}
//-------------------------------------
void board::sort_on_speed(void)
{
   int i,j;
   tank *temp;
   for(i=0;i<T_C-1;i++)
     for(j=i+1;j<T_C;j++)
     {
	if((que[j])->speed > (que[i])->speed)
	{
	  temp=que[i];
	  que[i]=que[j];
	  que[j]=temp;
	}
     }

     for(i=0;i<T_C;i++)
	que[i]->handle=i+1;
}
//----------------------------------------
int board::get_key(int exit_key)
{
   int i=0;
//   cur_level++;
   class tir *tmp_tir;
   //flushall();

   for(;key!=exit_key;)
   {
     // flushall();
      tir_list->reset();
      while( ((tmp_tir=tir_list->next_tir())!=0) )
      {
	tmp_tir->action();
      }

      key=0  ;
      if(bioskey(1))
      {
	key_stat=bioskey(2);
	key=bioskey(0);
      }

      if(key==0x2d00)
	return(key);

      if(key==283)//escape
	getch();

       //	printf("key=%x",key);

      for(i=0;i<T_C;i++)
      {
	que[i]->action(key);
      }

      delay(25);

      if(tank_counter==0)
	return(0);

    }
return 1;
}
//---------------------------------------
void board::draw(int color=1)
{
   int i=13,j=17;

/*   for(i=0;i<13;i++)
   {
     for(j=0;j<17;j++)
     {
	if( (i%4) &&(j%4))   //this should be change
			    // should load from array status
	   box_3d(j*WAY_W,i*WAY_H,WAY_W,WAY_H,1,color);
	else
	   box(j*WAY_W,i*WAY_H,WAY_W,WAY_H,10,1);*/

  for(i=1;i<14;i++)
   {
     for(j=1;j<18;j++)
     {
	if(status[i][j].stat&0x80)   //this should be change
			    // should load from array status
	   box_3d((j-1)*WAY_W,(i-1)*WAY_H,WAY_W,WAY_H,1,colors[color]);
	else
	   box((j-1)*WAY_W,(i-1)*WAY_H,WAY_W,WAY_H,10,1);

     }
   }
}
//----------------------------------------
void board::init(int l)
{
   int i,j;
   char a[6][13][17]={{{"00000000000000000"},
		     {"01110111011101110"},
		     {"01110111011101110"},
		     {"01110111011101110"},
		     {"00000000000000000"},
		     {"01110111011101110"},
		     {"01110111011101110"},
		     {"01110111011101110"},
		     {"00000000000000000"},
		     {"01110111011101110"},
		     {"01110111011101110"},
		     {"01110111011101110"},
		     {"00000000000000000"}},

		    {{"00000000000000000"},
		    {"01110111011101110"},
		    {"01110111011101110"},
		    {"00000000000000000"},
		    {"01101101101101110"},
		    {"01101101101101110"},
		    {"00000000000000000"},
		    {"01010101010101010"},
		    {"01010101010101010"},
		    {"01010101010101010"},
		    {"00000000000000000"},
		    {"01101101010010110"},
		    {"00000000000000000"}},

  /* char a2[13][17]=*/{{"00000000000000000"},
		    {"00000000000000000"},
		    {"01111111011111110"},
		    {"00000000000000000"},
		    {"01111011101111110"},
		    {"01111011101111110"},
		    {"00011010101010110"},
		    {"11011010101010110"},
		    {"11001010101010110"},
		    {"00000000000000000"},
		    {"01110111011101110"},
		    {"00000000000000000"},
		    {"00000000000000000"}},

/*   char a3[13][17]=*/{{"00000000000000000"},
		    {"01000000000111010"},
		    {"01010010010101010"},
		    {"01011111110101010"},
		    {"01000000000101010"},
		    {"01001111110101010"},
		    {"01010011000101010"},
		    {"01001111110101010"},
		    {"01000000000101010"},
		    {"01010001100101010"},
		    {"01010010110101010"},
		    {"01001110110101110"},
		    {"00000000000000000"}},


/*char a4[13][17]*/{{"00000000000000000"},
		    {"01110111010010100"},
		    {"00100101011010101"},
		    {"00100111010110110"},
		    {"00100101010010101"},
		    {"00000000000000000"},
		    {"01100010001001100"},
		    {"00010101010100010"},
		    {"01100101010100100"},
		    {"01000101010101000"},
		    {"00110010001000110"},
		    {"00000000000000000"},
		    {"00000000000000000"}},

/*   char a5[13][17]=*/{{"00000000000000000"},
		    {"01101110101110111"},
		    {"01001010100100101"},
		    {"01101010100100111"},
		    {"00101010100100101"},
		    {"01101110110100101"},
		    {"00000000000000000"},
		    {"00100101110101000"},
		    {"00110101010100000"},
		    {"00101101110101000"},
		    {"00100101010101000"},
		    {"00000000000000000"},
		    {"00000000000000000"} }};

   cur_level++;
   tank_counter=T_C - 1;

   for(i=0;i<15;i++)
     for(j=0;j<19;j++)
     {
	status[i][j].stat=0xff;
	status[i][j].no=0;
     }


 /*  for(i=1;i<14;i+=4)
     for(j=1;j<18;j++)
     {
       status[i][j].stat=0;
     }

   for(j=1;j<18;j+=4)
     for(i=1;i<14;i++)
     {
       status[i][j].stat=0;
     } */

     for(i=0;i<13;i++)
      for(j=0;j<17;j++)
      {
	 if( a[l][i][j] =='0')
	   status[i+1][j+1].stat=0;
      }



/*     for(i=0;i<13;i++)
       for(j=0;j<17;j++)
       {
	  if( a1[i][j] =='0')
	    status[j+1][i+1].stat=0;
       }*/

     for(i=0;i<T_C;i++)
       if(que[i]->tank_style==1)
       {
	 tank_x=que[i]->arrx_pos;
	 tank_y=que[i]->arry_pos;
       }
     tir_counter=T_C;
}
//***********************************************
//---------------------------
void tir::action(void)
{
  int i,next_x,next_y,nx_pix,ny_pix;
  scr_stat next_stat;
  class tir *tmp;

  for(i=0;i<TIR_SPEED/(MOVE_PIXEL*2);i++)
  {
    // next_stat=board::status[board::con_x2arr(x_pos)][board::con_y2arr(y_pos)];
    /*next_x=scr->con_x2arr(x_pos);
    next_y=scr->con_y2arr(y_pos);*/

    //next_x=arrx_pos;
    //next_y=arry_pos;
    nx_pix=x_pos;
    ny_pix=y_pos;

    switch(dir)
    {
       case 1:
	    ny_pix-=MOVE_PIXEL*2;
	    break;
       case 2://next_x--;
	    nx_pix-=MOVE_PIXEL*2;
	    break;
       case 3://next_y++;
	    ny_pix+=MOVE_PIXEL*2;
	    break;
       case 4://next_x++;
	    nx_pix+=MOVE_PIXEL*2;
	    break;
    }

    next_x=scr->con_x2arr(nx_pix);
    next_y=scr->con_y2arr(ny_pix);

    next_stat=scr->status[next_y][next_x];


    //if(next_stat.no==0 || next_stat.no==handle)    //dont forget wall check
    if(next_stat.stat & 0x80)
    {
      explode();
      //return();
    }
    else if( next_stat.stat & 0x03)
    {
      moveto(nx_pix,ny_pix);
      if( (next_stat.no != parent_tank_handle) && (next_stat.no != handle))
      {
	explode();
	scr->que[next_stat.no -1 ]->explode();

      }
    }
    //contact of 2 tir
    else if( (next_stat.stat & 0x04) && (next_stat.no != handle ))
    {
	moveto(nx_pix,ny_pix);
	tmp=scr->tir_list->find(next_stat.no);
	if(tmp) tmp->explode();
	explode();
    }
    //if(!(next_stat.stat & 0x80))//not wall
    else
    {
       moveto(nx_pix,ny_pix);
    }
  }
}
//--------------------------
void tir::moveto(int nx,int ny)
{
   erase();
   scr->status[arry_pos][arrx_pos].stat&=reset_mask;
   scr->status[arry_pos][arrx_pos].no=0;

   x_pos=nx;
   y_pos=ny;
   arrx_pos=scr->con_x2arr(x_pos);
   arry_pos=scr->con_y2arr(y_pos);

   draw();
   scr->status[arry_pos][arrx_pos].stat|=set_mask;
   scr->status[arry_pos][arrx_pos].no=handle;
}
//----------------------------------
void tir::erase(void)
{
   box(x_pos,y_pos,6,6,10,1);
}
//----------------------------------
void tir::draw(void)
{
   box_3d(x_pos,y_pos,6,6,1,4);
}
//-----------------------------
//inline tir::tir(class board *s,int x,int y,int direction)
tir::tir(class board *s,int x,int y,int direction,int parent)
{
   //handle=++counter;
   scr=s;
   handle=++(scr->tir_counter);

   parent_tank_handle=parent;
   set_mask=0x04;
   reset_mask=0xfb;

   speed=TIR_SPEED;

   x_pos=x;
   y_pos=y;
   dir=direction;

   arrx_pos=scr->con_x2arr(x_pos);
   arry_pos=scr->con_y2arr(y_pos);

   action();
}
//-------------------------------------------
void tir::explode(void)
{
  tir *tmp;
  erase();
  scr->que[parent_tank_handle -1]->tir_qty--;
  tmp=scr->tir_list->del(handle);
  delete tmp;
}
//******************************************
class node{
public:
   class tir *gololeh ;
   class node *next;
   class node *prev;

   node(void){ gololeh=NULL; next=NULL; prev=NULL;}
   node(class tir *g){gololeh=g; next=NULL; prev=NULL;};
   node(class tir *g,class node *p,class node *n){gololeh=g; next=n;prev=p;};
};
//*******************************************
//-------------------------------------------
link_list::link_list(void)
{
   current_node=end=root=(class node *)NULL;
}
//-----------------------------------------
void link_list::erase_list(void)
{
  class tir *tmp;
  while(root)
  {
    tmp=root->gololeh;
    delete(tmp);
    delete(root);
    root=root->next;
  }
}
//----------------------------------------
class tir *link_list::next_tir(void)
{
  class tir *tmp;

  if(!current_node) return(NULL);
  tmp=current_node->gololeh;
  current_node=current_node->next;

  return(tmp);
}
//------------------------------------------
void link_list::add(class tir *data_p)
{
  class node *temp;

  //temp=(class node *)malloc(sizeof(class node));
  temp=new node(data_p);

  if(!temp)
  {
    printf("not enough memory");
    getch();
    exit(1);
  }
  //add to end of list
  if(!root)
  {
    current_node=root=end=temp;
  }
  else
  {
    //end->prev->next=temp;
    end->next=temp;
    temp->prev=end;
    end=temp;
  }
}
//----------------------------------
class tir* link_list::find(int key)
{
  if(!root)
    return(NULL);

   class node *temp=root;

   while(temp)
   {
     if(temp->gololeh->handle==key)
       break;
     temp=temp->next;
   }

   if(!temp)
   { return(NULL);}

   return(temp->gololeh);

}
//--------------------------------
class tir* link_list::del(int key)
{
  if(!root)
    return(NULL);

   class node *temp=root;
   class tir* t;

   while(temp)
   {
     if(temp->gololeh->handle==key)
     {	break; }
     temp=temp->next;
   }

   if(!temp)
   { return(NULL);}

   t=temp->gololeh;

   if(temp==end)
   {
     if(root==end)
       current_node=root=end=NULL;
     else
     {
       end=end->prev;
       end->next=NULL;
     }
   }
   else
   {
     if(temp==root)
     {
       root=root->next;
       root->prev=NULL;
     }
     else
       temp->prev->next=temp->next;

     temp->next->prev=temp->prev;
   }

   delete(temp);
   return t;
}
//********************************************
//----------------------------------------
menu::menu(int pos_x=620,int pos_y=1,int width=20,int height=470,int col=7)
{
    x=pos_x;
    y=pos_y;
    w=width;
    h=height;
    color=col;
}
//----------------------------------------
void menu::draw(void)
{
  box_3d(x,y,w,h,1,color);
}

//***************************************
tank::tank(class board *brd,int x=132,int y=132,int color=0)
{
//define color
   color_set[0][0]=4;
   color_set[0][1]=3;
   color_set[0][2]=2;
   color_set[0][3]=14;

   color_set[1][0]=9;
   color_set[1][1]=6;
   color_set[1][2]=12;
   color_set[1][3]=4;

   color_set[2][0]=2;
   color_set[2][1]=5;
   color_set[2][2]=4;
   color_set[2][3]=9;

   active=1;
   active_color=color;
   screen=brd;
   w_style=1;
   tank_style=1;
   dir=1;
   tir_qty=0;

   x_pos=x;
   y_pos=y;
   arrx_pos=screen->con_x2arr(x_pos);
   arry_pos=screen->con_y2arr(y_pos);

   width=TANK_WIDTH;
   height=TANK_HEIGHT;
   tank_style=1;

   set_mask=0x01;
   reset_mask=0xfe;
   max_tir_qty=3;


   //set speed
};
//---------------------------------------------
void tank::explode(void)
{
  x_pos=x_pos;
  y_pos=y_pos;

  screen->tank_counter--;

  sound(250);
  active=0;

  for(int i=1;i<5;i++)
  {
    dir=i;
    draw();
    delay(5);
    erase();
  }

  delay(10);
  erase();

  screen->status[arry_pos][arrx_pos].no=0;
  screen->status[screen->con_y2arr(y_pos+height)][screen->con_x2arr(x_pos+width)].no=0;
  screen->status[arry_pos][arrx_pos].stat&=reset_mask;
  screen->status[screen->con_y2arr(y_pos+height)][screen->con_x2arr(x_pos+width)].stat&=reset_mask;

  x_pos=y_pos=-1;
  arrx_pos=arry_pos=0;
  nosound();

  if(tank_style==1)
  {
    screen->tank_x=0;
    screen->tank_y=0;
    screen->game_over();
  }

}
//----------------------------------------
void tank::init(int level)
{
   width=TANK_WIDTH;
   height=TANK_HEIGHT;
   tir_qty=0;

   set_mask=0x01;
   reset_mask=0xfe;

   x_pos=8*WAY_W;
   y_pos=450;
   dir=1;
   speed=random(2*LEVEL_SPEED_VAR) +(level)*LEVEL_SPEED_VAR  + 4;
   //wait=TIMEOUT/speed;
   //step=speed;

}
//-----------------------------------------
int tank::can_turn(int direction)
{
    if(direction==dir)
    {
      return(1);
    }

   int all_case_x[3],all_case_y[3];
   int i,a_x,a_y,t_x,t_y;

   all_case_x[0]=screen->con_x2arr(get_x());
   all_case_x[1]=screen->con_x2arr(get_x() +8);
   all_case_x[2]=screen->con_x2arr(get_x() -8);

   all_case_y[0]=screen->con_y2arr(get_y());
   all_case_y[1]=screen->con_y2arr(get_y() +8);
   all_case_y[2]=screen->con_y2arr(get_y() -8);


   if(dir%2)//odd up,down
   {

     for(i=0;i<3;i++)
     {
	 t_x=a_x=all_case_x[0];
	 t_y=a_y=all_case_y[i];

	  switch(direction)
	  {
	    case 1:a_y--;
		   break;
	    case 2:a_x--;
		   break;
	    case 3:a_y++;
		   break;
	    case 4:a_x++;
		   break;
	  }

       //	if(screen->is_cross(a_x*WAY_W , a_y*WAY_H)<=3)
       //	    continue;

	if(!(screen->status[a_y][a_x].stat & 0x80))//wall
	  break;
     }
   }
   else//even <-,->
   {

     for(i=0;i<3;i++)
     {
	 t_y=a_y=all_case_y[0];
	 t_x=a_x=all_case_x[i];

	  switch(direction)
	  {
	    case 1:a_y--;
		   break;
	    case 2:a_x--;
		   break;
	    case 3:a_y++;
		   break;
	    case 4:a_x++;
		   break;
	  }

	//if(screen->is_cross(a_x*WAY_W , a_y*WAY_H)<=3)
	   // continue;

	if(!(screen->status[a_y][a_x].stat & 0x80))//wall
	  break;
     }
   }

   if(screen->status[a_y][a_x].stat & 0x80)//wall
    return(0);

    dir=direction;//can turn
    if(dir==0)
    {  outtextxy(x_pos,y_pos,"dir is zero"); return(0);}
    //moveto( (a_x-1)*WAY_W ,(a_y-1)*WAY_H);
    moveto( (t_x-1)*WAY_W ,(t_y-1)*WAY_H);
    return(2);


}
//-----------------------------------------
int tank::get_x(void)
{
    switch(dir)
    {
      case 1:return(x_pos);
      case 2:return(x_pos);
      case 3:return(x_pos);
      case 4:return(x_pos+width);
      default:return(x_pos);
    }
}
//-----------------------------------------
int tank::get_y(void)
{
    switch(dir)
    {
      case 1:return(y_pos);
      case 2:return(y_pos);
      case 3:return(y_pos+height);
      case 4:return(y_pos);
      default: return(y_pos);
     }
}
//-----------------------------------------
void tank::fire(void)
{
  class tir *tmp_tir;
  int mid_x=get_x(),mid_y=get_y();

  switch(dir)
  {
    case 1:mid_x+=14;mid_y++;
      break;
    case 2:mid_y+=14;
      break;
    case 3:mid_x+=14;mid_y--;
      break;
    case 4:mid_y+=14;
      break;
  }
  //dont forget check qty of tir and handle of father tir
  if(tir_qty < max_tir_qty)
  {
     tmp_tir=new tir(screen,mid_x,mid_y,dir,handle);
     tir_qty++;
     screen->tir_list->add(tmp_tir);
  }
}
//----------------------------------------
void tank::action(int key)
{

    if(active==0) return;
//    if(key=='0') return;

    int mask_wall=0x80;
    int mask_obj=0xff00;
    //int next_status=0;
    scr_stat next_status;
    int x_arr=0,y_arr=0,direction=dir;

//    printf("k=%x",key);
    if(key==0x2d78)
      return;

    if(key==0x3920) //0x20
    {
      fire();
      screen->key=0;
    }

     switch(key)
     {
	case 0x4800://72 up
	      direction=1;
	   break;
	case  0x4b00: //75 left
	      direction=2;
	   break;
	case 0x5000: //80 down
	      direction=3;
	   break;
	case 0x4d00://77 right
		direction=4;
	    break;
     }
/*    if(handle< 2)  //should delete
    {
      direction=random(4)+1;
    }*/
    screen->key=0;
    go(direction);
}
//----------------------------------------
void tank::go(int d)
{
   int i,x,y,step=MOVE_PIXEL,flag;
   scr_stat next_status;
   //check direction first
   //determine x,y;
   x=x_pos;y=y_pos;
   step=MOVE_PIXEL;

//   if(flag=can_turn(d))

   flag=can_turn(d);
   if(flag)
   {
      if(flag==1)
      {
	for(i=0;i<=speed/MOVE_PIXEL;i++)
	{
	//dont forget set and control position
	   if(i*MOVE_PIXEL>speed)
	     step=speed%MOVE_PIXEL;

	     //printf("%d_",d);
	   next_status=screen->next_step_stat( (class tank *)this,d,x,y,MOVE_PIXEL);
	   if(next_status.stat & 0x80)//wall
	   {
	     //here
	   }
	   else
	   {
	     if(next_status.stat & 0x02)//enemytank
	     {
	      setcolor(random(14)+1);
	      outtextxy(x_pos,y_pos,"BOOM");
	      //getch();
	      /*sound(200);
	      delay(50);
	      nosound();*/
	      screen->que[next_status.no -1]->explode();
	      explode();
	     }

	      moveto(x,y);
	      delay(3);
	   }

	}
      }
   }
}
//----------------------------------------
void tank::draw(void)
{
  int x=x_pos, y=y_pos;
  #define PIPE    15
  #define WHILL_W  6
  #define WHILL_H  30
  #define MIDDLE_W   TANK_WIDTH - 2*WHILL_W
  #define MIDDLE_H   MIDDLE_W+2
  #define T_Y  TANK_HEIGHT - WHILL_H

  //box(x , y+T_Y ,WHILL_W , WHILL_H ,6,4);
  //box(x+MIDDLE_W+WHILL_W+2 , y+T_Y , WHILL_W,WHILL_H,6,4);

switch(dir)
{
  case 1:
  x+=1;
  setlinestyle(w_style,2,3);
  setcolor(color_set[active_color][0]);
//  line(x , y+T_Y ,x , WHILL_H+y+T_Y-1 );
  line(x , y+2 ,x , WHILL_H+y-2 );
//  line(x+3 , y+T_Y-2 ,x+3 , WHILL_H+y+T_Y );
  line(x+3+1 , y ,x+3+1 , WHILL_H+y );

//  line(x+MIDDLE_W+WHILL_W+2 , y+T_Y-2 , x+MIDDLE_W+WHILL_W+2,WHILL_H+y+T_Y);
  line(x+MIDDLE_W+WHILL_W-1 , y , x+MIDDLE_W+WHILL_W-1,WHILL_H+y);
//  line(x+MIDDLE_W+WHILL_W+5 , y+T_Y , x+MIDDLE_W+WHILL_W+5,WHILL_H+y+T_Y-1);
  line(x+MIDDLE_W+WHILL_W+3 , y+2 , x+MIDDLE_W+WHILL_W+3,WHILL_H+y-2);


//  box_3d(x+WHILL_W+1, y+PIPE, MIDDLE_W ,MIDDLE_H,1,color_set[active_color][1]);
  box_3d(x+WHILL_W , y+6 , MIDDLE_W,MIDDLE_H,1,color_set[active_color][1]);
//  box_3d(x+WHILL_W+6,y+PIPE+6,16-8,12-4,1,color_set[active_color][2]);
 box_3d(x+WHILL_W+7 , y , 4,PIPE,1,color_set[active_color][3]);//pipe
  box_3d(x+WHILL_W+5,y+14,8,8,1,color_set[active_color][2]);

 // box_3d(x + (MIDDLE_W/2)-5 , y , 4,PIPE+5,1,color_set[active_color][3]);//pipe


   //setwritemode(1);
   //setcolor(7);
   //setlinestyle(0,2,3);
   //line(x + (MIDDLE_W/2)-3,y+PIPE+5,x + (MIDDLE_W/2)-3,y);

   //setwritemode(0);
  break;
  case 2:
  y+=2;
  setlinestyle(w_style,2,3);
  setcolor(color_set[active_color][0]);
  line(x+2 , y ,x+WHILL_H-2 , y );
  line(x , y+4 ,x+WHILL_H , y+4 );
  line(x , y+MIDDLE_W+5 , x+WHILL_H,y+MIDDLE_W+5);
  line(x+2, y+MIDDLE_W+3+6 ,x+WHILL_H-2,y+MIDDLE_W+3+6);

  box_3d(x+8, y+6, MIDDLE_H ,MIDDLE_W,1,color_set[active_color][1]);
  box_3d(x+2 , y+WHILL_W+7 , PIPE,4,1,color_set[active_color][3]);//pipe
  box_3d(x+PIPE+1,y+11,8,8,1,color_set[active_color][2]);


  break;
  case 3:
  x+=1;
  setlinestyle(w_style,2,3);
  setcolor(color_set[active_color][0]);
  line(x , y+2 ,x , WHILL_H+y-2 );
  line(x+3+1 , y ,x+3+1 , WHILL_H+y );

  line(x+MIDDLE_W+WHILL_W-1 , y , x+MIDDLE_W+WHILL_W-1,WHILL_H+y);
  line(x+MIDDLE_W+WHILL_W+3 , y+2 , x+MIDDLE_W+WHILL_W+3,WHILL_H+y-2);


  box_3d(x+WHILL_W , y+6 , MIDDLE_W,MIDDLE_H,1,color_set[active_color][1]);

   box_3d(x+WHILL_W+7 , y+15 , 4,PIPE,1,color_set[active_color][3]);//pipe
  box_3d(x+WHILL_W+5,y+9,8,8,1,color_set[active_color][2]);



   //setwritemode(1);
   //setcolor(7);
   //setlinestyle(0,2,3);
   //line(x + (MIDDLE_W/2)-3,y+PIPE+5,x + (MIDDLE_W/2)-3,y);

   //setwritemode(0);
  break;

  case 4: //horizental right
  y+=2;
  setlinestyle(w_style,2,3);
  setcolor(color_set[active_color][0]);
  line(x+2 , y ,x+WHILL_H-2 , y );
  line(x , y+4 ,x+WHILL_H , y+4 );
  line(x , y+MIDDLE_W+5 , x+WHILL_H,y+MIDDLE_W+5);
  line(x+2, y+MIDDLE_W+3+6 ,x+WHILL_H-2,y+MIDDLE_W+3+6);

  box_3d(x+6, y+6, MIDDLE_H ,MIDDLE_W,1,color_set[active_color][1]);
  box_3d(x+16  , y+WHILL_W+7 , PIPE,4,1,color_set[active_color][3]);//pipe
  box_3d(x+10,y+11,8,8,1,color_set[active_color][2]);


  break;
  }


}

//---------------------------------------
void tank::erase(void)
{
  //box(x_pos,y_pos,30,30,1,0);
  box(x_pos,y_pos,WAY_W-3,WAY_W-3,10,1);
  //box(x_pos,y_pos,TANK_WIDTH,TANK_HEIGHT,10,1);
}
//---------------------------------------
void tank::moveto(int x,int y)
{
     erase();
     screen->set_pos_stat((class tank *)this,x,y);
     x_pos=x;
     y_pos=y;
     if(w_style==1) w_style=2;
       else w_style=1;

     draw();

}

//***************************************************
enemy_tank::enemy_tank(class board *brd,int x,int y,int color):tank(brd,x,y,color)
{
   tank_style=2;

   set_mask=0x02;
   reset_mask=0xfd;
   max_tir_qty=1;
}
//------------------------------------------
int enemy_tank::in_line_of_sight(void)
{
  int i;
  switch(dir)
  {
    case 1://up
       for(i=arry_pos-1;i>0 && !(screen->status[i][arrx_pos].stat & 0x82) ;i--)
	 if(screen->status[i][arrx_pos].stat & 0x01) return(1);
       return(0);

    case 2: //left
       for(i=arrx_pos-1;i>0 && !(screen->status[arry_pos][i].stat & 0x82) ;i--)
	 if(screen->status[arry_pos][i].stat & 0x01) return(1);
       return(0);

    case 3: //down
       for(i=arry_pos+1;i<15 && !(screen->status[i][arrx_pos].stat & 0x82) ;i++)
	 if(screen->status[i][arrx_pos].stat & 0x01) return(1);
       return(0);

    case 4: //right
       for(i=arrx_pos+1;i<19 && !(screen->status[arry_pos][i].stat & 0x82) ;i++)
	 if(screen->status[arry_pos][i].stat & 0x01) return(1);
       return(0);

  }
return 1;
}
//-----------------------------------------
int enemy_tank::turn_allow(int direction,int *d)
{
//    int d[5]={0};
    int a_x= screen->con_x2arr(get_x());
    int a_y= screen->con_y2arr(get_y());


    if(!(screen->status[a_y-1][a_x].stat & 0x80) && !(screen->status[a_y-1][a_x].stat & 0x02))
    {
      d[++d[0]]=1;
    }

    if(!(screen->status[a_y][a_x-1].stat & 0x80) && !(screen->status[a_y][a_x-1].stat & 0x02))
    {
      d[++d[0]]=2;
    }

    if(!(screen->status[a_y+1][a_x].stat & 0x80) && !(screen->status[a_y+1][a_x].stat & 0x02))
    {
      d[++d[0]]=3;
    }

    if(!(screen->status[a_y][a_x+1].stat & 0x80) && !(screen->status[a_y][a_x+1].stat & 0x02))
    {
      d[++d[0]]=4;
    }


    if(direction==dir)
    {
      return(1);
    }
    else
    {
       switch(direction)
       {
	 case 1:a_y--;
		break;
	 case 2:a_x--;
		break;
	 case 3:a_y++;
		break;
	 case 4:a_x++;
		break;
       }

       if(screen->status[a_y][a_x].stat & 0x80)//wall
	 return(0);

       if(screen->status[a_y][a_x].stat & 0x02)//enemy_tank
       {
	 return(0);
       }
       return(2);
    }
}
//---------------------------------------------------
void enemy_tank::action(int)
{
//should change for detect cross
   if(active==0)
     return;
   int new_dir=0,flag=0;

   if(in_line_of_sight())
     if(!random(20))
       fire();
   new_dir=make_new_dir();
   go(new_dir);
}
//----------------------------------------
int enemy_tank::make_new_dir(void)
{
  int d[5]={0},i;
  int a_x= screen->con_x2arr(get_x());
  int a_y= screen->con_y2arr(get_y());
  int dx=arrx_pos - (screen->tank_x);
  int dy=arry_pos - (screen->tank_y);
  int xarrow=0,yarrow=0,arrow;
  int cross_stat=screen->is_cross(get_x(),get_y());
   //3 is straight way
   if(cross_stat > 3)
   {
      if(dy > 0)
	 yarrow=1;
      else if(dy < 0)
	 yarrow=3;

      if( dx > 0)
	xarrow=2;
      else if(dx < 0)
	xarrow=4;

      //  else
      //    return(0);
      if(!(xarrow||yarrow))  //contact with tank
      {
	setcolor(random(14)+1);
	screen->game_over();
	return(0);
      }

/*      if(xarrow>0)
	arrow=xarrow;
      else
	arrow=yarrow;

      if(xarrow!=0 && yarrow!=0)
      {
	if(random(2))
	  arrow=xarrow;
	else
	  arrow=yarrow;
      }


      if(turn_allow(arrow,d))
	return arrow;
      else
      {
	if(arrow==xarrow)
	  return(yarrow);
	else
	  return(xarrow);
      }
  */

      if(xarrow!=0)
	arrow=xarrow;
      else if(yarrow!=0)
	arrow=yarrow;

      if(xarrow!=0 && yarrow!=0)
      {
	if(random(2))
	  arrow=xarrow;
	else
	  arrow=yarrow;
      }

      if(turn_allow(arrow,d))
      {
	return arrow;
      }
      else
      {
	 if(xarrow)
	   for(i=1;i<=d[0];i++)
	     if(xarrow==d[i])
	       return(xarrow);

	 if(yarrow)
	   for(i=1;i<=d[0];i++)
	     if(yarrow==d[i])
	       return(yarrow);

	 if(d[0]>0)
	 { int R=random(d[0])+1;
	   return( d[R]);
	 }
      }

   }

   else if(cross_stat<3)
   {
       invert_dir();
       return(dir);
   }

   return(dir);

}
//---------------------------------------
void enemy_tank::invert_dir(void)
{
  int arr_dir[5]={4,3,4,1,2};
  dir=arr_dir[dir];
}
//---------------------------------------
void enemy_tank::init(int level)
{
   tir_qty=0;
   active=1;
   dir=(random(2)+1)*2;
   speed=random(LEVEL_SPEED_VAR) + (level-1)*LEVEL_SPEED_VAR + 4;
   x_pos=(random(5)*4)*WAY_W;
   y_pos=0;
}
//----------------------------------------
void enemy_tank::go(int d)
{
   int i,x,y,step=MOVE_PIXEL,flag;
   scr_stat next_status;
   //check direction first
   //determine x,y;
   x=x_pos;y=y_pos;
   step=MOVE_PIXEL;

   if((flag=can_turn(d))!=0)
   {
      if(flag==1)
      {
	for(i=0;i<=speed/MOVE_PIXEL;i++)
	{
	//dont forget set and control position
	   if(i*MOVE_PIXEL>speed)
	     step=speed%MOVE_PIXEL;

	     //printf("%d_",d);
	   next_status=screen->next_step_stat( (class tank *)this,d,x,y,MOVE_PIXEL);

	   if(next_status.stat & 0x80)//wall
	   {
	     //here
	   }
	   else
	   {
	     if((next_status.stat & 0x02) && (next_status.no !=handle) &&!(next_status.stat & 0x01) )//other enemy_tank
	     {
		  invert_dir();
		  d=dir;
	     }

	     if(next_status.stat & 0x01)//tank
	     {
	      moveto(x,y);
	      setcolor(random(14)+1);
	      outtextxy(x_pos,y_pos,"BOOM");
	      //sound(1000);
	      delay(100);
	      //nosound();
	      explode();//me
	      screen->que[next_status.no -1 ]->explode();

	      return;
	     }

	      moveto(x,y);
	      //x_pos=x;y_pos=y;
	      delay(3);
	   }
	     // if(speed%MOVE_PIXEL)
	     //   moveto(x,y);

	}
      }
   }
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//int LEVEL=1;
int main(void)
{
   /* request auto detection */
   int gdriver = DETECT, gmode, errorcode;

   /* initialize graphics mode */
   initgraph(&gdriver, &gmode, "");

   /* read result of initialization */
   errorcode = graphresult();

   if (errorcode != grOk)  /* an error occurred */
   {
      printf("Graphics error: %s\n", grapherrormsg(errorcode));
      printf("Press any key to halt:");
      getch();
      exit(1);             /* return with error code */
   }

   int i,j,c=0;
   char level_str[10],msg[20]={0};

   board screen1;
   randomize();

   menu menu1(17*WAY_W,1,640-17*WAY_W,480,7);

   screen1.que[2]=new tank(&screen1,WAY_W*12,450,1);

   screen1.que[0]=new enemy_tank(&screen1,WAY_W*0,50,0);
   screen1.que[1]=new enemy_tank(&screen1,WAY_W*4,50,0);
   screen1.que[3]=new enemy_tank(&screen1,WAY_W*8,50,0);


//   screen1.sort_on_speed();

for(j=0;j<6;j++)
{
   screen1.init(j);
   screen1.draw(j);
   screen1.tir_list->erase_list();

   menu1.draw();
   setcolor(j+1);
   settextstyle(10,1,3);
   itoa(j+1,level_str,10);
   strcpy(msg,"LEVEL :");
   strcat(msg,level_str);
   outtextxy(menu1.x,menu1.y+120,msg);
   settextstyle(12,0,1);

   for(i=0;i<T_C;i++)
   {
     screen1.que[i]->init(j);
   }
   screen1.sort_on_speed();

   for(i=0;i<T_C;i++)
   {
     screen1.que[i]->draw();
   }

   bioskey(0);

  screen1.get_key(97);

  delay(1000);
}

   outtextxy(100,100,"Congratulation: YOU WON");
   getch();
   closegraph();
   return 0;
  }



//===========================
/*----------------------------------------*/
int box_3d(int x1,int y1,int w,int h,int style,int color)
{
    w--;h--;
    box(x1,y1,w,h,style,color);

  setlinestyle(0,0,1);

  setcolor(15);
  line(x1,y1,x1+w,y1);
  line(x1,y1,x1,y1+h);

  setcolor(0);//shadow color
  line(x1+w,y1,x1+w,y1+h);
  line(x1,y1+h,x1+w,y1+h);

  setcolor(8);
  line(x1+w-1,y1+1,x1+w-1,y1+h-1);
  line(x1+1,y1+h-1,x1+w-1,y1+h-1);
//  putpixel(x1+1,y1+h-1,0);


  //settextstyle(3,0,1);

  //if(cap)
  //  outtextxy(x1+(w-strlen(cap)*8)/2, y1+ h/2-5 ,cap);

  return 1;
}

/*----------------------------------------*/
int box(int x1,int y1,int w,int h,int style,int color)
{
  int poly[20]={100,100,150,100,150,120,100,120,100,100};
  poly[0]=x1;
  poly[1]=y1;
  poly[2]=x1+w;
  poly[3]=y1;
  poly[4]=x1+w;
  poly[5]=y1+h;
  poly[6]=x1;
  poly[7]=y1+h;
  poly[8]=x1;
  poly[9]=y1;

//  setbkcolor(9);

  setlinestyle(0,0,1);
  setcolor(0);//for frame
  setfillstyle(style,color);
  fillpoly(4,poly);

  return 0;
}

//----------------------------------
void Start_demo(void)
{

}
//------------------------------------