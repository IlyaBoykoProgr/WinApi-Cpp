#define OnTimer 1000
#include "../APIfunc.h"

int paint(){//'main' function
    srand(Time().wMilliseconds);
    window->hide()
          ->resetTimer(1);
    return 0;
}

bool isWindowMaximized(HWND h){
    WINDOWPLACEMENT wndplc;
    wndplc.length=sizeof(wndplc);
    GetWindowPlacement(h,&wndplc);
    return wndplc.showCmd&SW_SHOWMAXIMIZED;
}

BOOL CALLBACK fall(HWND wnd, LPARAM unused){
    if(!IsWindow(wnd))return true;
    if(!IsWindowVisible(wnd))return true;
    if(!isWindowMaximized(wnd))return true;
    if(wnd==GetDesktopWindow())return true;
    Window back(wnd);
    double x=back.x(), y=back.y();
    if(y+back.height()<screen->height()-40){//Not bottom
        back.move(x,y+10);
    }
    /*re calculate*/x=back.x(), y=back.y();
    if(x<0)back.move(x+5,y);//left of screen
    else if(x+back.width()>screen->width())back.move(x-5,y);//right of screen
    UNUSED(unused);
    return true;
}

void timer(){
    EnumWindows(fall,0);
}
