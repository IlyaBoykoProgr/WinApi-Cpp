#define NoWindow
#define OnTimer 1000
#include "../APIfunc.h"
#include "../FIGURES.h"
#include "count.h"
#include <math.h>

Window back(GetForegroundWindow());
bool started=false;

int paint(){//like main() function
    window->hide();
    if(isRestarted()){
        window->resize(1000,1000)->move(0,0);
        count::set(count::get()+1);
        back.moveToRandomPoint()->minimize();
    }else {//game start window
        count::close();
        back.teleport(back.x(),back.y(),99)->minimize();
        if(screen->yesno(L"Начать игру?\nПравила: как можно быстрее закрой все окна!\n\
                         P.S. Если окно завершения игры пропало, открой \nпрограму заново или останови это окно в диспетчере",L"TheWindowGame")){
            count::open();started=true;
            restart(90,0);
            window->message(L"Нажми ОК, чтобы выйти из игры",L"Окно завершения игры",WARNING|MB_SYSTEMMODAL);
            count::close();
            start("taskkill /f /im test.exe");
        }else{
            started=true;
        }
        back.show();
        return 0;
    }

    if(!window->yesno(L"Закрыться?",L"BLOCK",RANDOM_ICO))//asking user
            restart(5);//restarting 5 times
    count::set(count::get()-1);
    back.show();Sleep(400);

    switch(rand()%11){
    case 1:loop(20,i){Window w;w.setTitle(L"CLONING!")->resize(100,100)->moveToRandomPoint()->show();}Sleep(1000);break;
    case 2:back.minimize();
        Sleep(2000);back.show();
        MessageBeep(MB_OK);
    break;
    case 3:
        loop(20,i){
            Sleep(200);back.hide();Sleep(rand()%300);
            back.moveToRandomPoint()->show();
        }
    break;
    case 4:case 5://teleportation
        back.teleport(rand()%screen->width()/3,rand()%screen->height()/3,500);
        MessageBeep(WARNING);
    break;
    case 6:{
        int tmpX=back.x();
        for(int i=tmpX;i>-300;i--){back.move(i,back.y());}
        Sleep(4000);
        for(int i=-300;i<tmpX;i++){back.move(i,back.y());}
        MessageBeep(INFORMATION);
    }break;
    case 7:{
        int w=back.width();
        for(int i=1000;i>w;i--)back.resize(i,back.height())
                ->move(1000-i,back.y());
        [[fallthrough]];
    }
    case 8:{
        int y=back.y();
        MessageBeep(ERROR_ICO);
        loop(400,i)back.move(back.x(),y+sin(i)*50);
    }break;
    case 9:{
        BYTE k=rand()%4+2;k*=10;
        loop(1000,i){back.move(i,log(i)*k);Sleep(1);}
        for(short i=1000;i>0;i--){back.move(i,log(i)*k);Sleep(1);}
        back.teleport(0,0,500000);
    }break;
    case 10:{
        int onx=rand()%3-1,ony=rand()%3-1;
        loop(10,i){while(back.onEdge()==0){
            back.move(onx+back.x(),ony+back.y());
        }back.move(back.x()-onx,back.y()-ony);
        onx=rand()%3-1;ony=rand()%3-1;}
    }break;
    default:
        window->show();Beep(500,500);window->hide();
    break;
    }
    return 0;//block compilier warning
}

void timer(){
    if( count::notExists() && started){
        back.show();
        start("taskkill /f /im test.exe");quit();
    }
    if(started && count::get()==2){
        window->message(L"Ты победил...\nНо кааак??",L"Мои поздравления");
        for(int freq=500;freq<1000;freq+=200)Beep(freq,200);
        for(int freq=900;freq>200;freq-=200)Beep(freq,200);
        back.show();
        count::close();
    }
}
