#include <windows.h>

#define RED RGB(255,0,0)
#define GREEN RGB(0,255,0)
#define BLUE RGB(0,0,255)
#define YELLOW RGB(255,255,0)
#define BLACK RGB(0,0,0)
#define WHITE RGB(255,255,255)
#define MAGENTA RGB(255,0,255)

class ScreenObj{
public:
    int x=0,y=0,width=0,height=0;
    HDC dc;
    void place(int newX,int newY){
	x=newX;y=newY;
    }
    void resize(int newWdth, int newHght){
	width=newWdth;height=newHght;
    }
    virtual void show(COLORREF color=RED, COLORREF border=BLACK)=0;
    void erase(){show(WHITE,WHITE);}
};

class Square: public ScreenObj{
public:
    Square(HWND window){
	dc=GetDC(window);
    }
    void show(COLORREF color=RED,COLORREF border=BLACK){
	SelectObject(dc,CreatePen(PS_SOLID,1,border));
	SelectObject(dc,CreateSolidBrush(color));
	Rectangle(dc,x,y,x+width,y+height);
    }
};
class Circle: public ScreenObj{
public:
    Circle(HWND window){
	dc=GetDC(window);
    }
    void show(COLORREF color=RED,COLORREF border=BLACK){
	SelectObject(dc,CreatePen(PS_SOLID,1,border));
	SelectObject(dc,CreateSolidBrush(color));
	Ellipse(dc,x,y,x+width,y+height);
    }
};
