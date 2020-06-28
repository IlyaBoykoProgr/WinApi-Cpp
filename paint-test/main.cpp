#define OnClick onKey
#include "../APIfunc.h"
#include "../FIGURES.h"

Square* sq;Circle* cir;
int paint(){
    sq=new Square(window);
    cir=new Circle(window);
    sq->resize(300,300)->
        color(BLUE,MAGENTA);
    cir->resize(100,100)->
         move(300-cir->width,300-cir->height);

    window->setTitle(L"Paint simple")->
           resize(sq->width+16/*borders*/,sq->height+38/*borders*/)->show();
    onKey(MK_LBUTTON,50,50);
    return 0;
}

void onKey(unsigned key,int x,int y){
    if(key!=MK_LBUTTON)restart();
    sq->show();
    cir->color(RANDOM,RANDOM)->move(x-50,y-50)->show();
}
