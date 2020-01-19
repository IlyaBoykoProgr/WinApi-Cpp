#ifndef Widgetsh
#define Widgetsh
#include "APIfunc.h"

class DropBox: public Widget{
public:
  DropBox(Window* parent, LPCWSTR name=L""):Widget(parent,name,WC_COMBOBOXW,CBS_DROPDOWN){
      SendMessageW(hWnd,CB_SETCURSEL,0,0);
  }
  DropBox* add(LPCWSTR string){
      SendMessageW(hWnd,CB_ADDSTRING,0,(LPARAM)string);return this;
  }
  int getIndex(){
      return SendMessageW(hWnd,CB_GETCURSEL,0,0);
  }
};

class Static: public Widget{
public:
  Static(Window* parent,LPCWSTR name=L""):Widget(parent,name){}
  void setText(LPCWSTR title){setTitle(title);}
};

class Edit: public Widget{
public:
    Edit(Window* parent,LPCWSTR name=L"",bool multiline=false)
        :Widget(parent,name,WC_EDITW,multiline ? ES_MULTILINE:0){}
    void getText(LPWSTR data,int maxsize=100){
	data= new WCHAR[maxsize];
	GetWindowTextW(hWnd,data,maxsize);
    }
};

class Progress:public Widget{
public:
    Progress* setRange(int min, int max){
	SendMessage(hWnd,PBM_SETRANGE,0,(LPARAM)MAKELPARAM(min,max));
	return this;
    }
    Progress* setStep(int step){
	SendMessage(hWnd,PBM_SETSTEP,step,0);
	return this;
    }
    Progress* setPos(int pos){
	SendMessage(hWnd,PBM_SETPOS,pos,0);
	return this;
    }
    Progress* step(){
	SendMessage(hWnd,PBM_STEPIT,0,0);
	return this;
    }
    Progress(Window* parent,LPCWSTR name=L""):
        Widget(parent,name,PROGRESS_CLASS){
    }
};

#endif//Widgets.h
