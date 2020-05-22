#define OnClose close
#define OnMove onMove
#define Manythread
#include "../APIfunc.h"
#include "../FIGURES.h"

#define COUNT screen->height()/12

const int Count = COUNT;
int add = 1;
Window* w = new Window[Count];
Window *parent= new Window(GetForegroundWindow());
void move_th1(int window);
void move_th2(int window);

int paint(){//'main' function
    parent->minimize();
    loop(Count,i){
        w[i].resize(0,0)->move(0,0)->show()->moveToRandomPoint();
    }

    if(rand()%2)
        loop(Count,index)thread1(move_th1,index)
    else
        loop(Count,index){
            w[index].move(0,index*7);
            thread1(move_th2,index);
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
    float y=0,x=0;

    while(y!=window*12 || x!=(screen->width()-c.width())/2){
        y=c.y();x=c.x();
        if(y<window*12)y+=add;
        if(y>window*12)y-=add;
        if(x<(screen->width()-c.width())/2)x+=add;
        if(x>(screen->width()-c.width())/2)x-=add;
        c.move(x,y);
    }
}

void move_th2(int window){
    Window c=w[window];
    int newX= window*(screen->width()/100);
    for(int i=0;i<newX;i+=2)c.resize(i+200,0);
}

int close(){
   loop(Count/2,i){
       w[i].hide();
       w[Count-i].hide();
       Beep(90,140);
   }
   parent->show();
   return 0;
}
