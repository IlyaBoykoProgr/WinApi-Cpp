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

bool yesno(HWND wind,const wchar_t* text,const wchar_t* caption=L"Choose Yes or No:",short icon=QUESTION){
    return IDYES==MessageBoxW(wind,text,caption,MB_YESNO|icon);
}

void message(HWND wind,const wchar_t* text,const wchar_t* caption=L"Information",short icon=INFORMATION){
    MessageBoxW(wind,text,caption,icon);
}

void message(HWND wind,const wchar_t *text, double var, const wchar_t* caption=L"Information",short icon=INFORMATION){
    std::wstring one(text), two=std::to_wstring(var);
    std::wstring yay=one.c_str(); two=yay+two;
    MessageBoxW(wind,two.c_str(),caption,icon);
}

SYSTEMTIME Time(){
    SYSTEMTIME time;
    GetSystemTime(&time);
    return time;
}

int xOf(HWND wind){
    tagRECT size;
    GetWindowRect(wind,&size);
    return size.left;
}
int yOf(HWND wind){
    tagRECT size;
    GetWindowRect(wind,&size);
    return size.top;
}
int widthOf(HWND wind){
    tagRECT size;
    GetWindowRect(wind,&size);
    return size.right-size.left;
}
int heightOf(HWND wind){
    tagRECT size;
    GetWindowRect(wind,&size);
    return size.bottom-size.top;
}
void quit(HWND hWnd){
    PostMessageW(hWnd,WM_DESTROY,0,0);
}
// Объявление функции окна (оконной процедуры)
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
HINSTANCE hInst; // Идентификатор приложения
// Указатель на константную строку символов - имя программы и класса окна
LPCWSTR AppName = L"MyProgramm";

// Точка входа в программу - функция WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                        LPSTR lpCmdLine, int nCmdShow)
{UNUSED(hPrevInstance);UNUSED(lpCmdLine);UNUSED(nCmdShow);
HWND hWnd; // Уникальный идентификатор окна (handle)
MSG msg; // Объявление структуры типа MSG, для работы с сообщениями
hInst = hInstance; // Сохраняем идентификатор приложения

// Заполняем структуру WNDCLASS
WNDCLASS wc;
        // Инициализируем выделенную для структуры память нулями
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
        L"", // Заголовок окна
        WS_OVERLAPPEDWINDOW, // Стиль окна
        CW_USEDEFAULT, 0, // Горизонтальная и вертикальная позиции окна
        0, 0, // Ширина и высота окна
        NULL, // Хендл родительского окна
        NULL, // Хендл меню
        hInst, // Идентификатор приложения
        NULL); // Дополнительные данные окна
	// Стандартный цикл обработки сообщений
	while(GetMessage(&msg, NULL, 0, 0))
	{
	        TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

extern void onKeyPress(HWND,WPARAM); tagRECT windowrect;
extern int paint(HWND);
// Оконная процедура
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
        switch(msg)
	{
	case WM_CREATE:
	    srand(Time().wMilliseconds);//randomize
	    ShowWindow(hWnd, SW_SHOWDEFAULT);
	    UpdateWindow(hWnd);
	    for(int i=0;i<=300;i++){
		MoveWindow(hWnd,xOf(hWnd),yOf(hWnd),i,i,true);
	    }
	    paint(hWnd);
	break;
	case WM_DESTROY:
	    for(int i=heightOf(hWnd);i>=0;i--)
		MoveWindow(hWnd,xOf(hWnd),yOf(hWnd),i,i,true);
	    PostQuitMessage(0);
	break;
	case WM_KEYUP:
	    onKeyPress(hWnd,wParam);
	break;
	default:
	    return DefWindowProc(hWnd, msg, wParam, lParam);
	}

return 0;
}
#endif//APIfunc
