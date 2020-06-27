#define OnKeyPress keypress
#define OnTimer 150
#include "../APIfunc.h"
#include "../FIGURES.h"
#include <thread>
using namespace std;

Box apples(window,"Apples eaten:");
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
    apples.clearDC();
    apples.setNum(eaten)->show();
    apple.clearDC()->show();
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
            apple.x=(rand()%27+3)*20; //random x
            apple.y=(rand()%27)*20; //random y
        }while(snake[apple.x/20][apple.y/20]);
    }
    if(head.x>=35||head.x<1||head.y>=35||head.y<-1){
        pause=true;
        window->message(L"Змея врезалась в стену!\n Счет: ",eaten,L"Проигрыш",RANDOM_ICO);
        restart();
    }
    Square *tail=new Square(window);
    tail->resize(20,20)->color(RANDOM,BLACK)->move(head.x*20,head.y*20)->show();
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
    apples.resize(350,20)->move(0,0)->show();
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
        if(rotate==DOWN)goto die_back;
        rotate=UP;
    break;
    case VK_DOWN:
        if(rotate==UP)goto die_back;
        rotate=DOWN;
    break;
    case VK_LEFT:
        if(rotate==RIGHT)goto die_back;
        rotate=LEFT;
    break;
    case VK_RIGHT:
        if(rotate==LEFT)goto die_back;
        rotate=RIGHT;
    break;
    }
    return;
    die_back:
    pause=true;
    window->message(L"Вы проиграли! Змея споткнулась сама об себя!",L"О нет..",ERROR_ICO);
    restart();
}
