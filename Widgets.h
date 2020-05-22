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
	GetWindowTextW(hWnd,data,maxsize);
    }
};

class Progress:public Widget{
public:
    Progress(Window* parent,LPCWSTR name=L""):
        Widget(parent,name,PROGRESS_CLASS,PBS_MARQUEE|PBS_SMOOTH){
	setRange(0,100)->setStep(1)->setPos(0);
	SendMessage(hWnd,PBM_SETBARCOLOR,0,(DWORD)(240)<<8);
    }
    inline Progress* setRange(int min, int max){
	SendMessage(hWnd,PBM_SETRANGE,0,(LPARAM)MAKELPARAM(min,max));
	return this;
    }
    inline Progress* setStep(int step){
	SendMessage(hWnd,PBM_SETSTEP,step,0);
	return this;
    }
    inline Progress* setPos(int pos){
	SendMessage(hWnd,PBM_SETPOS,pos,0);
	return this;
    }
    inline Progress* step(){
	SendMessage(hWnd,PBM_STEPIT,0,0);
	return this;
    }
    inline int getPos(){
	return SendMessage(hWnd,PBM_GETPOS,0,0);
    }
    Progress* setLoading(bool isLoad){
	SendMessage(hWnd,PBM_SETMARQUEE,(int)isLoad,0);
	return this;
    }
};

#endif//Widgets.h
