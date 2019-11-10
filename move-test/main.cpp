#define OnMove onMove
#include "../APIfunc.h"

#include "../FIGURES.h"

int paint(){//'main' function
    window->setTitle(L"Move me!")->move(200,200)->resize(300,300);
    window->hide()->show();
    return 0;
}

Box showX(window,"X:"),showY(window,"Y:");

void onMove(RECT* newPos){
    showX.setNum((int)newPos->left)->
          place(0,0)->
          resize(100,100)->
          show();
    showY.setNum((int)newPos->top)->
          place(0,showX.height)->
          resize(100,100)->
          show();
}
