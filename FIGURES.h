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
    COLORREF brush=WHITE,pen=BLACK;
    HDC dc;
    ScreenObj* place(int newX,int newY){
	x=newX;y=newY;return this;
    }
    ScreenObj* resize(int newWdth, int newHght){
	width=newWdth;height=newHght;return this;
    }
    ScreenObj* color(COLORREF fill, COLORREF border=BLACK){
	brush=fill;pen=border;return this;
    }
    bool hasPoint(int X, int Y){
	bool is=(x<X)&&(X<(x+width)) && (y<Y)&&(Y<(y+height));
	return is;
    }
    virtual void show(){}
    ScreenObj* erase(){
	color(WHITE,WHITE)->
	show();return this;
    }
    ~ScreenObj(){
	DeleteObject(dc);
    }
};


class Square: public ScreenObj{
public:
    Square(Window* stage=window){dc=GetDC(stage->hWnd);}
    void show(){
	SelectObject(dc,CreatePen(PS_SOLID,1,pen));
	SelectObject(dc,CreateSolidBrush(brush));
	Rectangle(dc,x,y,x+width,y+height);
    }
};
class Circle: public ScreenObj{
public:
    Circle(Window* stage=window){dc=GetDC(stage->hWnd);}
    void show(){
	SelectObject(dc,CreatePen(PS_SOLID,1,pen));
	SelectObject(dc,CreateSolidBrush(brush));
	Ellipse(dc,x,y,x+width,y+height);
    }
};

#include <string>
class Box: public ScreenObj{
    LPCSTR text="";
    LPCSTR label="";
public:
    const int height=40;
    Box(Window* stage=window,LPCSTR caption=""){dc=GetDC(stage->hWnd);label=caption;}
    Box* setText(char text[]){
	this->text=text;return this;
    }
    Box* setNum(double number){
	std::string ws = std::to_string(number);
	text=ws.c_str();
	return this;
    }
    Box* color(COLORREF fill, COLORREF border=BLACK){
	SetBkColor(dc,fill);SetTextColor(dc,border);
	return this;
    }
    void show(){
	SelectObject(dc,CreatePen(PS_SOLID,1,pen));
	SelectObject(dc,CreateSolidBrush(brush));
	std::string t=text, l=label;
	int v=(t.length()>l.length()?t:l).length();
	width=v*10>width?v*10:width;
	Rectangle(dc,x,y,x+width,y+height);
	TextOutA(dc,x+5,y+5,l.data(),l.length());
	TextOutA(dc,x+5,y+20,t.data(),t.length());
    }
};

void printInt(Window* stage,int x,int y,int number,COLORREF bckg=WHITE, COLORREF text=BLACK){
    HDC dc= GetDC(stage->hWnd);
    SetBkColor(dc,bckg);SetTextColor(dc,text);
    TextOutA(dc,x,y,std::to_string(number).c_str(),1);
    DeleteObject(dc);
}
void printChar(Window* stage,int x,int y,char symbol,COLORREF bckg=WHITE, COLORREF text=BLACK){
    HDC dc= GetDC(stage->hWnd);
    SetBkColor(dc,bckg);SetTextColor(dc,text);
    TextOutA(dc,x,y,&symbol,1);
    DeleteObject(dc);
}

void drawLine(Window* stage,int x1,int y1,int x2, int y2,COLORREF col=BLACK,unsigned width=1){
    HDC dc= GetDC(stage->hWnd);
    SelectObject(dc,CreatePen(PS_SOLID,width,col));
    MoveToEx(dc,x1,y1,NULL);
    LineTo(dc,x2,y2);
    DeleteObject(dc);
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
    Group* erase(){
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
