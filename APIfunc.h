/*WinAPI base functions
    Created by https://github.com/IlyaBoykoProgr
    Repository of file https://github.com/IlyaBoykoProgr/WinApi-Cpp
*/
#ifndef APIfunc
#define APIfunc

#define UNUSED(var) (void)var
#define WARNING MB_ICONWARNING
#define ERROR MB_ICONERROR
#define INFORMATION MB_ICONINFORMATION
#define loop(count,var) for(int var=0;var<count;var++)
#include <windows.h>
#include <string>

bool yesno(const wchar_t* text,const wchar_t* caption=L"Choose Yes or No:"){
    return IDYES==MessageBoxW(NULL,text,caption,MB_YESNO|MB_ICONQUESTION);
}

void message(const wchar_t* text,const wchar_t* caption=L"Information",short icon=INFORMATION){
    MessageBoxW(NULL,text,caption,icon);
}

void message(const wchar_t *text, double var, const wchar_t* caption=L"Information",short icon=INFORMATION){
    std::wstring one(text), two=std::to_wstring(var);
    std::wstring yay=one.c_str(); two=yay+two;
    MessageBoxW(NULL,
                two.c_str(),
    caption,icon);
}

int WinMain(HINSTANCE hIns,HINSTANCE hPreIns,LPSTR lpCmdLine,int nShowCmd){
    UNUSED(hIns);UNUSED(hPreIns);UNUSED(lpCmdLine);UNUSED(nShowCmd);
    ShowWindow(GetConsoleWindow(),0);
    return 0;
}

SYSTEMTIME Time(){
    SYSTEMTIME time;
    GetSystemTime(&time);
    return time;
}
#endif//APIfunc
