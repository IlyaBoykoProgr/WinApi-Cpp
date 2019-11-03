#define NoWindow
#include "../APIfunc.h"

int paint(){//like main() function, !use window object!
    const wchar_t* frases[5]={L"Go out?",L"Hide?",L"Close?",L"Erase?",L"Delete?"};//frases

    char path[100];         //path to programm
    GetModuleFileNameA(NULL,path,100);//getting path

    if(!yesno(frases[rand()%5] ) )//asking user with 1 of 5 frases
            loop(5,i)                 //if 'yes' => do loop
                    WinExec(path,0);  //executing this programm..
    quit();//end of this programm..
    return 0;//block compilier warning
}
