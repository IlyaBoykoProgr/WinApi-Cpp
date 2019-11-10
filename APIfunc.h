/*WinAPI base functions
    Created by https://github.com/IlyaBoykoProgr
    Repository of file https://github.com/IlyaBoykoProgr/WinApi-Cpp
    How to use: https://github.com/IlyaBoykoProgr/WinApi-Cpp/wiki/APIfunc.h
*/
#ifndef APIfunc
#define APIfunc

#define UNUSED(var) (void)var
#define WARNING MB_ICONWARNING
#define ERROR MB_ICONSTOP
#define INFORMATION MB_ICONINFORMATION
#define QUESTION MB_ICONQUESTION
#define loop(count,var) for(int var=0;var<count;var++)
#include <windows.h>
#include <string>

extern int paint();//MAIN FUNCTION

SYSTEMTIME Time(){
    SYSTEMTIME time;
    GetSystemTime(&time);
    return time;
}

void quit(){
    exit(0);
}

void restart(short howmany=1){
    char path[200];         //path to programm
    GetModuleFileNameA(NULL,path,200);//getting path
    loop(howmany,i)
          WinExec(path,SW_SHOW);
    exit(0);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
HINSTANCE hInst; // Идентификатор приложения
// Точка входа в программу - функция WinMain

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                        LPSTR lpCmdLine, int nCmdShow)
{UNUSED(hPrevInstance);UNUSED(lpCmdLine);UNUSED(nCmdShow);
    srand(Time().wMilliseconds);//randomize
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
public:// Уникальный идентификатор окна (handle)
    HWND hWnd;
    Window(){
        // Заполняем структуру WNDCLASS
        WNDCLASS wc;
        ZeroMemory(&wc, sizeof(wc));
            wc.style = CS_HREDRAW | CS_VREDRAW;
            wc.lpfnWndProc = (WNDPROC)WndProc;
            wc.hInstance = hInst;
            wc.hIcon = LoadIcon(hInst, IDI_APPLICATION);
            wc.hCursor = LoadCursor(NULL, IDC_ARROW);
            wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	    wc.lpszClassName = L"wind";
        RegisterClass(&wc); // Создаем и регистрируем оконный класс

        // Создаем окно программы
        hWnd = CreateWindow(
	L"wind", // Имя класса окна
	L"", // Заголовок окна
        WS_OVERLAPPEDWINDOW, // Стиль окна
	200, 200, // Горизонтальная и вертикальная позиции окна
        0, 0, // Ширина и высота окна
        NULL, // Хендл родительского окна
        NULL, // Хендл меню
        hInst, // Идентификатор приложения
        NULL); // Дополнительные данные окна
	// Стандартный цикл обработки сообщений
    }
    Window* hide(){ShowWindow(hWnd,SW_HIDE);return this;}
    Window* show(){ShowWindow(hWnd,SW_SHOW);return this;}

    int x(){
	tagRECT size;
	GetWindowRect(hWnd,&size);
	return size.left;
    }int y(){
	tagRECT size;
	GetWindowRect(hWnd,&size);
	return size.top;
    }int width(){
	tagRECT size;
	GetWindowRect(hWnd,&size);
	return size.right-size.left;
    }int height(){
	tagRECT size;
	GetWindowRect(hWnd,&size);
	return size.bottom-size.top;
    }
    Window* setTitle(LPCWSTR title){
	SetWindowTextW(hWnd,title);return this;
    }
    Window* move(int x, int y){
	MoveWindow(hWnd,x,y,width(),height(),0);return this;
    }
    Window* resize(int width, int height){
	MoveWindow(hWnd,x(),y(),width,height,1);return this;
    }bool yesno(const wchar_t* text,const wchar_t* caption=L"Choose Yes or No:",short icon=QUESTION){
	return IDYES==MessageBoxW(hWnd,text,caption,MB_YESNO|icon);
    }
    Window* message(const wchar_t* text,const wchar_t* caption=L"Information",short icon=INFORMATION){
	MessageBoxW(hWnd,text,caption,icon);return this;
    }
    Window* message(const wchar_t *text, double var, const wchar_t* caption=L"Information",short icon=INFORMATION){
	std::wstring one(text), two=std::to_wstring(var);
	std::wstring yay=one.c_str(); two=yay+two;
	MessageBoxW(hWnd,two.c_str(),caption,icon);
	return this;
    }
};
Window* window=new Window;

#include <commctrl.h>//system widgets
class Widget:public Window{
public:
    Widget(LPCWSTR widgetName,Window* parent,LPCWSTR name=L""){
	hWnd = CreateWindow(
	widgetName, // Имя класса окна
	name, // Заголовок окна
	WS_CHILDWINDOW, // Стиль окна
	0, 0, // Горизонтальная и вертикальная позиции окна
	100, 20, // Ширина и высота окна
	parent->hWnd, // Хендл родительского окна
	NULL, // Хендл меню
	hInst, // Идентификатор приложения
	NULL); // Дополнительные данные окна
	ShowWindow(hWnd,SW_SHOW);
    }
    bool isMe(LPARAM &widgets){
	return widgets==(LPARAM)hWnd;
    }
};

#ifdef OnKeyPress
    extern void OnKeyPress(unsigned key);
#endif
#ifdef OnMove
    extern void OnMove(RECT* newPos);
#endif
#ifdef OnClick
    extern void OnClick(unsigned key, int x, int y);
#endif
#ifdef Widgets
    extern void Widgets(LPARAM &widget);
#endif
    // Оконная процедура
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
 switch(msg){
    case WM_CREATE:
        UpdateWindow(hWnd);
    break;
    case WM_CLOSE:
     exit(0);
    break;
    #ifdef OnKeyPress
    case WM_KEYDOWN:
        OnKeyPress(wParam);
    break;
    #endif
    #ifdef OnMove
    case WM_MOVING:
        OnMove((RECT*) lParam);
    break;
    #endif
    #ifdef OnClick
    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
    case WM_MBUTTONDOWN:
        OnClick(wParam,MAKEPOINTS(lParam).x,MAKEPOINTS(lParam).y);
    break;
    #endif
    #ifdef Widgets
    case WM_COMMAND:
        Widgets(lParam);
    break;
    #endif
    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
return 0;
}

#endif//APIfunc
