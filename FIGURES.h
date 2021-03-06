#ifndef FIGURESH
#define FIGURESH
#include "APIfunc.h"

#define RED RGB(255,0,0)
#define GREEN RGB(0,255,0)
#define BLUE RGB(0,0,255)
#define YELLOW RGB(255,255,0)
#define BLACK RGB(0,0,0)
#define WHITE RGB(255,255,255)
#define MAGENTA RGB(255,0,255)
#define GRAY RGB(100,100,100)
#define RANDOM RGB(rand()%255,rand()%255,rand()%255)


class ScreenObj{
public:
    int x=0,y=0,width=0,height=0;
    Window* stage;
    COLORREF brush=WHITE,pen=BLACK;
    HDC dc;
    ScreenObj* move(int newX,int newY){
	x=newX;y=newY;return this;
    }
    ScreenObj* resize(int newWdth, int newHght){
	width=newWdth;height=newHght;return this;
    }
    ScreenObj* color(COLORREF fill, COLORREF border=BLACK){
	brush=fill;pen=border;return this;
    }
    ScreenObj* clearDC(){
        DeleteDC(dc);dc=GetDC(stage->hWnd);
        return this;
    }
    bool hasPoint(int X, int Y){
	bool is=(x<X)&&(X<(x+width)) && (y<Y)&&(Y<(y+height));
	return is;
    }
    void virtual show(){}
    ScreenObj* hide(){
	COLORREF b=brush,p=pen;
	color(WHITE,WHITE)->
	show();color(b,p);return this;
    }
    virtual ~ScreenObj(){
        ReleaseDC(stage->hWnd,dc);DeleteDC(dc);
    }
};


class Square: public ScreenObj{
public:
    Square(Window* w=window){
        stage=w;
        dc=GetDC(stage->hWnd);
        if(dc==NULL)stage->message(L"Error. Cannot get window's dc.",L"PAINT ERROR",APP_ERROR_ICO);
    }
    void show(){
        HPEN p=CreatePen(PS_SOLID,1,pen);
        HBRUSH b=CreateSolidBrush(brush);
        SelectObject(dc,p);
        SelectObject(dc,b);
        Rectangle(dc,x,y,x+width,y+height);
	DeleteObject(p);
	DeleteObject(b);
    }
};
class Circle: public ScreenObj{
public:
    Circle(Window* w=window){
        stage=w;
        dc=GetDC(stage->hWnd);
        if(dc==NULL)stage->message(L"Error. Cannot get window's dc.",L"PAINT ERROR",APP_ERROR_ICO);
    }
    void show(){
        HPEN p=CreatePen(PS_SOLID,1,pen);
        HBRUSH b=CreateSolidBrush(brush);
        SelectObject(dc,p);
        SelectObject(dc,b);
	Ellipse(dc,x,y,x+width,y+height);
	DeleteObject(p);
	DeleteObject(b);
    }
};

#include <string>
class Box: public ScreenObj{
    LPCSTR text="";
    LPCSTR label="";
    bool strORnum=2;
public:
    const int height=40;
    Box(Window* w=window,LPCSTR caption=""){
        stage=w;
        label=caption;
        dc=GetDC(stage->hWnd);
        if(dc==NULL)stage->message(L"Error. Cannot get window's dc.",L"PAINT ERROR",APP_ERROR_ICO);
    }
    Box* setText(const char text[]){
        strORnum=1;
	this->text=text;return this;
    }
    Box* setNum(float number){
        strORnum=0;
        text=std::to_string(number).c_str();
	return this;
    }
    Box* setNum(int number){
        strORnum=0;
        text=std::to_string(number).c_str();
	return this;
    }
    Box* color(COLORREF fill, COLORREF border=BLACK){
	SetBkColor(dc,fill);SetTextColor(dc,border);
	return this;
    }
    void show(){
        HPEN p=CreatePen(PS_SOLID,1,pen);
        HBRUSH b=CreateSolidBrush(brush);
        SelectObject(dc,p);
        SelectObject(dc,b);
	std::string t=text, l=label;
	int v=(t.length()>l.length()?t:l).length();
	width=v*10>width?v*10:width;
	Rectangle(dc,x,y,x+width,y+height);
        TextOutA(dc,x+5,y+5,l.data(),l.length());
        if(strORnum==0)
        TextOutA(dc,x+5,y+20,t.data(),t.length()-2);
        else TextOutA(dc,x+5,y+20,t.data(),t.length());
	DeleteObject(p);
	DeleteObject(b);
    }
};

void printInt(Window* stage,int x,int y,int number,COLORREF bckg=WHITE, COLORREF text=BLACK){
    HDC dc= GetDC(stage->hWnd);
    SetBkColor(dc,bckg);SetTextColor(dc,text);
    TextOutA(dc,x,y,std::to_string(number).c_str(),std::to_string(number).length());
    ReleaseDC(stage->hWnd,dc);DeleteDC(dc);DeleteObject(dc);
}
void printChar(Window* stage,int x,int y,const char* symbol,COLORREF bckg=WHITE, COLORREF text=BLACK){
    HDC dc= GetDC(stage->hWnd);
    SetBkColor(dc,bckg);SetTextColor(dc,text);
    std::string s=symbol;
    TextOutA(dc,x,y,s.c_str(),s.length());
    ReleaseDC(stage->hWnd,dc);DeleteDC(dc);DeleteObject(dc);
}

void drawLine(Window* stage,int x1,int y1,int x2, int y2,COLORREF col=BLACK,unsigned width=1){
    HDC dc= GetDC(stage->hWnd);
    SelectObject(dc,CreatePen(PS_SOLID,width,col));
    MoveToEx(dc,x1,y1,NULL);
    LineTo(dc,x2,y2);
    ReleaseDC(stage->hWnd,dc);DeleteDC(dc);DeleteObject(dc);
}

template<int items>
class Group{
    ScreenObj *figures[items];
    ScreenObj *none=new ScreenObj;
public:
    Group(){
	loop(items,i)figures[i]=none;
    }
    Group* show(){
	loop(items,i){
	    figures[i]->show();
	}
	return this;
    }
    Group* hide(){
	loop(items,i){
	    figures[i]->erase();
	}
	return this;
    }
    Group* operator<< (class ScreenObj* obj){
	int i=0;
	while(figures[i]!=none)i++;
	figures[i]=obj;
	return this;
    }
};
#endif//FIGUES.H
