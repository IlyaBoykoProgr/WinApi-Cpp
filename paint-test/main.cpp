#define OnClick onKey
#include "../APIfunc.h"
#include "../FIGURES.h"

Square* sq;Circle* cir;
int paint(){
    sq=new Square(hWnd);
    cir=new Circle(hWnd);

    sq->resize(300,300)->
        color(BLUE,MAGENTA);
    cir->resize(100,100)->
         place(300-cir->width,300-cir->height);

    window.setTitle(L"Paint simple")->
           resize(sq->width+16/*borders*/,sq->height+38/*borders*/)->show();
    onKey(MK_LBUTTON,0,0);
    return 0;
}

void onKey(unsigned key,int x,int y){
    if(key==MK_RBUTTON)quit();
    if(key==MK_MBUTTON)restart();
    if(key!=MK_LBUTTON)return;
    sq->show();
    cir->place(x-50,y-50)->color(RANDOM)->show();
}
