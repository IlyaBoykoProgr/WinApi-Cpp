#define OnKeyPress onKey
#define OnMove onMove
#include "../APIfunc.h"
using namespace std;

int paint(){//'main' function
    window.setTitle(L"Press a key!")->move(200,200)->resize(300,300);
    window.hide()->show();
    return 0;
}

void onKey(unsigned key){//function that calls on click
    if(key==VK_ESCAPE)quit(); //exit on 'Esc' key

    int size=key*3;
    if(size>window.height())            //if new size > window's height
        for(int i=window.height();i<=size;i++)
            window.resize(i,i);

    if(size<window.height())            //if new size < window's height
        for(int i=window.height();i>=size;i--)
            window.resize(i,i);
}

void onMove(RECT* newPos){
    string text="                                    ";
    TextOutA(GetDC(hWnd),0,0,text.c_str(),text.length());
    text="X: "+to_string(newPos->left)+", Y: "+to_string(newPos->top);
    TextOutA(GetDC(hWnd),0,0,text.c_str(),text.length());
}
