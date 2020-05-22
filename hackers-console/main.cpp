#define OnTimer 20
#define OnClose closing
#define Widgets widgets
#include "../APIfunc.h"
#include "../FIGURES.h"
#include "../Widgets.h"

#define ROWS 15
#define COLS 30

char nums[COLS][ROWS];
Widget* button= new Widget(window,L"Execute",WC_BUTTONW);
#define rand01 (rand()%2)
#define randE01 (rand()%6-4)

int paint(){//start function
    if(!isRestarted()){//the main window
        loop(COLS,x)loop(ROWS,y)nums[x][y]=-1;
        window->resize(COLS*8+20,ROWS*17+30)->setTitle(L"Hacker's rain")->show();
        button->move(0,ROWS*15)->resize(window->width(),window->height()-ROWS*17)->show();
        restart(50,0);
    }else{//additional epic windows
        window->moveToRandomPoint()->move(rand()%screen->width(),0)->enable(false)
              ->setWindLong(GWL_STYLE,WS_POPUP)->resize(8,17)->show();
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
        short unsigned delay=10;
        while(window->y()<screen->height()){
            if(rand01)window->move(window->x(),window->y()+17);
            chance(10)window->move(window->x()+(rand01?-8:8),window->y());
            printInt(window,0,0,rand01,BLACK,GREEN);
            chance(9000){
                printInt(window,0,0,2,BLACK,RED);
                Sleep(1000);break;
            }
            Sleep(delay);
        }
        window->move(window->x(),0);
        return;
    }
    loop(COLS,x)if(nums[x][0]<0 && randE01==0)
            nums[x][0]=rand01;

    for(short y=ROWS-1; y>0; y--)
        loop(COLS,x)if(nums[x][y-1]>-1){
                nums[x][y]=rand01;nums[x][y-1]=-1;}

    loop(COLS,x)nums[x][ROWS-1]=-1;
    loop(ROWS,y){
        loop(COLS,x){
            if(nums[x][y]<0){printChar(window,x*8,y*15,0,BLACK);continue;}
            printInt(window,x*8,y*15,nums[x][y],BLACK,GREEN);
        }
    }
}

int closing(){//closing all cmd.exe
    if(!isRestarted())
        system("taskkill /im hackers-console.exe");
    return 0;
}
