#include "../APIfunc.h"
#include "../FIGURES.h"

Circle* sq;
int paint(HWND window){
    sq=new Circle(window);
    SetWindowTextW(window,L"Paint simlple");
    MoveWindow(window,xOf(window),yOf(window),500,300,true);
    return 0;
}

void onKeyPress(HWND window, WPARAM key){
    if(key==VK_ESCAPE)quit(window);
    sq->resize(100,100);
    for(int i=0;i<=100;i++){
        sq->erase();
        sq->show(RED,YELLOW);
        sq->place(i,i);
        Sleep(5);
    }
    for(int i=100;i>=0;i--){
        sq->erase();
        sq->show(RED,MAGENTA);
        sq->place(i,i);
        Sleep(5);
    }
}
