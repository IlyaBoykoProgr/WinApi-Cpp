#define OnClose close
#define OnMove onMove
#include "../APIfunc.h"
#include "../FIGURES.h"

#define COUNT rand()%60+1

int Count = COUNT;
Window* w = new Window[Count];
Window *parent= new Window(GetForegroundWindow());
void move_th(int window);
int paint(){//'main' function
    parent->minimize();
    loop(Count,i){
        w[i].resize(200,200)->show()->moveToRandomPoint();
    }w[0].setTitle(L"Move me!");

    std::thread* moves[Count];
    loop(Count,index){
       w[index].show();
       moves[index] = new std::thread(move_th,index);
       moves[index]->detach();
    }
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

void move_th(int window){
    float add = Count/150.0;
    for(float y=w[window].y();y>=0;y-=add)
        w[window].move(w[window].x(),y);
    for(float x=w[window].x();x>=0;x-=add)
        w[window].move(x,0);
    for(float i=0;i<window*12;i+=add/2)
        w[window].move(i,i);
}

int close(){
   loop(Count,i){w[i].hide();Sleep(20);}
   loop(Count,i){w[i].show();Sleep(20);}
   loop(Count,i){
       w[i].destroy();
       Beep(i*60,100);
   }
   parent->show();
   return 0;
}
