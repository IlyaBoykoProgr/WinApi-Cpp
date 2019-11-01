#include "../APIfunc.h"

int paint(HWND window){//like main() function, but window is adress of your window
    ShowWindow(window,SW_HIDE);//hiding window,not needed
    srand(Time().wMilliseconds);//setting random seed
                                //Time() returns current time of system
    const wchar_t* frases[5]={L"Уйти?",L"Спрятаться?",L"Закрыться?",L"Стереться?",L"Не показываться?"};//frases
    char path[100];         //path to programm
    GetModuleFileNameA(NULL,path,100);//getting path
    if(!yesno(NULL,frases[rand()%5]) )//asking user with 1 of 5 frases
            loop(5,i)                 //if 'yes' => do loop
                    WinExec(path,0);  //executing this programm..
    exit(0);//end of this programm..
}

void onKeyPress(HWND window,WPARAM key){//function that calls if user press a key
    message(window,L"HOW? Ok,key: ",key,L"HOW?",WARNING);//window is hide, how can user press a key?
}
