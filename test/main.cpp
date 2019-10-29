#include "../APIfunc.h"

int main(int argc,const char** argv){
    UNUSED(argc);

    LPSYSTEMTIME time;
    GetLocalTime(time);
    srand(time->wMilliseconds);

    wchar_t* frases[5]={L"Уйти?",L"Спрятаться?",L"Закрыться?",L"Стереться?",L"Не показываться?"};

    if(!yesno(frases[rand()%5]))
            loop(2,i)WinExec(argv[0],0);
}
