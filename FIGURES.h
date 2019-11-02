#include <windows.h>

#define RED RGB(255,0,0)
#define GREEN RGB(0,255,0)
#define BLUE RGB(0,0,255)
#define YELLOW RGB(255,255,0)
#define BLACK RGB(0,0,0)
#define WHITE RGB(255,255,255)
#define MAGENTA RGB(255,0,255)
#define RANDOM RGB(rand()%255,rand()%255,rand()%255)

class ScreenObj{
public:
    int x=0,y=0,width=0,height=0;
    COLORREF brush=YELLOW,pen=BLACK;
    HDC dc;
    ScreenObj* place(int newX,int newY){
	x=newX;y=newY;return this;
    }
    ScreenObj* resize(int newWdth, int newHght){
	width=newWdth;height=newHght;return this;
    }
    ScreenObj* color(COLORREF color, COLORREF border=BLACK){
	brush=color;pen=border;return this;
    }
    virtual ScreenObj* show(){}
    void erase(){color(WHITE,WHITE)->show();}
};

class Square: public ScreenObj{
public:
    Square(HWND window){
	dc=GetDC(window);
    }
    ScreenObj* show(){
	SelectObject(dc,CreatePen(PS_SOLID,1,pen));
	SelectObject(dc,CreateSolidBrush(brush));
	Rectangle(dc,x,y,x+width,y+height);
	return this;
    }
};
class Circle: public ScreenObj{
public:
    Circle(HWND window){
	dc=GetDC(window);
    }
    ScreenObj* show(){
	SelectObject(dc,CreatePen(PS_SOLID,1,pen));
	SelectObject(dc,CreateSolidBrush(brush));
	Ellipse(dc,x,y,x+width,y+height);
	return this;
    }
};

class Group{
    ScreenObj *figures[50];
    ScreenObj none;
public:
    Group(){
	for(short i=0;i<50;i++)figures[i]=&none;
    }
    Group* show(){
	for(short i=0;figures[i]!=&none;i++){
	    figures[i]->show();
	}
	return this;
    }
    Group* erase(){
	for(short i=0;figures[i]!=&none;i++){
	    figures[i]->erase();
	}
	return this;
    }
    Group* operator << (ScreenObj* obj){
	short i=0;
	while(figures[i]!=&none)i++;
	figures[i]=obj;
	return this;
    }
};
