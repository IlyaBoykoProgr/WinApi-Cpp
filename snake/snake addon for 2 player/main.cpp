#define OnKeyPress keypress
#define OnTimer 200
#include "../../APIfunc.h"
#include "../../FIGURES.h"
#include <thread>
using namespace std;

int eaten=0;
bool pause=false;
bool snake[35][35]; //where tail&head are
Window* player1= new Window(FindWindowW(L"wind",L"Игра 'Змейка'"));
Square apple(player1);
void addBody(Square*,bool*);

typedef struct{
    int x=1, y=1;
} point;
point head; //head's cell

enum rotation{UP, DOWN, LEFT, RIGHT};
rotation rotate=RIGHT; //where snake's head points to

void timer(){
    if(pause)return;
    apple.show();
    if(head.x*20==apple.x&&head.y*20==apple.y){
        eaten++;
        if(eaten>=1000){
            player1->message(L"Ура! Игрок 2 победил, собрав 1000 яблочек!",L"Победа",APP_ERROR_ICO);
            restart();
        }
        apple.hide();
        do{
            apple.x=(rand()%33)*20; //random x
            apple.y=(rand()%33)*20; //random y
        }while(snake[apple.x/20][apple.y/20]);
        apple.clearDC();
    }
    if(head.x>33||head.x<0||head.y>33||head.y<0){
        pause=true;player1->sysmessage(WM_KEYDOWN,0x3B,0);
        player1->message(L"Змея 2 игрока врезалась в стену!\n Счет: ",eaten,L"Проигрыш",RANDOM_ICO);
        player1->sysmessage(WM_KEYDOWN,0x3A,0);
        restart();
    }
    Square *tail=new Square(player1);
    tail->resize(20,20)->color(YELLOW,BLACK)->move(head.x*20,head.y*20)->show();
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
        pause=true;player1->sysmessage(WM_KEYDOWN,0x3B,0);
        player1->message(L"Змея 2 игрока врезалась в себя!\n Счет: ",eaten,L"Проигрыш",RANDOM_ICO);
        player1->sysmessage(WM_KEYDOWN,0x3A,0);
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
    window->setTitle(L"snakeAddon");
    while(player1->hWnd==NULL)player1->hWnd=FindWindowW(L"wind",L"Игра 'Змейка'");
    apple.color(BLUE)->move(20,20)->resize(10,10)->show();
    loop(35,x)loop(35,y)snake[x][y]=0;
    return 0;
}

void keypress(unsigned key){
    switch(key){
    case 0x3A:// restart key
        restart();
    break;
    case 0x3B: //pause
        pause=true;
    break;
    case 0x3C: //unpause
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
