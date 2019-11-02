#include "../APIfunc.h"
#include "../FIGURES.h"

Square* sq;Circle* cir;
Group picture;
int paint(HWND window){
    sq=new Square(window);
    cir=new Circle(window);

    sq->resize(300,300)->color(BLUE,MAGENTA);
    cir->resize(100,100)->place(185,162);

    picture<<sq;
    picture<<cir;
    picture.show();

    SetWindowTextW(window,L"Paint simple");
    MoveWindow(window,xOf(window),yOf(window),300,300,true);
    return 0;
}

void onKeyPress(HWND window, WPARAM key){
    if(key==VK_ESCAPE)quit(window);
    picture.show();
    cir->place(rand()%185,rand()%162)->
            color(RANDOM);
}
