#include "../APIfunc.h"
#include "../FIGURES.h"
using namespace std;

string intPlusStr(int i,const char* str){
    string buff=to_string(i);
    buff += str;
    return buff;
}

int GetRam(){
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof (statex);
    GlobalMemoryStatusEx (&statex);
    return statex.dwMemoryLoad;
}

int GetCpu(){
    static ULARGE_INTEGER TimeIdle, TimeKernel, TimeUser;
    FILETIME Idle, Kernel, User;
    ULARGE_INTEGER uIdle, uKernel, uUser;
    GetSystemTimes(&Idle, &Kernel, &User);
    memcpy(&uIdle, &Idle, sizeof(FILETIME));
    memcpy(&uKernel, &Kernel, sizeof(FILETIME));
    memcpy(&uUser, &User, sizeof(FILETIME));
    long long t;
    t = (((((uKernel.QuadPart-TimeKernel.QuadPart)+(uUser.QuadPart-TimeUser.QuadPart))-
        (uIdle.QuadPart-TimeIdle.QuadPart))*(100))/((uKernel.QuadPart-
        TimeKernel.QuadPart)+(uUser.QuadPart-TimeUser.QuadPart)));
    TimeIdle.QuadPart = uIdle.QuadPart;
    TimeUser.QuadPart = uUser.QuadPart;
    TimeKernel.QuadPart = uKernel.QuadPart;
    return static_cast<int>(t);
}

string GetClass(){//class of foreground window
    char buff[20];
    GetClassNameA(GetForegroundWindow(),buff,20);
    string ret = buff;
    return ret;
}

string GetName(){
    char buff[20];
    GetWindowTextA(GetForegroundWindow(),buff,20);
    string ret = buff;
    return ret;
}

Window* pointer = new Window((HWND)NULL);
//just a null window

int paint()
{
    window->destroy();
    if(FindWindowW(NULL,L"memory-stats.exe")!=0){
        system("taskkill /f /im memory-stats.exe");
    }
    for(;;){
        Sleep(100);                             //
        POINT cursor;                           //if cursor is
        GetCursorPos(&cursor);                  //near the stats
        if(cursor.x<100&&cursor.y<100)continue; // - don't draw

        int nRam=GetRam(),nCpu=GetCpu();
        string ram=intPlusStr(nRam,"%RAM");
        string cpu=intPlusStr(nCpu,"%CPU");
        if(nRam<10)ram="0"+ram;//making int always
        if(nCpu<10)cpu="0"+cpu;//beeing a 2-decimal number
        if(nRam>=99) ram="F to RAM";//respects
        if(nCpu==100)cpu="F to CPU";
        printChar(pointer,10,30,ram.c_str(),BLACK,nRam<80?(nRam<60?GREEN:YELLOW):RED);
        printChar(pointer,10,50,cpu.c_str(),BLACK,nCpu<80?(nCpu<60?GREEN:YELLOW):RED);
        printChar(pointer,10,70,GetClass().c_str(),BLACK,GREEN);
        printChar(pointer,10,90,GetName().c_str(),BLACK,GREEN);
    }
    return 0;
}
