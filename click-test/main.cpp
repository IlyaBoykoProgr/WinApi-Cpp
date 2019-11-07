#define OnClick click
#include "../APIfunc.h"
#include "../FIGURES.h"

Square* sq= new Square(hWnd);
Box* count= new Box(hWnd,"Successful clicks:");
int clicks=0;

int paint(){
    window.setTitle(L"Click the square!")->resize(400,400)->show();
    sq->resize(100,100)->color(RANDOM,RANDOM)->show();
    return 0;
}

void click(unsigned key, int x, int y){
    if(key!=MK_LBUTTON)restart(4);
    if(x>sq->x && x<(sq->x+sq->width))
        if(y>sq->y && y<(sq->y+sq->height)){
            clicks++;
            if(clicks>=120){
                message(L"You won! Congratulations...",L"From square");
                if(yesno(L"Look like ending... Again?",L"From window:")){
                    restart();
                }
                quit();
            }
            if(clicks%20==0){
                message(L"Smaller!",L"From square:",WARNING);
                sq->erase()->resize(sq->width/2,sq->height/2);
            }
            sq->erase()->color(RANDOM,RANDOM)->place(rand()%300,rand()%260+40)->show();
            count->setNum(clicks)->show();
        }
}
