#define NoWindow
#define OnTimer 3000
#include "../APIfunc.h"
#include "count.h"
#include <math.h>

Window back(GetForegroundWindow());
bool started=false;

int paint(){//like main() function
    window->hide()->resize(1000,1000)->setTitle(L"Флешка! Ты ослеплен")->moveToRandomPoint();
    if(isRestarted()){
        count::set(count::get()+1);
        back.moveToRandomPoint()->minimize();
        switch(rand()%4){
            case 0:back.move(0,-35);break;
            case 1:back.move(0,screen->height()+20);break;
            case 2:back.move(screen->width(),-35);break;
            case 3:back.move(screen->width(),screen->height());break;
        }
    }else {
        back.minimize();
        count::open();
        if(window->yesno(L"Начать игру?\nПравила: как можно быстрее закрой все окна!",L"TheWindowGame")){
            count::set(count::get()+1);started=true;
            Sleep(200);
            restart(40,0);
                Sleep(4000);
            window->message(L"Нажми ОК, чтобы выйти из игры",L"Служебное окно");
            start("taskkill /f /im test.exe");
        }
        back.show();count::close();
        return 0;
    }

    if(!window->yesno(L"Закрыться?",L"ДА!",RANDOM_ICO))//asking user
            restart(5);//restarting 5 times
    count::set(count::get()-1);
    back.show();Sleep(400);
    switch(rand()%10){
    case 1: restart(5);MessageBeep(ERROR_ICO);break;
    case 2:back.minimize();
        Sleep(2000);back.show();
        MessageBeep(MB_OK);
    break;
    case 3:
        loop(20,i){
            Sleep(200);back.hide();Sleep(200);
            back.moveToRandomPoint()->show();
        }start("notepad.exe");
    break;
    case 4://teleportation
        back.teleport(rand()%screen->width()/4,rand()%screen->height()/4,500);
        MessageBeep(WARNING);
    break;
    case 5:{
        int tmpX=back.x();
        for(int i=tmpX;i>-300;i--){back.move(i,back.y());}
        Sleep(4000);
        for(int i=-300;i<tmpX;i++){back.move(i,back.y());}
        MessageBeep(INFORMATION);
    }break;
    case 6:{
        int w=back.width();
        for(int i=1000;i>w;i--)back.resize(i,back.height())
                ->move(1000-i,back.y());
    }
    case 7:{
        MessageBeep(ERROR_ICO);
        int y=back.y();
        for(int i=0;i<300;i++){back.move(back.x(),y+sin(i)*50);Sleep(1);}
    }break;
    default:
        window->show();Sleep(1500);window->hide();
    break;
    }
    return 0;//block compilier warning
}

void timer(){
    if(isRestarted())return;
    if( count::notExists() && started){
        back.show();
        start("taskkill /f /im test.exe");quit();
    }
    if(started && count::get()==1){
        window->message(L"Ты победил...\nНо кааак??",L"Мои поздравления");
        back.show();count::close();
        quit();
    }
}
