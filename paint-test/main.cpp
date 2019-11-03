#define OnKeyPress onKey
#include "../APIfunc.h"
#include "../FIGURES.h"

Square* sq;Circle* cir;
int paint(){
    sq=new Square(hWnd);
    cir=new Circle(hWnd);

    sq->resize(300,300)->
        color(BLUE,MAGENTA)->
        show();
    cir->resize(100,100)->
         place(300-cir->width,300-cir->height)->
         show();

    window.setTitle(L"Paint simple")->
           resize(sq->width+16/*borders*/,sq->height+38/*borders*/);
    return 0;
}

void onKey(unsigned key){
    if(key==VK_ESCAPE)quit();
    sq->show();
    int randomX=rand()%(300-cir->width);
    int randomY=rand()%(300-cir->height);
    cir->place(randomX,randomY)->
            color(RANDOM)->show();
}
