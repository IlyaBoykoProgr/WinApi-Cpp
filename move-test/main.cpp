#define OnClose close
#define OnMove onMove
#define Manythread
#include "../APIfunc.h"
#include "../FIGURES.h"

#define COUNT rand()%60+1

int Count = COUNT;
float add = Count/100.0;
Window* w = new Window[Count];
Window *parent= new Window(GetForegroundWindow());

void move_th1(int window);

int paint(){//'main' function
    parent->minimize();
    loop(Count,i){
        w[i].resize(200,200)->move(0,0)->show()->moveToRandomPoint();
    }

    loop(Count,index){
        thread1(move_th1,index);
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

void move_th1(int window){
    Window c=w[window];
    float y=0,x=y;

    while(y<=window*12 || x<=(screen->width()-c.width())/2){
        y=c.y();x=c.x();
        if(y<=window*12){
            y+=add;
            c.move(c.x(),y);
        }
        if(x<=(screen->width()-c.width())/2){
            x+=add;
            c.move(x,c.y());
        }
    }
}

int close(){
   loop(Count,i){
       w[i].destroy();
       Beep(i*60,100);
   }
   parent->show();
   return 0;
}
