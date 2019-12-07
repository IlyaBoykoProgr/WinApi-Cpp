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
    WCHAR* data=new WCHAR;
public:
    Edit(Window* parent,LPCWSTR name=L"",bool multiline=false)
        :Widget(parent,name,WC_EDITW,multiline ? ES_MULTILINE:0){}
    WCHAR* getText(int maxsize=100){
	delete data;data= new WCHAR[maxsize];
	GetWindowTextW(hWnd,data,maxsize);
	return data;
    }
};

#endif//Widgets.h
