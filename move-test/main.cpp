#define OnMove onMove
#include "../APIfunc.h"

#include "../FIGURES.h"
using namespace std;

int paint(){//'main' function
    window.setTitle(L"Press a key!")->move(200,200)->resize(300,300);
    window.hide()->show();
    return 0;
}

Box showX(hWnd,"X:"),showY(hWnd,"Y:");
void onMove(RECT* newPos){
    showX.setText((int)newPos->left)->
          place(0,0)->
          resize(100,100)->
          show();
    showY.setText((int)newPos->top)->
          place(0,showX.height)->
          resize(100,100)->
          show();
}
