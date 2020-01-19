/*WinAPI base functions
    Created by https://github.com/IlyaBoykoProgr
    Repository of file https://github.com/IlyaBoykoProgr/WinApi-Cpp
    How to use: https://github.com/IlyaBoykoProgr/WinApi-Cpp/wiki/APIfunc.h
*/
#ifndef APIfunc
#define APIfunc

#define __UNICODE
#define _UNICODE
#include <windows.h>
#include <string>
#include <iostream>//io
#include <commctrl.h>//system widgets
#include <thread>//multitasking
#define UNUSED(var) (void)var
#define ERROR_ICO MB_ICONHAND
#define WARNING MB_ICONWARNING
#define INFORMATION MB_ICONINFORMATION
#define QUESTION MB_ICONQUESTION
#define RANDOM_ICO (rand()%4*16+16)
#define loop(count,var) for(int var=0;var<count;var++)

void start(LPCSTR cmd){ WinExec(cmd,SW_SHOW);}
void process(LPCSTR file){
    std::thread t(start,file);
    t.detach();
}
extern int paint();//MAIN FUNCTION

SYSTEMTIME Time(){
    SYSTEMTIME time;
    GetSystemTime(&time);
    return time;
}

char pathToExecutable[200];//path to programm

#define quit() PostQuitMessage(0)

void restart(short howmany=1,bool closeAfterRestart=1,bool checkRestart=1){
    std::string dat=pathToExecutable;
    dat+=checkRestart?" restart":"";
    loop(howmany,i){
	    start(dat.c_str());
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
#ifndef NoWindow
    hInst = hInstance; // Сохраняем идентификатор приложения
#else
    UNUSED(hInstance);
#endif
    paint();
#ifndef NoWindow
    MSG msg; // Объявление структуры типа MSG, для работы с сообщениями
    while(GetMessage(&msg, NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
#endif
    return 0;
}

class Window{
    tagRECT rect;
public:// Уникальный идентификатор окна (handle)
    HWND hWnd;
    Window(WNDPROC wndproc=WndMain){
	srand(Time().wMilliseconds);//randomize
        // Заполняем структуру WNDCLASS
        WNDCLASS wc;
        ZeroMemory(&wc, sizeof(wc));
            wc.style = CS_HREDRAW | CS_VREDRAW;
	    wc.lpfnWndProc = (WNDPROC)wndproc;
            wc.hInstance = hInst;
	    wc.hIcon = LoadIcon(hInst, IDI_APPLICATION);
            wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	    wc.lpszClassName = L"wind";
        RegisterClass(&wc); // Создаем и регистрируем оконный класс

        // Создаем окно программы
        hWnd = CreateWindow(
	L"wind", // Имя класса окна
	L"", // Заголовок окна
	WS_OVERLAPPEDWINDOW, // Стиль окна
	rand()%300,rand()%200, // Горизонтальная и вертикальная позиции окна
	CW_USEDEFAULT, CW_USEDEFAULT, // Ширина и высота окна
        NULL, // Хендл родительского окна
        NULL, // Хендл меню
        hInst, // Идентификатор приложения
	NULL); // Дополнительные данные окна
	std::wcout<<"Created Window : "<<hWnd<<'\n'<<
	"WndProc is pointing to "<<&wndproc<<"\n\n";
#ifdef OnTimer
	SetTimer(hWnd,(int)hWnd,OnTimer,NULL);
#endif
    }
    Window(HWND handle){hWnd=handle;}
    Window* hide(){ShowWindow(hWnd,SW_HIDE);return this;}
    Window* show(){ShowWindow(hWnd,SW_RESTORE);return this;}
    Window* minimize(){ShowWindow(hWnd,SW_MINIMIZE);return this;}
    Window* maximize(){ShowWindow(hWnd,SW_MAXIMIZE);return this;}
    Window* focus(){SetFocus(hWnd);return this;}
    Window* sysmessage(UINT msg,WPARAM wParam=0,LPARAM lParam=0){SendMessage(hWnd,msg,wParam,lParam);return this;}
    Window* setWindLong(int index, long Long){SetWindowLongPtr(hWnd,index,Long);return this;}
    void destroy(){DestroyWindow(hWnd);delete this;}
    tagRECT* getRect(){
	GetWindowRect(hWnd,&rect);
	return &rect;
    }
    HDC getDC(){return GetDC(hWnd);}
    int x(){
	return getRect()->left;
    }int y(){
	return getRect()->top;
    }int width(){
	return getRect()->right- getRect()->left;
    }int height(){
	return getRect()->bottom-getRect()->top;
    }
    Window* setTitle(LPCWSTR title){
	SetWindowTextW(hWnd,title);return this;
    }
    Window* move(int x, int y){
	MoveWindow(hWnd,x,y,width(),height(),0);return this;
    }
    Window* moveToRandomPoint(){
	Window screen(GetDesktopWindow());
	move(rand()%screen.width() -width() ,
	     rand()%screen.height()-height()
	     );
	move(x()<0?0:x(),y()<0?0:y());
	return this;
    }
    Window* resize(int width, int height){
	MoveWindow(hWnd,x(),y(),width,height,1);return this;
    }
    Window* message(const wchar_t* text,const wchar_t* caption=L"Information",short icon=INFORMATION){
	MessageBoxW(hWnd,text,caption,icon);return this;
    }
    Window* message(const wchar_t *text, float var, const wchar_t* caption=L"Information",short icon=INFORMATION){
	std::wstring one(text), two=std::to_wstring(var);
	std::wstring yay=one.c_str(); two=yay+two;
	MessageBoxW(hWnd,two.c_str(),caption,icon);
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
    bool onEdge(){
	Window* screen=new Window(GetDesktopWindow());
	return
	      (x()<=0)||(y()<=0)||
	      (x()+width()>=screen->width())||
	      (y()+height()>=screen->height());
    }
    #ifdef OnTimer
    Window* resetTimer(int newDuration){
	KillTimer(hWnd,(int)hWnd);SetTimer(hWnd,(int)hWnd, newDuration,NULL);return this;
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
	std::wcout<<"Created "<<widgetName<<" : "<<hWnd<<"\nParent's hWnd: "<<parent->hWnd<<"\n\n";
    }
    Window* move(int x, int y){
	MoveWindow(hWnd,x-parent->x()-7,y-parent->y()-30,width(),height(),0);return this;
    }
    bool isMe(LPARAM &widgets){
	return widgets==(LPARAM)hWnd;
    }
};

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
#ifdef OnTimer
    extern void timer();
#endif
#ifdef OnClose
    extern int OnClose();
#endif
    // Оконная процедура
Window* event;
LRESULT CALLBACK WndMain(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
 event=new Window(hWnd);
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
event=NULL;
return 0;
}


#endif//APIfunc
