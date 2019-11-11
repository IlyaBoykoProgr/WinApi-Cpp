#define Widgets command
#define OnResize resize
#include "../APIfunc.h"

Widget
label(WC_STATICW,L"Введите данные:"),
caption(WC_EDITW,L"Здесь заголовок,"),
text(WC_EDITW,L"Сюда текст."),
icon(WC_COMBOBOXW,L"Иконки",window,CBS_DROPDOWN),
button(WC_COMBOBOXW,L"Кнопки",window,CBS_DROPDOWN),
smessage(WC_BUTTONW,L"Готово");
int paint(){
    window->setTitle(L"Test widgets")->resize(400,400)->show();
    SendMessageW(icon.hWnd,CB_ADDSTRING,0,(LPARAM)L"Ошибка");
    SendMessageW(icon.hWnd,CB_ADDSTRING,0,(LPARAM)L"Вопрос");
    SendMessageW(icon.hWnd,CB_ADDSTRING,0,(LPARAM)L"Восклицание");
    SendMessageW(icon.hWnd,CB_ADDSTRING,0,(LPARAM)L"Информация");

    SendMessageW(button.hWnd,CB_ADDSTRING,0,(LPARAM)L"Ок");
    SendMessageW(button.hWnd,CB_ADDSTRING,0,(LPARAM)L"Ок/Отмена");
    SendMessageW(button.hWnd,CB_ADDSTRING,0,(LPARAM)L"Прервать/Повтор/Пропустить");
    SendMessageW(button.hWnd,CB_ADDSTRING,0,(LPARAM)L"Да/Нет/Отмена");
    SendMessageW(button.hWnd,CB_ADDSTRING,0,(LPARAM)L"Да/Нет");
    SendMessageW(button.hWnd,CB_ADDSTRING,0,(LPARAM)L"Повторить/Отмена");
    SendMessageW(button.hWnd,CB_ADDSTRING,0,(LPARAM)L"Отмена/Повторить/Продолжить");

    tagRECT rect;GetWindowRect(window->hWnd,&rect);
    resize(&rect);
    return 0;
}

void command(LPARAM &widgets){
    if(smessage.isMe(widgets)){
        WCHAR txt[100], cptn[100];
        GetWindowTextW(text.hWnd,txt,100);
        GetWindowTextW(caption.hWnd,cptn,100);
        short icon_id= SendMessageW(icon.hWnd,CB_GETCURSEL,0,0);
        if(icon_id==CB_ERR){
            window->message(L"Не выбран тип значка",L"Упс!",ERROR_ICO);
            return;
        }
        icon_id++; icon_id*=10;
        switch(icon_id){
        case 10:icon_id=ERROR_ICO;break;
        case 20:icon_id=QUESTION;break;
        case 30:icon_id=WARNING;break;
        case 40:icon_id=INFORMATION;break;
        }
        short button_id= SendMessageW(button.hWnd,CB_GETCURSEL,0,0);
        if(button_id==CB_ERR){
            window->message(L"Не выбраны кнопки ответа",L"Упс!",ERROR_ICO);
            return;
        }
        MessageBoxW(window->hWnd,txt,cptn,icon_id|button_id);
    }
}

void resize(RECT* newpos){
    UNUSED(newpos);
    int q= window->height()-40;q/=6;
    int width=window->width();

    label.move(0,0)->resize(width,q);
    caption.move(0,q)->resize(width,q);
    text.move(0,q*2)->resize(width,q);
    icon.move(0,q*3)->resize(width-40,q+50);
    button.move(0,q*4)->resize(width-40,q+100);
    smessage.move(0,q*5)->resize(width,q);
}
