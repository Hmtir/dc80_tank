TObject::TObject(int pwnd)
{
	p_handle=pwnd;
	TObject *t;
	selfZ=NULL;
	t=Application.GetObject(pwnd);
	if (t!=NULL)
		handle=Application.PushZ(this,&(t->selfZ));
	else
		handle=Application.PushZ(this,&(Application.start));
	hint[0]='\x0';
	showhint=false;
	OnMouseMove=NULL;
	OnMouseClick=NULL;
	OnMouseUp=NULL;
	OnKeyPress=NULL;
	OnStartDrag=NULL;
	OnEndDrag=NULL;
	this->allowhint=true;
	this->allowup=true;
	this->allowdown=true;
	this->allowderag=false;
	this->visible=false;
	this->active=false;
};

void TObject::SetHint(char *Hint)
{
	if (hint!=NULL){
		showhint=true;
		strcpy(hint,Hint);
	}
	else{
		strcpy(hint,NULL);
		showhint=false;
	}
};

HWND TObject::Handle(void)
{
	return handle;
};

HWND TObject::P_Handle(void)
{
	return p_handle;
};

void TObject::SetName(char *Name)
{
	strcpy(name,Name);
}

TObject::~TObject(void)
{
	TObject *parent;
	if (P_Handle()==0)
		parent=NULL;
	else
		parent=Application.GetObject(P_Handle());
	Application.RemoveChild(parent,Handle());
	Application.DeleteObjectList(Handle());
};