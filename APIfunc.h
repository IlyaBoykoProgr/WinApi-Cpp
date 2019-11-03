/*WinAPI base functions
    Created by https://github.com/IlyaBoykoProgr
    Repository of file https://github.com/IlyaBoykoProgr/WinApi-Cpp
    How to use: https://github.com/IlyaBoykoProgr/WinApi-Cpp/wiki/APIfunc.h
*/
#ifndef APIfunc
#define APIfunc

#define UNUSED(var) (void)var
#define WARNING MB_ICONWARNING
#define ERROR MB_ICONERROR
#define INFORMATION MB_ICONINFORMATION
#define QUESTION MB_ICONQUESTION
#define loop(count,var) for(int var=0;var<count;var++)
#include <windows.h>
#include <string>

extern int paint();//MAIN FUNCTION
HWND hWnd; //Идентификатор окна

bool yesno(const wchar_t* text,const wchar_t* caption=L"Choose Yes or No:",short icon=QUESTION){
    return IDYES==MessageBoxW(hWnd,text,caption,MB_YESNO|icon);
}
void message(const wchar_t* text,const wchar_t* caption=L"Information",short icon=INFORMATION){
    MessageBoxW(hWnd,text,caption,icon);
}
void message(const wchar_t *text, double var, const wchar_t* caption=L"Information",short icon=INFORMATION){
    std::wstring one(text), two=std::to_wstring(var);
    std::wstring yay=one.c_str(); two=yay+two;
    MessageBoxW(hWnd,two.c_str(),caption,icon);
}

SYSTEMTIME Time(){
    SYSTEMTIME time;
    GetSystemTime(&time);
    return time;
}

void quit(){
#ifndef NoWindow
    PostMessageW(hWnd,WM_DESTROY,0,0);
#else
    exit(0);
#endif
}
#ifndef NoWindow
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
HINSTANCE hInst; // Идентификатор приложения
MSG msg; // Объявление структуры типа MSG, для работы с сообщениями
#endif
// Точка входа в программу - функция WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                        LPSTR lpCmdLine, int nCmdShow)
{UNUSED(hPrevInstance);UNUSED(lpCmdLine);UNUSED(nCmdShow);
    srand(Time().wMilliseconds);//randomize
#ifndef NoWindow
    hInst = hInstance; // Сохраняем идентификатор приложения
    paint();//main
    while(GetMessage(&msg, NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
#else
    return paint();
#endif
}

#ifndef NoWindow
class Window{ // Уникальный идентификатор окна (handle)
LPCWSTR AppName=L"Wind";
public:
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
            wc.lpszClassName = AppName;
        RegisterClass(&wc); // Создаем и регистрируем оконный класс

        // Создаем окно программы
        hWnd = CreateWindow(
        AppName, // Имя класса окна
        AppName, // Заголовок окна
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

    int x(HWND &window=hWnd){
	tagRECT size;
	GetWindowRect(window,&size);
	return size.left;
    }int y(HWND &window=hWnd){
	tagRECT size;
	GetWindowRect(window,&size);
	return size.top;
    }int width(HWND &window=hWnd){
	tagRECT size;
	GetWindowRect(window,&size);
	return size.right-size.left;
    }int height(HWND &window=hWnd){
	tagRECT size;
	GetWindowRect(window,&size);
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
    }
};
Window window;

// Оконная процедура
#ifdef OnKeyPress
    extern void OnKeyPress(unsigned key);
#endif
#ifdef OnMove
    extern void OnMove(RECT* newPos);
#endif
#ifdef OnClick
    extern void OnClick(unsigned key, int x, int y);
#endif
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
 switch(msg){
    case WM_CREATE:
        ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
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
    case WM_MBUTTONDOWN:
        OnClick(wParam,LOWORD(lParam),HIWORD(lParam));
    break;
    #endif
    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
return 0;
}
#endif//Window

#endif//APIfunc
