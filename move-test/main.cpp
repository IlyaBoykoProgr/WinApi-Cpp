#include "../APIfunc.h"

int paint(HWND window){//'main' function
    SetWindowTextW(window,L"Нажми клавишу");
    MoveWindow(window,200,200,200,200,true);
    return 0;
}

void onKeyPress(HWND window,WPARAM key){//function that calls on click
    key*=3;                             //there i want to resize window
    if(key>heightOf(window))            //if key code > window's height
        for(unsigned i=heightOf(window);i<=key;i++)
            MoveWindow(window,xOf(window),yOf(window),i,i,true);//resizing
    if(key<heightOf(window))            //if key code < window's height
        for(unsigned i=heightOf(window);i>=key;i--)
            MoveWindow(window,xOf(window),yOf(window),i,i,true);//resizing
    if(key/3==VK_ESCAPE)quit(window); //exit on 'Esc' key
}
