#define OnTimer 20
#define OnClose closing
#define Widgets widgets
#define ROWS 15
#define COLS 30
#define delay 20
#define ADDITIONAL_COUNT 10
#define InWindow 0
#include "../APIfunc.h"
#include "../FIGURES.h"
#include "../Widgets.h"



char nums[COLS][ROWS];
Widget* button= new Widget(window,L"Execute",WC_BUTTONW);
#define rand01 (rand()%2)
#define randE01 (rand()%6-4)

int paint(){//start function
    if(!isRestarted()){//the main window
#if InWindow==1
        loop(COLS,x)loop(ROWS,y)nums[x][y]=-1;
        window->resize(COLS*8+20,ROWS*17+30)->setTitle(L"Hacker's rain")->show();
        button->move(0,ROWS*15)->resize(window->width(),window->height()-ROWS*17)->show();
#endif
        restart(ADDITIONAL_COUNT,0,1,100/ADDITIONAL_COUNT);
#if InWindow==0
        exit(0);
#endif
    }else{//additional epic windows
        window->moveToRandomPoint()->move(rand()%screen->width(),0)->enable(false)
              ->setWindLong(GWL_STYLE,WS_POPUP|WS_CHILD)->resize(8,17)->show();
    }
    return 0;
}

void widgets(LPARAM &widgets){
    if(button->isMe(widgets)){
        start("cmd.exe");
    }
}

void timer(){//logic function
    if(isRestarted()){//is window additional?
        while(window->y()<screen->height()){
            if(rand01)window->move(window->x(),window->y()+17);
            chance(100)window->move(window->x()+(rand01?-8:8),window->y());
            printInt(window,0,0,rand01,BLACK,GREEN);
            chance(9000){
                printInt(window,0,0,2,BLACK,RED);
                Sleep(1000);break;
            }
            Sleep(delay);
        }
        window->move(window->x(),0);
        return;
        SetWindowPos(window->hWnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
    }
#if InWindow==1
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
#endif
}

int closing(){//closing all cmd.exe
    if(!isRestarted())
        system("taskkill /im hackers-console.exe");
    return 0;
}
