#include "../APIfunc.h"

int paint(HWND window){//like main() function, window is adress of your window
    ShowWindow(window,SW_HIDE);//hiding window,not needed
    const wchar_t* frases[5]={L"Go out?",L"Hide?",L"Close?",L"Erase?",L"Delete?"};//frases
    char path[100];         //path to programm
    GetModuleFileNameA(NULL,path,100);//getting path
    if(!yesno(NULL, frases[rand()%5] ) )//asking user with 1 of 5 frases
            loop(5,i)                 //if 'yes' => do loop
                    WinExec(path,0);  //executing this programm..
    quit(window);//end of this programm..
    return 0;//block compilier warning
}

void onKeyPress(HWND window,WPARAM key){//function that calls if user press a key
    message(window,L"HOW? Ok,key: ",key,L"HOW?",WARNING);//window is hide, how can user press a key?
}
