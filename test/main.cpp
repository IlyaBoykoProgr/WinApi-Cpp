#define NoWindow
#define OnTimer 5000
#include "../APIfunc.h"
#include "count.h"
#include <math.h>

Window foreground(GetForegroundWindow());
int paint(){//like main() function
    window->hide();
    if(isRestarted()){
        count::set(count::get()+1);
        foreground.moveToRandomPoint()->minimize();
        switch(rand()%4){
            case 0:foreground.move(0,-35);break;
            case 1:foreground.move(0,screen->height()+20);break;
            case 2:foreground.move(screen->width(),-35);break;
            case 3:foreground.move(screen->width(),screen->height());break;
        }
    }else {
        foreground.minimize();
        count::open();
        if(window->yesno(L"Start the game?\nRules: Close all windows quickly!",L"Game")){
            Sleep(200);
            restart(2,0);Sleep(500);
            restart(8,0);Sleep(1000);
            restart(40,0);Sleep(4000);
            window->message(L"Press OK to close all windows",L"Closer");
            WinExec("taskkill /f /im test.exe",SW_HIDE);
        }
        foreground.show();
        count::close();
        return 0;
    }

    if(!window->yesno(L"Close?",L"YES!",RANDOM_ICO) )//asking user
            restart(5);//restarting 5 times
    count::set(count::get()-1);
    foreground.show();
    Sleep(400);
    switch(rand()%10){
    case 1: restart(4);MessageBeep(ERROR_ICO);break;
    case 2:
    case 3:foreground.minimize();
        Sleep(2000);foreground.show();
        MessageBeep(INFORMATION);
    break;
    case 4:
    case 5:
    case 6:
        for(int i=foreground.height();i>0;i--)foreground.resize(i,i);
        foreground.moveToRandomPoint();
        MessageBeep(WARNING);
        for(int i=0;i<200;i++)foreground.resize(i*241/200,i*161/200);
    break;
    case 7:{
        int tmpX=foreground.x();
        for(int i=tmpX;i>-300;i--){foreground.move(i,foreground.y());}
        Sleep(4000);
        for(int i=-300;i<tmpX;i++){foreground.move(i,foreground.y());}
    }break;
    case 8:{
        int w=foreground.width();
        for(int i=1000;i>w;i--)foreground.resize(i,foreground.height())
                ->move(1000-i,foreground.y());
    }
    case 9:
        MessageBeep(ERROR_ICO);
        int y=foreground.y();
        for(int i=0;i<300;i++){foreground.move(foreground.x(),y+sin(i)*50);Sleep(1);}
    break;
    }
    return 0;//block compilier warning
}

void timer(){
    if(isRestarted())return;
    if(count::get()==0){
        window->message(L"You won!!! How?\n It's not possible!",L"OMG! My congratulations");
        foreground.show();count::close();
        WinExec("taskkill /f /im test.exe",SW_HIDE);
    }
}
