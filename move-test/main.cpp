#define OnMove
#include "../APIfunc.h"
using namespace std;

int paint(){//'main' function
    window.setTitle(L"Press a key!")->move(200,200)->resize(400,200);
    return 0;
}

void onKeyPress(unsigned key){//function that calls on click
    if(key==VK_ESCAPE)quit(); //exit on 'Esc' key

    int size=key*3;
    if(size>window.height())            //if key code > window's height
        for(int i=window.height();i<=size;i++)
            MoveWindow(hWnd,window.x(),window.y(),i,i,true);//resizing

    if(size<window.height())            //if key code < window's height
        for(int i=window.height();i>=size;i--)
            MoveWindow(hWnd,window.x(),window.y(),i,i,true);//resizing
}

void onMove(RECT* newPos){
    string text="                                    ";
    TextOutA(GetDC(hWnd),0,0,text.c_str(),text.length());
    text="X: "+to_string(newPos->left)+", Y: "+to_string(newPos->top);
    TextOutA(GetDC(hWnd),0,0,text.c_str(),text.length());
}
