/*WinAPI base functions
    Created by https://github.com/IlyaBoykoProgr
    Repository of file https://github.com/IlyaBoykoProgr/WinApi-Cpp
    How to use: https://github.com/IlyaBoykoProgr/WinApi-Cpp/wiki/APIfunc.h
*/
#ifndef APIfunc
#define APIfunc

#ifndef _UNICODE
    #define _UNICODE
#endif
#include <windows.h>
#include <string>
#include <iostream>//io
#include <math.h>
#include <commctrl.h>//system widgets
#include <Commctrl.h>//system widgets
#include <thread>//multitasking
#define UNUSED(var) (void)var
#define ERROR_ICO MB_ICONHAND
#define WARNING MB_ICONWARNING
#define INFORMATION MB_ICONINFORMATION
#define QUESTION MB_ICONQUESTION
#define APP_ERROR_ICO -1
#define RANDOM_ICO (rand()%4*16+16)
#define loop(count,var) for(int var=0;var<count;var++)
#define loopEx(count,var,pause) for(int var=0;var<count;var+=SleepEx(pause,false)+1)
#define chance(ch) if((rand()%ch)==0)

#ifdef Manythread
    #define thread0(func) std::thread(func).detach();
    #define thread1(func,arg1) std::thread(func,arg1).detach();
    #define thread2(func,arg1,arg2) std::thread(func,arg1,arg2).detach();
    #define thread3(func,arg1,arg2,arg3) std::thread(func,arg1,arg2,arg3).detach();
#else
    #define thread0(func) func()
    #define thread1(func,arg1) func(arg1)
    #define thread2(func,arg1,arg2) func(arg1,arg2)
    #define thread3(func,arg1,arg2,arg3) func(arg1,arg2,arg3)
#endif

void start(LPCSTR cmd){ WinExec(cmd,SW_SHOW);}
void process(LPCSTR file){
    std::thread *t= new std::thread(start,file);
    t->detach();
    delete t;
}
extern int paint();//MAIN FUNCTION
void exec(){
    MSG msg;
    while(GetMessage(&msg, NULL, 0, 0)){
	TranslateMessage(&msg);
	DispatchMessage(&msg);
    }
}//EVENT LOOP

template<typename lambda>
///returns run time
unsigned long run(lambda runnable){
    unsigned long timeBefore = clock();
    runnable();
    return clock()-timeBefore;
}

SYSTEMTIME Time(){
    SYSTEMTIME time;
    GetSystemTime(&time);
    return time;
}

char pathToExecutable[200];//path to programm

#define quit() PostQuitMessage(0)

void restart(short howmany=1,bool closeAfterRestart=1,bool checkRestart=1,unsigned long pause=0){
    std::string dat=pathToExecutable;
    dat+=checkRestart?" restart":"";
    loop(howmany,i){
	    WinExec(dat.c_str(),SW_SHOW);
            Sleep(pause);
    }
    if(closeAfterRestart)exit(0);
}
bool isRestarted(){
    if(__argc>0)
	return !stricmp(__argv[1],"restart");
    return 0;
}


LRESULT CALLBACK WndMain(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
HINSTANCE hInst; // Идентификатор приложения

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                        LPSTR lpCmdLine, int nCmdShow)
{UNUSED(hPrevInstance);UNUSED(lpCmdLine);UNUSED(nCmdShow);
    GetModuleFileNameA(NULL,pathToExecutable,200);//getting path
    srand(Time().wMilliseconds);//randomize
#ifndef NoWindow
    hInst = hInstance; // Сохраняем идентификатор приложения
#else
    UNUSED(hInstance);
#endif
    paint();
#ifndef NoWindow
    exec();
#endif
    return 0;
}

enum Edge{
    Left,Right,Top,Bottom,NotOnEdge
};

class Window{
    tagRECT rect;
    void registerClass(WNDPROC wndproc=WndMain,LPCWSTR className=L"wind"){
	ZeroMemory(&wc, sizeof(wc));
	    wc.lpfnWndProc = wndproc;
	    wc.lpszClassName = className;
	RegisterClass(&wc);
    }
public:// Уникальный идентификатор окна (handle)
    HWND hWnd;
    WNDCLASS wc;
    Window(WNDPROC wndproc=WndMain){
        registerClass(wndproc);
        hWnd = CreateWindow(
	L"wind", // Имя класса окна
	L"", // Заголовок окна
	WS_OVERLAPPEDWINDOW, // Стиль окна
	CW_USEDEFAULT,CW_USEDEFAULT, // Горизонтальная и вертикальная позиции окна
	CW_USEDEFAULT,CW_USEDEFAULT, // Ширина и высота окна
        NULL, // Хендл родительского окна
        NULL, // Хендл меню
        hInst, // Идентификатор приложения
	NULL); // Дополнительные данные окна
#ifdef OnTimer
	SetTimer(hWnd,(UINT_PTR)hWnd,(UINT)OnTimer,NULL);
#endif
    }
    Window(HWND handle){hWnd=handle;}
    Window* hide(){ShowWindow(hWnd,SW_HIDE);return this;}
    Window* show(){ShowWindow(hWnd,SW_RESTORE);return this;}
    Window* enable(bool enabled){EnableWindow(hWnd,enabled);return this;}
    Window* minimize(){ShowWindow(hWnd,SW_MINIMIZE);return this;}
    Window* maximize(){ShowWindow(hWnd,SW_MAXIMIZE);return this;}
    Window* repaint(){InvalidateRect(hWnd,&rect,true);SendMessage(hWnd,WM_PAINT,0,0);return this;}
    Window* focus(){SetFocus(hWnd);return this;}
    Window* sysmessage(UINT msg,WPARAM wParam=0,LPARAM lParam=0){SendMessage(hWnd,msg,wParam,lParam);return this;}
    Window* setWindLong(int index, long Long){SetWindowLongPtr(hWnd,index,Long);return this;}
    void destroy(){DestroyWindow(hWnd);delete this;}
    inline tagRECT* getRect(){
	GetWindowRect(hWnd,&rect);
	return &rect;
    }
    inline HDC getDC(){return GetDC(hWnd);}
    inline int x(){
	return getRect()->left;
    }inline int y(){
	return getRect()->top;
    }inline int width(){
	return getRect()->right- getRect()->left;
    }inline int height(){
	return getRect()->bottom-getRect()->top;
    }
    Window* setTitle(LPCWSTR title){
	SetWindowTextW(hWnd,title);return this;
    }
    Window* move(int x, int y){
	MoveWindow(hWnd,x,y,width(),height(),1);return this;
    }
    Window* moveToRandomPoint(){
	Window screen(GetDesktopWindow());
        move(rand()%screen.width(),
             rand()%screen.height());
        move(x()-width(),y()-height());
	move(x()<0?0:x(),y()<0?0:y());
	return this;
    }
    Window* resize(int width, int height){
	MoveWindow(hWnd,x(),y(),width,height,1);return this;
    }
    Window* message(const wchar_t* text,const wchar_t* caption=L"Information",short icon=INFORMATION){
        MessageBoxW(hWnd,text,caption,icon);
        if(icon==-1){exit(-1);}
        return this;
    }
    Window* message(const wchar_t *text, float var, const wchar_t* caption=L"Information",short icon=INFORMATION){
	std::wstring one(text), two=std::to_wstring(var);
	std::wstring yay=one.c_str(); two=yay+two;
        MessageBoxW(hWnd,two.c_str(),caption,icon);
        if(icon==-1){exit(-1);}
        return this;
    }bool yesno(const wchar_t* text,const wchar_t* caption=L"Choose Yes or No:",short icon=QUESTION){
	return IDYES==MessageBoxW(hWnd,text,caption,MB_YESNO|icon);
    }
    Window* teleport(int x1,int y1,unsigned mSecs){
	unsigned h=height(),w=width();
	for(unsigned i=mSecs;i>0;i--)resize(i*w/mSecs,i*h/mSecs);
	move(x1,y1);
	for(unsigned i=0;i<mSecs;i++)resize(i*w/mSecs,i*h/mSecs);
	return this;
    }
    Edge onEdge(){
	Window* screen=new Window(GetDesktopWindow());
	if(x()<=0)return Edge::Left;
	if(y()<=0)return Edge::Top;
	if(x()+width()>=screen->width())return Edge::Right;
	if(y()+height()>=screen->height())return Edge::Bottom;
	return Edge::NotOnEdge;
    }
    bool operator==(Window* other){return this->hWnd==other->hWnd;}
    bool operator!=(Window* other){return this->hWnd!=other->hWnd;}
    #ifdef OnTimer
    Window* resetTimer(int newDuration){
        KillTimer(hWnd,(UINT_PTR)hWnd);
        SetTimer(hWnd,(UINT_PTR)hWnd, newDuration,NULL);return this;
    }
    #endif
};
Window* window=new Window;Window* screen=new Window(GetDesktopWindow());

class Widget:public Window{
    Window* parent;
public:
    Widget(Window* parent,LPCWSTR name=L"",LPCWSTR widgetName=WC_STATICW,
           long parameters=WS_VISIBLE):Window(parent->hWnd){
	this->parent=parent;
	hWnd = CreateWindow(
	widgetName, // Имя класса окна
	name, // Заголовок окна
	WS_CHILD| parameters, // Стиль окна
	0, 0, // Горизонтальная и вертикальная позиции окна
	100, 20, // Ширина и высота окна
	parent->hWnd, // Хендл родительского окна
	NULL, // Хендл меню
	hInst, // Идентификатор приложения
	NULL); // Дополнительные данные окна
	ShowWindow(hWnd,SW_SHOW);
    }
    Window* move(int x, int y){
	MoveWindow(hWnd,x-parent->x()-7,y-parent->y()-30,width(),height(),0);return this;
    }
    bool isMe(LPARAM &widgets){
	return widgets==(LPARAM)hWnd;
    }
};

#ifdef OnTimer
    extern void timer();
#endif
#ifdef OnKeyPress
    extern void OnKeyPress(unsigned key);
#endif
#ifdef OnMove
    extern void OnMove();
#endif
#ifdef OnClick
    extern void OnClick(unsigned key, int x, int y);
#endif
#ifdef OnResize
    extern void OnResize(RECT*,int);
#endif
#ifdef Widgets
    extern void Widgets(LPARAM &widgets);
#endif
#ifdef OnClose
    extern int OnClose();
#endif
    // Оконная процедура
Window event((HWND)0);
LRESULT CALLBACK WndMain(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){
 event.hWnd=hWnd;
 switch(msg){
    case WM_CREATE:
        UpdateWindow(hWnd);
    break;
    case WM_CLOSE:
    #ifdef OnClose
        if(OnClose()==0)exit(0);
    #else
        exit(0);
    #endif
    case WM_DESTROY:
    break;
    #ifdef OnKeyPress
    case WM_KEYDOWN:
        OnKeyPress(wParam);
    break;
    #endif
    #ifdef OnMove
    case WM_MOVING:
        OnMove();
    break;
    #endif
    #ifdef OnClick
    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
    case WM_MBUTTONDOWN:
    case WM_XBUTTONDOWN:
        OnClick(wParam,MAKEPOINTS(lParam).x,MAKEPOINTS(lParam).y);
    break;
    #endif
    #ifdef Widgets
    case WM_COMMAND:
        Widgets(lParam);
    break;
    #endif
    #ifdef OnResize
    case WM_SIZE:
    case WM_SIZING:
        OnResize((RECT*)lParam,wParam);
    break;
    #endif
    #ifdef OnTimer
    case WM_TIMER:timer();break;
    #endif
    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
event.hWnd=NULL;
return 0;
}


#endif//APIfunc
