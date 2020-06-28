#define OnKeyPress keypress
#define OnTimer 200
#include "../APIfunc.h"
#include "../FIGURES.h"
#include <thread>
using namespace std;

int eaten=0;
bool pause=false;
bool snake[35][35]; //where tail&head are
Square apple;
void addBody(Square*,bool*);
Window* player2=NULL;

typedef struct{
    int x=1, y=1;
} point;
point head; //head's cell

enum rotation{UP, DOWN, LEFT, RIGHT};
rotation rotate=DOWN; //where snake's head points to

void timer(){
    if(player2==NULL&&FindWindowW(L"wind",L"snakeAddon")!=NULL){
        player2= new Window(FindWindowW(L"wind",L"snakeAddon"));
    }
    window->resize(700,700)->show(); //dont resize the window
    if(pause)return;
    apple.show();
    window->focus();
    if(head.x*20==apple.x&&head.y*20==apple.y){
        eaten++;
        if(eaten>=1000){
            window->message(L"Ура! Вы выиграли, собрав 1000 яблочек!",L"Победа",APP_ERROR_ICO);
            player2->sysmessage(WM_KEYDOWN,0x3A,0);
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
        pause=true;if(player2!=NULL)player2->sysmessage(WM_KEYDOWN,0x3B,0);
        window->message(L"Змея врезалась в стену!\n Счет: ",eaten,L"Проигрыш",RANDOM_ICO);
        if(player2!=NULL)player2->sysmessage(WM_KEYDOWN,0x3A,0);
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
        pause=true;if(player2!=NULL)player2->sysmessage(WM_KEYDOWN,0x3B,0);
        window->message(L"Змея врезалась в себя!\n Счет: ",eaten,L"Проигрыш",RANDOM_ICO);
        if(player2!=NULL)player2->sysmessage(WM_KEYDOWN,0x3A,0);
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
    case 0x3A:// restart key
        restart();
    break;
    case VK_F9:
        pause=true;if(player2!=NULL)player2->sysmessage(WM_KEYDOWN,0x3B,0);
        if(pause)window->message(L"Игра на паузе. Нажмите ОК, чтобы снять паузу.");
        pause=false;if(player2!=NULL)player2->sysmessage(WM_KEYDOWN,0x3C,0);
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
    case 0x57://W
        if(player2!=NULL)player2->sysmessage(WM_KEYDOWN,VK_UP,0);
    break;
    case 0x53://S
        if(player2!=NULL)player2->sysmessage(WM_KEYDOWN,VK_DOWN,0);
    break;
    case 0x41://A
        if(player2!=NULL)player2->sysmessage(WM_KEYDOWN,VK_LEFT,0);
    break;
    case 0x44://D
        if(player2!=NULL)player2->sysmessage(WM_KEYDOWN,VK_RIGHT,0);
    break;
    case 0x3B: //pause
        pause=true;
    break;
    case 0x3C: //unpause
        pause=false;
    break;
    }
}
