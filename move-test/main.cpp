#define OnClose close
#define OnMove onMove
#include "../APIfunc.h"
#include "../FIGURES.h"

#define COUNT rand()%50

int Count = COUNT;
Window* w = new Window[Count];
int paint(){//'main' function
    loop(Count,no){
        w[no].resize(200,200)->show()->moveToRandomPoint()->minimize();
    }w[0].show()->setTitle(L"Move me!");
    return 0;
}

void onMove(){
    Box showX(event,"X:"),showY(event,"Y:");
    showX.setNum(event->x())->
          place(0,0)->
          resize(100,100)->
          show();
    showY.setNum(event->y())->
          place(0,showX.height)->
          resize(100,100)->
          show();
}

int close(){
    loop(Count,no){
        w[no].hide()->setWindLong(GWL_STYLE,WS_CAPTION)->
        show()->focus();
        float add = (float)(Count/800.0);
        for(float y=w[no].y();y>=0;y-=add)w[no].move(w[no].x(),y);
        for(float x=w[no].x();x>=0;x-=add)w[no].move(x,0);
        for(float i=0;i<no*5;i+=add/10)w[no].move(i,i);
    }
    loop(Count,i){
        w[i].destroy();Beep(i*10,200);
    }
    return 0;
}
