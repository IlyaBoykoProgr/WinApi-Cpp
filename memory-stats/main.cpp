#include "../APIfunc.h"
#include "../FIGURES.h"
using namespace std;

const char* intPlusStr(int i,const char* str){
    string buff=to_string(i);
    return (buff+str).c_str();
}
const char* strPlusStr(const char* a, const char* b){
    string buff=a;
    return (buff+b).c_str();
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

Window* pointer;

int paint()
{
    window->destroy();
    for(;;){
        pointer=new Window((HWND)NULL);
        int nRam=GetRam(),nCpu=GetCpu();
        const char* ram=intPlusStr(nRam,"%RAM");
        if(nRam<10)ram=strPlusStr("0",ram);
        if(nRam==100)ram="F to RAM";
            printChar(pointer,10,30,ram,BLACK,nRam<80?(nRam<60?GREEN:YELLOW):RED);
        const char* cpu=intPlusStr(nCpu,"%CPU");
        if(nCpu<10)cpu=strPlusStr("0",cpu);
        if(nCpu==100)cpu="F to CPU";
            printChar(pointer,10,50,cpu,BLACK,nCpu<80?(nCpu<60?GREEN:YELLOW):RED);
        Sleep(100);
        delete pointer;
    }
    return 0;
}
