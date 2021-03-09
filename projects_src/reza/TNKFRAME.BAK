void Form1_Action(position pos,TObject *Me,TObject *obj);
void Form1_OnStartDrag(TObject *obj);

void TForm1::TForm1(void):TForm(0,"TankGame")
{
       level=-1;
       colorlist[0]=9;
       colorlist[1]=4;
       colorlist[2]=6;
       colorlist[3]=2;
       colorlist[4]=1;
       retry=false;
       OnStartDrag=Form1_OnStartDrag;
}

void TForm1::StartNextMission(void)
{
	if (retry!=true)
	level++;
	if (level>=5) return;
	char test[5][10][10]={{{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
			   {' ','b','b',' ','b','b',' ','b','b',' '},
			   {' ','b','b',' ','b','b',' ','b','b',' '},
			   {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
			   {' ','b','b',' ','b','b',' ','b','b',' '},
			   {' ','b','b',' ','b','b',' ','b','b',' '},
			   {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
			   {' ','b','b',' ','b','b',' ','b','b',' '},
			   {' ','b','b',' ','b','b',' ','b','b',' '},
			   {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}},

			   {{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
			    {' ','b','b',' ','b','b',' ','b','b',' '},
			    {' ','b','b',' ','b','b',' ','b','b',' '},
			    {' ','b','b',' ',' ',' ',' ','b','b',' '},
			    {' ',' ',' ',' ','b','b',' ',' ',' ',' '},
			    {' ',' ',' ',' ','b','b',' ',' ',' ',' '},
			    {' ','b','b',' ',' ',' ',' ','b','b',' '},
			    {' ','b','b',' ','b','b',' ','b','b',' '},
			    {' ','b','b',' ','b','b',' ','b','b',' '},
			    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}},

			   {{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
			    {' ','b','b','b',' ',' ','b','b','b',' '},
			    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
			    {' ','b','b','b',' ',' ','b','b','b',' '},
			    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
			    {' ','b','b','b',' ',' ','b','b','b',' '},
			    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
			    {' ','b','b',' ',' ',' ',' ','b','b',' '},
			    {' ',' ',' ',' ','b','b',' ',' ',' ',' '},
			    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}},

			   {{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
			    {' ','b',' ','b',' ','b',' ','b',' ',' '},
			    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
			    {' ',' ','b',' ','b',' ','b',' ','b',' '},
			    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
			    {' ','b',' ','b',' ','b',' ','b',' ',' '},
			    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
			    {' ',' ','b',' ','b',' ','b',' ','b',' '},
			    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
			    {' ',' ',' ',' ','b','b',' ',' ',' ',' '}},

			   {{'b',' ',' ',' ',' ',' ',' ',' ',' ','b'},
			    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
			    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
			    {' ',' ',' ',' ','b','b',' ',' ',' ',' '},
			    {' ',' ',' ',' ','b','b',' ',' ',' ',' '},
			    {' ',' ',' ',' ','b','b',' ',' ',' ',' '},
			    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
			    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
			    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
			    {'b',' ',' ',' ',' ',' ',' ',' ',' ','b'}}
			    };
	for(int i=0;i<10;i++)
		for(int j=0;j<10;j++){
			block[i][j]=test[level][i][j];
			tanklist[i][j].state=0;
			tanklist[i][j].tank=NULL;
			bombloclist[i][j]=NULL;
		}
       for(i=0;i<50;i++)
		bomblist[i]=NULL;
       for(i=0;i<3;i++)
		enemy[i]=NULL;
       if (Image1->visible==true)
       {
		Image1->visible=false;
		Image1->Clear();
       }
       if (Image2->visible==true)
       {
		Image2->visible=false;
		Image2->Clear();
       }
       if (Image3->visible==true)
       {
		Image3->visible=false;
		Image3->Clear();
       }
       DrawBlock();
       end=false;
       start=false;
       bombindex=-1;
       Init();
}

void TForm1::Init(void)
{
       char mission[20],clevel[3];
       Rect loc;
       strcpy(mission,"Mission ");
       itoa(level+1,clevel,10);
       strcat(mission,clevel);
       pbar1->Go(0);
       pbar2->Go(0);
       pbar3->Go(0);
       pbar4->Go(0);
       Lable5->SetCaption(mission);
       Lable6->SetCaption("Press < F2 > For State Game ...");

       loc.top=pos.top+300;
       loc.left=pos.left+2;
       Image1->pos=loc;
       Image1->kill=2;
       Image1->x=-1;
       Image1->index=-1;
       position location=SetLocation(1,1,Image1);
       loc.left=location.x;
       loc.top=location.y;
       Image1->pos=loc;
       Image1->LoadFromFile("image\\uptank.gbf");
       Image1->id='m';
       SetTankPos(Image1);
       Image1->state=1;
       Image1->visible=true;
       Image1->speed=(2*level)+15;

       loc.top=pos.top+45;
       loc.left=pos.left+2;
       Image2->pos=loc;
       Image2->kill=2;
       Image2->x=-1;
       Image2->index=-1;
       location=SetLocation(1,1,Image2);
       loc.left=location.x;
       loc.top=location.y;
       Image2->pos=loc;
       Image2->LoadFromFile("image\\downet.gbf");
       Image2->id='e';
       SetTankPos(Image2);
       Image2->state=2;
       Image2->visible=true;
       Image2->speed=(2*level)+1;

       loc.top=pos.top+20;
       loc.left=pos.left+200;
       Image3->pos=loc;
       Image3->kill=2;
       Image3->x=-1;
       Image3->index=-1;
       location=SetLocation(4,4,Image3);
       loc.left=location.x;
       loc.top=location.y;
       Image3->pos=loc;
       Image3->LoadFromFile("image\\rightet.gbf");
       Image3->id='e';
       SetTankPos(Image3);
       Image3->state=4;
       Image3->visible=true;
       Image3->speed=(1*level)+1;
       Image3->pbar=pbar3;

       enemy[0]=Image2;
       enemy[1]=Image3;
       GetPicture();
       Application.Hook(this,EV_MOUSEMOVE,Form1_Action);
}

void TForm1::DrawBlock(void)
{
	int *poly,top,left;
	Mouse.hide();
	poly=fillpol(pos.left+4,pos.top+21,pos.left+pos.width-107,pos.top+pos.height-22);
	box(poly,0,0,1);
	setcolor(15);
	for(int i=0;i<10;i++)
		for(int j=0;j<10;j++)
			if (block[i][j]=='b'){
			    left=(pos.left+4)+(j*37);
			    top=(pos.top+23)+(i*37);
			    poly=fillpol(left,top,left+36,top+36);
			    setfillstyle(9,colorlist[level]);
			    fillpoly(4,poly);
			    free(poly);
			}
	Mouse.show();
}

position TForm1::SetLocation(char state,char laststate,TObject *obj)
{
	int x,y,dy,tmp,y1,x1;
	position loc;
	x=obj->pos.left-(pos.left+4);
	y=obj->pos.top-(pos.top+21);
	x/=37;
	y/=37;
	x1=obj->pos.left+obj->pos.width-(pos.left+4)-5;
	y1=obj->pos.top+obj->pos.height-(pos.top+21)-5;
	x1/=37;
	y1/=37;
	if (x1==10) x1=9;
	if (y1==10) y1=9;
	dy=(y*37)+pos.top+21;
	switch(state)
	{
		case 1:if ( (37-(obj->pos.top-dy)) <= 19 ) y++;
		       if (laststate==4) x=x1;
		       loc.x=(x*37)+(pos.left+6+5);
		       loc.y=(y*37)+(pos.top+23);
		       break;
		case 2:if ( (37-(obj->pos.top-dy)) <= 19 ) y++;
		       if (laststate==4) x=x1;
		       loc.x=(x*37)+(pos.left+6+5);
		       loc.y=(y*37)+(pos.top+23);
		       break;
		case 3:loc.x=(x*37)+(pos.left+6+5);;
		       if (laststate==2) y=y1;
		       loc.y=(y*37)+(pos.top+23)+7;
		       break;
		case 4:loc.x=(x*37)+(pos.left+6+5);;
		       if (laststate==2) y=y1;
		       loc.y=((y*37)+pos.top+23)+7;
		       break;
	}
	return loc;
}

int TForm1::SetStep(int step,Rect loc,char dir)
{
	int dx,dy,sp;
	dy=loc.top-pos.top;
	dx=loc.left-pos.left;
	sp=step;
	switch (dir)
	{
		case 1:if ( (dy-21) < sp )             //up
				sp=dy-21;
		       break;
		case 2:if ( (pos.height-58-dy) < sp )  //down
				sp=pos.height-58-dy;
		       break;
		case 3:if ( (dx-4) < sp )              //left
				sp=dx-4;
		       break;
		case 4:if ( (pos.width-142-dx) < sp )  //right
				sp=pos.width-142-dx;
		       break;
	}
	return sp;
};

bool TForm1::SetTankPos(TImage *tank)
{
	int x,y,x1,y1;
	char ch;
	TImage *t;
	bool result=false;
	if (tank->id=='m') ch='e';
	else  ch='m';
	x=tank->pos.left-(pos.left+4);
	y=tank->pos.top-(pos.top+21);
	x/=37;
	y/=37;
	x1=tank->pos.left+tank->pos.width-(pos.left+4)-5;
	y1=tank->pos.top+tank->pos.height-(pos.top+21)-5;
	x1/=37;
	y1/=37;
	if (y==10) y--;
	if (y1==10) y1--;
	if (x==10) x--;
	if (x1==10) x1--;
	switch (tank->state)
	{
		case 1: if (tanklist[y][x].state==ch)
			{
			      t=tanklist[y][x].tank;
			      if ( (tank->pos.top-(t->pos.top+t->pos.height))<=5 )
			      result=true;
			}
			break;
		case 2: if (tanklist[y1][x].state==ch)
			{
			      t=tanklist[y1][x].tank;
			      if ( (t->pos.top-(tank->pos.top+tank->pos.height))<=5 )
			      result=true;
			}
			break;
		case 3: if (tanklist[y][x].state==ch)
			{
			      t=tanklist[y][x].tank;
			      if ( (tank->pos.left-(t->pos.left+t->pos.width))<=5 )
			      result=true;
			}
			break;
		case 4: if (tanklist[y][x1].state==ch)
			{
			      t=tanklist[y][x1].tank;
			      if ( (t->pos.left-(tank->pos.left+tank->pos.width))<=5 )
			      result=true;
			}
			break;
	}
	if (result==true) return result;
	if (tank->x!=-1){
		tanklist[tank->y][tank->x].state=0;
		tanklist[tank->y][tank->x].tank=NULL;
		if (tanklist[tank->y+1][tank->x].state==tank->id){
			tanklist[tank->y+1][tank->x].state=0;
			tanklist[tank->y+1][tank->x].tank=NULL;
		}
		if (tanklist[tank->y][tank->x+1].state==tank->id){
			tanklist[tank->y][tank->x+1].state=0;
			tanklist[tank->y][tank->x+1].tank=NULL;
		}
/*		if (tanklist[tank->y-1][tank->x].state==tank->id){
			tanklist[tank->y-1][tank->x].state=0;
			tanklist[tank->y-1][tank->x].tank=NULL;
		}
		if (tanklist[tank->y][tank->x-1].state==tank->id){
			tanklist[tank->y][tank->x-1].state=0;
			tanklist[tank->y][tank->x-1].tank=NULL;
		}*/
	}
	tanklist[y][x].state=tank->id;
	tanklist[y][x].tank=tank;
	tank->x=x;
	tank->y=y;
	if (y1!=y){
		tanklist[y1][x].state=tank->id;
		tanklist[y1][x].tank=tank;
	}
	if (x1!=x){
		tanklist[y][x1].state=tank->id;
		tanklist[y][x1].tank=tank;
	}
	return result;
};

bool TForm1::CanDo(TImage *tank,char action,char *step)
{
	bool result=true;
	int sp,x,y,x1,y1;
	y1=tank->pos.top+tank->pos.height-(pos.top+21)-5;
	y1=y1/37;
	x1=tank->pos.left+tank->pos.width-(pos.left+4)-5;
	x1=x1/37;
	x=tank->x;
	y=tank->y;
	switch (action)
	{
		case 1: if (tank->state==4) x=x1;
			if ( (tanklist[y][x].state!=0)&&(tanklist[y][x].state!=tank->id) ) {result=false;break;}
			if ( (y!=0)&&(tanklist[y-1][x].state==tank->id)&&(tanklist[y-1][x].tank!=tank) ) {*step=0;break;}
			if ( (y==0)&&((tank->pos.top-(pos.top+23))<=0) )
			   result=false;
			else
			if ( (y==0)&&(tank->state!=1) )
			    result=false;
			else
			   if (block[y-1][x]=='b')
			   {
				sp=tank->pos.top-((y*37)+pos.top+23);
				if ( sp < *step )  *step=sp;
				if (sp<=3)   result=false;
				else   result=true;
				if (tank->state!=1) result=false;
			   }
			break;
		case 2: if (tank->state==4) x=x1;
			if ( (tanklist[y][x].state!=0)&&(tanklist[y][x].state!=tank->id) ) {result=false;break;}
			if ( (y!=9)&&(tanklist[y+1][x].state==tank->id)&&(tanklist[y+1][x].tank!=tank) ) {*step=0;break;}
			if (y==9)
			   result=false;
			else
			   if (block[y1+1][x]=='b')
			   {
				sp=(((y1+1)*37)+pos.top+19)-(tank->pos.top+tank->pos.height);
				if (sp < *step )  *step=sp;
				if ( (sp>=37)||(sp<=3) )   result=false;
				else   result=true;
				if (tank->state!=2) result=false;
			   }
			break;
		case 3: if (tank->state==2) y=y1;
			if ( (tanklist[y][x].state!=0)&&(tanklist[y][x].state!=tank->id) ) {result=false;break;}
			if ( (x!=0)&&(tanklist[y][x-1].state==tank->id)&&(tanklist[y][x-1].tank!=tank) ) {*step=0;break;}
			if ( (x==0)&&((tank->pos.left-(pos.left+4))==7/* *step*/) )
			   result=false;
			else
			   if (block[y][x-1]=='b')
			   {
				sp=tank->pos.left-((x*37)+pos.left+5);
				if (sp < *step )  *step=sp;
				if ( (sp<=3)||(sp>=37) )  result=false;
				else   result=true;
				if (tank->state!=3) result=false;
			   }
			break;
		case 4:	if (tank->state==2) y=y1;
			if ( (tanklist[y][x].state!=0)&&(tanklist[y][x].state!=tank->id) ) {result=false;break;}
			if ( (x!=9)&&(tanklist[y][x+1].state==tank->id)&&(tanklist[y][x+1].tank!=tank) ) {*step=0;break;}
			if (x==9)
			   result=false;
			else
			   if (block[y][x1+1]=='b')
			   {
				sp=(((x1+1)*37)+pos.left+3)-(tank->pos.left+tank->pos.width);
				if (sp < *step )  *step=sp;
				if ( (sp<=3)||(sp>=37) )   result=false;
				else   result=true;
				if (tank->state!=4) result=false;
			   }
			break;
	}
	return result;
}

void TForm1::SetBombLoc(TBomb *bomb)
{
	int x,y;
	x=bomb->pos.left-(pos.left+4);
	y=bomb->pos.top-(pos.top+21);
	x/=37;
	y/=37;
	if (bomb->x!=100)   bombloclist[bomb->y][bomb->x]=NULL;
	if (bombloclist[y][x]!=NULL)
	{
		DeleteBomb(bomb);
		DeleteBomb(bombloclist[y][x]);
	}
	else
	{
		bombloclist[y][x]=bomb;
		bomb->x=x;
		bomb->y=y;
	}
}

void TForm1::BombAction(TBomb *bomb)
{
	int x1,y1,x2,y2,step=10,sp;
	char st;
	if (bomb->tank->id=='m')
		st='e';
	else
		st='m';
	bool result=true;
	x1=bomb->pos.left+step;
	y1=bomb->pos.top+step;
	x2=bomb->pos.left-step;
	y2=bomb->pos.top-step;

	y1=y1+bomb->pos.height-(pos.top+21);
	y1=y1/37;
	x1=x1+bomb->pos.width-(pos.left+4);
	x1=x1/37;
	y2=y2+bomb->pos.height-(pos.top+21);
	y2=y2/37;
	x2=x2+bomb->pos.width-(pos.left+4);
	x2=x2/37;
	if (y1==10) y1=9;
	if (x1==10) x1=9;
	if (y2==10) y2=9;
	if (x2==10)  x2=9;
	switch(bomb->dir)
	{
		case 1:if (bombloclist[y2-1][x1]!=NULL)
			{
				DeleteBomb(bombloclist[y2-1][x1]);
				result=false;
				break;
			}
		       if (y2==0)
		       {
				sp=bomb->pos.top-(((y2)*37)+pos.top+23);
				if ( sp < step )  step=sp;
				if (sp<=2)  result=false;
				else   result=true;
		       }
		       if (block[y2][x1]=='b')
				result=false;
		       else
		       if ( (tanklist[y2][x1].state!=0)&&(tanklist[y2][x1].tank!=bomb->tank) )
		       {
				tanklist[y2][x1].tank->pbar->Go((3-tanklist[y2][x1].tank->kill)*33);
				if (tanklist[y2][x1].tank->kill==0)
					DestroyTank(tanklist[y2][x1].tank);
				else
					(tanklist[y2][x1].tank->kill)--;
				result=false;
		       }
		       break;
		case 2:if ( (bombloclist[y1+1][x1]!=NULL)&&(y1!=9) )
			{
				DeleteBomb(bombloclist[y1+1][x1]);
				result=false;
				break;
			}
		       if (y1==9)
		       {
				sp=((((y1+1))*37)+pos.top+19)-(bomb->pos.top+bomb->pos.height);
				if (sp < step )  step=sp;
				if (sp<=2)  result=false;
				else   result=true;
		       }
		       if (block[y1][x1]=='b')
				result=false;
		       else
		       if ( (tanklist[y1][x1].state!=0)&&(tanklist[y1][x1].tank!=bomb->tank) )
		       {
				tanklist[y1][x1].tank->pbar->Go((3-tanklist[y1][x1].tank->kill)*33);
				if (tanklist[y1][x1].tank->kill==0)
					DestroyTank(tanklist[y1][x1].tank);
				else
					(tanklist[y1][x1].tank->kill)--;
				result=false;
		       }
		       break;
		case 3:if ( (bombloclist[y2][x2-1]!=NULL)&&(tanklist[y2][x1].tank!=bomb->tank) )
			{
				DeleteBomb(bombloclist[y2][x2-1]);
				result=false;
				break;
			}
		       if (x2==0)
		       {
				sp=bomb->pos.left-(((x2)*37)+pos.left+4);
				if (sp < step )  step=sp;
				if  (sp<=2)   result=false;
				else   result=true;
		       }
		       if (block[y2][x2]=='b')
				result =false;
		       else
		       if ( (tanklist[y2][x2].state!=0)&&(tanklist[y2][x2].tank!=bomb->tank) )
		       {
				tanklist[y2][x2].tank->pbar->Go((3-tanklist[y2][x2].tank->kill)*33);
				if (tanklist[y2][x2].tank->kill==0)
					DestroyTank(tanklist[y2][x2].tank);
				else
					(tanklist[y2][x2].tank->kill)--;
				result=false;
		       }
		       break;
		case 4:if ( (bombloclist[y2][x1+1]!=NULL)&&(x1<=8) )
			{
				DeleteBomb(bombloclist[y2][x1+1]);
				result=false;
				break;
			}
		       if (x2==9)
		       {
				sp=(((x2+1)*37)+pos.left+2)-(bomb->pos.left+bomb->pos.width);
				if (sp < step )  step=sp;
				if (sp<=2)   result=false;
				else   result=true;
		       }
		       if (block[y2][x1]=='b')
				result=false;
		       else
		       if ( (tanklist[y2][x1].state!=0)&&(tanklist[y2][x1].tank!=bomb->tank) )
		       {
				tanklist[y2][x1].tank->pbar->Go((3-tanklist[y2][x1].tank->kill)*33);
				if (tanklist[y2][x1].tank->kill==0)
					DestroyTank(tanklist[y2][x1].tank);
				else
					(tanklist[y2][x1].tank->kill)--;
				result=false;
		       }
		       break;
	}
	if (result==true)
	{
		bomb->MoveBomb(step);
		SetBombLoc(bomb);
	}
	else
		DeleteBomb(bomb);
	st=st;
}

void  TForm1::DeleteBomb(TBomb *bomb)
{
	int index,*poly;
	for(int i=0;i<=bombindex;i++)
		if (bomblist[i]==bomb)
		{
			for(int j=i;j<=bombindex;j++)
				bomblist[j]=bomblist[j+1];
			bombindex--;
			break;
		}
	bombloclist[bomb->y][bomb->x]=NULL;

       bomb->tank->index--;
       poly=fillpol(bomb->pos.left,bomb->pos.top,bomb->pos.left+bomb->pos.width+1,bomb->pos.top+bomb->pos.height+1);
       box(poly,0,0,1);


//	delete bomb;
	setcolor(0);
}

void TForm1::MoveEnemyTank(void)
{
       char state;
       int sp;
       if ( Application.GetActiveWindow()!=this->Handle() ) return;
       for(int i=0;i<3;i++)
	 if (enemy[i]!=NULL)
	 {
	       state=CreatePath(enemy[i],enemy[i]->state,&sp);
	       if (sp==0) state=0;
	       switch(state)
	       {
		       case 1:sp=SetStep(enemy[i]->speed,enemy[i]->pos,1);   //up
			      if ( (enemy[i]->state!=1)&&(sp!=0) )
			      {
				      enemy[i]->Clear();
				      position location=SetLocation(1,enemy[i]->state,enemy[i]);
				      enemy[i]->pos.left=location.x;
				      enemy[i]->pos.top=location.y-2;
				      if (TankFrame->Image1->y!=9)
					  enemy[i]->pos.top-=sp;
				      enemy[i]->LoadFromFile("image\\upet.gbf");
				      enemy[i]->state=1;
			       }
			       else enemy[i]->Move(-sp,0);
			       break;
			case 2:sp=SetStep(enemy[i]->speed,enemy[i]->pos,2);   //down
			      if ( (enemy[i]->state!=2)&&(sp!=0) )
			      {
				     enemy[i]->Clear();
				     if (enemy[i]->x==3){
					sp=sp;
				     }
				     position location=SetLocation(2,enemy[i]->state,enemy[i]);
				     enemy[i]->pos.left=location.x;
				     enemy[i]->pos.top=location.y+2;
				     if (TankFrame->Image1->y!=8)
					 enemy[i]->pos.top+=sp;
				     enemy[i]->LoadFromFile("image\\downet.gbf");
				     enemy[i]->state=2;
				}
			       else  enemy[i]->Move(sp,0);
			       break;
			case 3:sp=SetStep(enemy[i]->speed,enemy[i]->pos,3);   //left
			       if ( (enemy[i]->state!=3)&&(sp!=0) )
			       {
				     enemy[i]->Clear();
				     position location=SetLocation(3,enemy[i]->state,enemy[i]);
				     enemy[i]->pos.left=location.x-5;
				     enemy[i]->pos.top=location.y;
				     if (TankFrame->Image1->x!=0)
					 enemy[i]->pos.left-=sp;
				     enemy[i]->LoadFromFile("image\\leftet.gbf");
				     enemy[i]->state=3;
			       }
			       else  enemy[i]->Move(0,-sp);
			       break;
			case 4:sp=SetStep(enemy[i]->speed,enemy[i]->pos,4);   //right
			       if ( (enemy[i]->state!=4)&&(sp!=0) )
			       {
				      enemy[i]->Clear();
				      position location=SetLocation(4,enemy[i]->state,enemy[i]);
				      enemy[i]->pos.left=location.x;
				      enemy[i]->pos.top=location.y;
				      enemy[i]->pos.left+=sp;
				      enemy[i]->LoadFromFile("image\\rightet.gbf");
				      enemy[i]->state=4;
			       }
			       else  enemy[i]->Move(0,sp);
			       break;
		}
		if ( (enemy[i]->x==3)&&(enemy[i]->y==1) )
		{
			int i;
			i++;
		}
		enemy[i]->Bombing(tanklist);
		if (SetTankPos(enemy[i])==true)
		{
			Image1->pbar->Go(99);
			DestroyTank(Image1);
			EndMission();
		}
	  }
	  delay(40);
}


char TForm1::CreatePath(TImage *tank,char state,int *sp)
{
	int value[4]={0,0,0,0},max=0;
	char step[4];
	if ( (tank->x==6)&&(tank->y==4) )
	{
		step[0]=step[0];
	}
	for (int i=0;i<=3;i++)
		step[i]=tank->speed;
	for (i=0;i<4;i++)
		if ( CanDo(tank,i+1,&step[i+1])==true )	value[i]++;
		else  value[i]=0;
	for (i=tank->y;i<=9;i++)
		if ( (tanklist[i][tank->x].state=='m')&&(value[1]!=0) ) value[1]+=1;
	for (i=tank->y;i>=0;i--)
		if ( (tanklist[i][tank->x].state=='m')&&(value[0]!=0) ) value[0]+=1;
	for (i=tank->x;i>=0;i--)
		if ( (tanklist[tank->y][i].state=='m')&&(value[2]!=0) ) value[2]+=1;
	for (i=tank->x;i<=9;i++)
		if ( (tanklist[tank->y][i].state=='m')&&(value[3]!=0) ) value[3]+=1;
	if ( (tank->y > Image1->y)&&(value[0]!=0) ) value[0]+=1;
	if ( (tank->y < Image1->y)&&(value[1]!=0) ) value[1]+=1;
	if ( (tank->x > Image1->x)&&(value[2]!=0) ) value[2]+=1;
	if ( (tank->x < Image1->x)&&(value[3]!=0) ) value[3]+=1;
	for (i=1;i<=3;i++)
		if (value[i]>value[max])
			max=i;
	*sp=step[max+1];
	state=state;
	return (max+1);
}

void TForm1::EndMission(void)
{
	Lable5->SetCaption("GAME OVER");
	for (int i=0;i<3;i++)
	{
		if (enemy[i]!=NULL)
		switch(enemy[i]->state)
		{
			case 1:enemy[i]->LoadFromFile("image\\upet.gbf");
			       break;
			case 2:enemy[i]->LoadFromFile("image\\downet.gbf");
			       break;
			case 3:enemy[i]->LoadFromFile("image\\leftet.gbf");
			       break;
			case 4:enemy[i]->LoadFromFile("image\\rightet.gbf");
			       break;
		}
		enemy[i]=NULL;
	}
	end=true;
	for (i=500;i>=10;i-=40){
		sound(i);
		delay(5);
		nosound();
	}
	Application.UnHook(Handle());
}

void TForm1::DestroyTank(TImage *tank)
{
	int idx=0;
	tank->Clear();
	tanklist[tank->y][tank->x].state=0;
	tanklist[tank->y][tank->x].tank=NULL;
	if (tanklist[tank->y+1][tank->x].tank==tank)
	{
		tanklist[tank->y+1][tank->x].state=0;
		tanklist[tank->y+1][tank->x].tank=NULL;
	}
	if (tanklist[tank->y][tank->x+1].tank==tank)
	{
		tanklist[tank->y][tank->x+1].state=0;
		tanklist[tank->y][tank->x+1].tank=NULL;
	}
	for(int i=0;i<3;i++)
	{
		if (enemy[i]==tank) enemy[i]=NULL;
		if (enemy[i]==NULL) idx++;
	}
	tank->visible=false;
	tank->Clear();
	sound(481);
	delay(10);
	nosound();
	if (Image1->kill==0) EndMission();
	if (idx==3)  WinMission();
}

void TForm1::WinMission(void)
{
	Lable5->SetCaption("You Win..");
	end=true;
	Application.UnHook(Handle());
	for (int i=500;i<3000;i+=40){
		sound(i);
		delay(10);
		nosound();
	}
}
void TForm1::OnRefresh(Rect rec)
{
	rec=rec;
	refresh(rec.left+rec.width,rec.top+rec.height-30,rec.left+rec.width+30,rec.top+rec.height);
}