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
};


class Square: public ScreenObj{
public:
    Square(Window* stage){dc=GetDC(stage->hWnd);}
    void show(){
	SelectObject(dc,CreatePen(PS_SOLID,1,pen));
	SelectObject(dc,CreateSolidBrush(brush));
	Rectangle(dc,x,y,x+width,y+height);
    }
};
void inline printSquare(Window* stage,int x, int y, int width, int height, COLORREF fill=WHITE, COLORREF border=BLACK){
    HDC d=GetDC(stage->hWnd);
    SelectObject(d,CreatePen(PS_SOLID,1,border));
    SelectObject(d,CreateSolidBrush(fill));
    Rectangle(d,x,y,x+width,y+height);
}
class Circle: public ScreenObj{
public:
    Circle(Window* stage){dc=GetDC(stage->hWnd);}
    void show(){
	SelectObject(dc,CreatePen(PS_SOLID,1,pen));
	SelectObject(dc,CreateSolidBrush(brush));
	Ellipse(dc,x,y,x+width,y+height);
    }
};
void printCircle(Window* stage,int x, int y, int width, int height, COLORREF fill=WHITE, COLORREF border=BLACK){
    HDC d=GetDC(stage->hWnd);
    SelectObject(d,CreatePen(PS_SOLID,1,border));
    SelectObject(d,CreateSolidBrush(fill));
    Ellipse(d,x,y,x+width,y+height);
}

#include <string>
class Box: public ScreenObj{
    LPCSTR text;
    LPCSTR label;
public:
    const int height=40;
    Box(Window* stage,LPCSTR caption){dc=GetDC(stage->hWnd);label=caption;}
    Box* setText(char* text){
	this->text=text;return this;
    }
    Box* setNum(float number){
	std::string ws = std::to_string(number);
	text=ws.c_str();
	return this;
    }
    Box* setNum(int number){
	std::string ws = std::to_string(number);
	text=ws.c_str();
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
