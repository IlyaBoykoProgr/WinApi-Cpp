#ifndef APIfunc
#define APIfunc

#define UNUSED(var) (void)var
#define loop(count,var) for(int var=0;var<count;var++)
#include <windows.h>
#include <string>

bool yesno(const wchar_t* text,const wchar_t* caption=L"Choose Yes or No:"){
    return IDYES==MessageBoxW(NULL,text,caption,MB_YESNO|MB_ICONQUESTION);
}

void message(const wchar_t* text,const wchar_t* caption=L"Information"){
    MessageBoxW(NULL,text,caption,MB_ICONINFORMATION);
}

void message(const wchar_t *text, double var, const wchar_t* caption=L"Information"){
    std::wstring one(text), two=std::to_wstring(var);
    std::wstring yay=one.c_str(); two=yay+two;
    MessageBoxW(NULL,
                two.c_str(),
    caption,MB_ICONINFORMATION);
}

int WinMain(HINSTANCE hIns,HINSTANCE hPreIns,LPSTR lpCmdLine,int nShowCmd){
    UNUSED(hIns);UNUSED(hPreIns);UNUSED(lpCmdLine);UNUSED(nShowCmd);
    ShowWindow(GetConsoleWindow(),0);
    return 0;
}
#endif//APIfunc
