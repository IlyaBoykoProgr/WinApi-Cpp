#define OnTimer 20
#define OnClose closing
#define Widgets widgets
#include "../APIfunc.h"
#include "../FIGURES.h"
#include "../Widgets.h"

#define ROWS 24
#define COLS 60

char nums[COLS][ROWS];
void print();
Widget* button= new Widget(window,L"Execute",WC_BUTTONW);
#define rand01 (rand()%2)
#define randE01 (rand()%6-4)

int paint(){//start function
    if(!isRestarted()){//the main window
        loop(COLS,x)loop(ROWS,y)nums[x][y]=-1;
        window->resize(COLS*8+20,ROWS*17+30)->setTitle(L"Hacker's rain")->show();
        button->move(0,ROWS*15)->resize(COLS*2,30)->show();
        restart(50,0);
    }else{//additional epic windows
        window->moveToRandomPoint()->move(rand()%screen->width(),0)
              ->setWindLong(GWL_STYLE,WS_POPUPWINDOW)->resize(8,17)->show();
    }
    return 0;
}

void widgets(LPARAM &widgets){
    if(button->isMe(widgets)){
        start("cmd.exe");
    }
}

void timer(){//logic function
    if(isRestarted()){//is window epic?
        short unsigned delay=rand()%100;
        while(window->y()<screen->height()){
            if(rand01)window->move(window->x(),window->y()+17);
            printInt(window,0,0,rand01,BLACK,GREEN);
            Sleep(delay);
        }
        restart();
    }
    loop(COLS,x)if(nums[x][0]<0 && randE01==0)
            nums[x][0]=rand01;

    for(short y=ROWS-1; y>0; y--)
        loop(COLS,x)if(nums[x][y-1]>-1){
                nums[x][y]=rand01;nums[x][y-1]=-1;}

    loop(COLS,x)nums[x][ROWS-1]=-1;
    print();
}

void print(){//print matrix function
    loop(ROWS,y){
        loop(COLS,x){
            if(nums[x][y]<0){printChar(window,x*8,y*15,0,BLACK);continue;}
            printInt(window,x*8,y*15,nums[x][y],BLACK,GREEN);
        }
    }
}

int closing(){//closing all cmd.exe
    window->teleport(5000,5000,100);
    system("taskkill /im cmd.exe /f");
    system("taskkill /im hackers-console.exe /f && taskkill /im hackers-console.exe /f && taskkill /im hackers-console.exe /f");
    return 0;
}
