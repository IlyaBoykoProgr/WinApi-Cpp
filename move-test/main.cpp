#define Manythread
#include "../APIfunc.h"
#include "../FIGURES.h"
#include <ctime>
#define pieces 50
Window *parent= new Window(GetForegroundWindow());
Window* w[pieces*pieces];

int paint(){//'main' function
    if(!parent->yesno(L"Провести быстрый тест производительности ЦП?"))exit(0);
    long before=clock();
    parent->minimize();
    loop(pieces*pieces,i){
        w[i]=new Window;
        w[i]->resize(screen->width()/pieces,screen->height()/pieces);
        w[i]->move((i%pieces)*screen->width()/pieces,i/pieces*screen->height()/pieces);
        w[i]->show();
        printInt(w[i],0,0,i);
        if(i>500)w[i-500]->destroy();
    }
    parent->message(L"Чем меньше очков, тем лучше.(мои 35361) Ваши очки: ",
                    clock()-before,
                    L"Готовый результат");
    parent->show();
    exit(0);
    return 0;
}
