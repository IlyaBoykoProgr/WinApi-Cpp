#include "../APIfunc.h"

int paint(HWND window){//'main' function
    SetWindowTextW(window,L"Нажми клавишу");
    MoveWindow(window,200,200,200,200,true);
    return 0;
}

void onKeyPress(HWND window,WPARAM key){//function that calls on click
    if(key==VK_ESCAPE)quit(window); //exit on 'Esc' key

    int size=key*3;
    if(size>heightOf(window))            //if key code > window's height
        for(int i=heightOf(window);i<=size;i++)
            MoveWindow(window,
                       widthOf(GetDesktopWindow())/2-widthOf(window)/2,   //-|centering
                       heightOf(GetDesktopWindow())/2-heightOf(window)/2, //-|window
                       i,i,true);//resizing
    if(size<heightOf(window))            //if key code < window's height
        for(int i=heightOf(window);i>=size;i--)
            MoveWindow(window,
                       widthOf(GetDesktopWindow())/2-widthOf(window)/2,   //-|centering
                       heightOf(GetDesktopWindow())/2-heightOf(window)/2, //-|window
                       i,i,true);//resizing
}
