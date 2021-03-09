void TestObjSub(position pos,TObject *Me,TObject *obj);
void Form1_OnKeyPress(int key,int tmp);

Start_Menu::Start_Menu(int pwnd):TWindow(pwnd)
{
	FILE *f;
	char item[10][30],tmp[30];
	int index=-1,x1,y1,x2,y2,t1,t2,*poly;
	long int size;
	void huge *buf;
	visible=true;
	allowdown=false;
	itemindex=-1;
	strcpy(name,"StartMenu");
	strcpy(classname,"Start_Menu");
	Mouse.hide();
	f=fopen("StartMenu.gmf","rb");
	if (!f){
		f=fopen("StartMenu.gmf","wb");
		if (f){
			fprintf(f,"items:");
			fclose(f);
			f=fopen("StartMenu.gmf","rb");
		}
	}
	if (f) fscanf(f,"%s\n",tmp);
	t2=textwidth("Shout Down");
	strcpy(item[0],"Shout Down");
	strcpy(item[1],"Run");
	index=1;
	if (f)
	while (!feof(f)){
		index++;
		fgets(tmp,255,f);
		if (tmp[strlen(tmp)-1]=='\n') tmp[strlen(tmp)-2]='\x0';
		strcpy(item[index],tmp);
		if (textwidth(tmp) > t2)  t2=textwidth(tmp);
	};
	fclose(f);
	t1=26*(index);
	t2+=8+28+6+20;
	len=t2;
	t1+=7;
	items=index;
	if (t1<130) t1=130;
	f=fopen("TempFile.gtp","wb");
	size=imagesize(0,getmaxy()-25-t1,t2,getmaxy()-25);
	buf=malloc(size);
	getimage(0,getmaxy()-25-t1,t2,getmaxy()-25,buf);
	fprintf(f,"%ld %d %d",size,0,getmaxy()-25-t1);
	fwrite((void *)buf,size,1,f);
	fclose(f);
	free((void *)buf);
	pos.top=getmaxy()-25-t1;
	pos.left=0;
	pos.width=t2;
	pos.height=t1;
	setcolor(15);
	rectangle(0,getmaxy()-26-t1,t2,getmaxy()-26);
	rectangle(1,getmaxy()-26-t1+1,t2-1,getmaxy()-26-1);
	setcolor(0);
	line(0,getmaxy()-26,t2,getmaxy()-26);
	line(t2,getmaxy()-26-t1,t2,getmaxy()-26);
	setcolor(8);
	line(t2-1,getmaxy()-26-t1+1,t2-1,getmaxy()-26-2);
	line(0,getmaxy()-26-1,t2,getmaxy()-26-1);
	poly=fillpol(29,getmaxy()-26-t1+2,t2-2,getmaxy()-26-2);
	setcolor(7);
	setfillstyle(1,7);
	fillpoly(4,poly);
	free(poly);
	setcolor(1);
	poly=fillpol(3,getmaxy()-26-t1+2,28,getmaxy()-26-2);
	setfillstyle(1,1);
	fillpoly(4,poly);
	free(poly);
	settextstyle(1, 1, 1);
	setcolor(15);
	outtextxy(2,340,"Reza Ghale");
	settextstyle(0,0,1);
	setcolor(0);
	for(int i=0;i<=index;i++)
	{
		strcpy(Item[i],item[i]);
		outtextxy(55,437-(i*26),item[i]);
	}
	f=fopen("icon.gbf","rb");
	buf=(unsigned char *)malloc(258);
///shout down icon
	fread((void *)buf,258,2,f);
	putimage(30,452-22,buf,0);
	free((void *)buf);
//run icon
//	run=(unsigned char *)malloc(258);
//	fread(run,258,2,f);
//	putimage(30,452-47,run,0);
	fclose(f);
	setcolor(8);
	line(30,452-27,t2-3,452-27);
	setcolor(15);
	line(30,452-26,t2-3,452-26);
	StartButton->allowup=false;
	StartButton->allowhint=false;
	len=t2;
	l_dv=l_md=-1;
	Mouse.show();
	GetPicture();
	this->active=false;
	Application.SetActiveWindow(this);
}

void Start_Menu::SetMenu(void)
{
	int *poly,st;
	if (SMenu->l_md<0) return;
	itemindex=-1;
	Mouse.hide();
	setcolor(7);
	if (SMenu->l_md==0){
		st=51;
		line(29,453-(SMenu->l_md*26)-23,29,453-(((SMenu->l_md)*26)+3));
	}
	else st=29;
	poly=fillpol(st,453-(SMenu->l_md*26)-23,SMenu->len-2,453-(((SMenu->l_md)*26)+3));
	setfillstyle(1,7);
	fillpoly(4,poly);
	free(poly);
	setcolor(0);
	outtextxy(55,453-(SMenu->l_md*26)-16,SMenu->Item[SMenu->l_md]);
	Mouse.show();
}

Start_Menu::~Start_Menu(void)
{
	position pos;
	Application.UnHook(Handle());
	Mouse.hide();
	StartButton->allowup=true;
	StartButton->allowhint=true;
	StartButton->UnClick();
	FILE *f;
/*	int x,y;
	long int size;
	void huge *buf;
	f=fopen("tempfile.gtp","rb");
	fscanf(f,"%ld %d %d",&size,&x,&y);
	buf=malloc(size);
	fread((void *)buf,size,1,f);
	putimage(x,y,buf,0);
	free((void *)buf);*/
	DoOperation();
	fclose(f);
	Mouse.show();
	Hide();
}

void Start_Menu::DoOperation(void)
{
	if (itemindex<0) return;
	switch (itemindex){
		case 0: Rect pos;
			pos.left=220;
			pos.top=170;
			pos.width=200;
			pos.height=100;
			s = new _ShoutDown(0);
			s->pos=pos;
			s->maximize=s->minimize=false;
			s->PaintForm(0,7,0);
			s->lable1= new TLable(s->Handle());
			s->lable1->SetName("Label1");
			pos.top=30;
			pos.left=20;
			s->lable1->pos=pos;
			s->lable1->SetCaption("Do you want to exit ?");
			break;
		case 1: Rect loc;
			loc.top=20;
			loc.left=20;
			loc.height=220;
			loc.width=180;
			TestObj = new TForm2;
			TestObj->pos=loc;
			TestObj->SetClassname("TForm2");
			TestObj->PaintForm(15,7,0);

			TestObj->Lable1 = new TLable(TestObj->Handle());
			TestObj->Lable1->SetName("Label1");
			loc.top=30;
			loc.left=10;
			TestObj->Lable1->pos=loc;
			TestObj->Lable1->parentcolor=7;
			TestObj->Lable1->SetCaption("Handle");
			TestObj->Lable1->SetColor(0);

			TestObj->Lable2 = new TLable(TestObj->Handle());
			TestObj->Lable2->SetName("Label2");
			loc.top=50;
			loc.left=10;
			TestObj->Lable2->pos=loc;
			TestObj->Lable2->parentcolor=7;
			TestObj->Lable2->SetCaption("Name");
			TestObj->Lable2->SetColor(0);

			TestObj->Lable3 = new TLable(TestObj->Handle());
			TestObj->Lable3->SetName("Label3");
			loc.top=70;
			loc.left=10;
			TestObj->Lable3->pos=loc;
			TestObj->Lable3->parentcolor=7;
			TestObj->Lable3->SetCaption("ClassName");
			TestObj->Lable3->SetColor(0);

			TestObj->Lable4 = new TLable(TestObj->Handle());
			TestObj->Lable4->SetName("Label4");
			loc.top=90;
			loc.left=10;
			TestObj->Lable4->pos=loc;
			TestObj->Lable4->parentcolor=7;
			TestObj->Lable4->SetCaption("Parent Handle");
			TestObj->Lable4->SetColor(0);

			TestObj->Lable5 = new TLable(TestObj->Handle());
			TestObj->Lable5->SetName("Label5");
			loc.top=110;
			loc.left=10;
			TestObj->Lable5->pos=loc;
			TestObj->Lable5->parentcolor=7;
			TestObj->Lable5->SetCaption("Position ");
			TestObj->Lable5->SetColor(15);

			TestObj->Lable6 = new TLable(TestObj->Handle());
			TestObj->Lable6->SetName("Lable6");
			loc.top=130;
			loc.left=10;
			TestObj->Lable6->pos=loc;
			TestObj->Lable6->parentcolor=7;
			TestObj->Lable6->SetCaption("Left");
			TestObj->Lable6->SetColor(0);

			TestObj->Lable7 = new TLable(TestObj->Handle());
			TestObj->Lable7->SetName("Lable7");
			loc.top=130;
			loc.left=85;
			TestObj->Lable7->pos=loc;
			TestObj->Lable7->parentcolor=7;
			TestObj->Lable7->SetCaption("Top");
			TestObj->Lable7->SetColor(0);

			TestObj->Lable8 = new TLable(TestObj->Handle());
			TestObj->Lable8->SetName("Label8");
			loc.top=150;
			loc.left=10;
			TestObj->Lable8->pos=loc;
			TestObj->Lable8->parentcolor=7;
			TestObj->Lable8->SetCaption("width");
			TestObj->Lable8->SetColor(0);

			TestObj->Lable9 = new TLable(TestObj->Handle());
			TestObj->Lable9->SetName("Label9");
			loc.top=150;
			loc.left=85;
			TestObj->Lable9->pos=loc;
			TestObj->Lable9->parentcolor=7;
			TestObj->Lable9->SetCaption("height");
			TestObj->Lable9->SetColor(0);

			TestObj->Lable10 = new TLable(TestObj->Handle());
			TestObj->Lable10->SetName("Label10");
			loc.top=170;
			loc.left=10;
			TestObj->Lable10->pos=loc;
			TestObj->Lable10->parentcolor=7;
			TestObj->Lable10->SetCaption("Mouse Position");
			TestObj->Lable10->SetColor(15);

			TestObj->Lable11 = new TLable(TestObj->Handle());
			TestObj->Lable11->SetName("Label11");
			loc.top=190;
			loc.left=10;
			TestObj->Lable11->pos=loc;
			TestObj->Lable11->parentcolor=7;
			TestObj->Lable11->SetCaption("X");
			TestObj->Lable11->SetColor(0);

			TestObj->Lable12 = new TLable(TestObj->Handle());
			TestObj->Lable12->SetName("Label12");
			loc.top=190;
			loc.left=85;
			TestObj->Lable12->pos=loc;
			TestObj->Lable12->parentcolor=7;
			TestObj->Lable12->SetCaption("Y");
			TestObj->Lable12->SetColor(0);

			TestObj->Lable13 = new TLable(TestObj->Handle());
			TestObj->Lable13->SetName("Label13");
			loc.top=50;
			loc.left=80;
			TestObj->Lable13->pos=loc;
			TestObj->Lable13->parentcolor=7;
			TestObj->Lable13->SetCaption(" ");
			TestObj->Lable13->SetColor(14);

			TestObj->Lable14 = new TLable(TestObj->Handle());
			TestObj->Lable14->SetName("Label14");
			loc.top=30;
			loc.left=80;
			TestObj->Lable14->pos=loc;
			TestObj->Lable14->parentcolor=7;
			TestObj->Lable14->SetCaption(" ");
			TestObj->Lable14->SetColor(14);

			TestObj->Lable15 = new TLable(TestObj->Handle());
			TestObj->Lable15->SetName("Label15");
			loc.top=70;
			loc.left=90;
			TestObj->Lable15->pos=loc;
			TestObj->Lable15->parentcolor=7;
			TestObj->Lable15->SetCaption(" ");
			TestObj->Lable15->SetColor(14);

			TestObj->Lable16 = new TLable(TestObj->Handle());
			TestObj->Lable16->SetName("Lable16");
			loc.top=90;
			loc.left=130;
			TestObj->Lable16->pos=loc;
			TestObj->Lable16->parentcolor=7;
			TestObj->Lable16->SetCaption(" ");
			TestObj->Lable16->SetColor(14);

			TestObj->Lable17 = new TLable(TestObj->Handle());
			TestObj->Lable17->SetName("Lable17");
			loc.top=130;
			loc.left=50;
			TestObj->Lable17->pos=loc;
			TestObj->Lable17->parentcolor=7;
			TestObj->Lable17->SetCaption(" ");
			TestObj->Lable17->SetColor(14);
			TestObj->GetPicture();

			TestObj->Lable18 = new TLable(TestObj->Handle());
			TestObj->Lable18->SetName("Lable18");
			loc.top=130;
			loc.left=125;
			TestObj->Lable18->pos=loc;
			TestObj->Lable18->parentcolor=7;
			TestObj->Lable18->SetCaption(" ");
			TestObj->Lable18->SetColor(14);
			TestObj->GetPicture();

			TestObj->Lable19 = new TLable(TestObj->Handle());
			TestObj->Lable19->SetName("Lable19");
			loc.top=150;
			loc.left=55;
			TestObj->Lable19->pos=loc;
			TestObj->Lable19->parentcolor=7;
			TestObj->Lable19->SetCaption(" ");
			TestObj->Lable19->SetColor(14);
			TestObj->GetPicture();

			TestObj->Lable20 = new TLable(TestObj->Handle());
			TestObj->Lable20->SetName("Lable20");
			loc.top=150;
			loc.left=140;
			TestObj->Lable20->pos=loc;
			TestObj->Lable20->parentcolor=7;
			TestObj->Lable20->SetCaption(" ");
			TestObj->Lable20->SetColor(14);
			TestObj->GetPicture();

			TestObj->Lable21 = new TLable(TestObj->Handle());
			TestObj->Lable21->SetName("Lable21");
			loc.top=190;
			loc.left=40;
			TestObj->Lable21->pos=loc;
			TestObj->Lable21->parentcolor=7;
			TestObj->Lable21->SetCaption(" ");
			TestObj->Lable21->SetColor(14);
			TestObj->GetPicture();

			TestObj->Lable22 = new TLable(TestObj->Handle());
			TestObj->Lable22->SetName("Lable22");
			loc.top=190;
			loc.left=110;
			TestObj->Lable22->pos=loc;
			TestObj->Lable22->parentcolor=7;
			TestObj->Lable22->SetCaption(" ");
			TestObj->Lable22->SetColor(14);
			TestObj->GetPicture();

			TestObj->GetPicture();
			Application.Hook(TestObj,MW_MOUSEMOVE,TestObjSub);

			break;
		case 2: if (TankFrame!=NULL) break;
			loc.top=20;
			loc.left=120;
			loc.height=415;
			loc.width=481;
			TankFrame = new TForm1;
			TankFrame->pos=loc;
			TankFrame->SetClassname("TForm1");
			TankFrame->PaintForm(15,0,1);
			TankFrame->Panel1 = new TPanel(TankFrame->Handle());
			TankFrame->Panel1->SetName("Panel1");
			TankFrame->Panel1->SetClassname("TPanel");
			loc.top=42;
			loc.left=496;
			loc.height=369;
			loc.width=100;
			TankFrame->Panel1->pos=loc;
			TankFrame->Panel1->Paint(8,8);

			TankFrame->Lable1= new TLable(TankFrame->Handle());
			TankFrame->Lable1->SetName("Label1");
			loc.top=65;
			loc.left=390;
			TankFrame->Lable1->pos=loc;
			TankFrame->Lable1->SetCaption("Your Tank");

			TankFrame->pbar1= new TProgressBar(TankFrame->Handle());
			TankFrame->pbar1->SetName("ProgressBar1");
			loc.top=50;
			loc.left=253;
			loc.width=80;
			loc.height=15;
			TankFrame->pbar1->textcolor=15;
			TankFrame->pbar1->backcolor=8;
			TankFrame->pbar1->fillcolor=4;
			TankFrame->pbar1->pos=loc;
			TankFrame->pbar1->Show();


			TankFrame->Lable2= new TLable(TankFrame->Handle());
			TankFrame->Lable2->SetName("Label2");
			loc.top=105;
			loc.left=385;
			TankFrame->Lable2->pos=loc;
			TankFrame->Lable2->SetCaption("Enemy Tank1");

			TankFrame->pbar2= new TProgressBar(TankFrame->Handle());
			TankFrame->pbar2->SetName("ProgressBar2");
			loc.top=70;
			loc.left=253;
			loc.width=80;
			loc.height=15;
			TankFrame->pbar2->textcolor=15;
			TankFrame->pbar2->backcolor=8;
			TankFrame->pbar2->fillcolor=4;
			TankFrame->pbar2->pos=loc;
			TankFrame->pbar2->Show();

			TankFrame->Lable3= new TLable(TankFrame->Handle());
			TankFrame->Lable3->SetName("Label3");
			loc.top=145;
			loc.left=385;
			TankFrame->Lable3->pos=loc;
			TankFrame->Lable3->SetCaption("Enemy Tank2");

			TankFrame->pbar3= new TProgressBar(TankFrame->Handle());
			TankFrame->pbar3->SetName("ProgressBar3");
			loc.top=90;
			loc.left=253;
			loc.width=80;
			loc.height=15;
			TankFrame->pbar3->textcolor=15;
			TankFrame->pbar3->backcolor=8;
			TankFrame->pbar3->fillcolor=4;
			TankFrame->pbar3->pos=loc;
			TankFrame->pbar3->Show();

			TankFrame->Lable4= new TLable(TankFrame->Handle());
			TankFrame->Lable4->SetName("Label4");
			loc.top=185;
			loc.left=385;
			TankFrame->Lable4->pos=loc;
			TankFrame->Lable4->SetCaption("Enemy Tank3");

			TankFrame->pbar4= new TProgressBar(TankFrame->Handle());
			TankFrame->pbar4->SetName("ProgressBar4");
			loc.top=110;
			loc.left=253;
			loc.width=80;
			loc.height=15;
			TankFrame->pbar4->textcolor=15;
			TankFrame->pbar4->backcolor=8;
			TankFrame->pbar4->fillcolor=4;
			TankFrame->pbar4->pos=loc;
			TankFrame->pbar4->Show();

			TankFrame->Lable5= new TLable(TankFrame->Handle());
			TankFrame->Lable5->SetName("Label5");
			loc.top=300;
			loc.left=390;
			TankFrame->Lable5->pos=loc;
			TankFrame->Lable5->parentcolor=8;
//			TankFrame->Lable5->SetCaption("Mission 1");
			TankFrame->Lable5->SetColor(4);

			TankFrame->Lable6= new TLable(TankFrame->Handle());
			TankFrame->Lable6->SetName("Label6");
			loc.top=400;
			loc.left=110;
			TankFrame->Lable6->pos=loc;
			TankFrame->Lable6->parentcolor=8;
			TankFrame->Lable6->SetCaption("Press < F2 > For State Game ...");
			TankFrame->Lable6->SetColor(1);

			TankFrame->Image1 = new TImage(TankFrame->Handle());
			TankFrame->Image1->SetHint("Your Tank");
			TankFrame->Image1->pbar=TankFrame->pbar1;
/*			loc.top=360;
			loc.left=90;
			TankFrame->Image1->pos=loc;
			position location=TankFrame->SetLocation(1,1,TankFrame->Image1);
			loc.left=location.x;
			loc.top=location.y;
			TankFrame->Image1->pos=loc;
			TankFrame->Image1->LoadFromFile("image\\uptank.gbf");
			TankFrame->Image1->id='m';
			TankFrame->SetTankPos(TankFrame->Image1);
			TankFrame->Image1->SetHint("Your Tank");
			TankFrame->Image1->state=1;
			TankFrame->Image1->visible=true;
			TankFrame->Image1->speed=15;
			TankFrame->Image1->pbar=TankFrame->pbar1;*/

			TankFrame->Image2 = new TImage(TankFrame->Handle());
			TankFrame->Image2->SetHint("Enemy Tank");
			TankFrame->Image2->pbar=TankFrame->pbar2;
/*			loc.top=50;
			loc.left=90;
			TankFrame->Image2->pos=loc;
			location=TankFrame->SetLocation(1,1,TankFrame->Image2);
			loc.left=location.x;
			loc.top=location.y;
			TankFrame->Image2->pos=loc;
			TankFrame->Image2->LoadFromFile("image\\downet.gbf");
			TankFrame->Image2->id='e';
			TankFrame->SetTankPos(TankFrame->Image2);
			TankFrame->Image2->SetHint("Enemy Tank");
			TankFrame->Image2->state=2;
			TankFrame->Image2->visible=true;
			TankFrame->Image2->speed=1;
			TankFrame->Image2->pbar=TankFrame->pbar2;*/

			TankFrame->Image3 = new TImage(TankFrame->Handle());
			TankFrame->Image3->SetHint("Enemy Tank");
			TankFrame->Image3->pbar=TankFrame->pbar3;
/*			loc.top=50;
			loc.left=400;
			TankFrame->Image3->pos=loc;
			location=TankFrame->SetLocation(4,4,TankFrame->Image3);
			loc.left=location.x;
			loc.top=location.y;
			TankFrame->Image3->pos=loc;
			TankFrame->Image3->LoadFromFile("image\\rightet.gbf");
			TankFrame->Image3->id='e';
			TankFrame->SetTankPos(TankFrame->Image3);
			TankFrame->Image3->SetHint("Enemy Tank");
			TankFrame->Image3->state=4;
			TankFrame->Image3->visible=true;
			TankFrame->Image3->speed=1;
			TankFrame->Image3->pbar=TankFrame->pbar3;*/

/*			TankFrame->Image4 = new TImage(TankFrame->Handle());
			loc.top=50;
			loc.left=300;
			TankFrame->Image4->pos=loc;
			location=TankFrame->SetLocation(4,4,TankFrame->Image4);
			loc.left=location.x;
			loc.top=location.y;
			TankFrame->Image4->pos=loc;
			TankFrame->Image4->LoadFromFile("image\\leftet.gbf");
			TankFrame->Image4->id='e';
			TankFrame->SetTankPos(TankFrame->Image4);
			TankFrame->Image4->SetHint("Enemy Tank");
			TankFrame->Image4->state=3;
			TankFrame->Image4->visible=true;
			TankFrame->Image4->speed=1;
			TankFrame->Image4->pbar=TankFrame->pbar4;*/

/*			TankFrame->enemy[0]=TankFrame->Image2;
			TankFrame->enemy[1]=TankFrame->Image3;
//			TankFrame->enemy[2]=TankFrame->Image4;*/
			TankFrame->OnKeyPress=Form1_OnKeyPress;


/*			int *poly;
			poly=fillpol(140,50,143,53);
			box(poly,14,14,1);*/


//			TankFrame->Image1->refresh;
/*			int *poly;
//------------------------------------------------------------
			poly=fillpol(40,130,43,155);
			box(poly,8,8,6);

			poly=fillpol(44,133,58,152);
			box(poly,15,4,1);
			setcolor(15);
			line(44,133,44,152);
			line(44,133,58,133);

			poly=fillpol(59,130,62,155);
			box(poly,8,8,6);

			poly=fillpol(48,139,54,145);
			box(poly,15,15,1);
			setcolor(15);
			line(48,139,54,139);
			line(48,139,48,145);


			poly=fillpol(50,138,52,120);
			box(poly,8,8,1);
			Application.getbmp(40,120,62,155,"image\\upet.gbf");
//----------------------------------------------------
//			int *poly;
			poly=fillpol(40,230,43,255);
			box(poly,8,8,6);

			poly=fillpol(44,233,58,252);
			box(poly,15,4,1);
			setcolor(15);
			line(44,233,44,252);
			line(44,233,58,233);

			poly=fillpol(59,230,62,255);
			box(poly,8,8,6);

			poly=fillpol(48,239,54,245);
			box(poly,15,15,1);
			setcolor(15);
			line(48,239,54,239);
			line(48,239,48,245);

			poly=fillpol(50,246,52,263);
			box(poly,8,8,1);
//			poly=fillpol(50,138,52,120);
			Application.getbmp(40,230,62,265,"image\\downet.gbf");
//-------------------------------------------------------------
//			int *poly;
			poly=fillpol(100,130,125,133);
			box(poly,8,8,6);

			poly=fillpol(103,134,122,148);
			box(poly,15,4,1);
			setcolor(15);
			line(103,134,122,134);
			line(103,134,103,148);

			poly=fillpol(100,149,125,152);
			box(poly,8,8,6);

			poly=fillpol(110,138,116,144);
			box(poly,15,15,1);
			setcolor(15);
			line(110,138,116,138);
			line(110,138,110,144);

			poly=fillpol(109,140,91,142);
			box(poly,8,8,1);
			Application.getbmp(91,130,125,152,"image\\leftet.gbf");

//--------------------------------------------------------------
			poly=fillpol(100,230,125,233);
			box(poly,8,8,6);

			poly=fillpol(103,234,122,248);
			box(poly,15,4,1);
			setcolor(15);
			line(103,234,122,234);
			line(103,234,103,248);

			poly=fillpol(100,249,125,252);
			box(poly,8,8,6);

			poly=fillpol(110,238,116,244);
			box(poly,15,15,1);
			setcolor(15);
			line(110,238,116,238);
			line(110,238,110,244);

			poly=fillpol(117,240,135,242);
			box(poly,8,8,1);
			Application.getbmp(100,230,135,252,"image\\rightet.gbf");*/

//			WINDOW(40,43,130,155,7,6,0);
/*			Panels[0]= new TPanel(Form1->Handle());
			Panels[0]->SetName("Panel1");
			Panels[0]->SetClassname("TPanel");
			loc.top=73;
			loc.left=60;
			loc.height=70;
			loc.width=70;
			Panels[0]->pos=loc;
			Panels[0]->Paint(7,15);*/

/*			getch();
			for(int i=0;i<30;i++)
			{
				delay(10);
				TankFrame->Image1->Move(-10,0);
//					TankFrame->Image1->refresh(x1,y1,x2,y2);
			}*/
//			TankFrame->GetPicture();
//			Application.SetActiveWindow(Form1);
			TankFrame->StartNextMission();
			break;
	}
};

