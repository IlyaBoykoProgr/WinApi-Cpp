#define Widgets command
#define OnResize resize
#include "../Widgets.h"
#include "../APIfunc.h"

Static label(window,L"Введите данные:");
Progress bar(window,L"bar");
Edit
caption(window,L"Здесь заголовок,"),
text(window,L"Сюда текст.");
Widget
smessage(window,L"Готово",WC_BUTTON);
DropBox
icon(window,L"Иконки"),
button(window,L"Кнопки");
int paint(){
    window->setTitle(L"Test widgets")->resize(400,400)->show()->minimize();
    icon.add(L"Без иконки")->add(L"Ошибка")->add(L"Вопрос")->add(L"Восклицание")->add(L"Информация");
    button.add(L"Ок")->add(L"Ок/Отмена")->add(L"Прервать/Повтор/Пропустить")->
           add(L"Да/Нет/Отмена")->add(L"Да/Нет")->add(L"Повторить/Отмена")->add(L"Отмена/Повторить/Продолжить");
    resize(NULL,0);

    bar.setPos(0)->resize(window->width(),20)->move(0,30)->show();
    bar.setLoading(true);
    return 0;
}

void command(LPARAM &widgets){
    if(smessage.isMe(widgets)){

        loop(100,i){bar.setPos(i)->show();Sleep(6);}

        int icon_id=icon.getIndex();
        int button_id= button.getIndex();

        if(icon_id==CB_ERR){
            window->message(L"Не выбран тип значка",L"Упс!",ERROR_ICO);
            goto unload;
        }icon_id*=0x10;

        if(button_id==CB_ERR){
            window->message(L"Не выбраны кнопки ответа",L"Упс!",ERROR_ICO);
            goto unload;
        }

        WCHAR msg[100],cap[100];
        text.getText(msg);
        caption.getText(cap);
        MessageBoxW(NULL,msg,cap,icon_id|button_id);
        unload:
        loop(100,i){bar.setPos(99-i)->show();Sleep(3);}
    }
}

void resize(RECT* newpos,int state){
    UNUSED(newpos);
    int q= window->height()-40;q/=6;
    int width=window->width();

    bar.move(0,20)->resize(width,q);
    label.move(0,0)->resize(width,q);
    caption.move(0,q)->resize(width,q);
    text.move(0,q*2)->resize(width,q);
    icon.move(0,q*3)->resize(width-40,q+50);
    button.move(0,q*4)->resize(width-40,q+100);
    smessage.move(0,q*5)->resize(width,q);
    if(state==SIZE_MINIMIZED)window->show();
}
