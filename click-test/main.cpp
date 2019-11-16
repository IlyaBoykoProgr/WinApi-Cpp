#define OnClick click
#include "../APIfunc.h"
#include "../FIGURES.h"

Square* sq= new Square(window);
Box* count= new Box(window,"Successful clicks:");
int clicks=0;

int paint(){
    if(isRestarted())clicks=119;
    window->setTitle(L"Click the square!")->resize(400,400)->show();
    sq->resize(100,100)->color(RANDOM,RANDOM)->place(rand()%300,rand()%260+40)->show();
    count->setNum(clicks)->show();
    return 0;
}

void click(unsigned key, int x, int y){
    if(key!=MK_LBUTTON)restart();
    if(sq->hasPoint(x,y)){
        clicks++;
        if(clicks>=120){
            window->message(L"You won! Congratulations...",L"From square");
            if(window->yesno(L"Look like ending... Again?",L"From window:")){
                restart(1,0);
            }
                quit();
            }
            if(clicks%20==0){
                window->message(L"Smaller!",L"From square:",WARNING);
                sq->erase()->resize(sq->width/2,sq->height/2);
            }
            sq->erase()->color(RANDOM,RANDOM)->place(rand()%300,rand()%260+40)->show();
            count->setNum(clicks)->show();
        }
}
