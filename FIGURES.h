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
    COLORREF brush=WHITE,pen=BLACK;
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
    virtual void show(){}
    ScreenObj* erase(){
	color(WHITE,WHITE)->
	show();return this;
    }
};

class Square: public ScreenObj{
public:
    Square(HWND window){
	dc=GetDC(window);
    }
    void show(){
	SelectObject(dc,CreatePen(PS_SOLID,1,pen));
	SelectObject(dc,CreateSolidBrush(brush));
	Rectangle(dc,x,y,x+width,y+height);
    }
};
class Circle: public ScreenObj{
public:
    Circle(HWND window){
	dc=GetDC(window);
    }
    void show(){
	SelectObject(dc,CreatePen(PS_SOLID,1,pen));
	SelectObject(dc,CreateSolidBrush(brush));
	Ellipse(dc,x,y,x+width,y+height);
    }
};

#include <string>
class Box: public ScreenObj{
    LPCSTR text;
    LPCSTR label;
public:
    const int height=40;
    Box(HWND window,LPCSTR heading){
	label=heading;dc=GetDC(window);
    }
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
