#include "../APIfunc.h"
#include "../FIGURES.h"

Square* sq;Circle* cir;
Group picture;
int paint(HWND window){
    sq=new Square(window);
    cir=new Circle(window);

    sq->resize(200,200)->color(BLUE,MAGENTA);
    cir->geometry(50,50,100,100);
    picture<<sq;
    picture<<cir;

    SetWindowTextW(window,L"Paint simple");
    MoveWindow(window,xOf(window),yOf(window),500,300,true);
    return 0;
}

void onKeyPress(HWND window, WPARAM key){
    if(key==VK_ESCAPE)quit(window);
    picture.show();
    picture.place(picture.x+1,picture.y);
}
