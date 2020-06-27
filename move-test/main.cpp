#define Manythread
#include "../APIfunc.h"
#include "../FIGURES.h"
#define pieces 3
Window *parent= new Window(GetForegroundWindow());
Window* w[pieces*pieces];

int paint(){//'main' function
    parent->minimize();
    loop(pieces*pieces,i){
        w[i]=new Window;
        w[i]->resize(screen->width()/pieces,screen->height()/pieces);
        w[i]->move((i%pieces)*screen->width()/pieces,i/pieces*screen->height()/pieces);
        w[i]->show();
        printInt(w[i],0,0,i);
        if(i>500)w[i-500]->destroy();
        Sleep(100/pieces);
    }
    Sleep(1000);
    loop(pieces*pieces,i){
        w[pieces*pieces-i-1]->minimize();
        Sleep(20);
    }
    Sleep(200);
    parent->show();
    exit(0);
    return 0;
}
