#define OnKeyPress keypress
#define OnTimer 300
#include "../APIfunc.h"
#include "../FIGURES.h"
#include <thread>
using namespace std;

int eaten=0;
bool pause=false;
bool snake[35][35]; //where tail&head are
Square apple;
void addBody(Square*,bool*);

typedef struct{
    int x=1, y=1;
} point;
point head; //head's cell

enum rotation{UP, DOWN, LEFT, RIGHT};
rotation rotate=DOWN; //where snake's head points to

void timer(){
    window->resize(700,700)->move(0,0)->show(); //dont resize the window
    if(pause)return;
    window->focus();
    if(head.x*20==apple.x&&head.y*20==apple.y){
        eaten++;
        if(eaten==1000){
            window->message(L"Ура! Вы выиграли, собрав 1000 яблочек!",L"Победа",APP_ERROR_ICO);
            restart();
        }
        apple.hide();
        do{
            apple.x=(rand()%33)*20; //random x
            apple.y=(rand()%33)*20; //random y
        }while(snake[apple.x/20][apple.y/20]);
        apple.clearDC()->show();
    }
    if(head.x>33||head.x<0||head.y>33||head.y<0){
        pause=true;
        window->message(L"Змея врезалась в стену!\n Счет: ",eaten,L"Проигрыш",RANDOM_ICO);
        restart();
    }
    Square *tail=new Square(window);
    tail->resize(20,20)->color(GREEN,BLACK)->move(head.x*20,head.y*20)->show();
    thread *th= new thread(addBody,tail,&snake[head.x][head.y]);
    th->detach();
    delete th;

    switch(rotate){ //move
    case UP: head.y-=1; break;
    case DOWN: head.y+=1; break;
    case LEFT: head.x-=1; break;
    case RIGHT: head.x+=1; break;
    }
}

void addBody(Square* part,bool *cell){
    if(snake[head.x][head.y]){
        pause=true;
        window->message(L"Змея врезалась в себя!\n Счет: ",eaten,L"Проигрыш",RANDOM_ICO);
        restart();
    }
    *cell=1;
    this_thread::sleep_for(chrono::milliseconds(eaten*OnTimer));
    while(pause);
    part->hide();
    *cell=0;
    delete part;
}

int paint()
{
    window->setTitle(L"Игра 'Змейка'");
    apple.color(RED)->move(20,20)->resize(10,10)->show();
    loop(35,x)loop(35,y)snake[x][y]=0;
    return 0;
}

void keypress(unsigned key){
    switch(key){
    case VK_F9:
        pause=true;
        if(pause)window->message(L"Игра на паузе. Нажмите ОК, чтобы снять паузу.");
        pause=false;
    break;
    case VK_UP:
        if(rotate==DOWN)return;
        rotate=UP;
    break;
    case VK_DOWN:
        if(rotate==UP)return;
        rotate=DOWN;
    break;
    case VK_LEFT:
        if(rotate==RIGHT)return;
        rotate=LEFT;
    break;
    case VK_RIGHT:
        if(rotate==LEFT)return;
        rotate=RIGHT;
    break;
    }
}
