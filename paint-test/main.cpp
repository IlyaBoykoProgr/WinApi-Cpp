#include "../APIfunc.h"
#include "../FIGURES.h"

Square* sq;Circle* cir;
Group picture;
int paint(){
    sq=new Square(hWnd);
    cir=new Circle(hWnd);

    sq->resize(300,300)->color(BLUE,MAGENTA);
    cir->resize(100,100)->place(185,162);

    picture<<sq;
    picture<<cir;
    picture.show();

    window.setTitle(L"Paint simple")->resize(300,300);
    return 0;
}

void onKeyPress(unsigned key){
    if(key==VK_ESCAPE)quit();
    picture.show();
    cir->place(rand()%185,rand()%162)->
            color(RANDOM);
}
