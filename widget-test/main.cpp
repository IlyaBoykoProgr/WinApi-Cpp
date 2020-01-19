#define Widgets command
#define OnResize resize
#include "../APIfunc.h"
#include "../Widgets.h"

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
    if(isRestarted())window->message(L"Restarted.");
    window->setTitle(L"Test widgets")->resize(400,400)->show()->minimize();
    icon.add(L"Без иконки")->add(L"Ошибка")->add(L"Вопрос")->add(L"Восклицание")->add(L"Информация");
    button.add(L"Ок")->add(L"Ок/Отмена")->add(L"Прервать/Повтор/Пропустить")->
           add(L"Да/Нет/Отмена")->add(L"Да/Нет")->add(L"Повторить/Отмена")->add(L"Отмена/Повторить/Продолжить");
    resize(NULL,0);

    bar.step()->resize(100,100)->move(0,0)->show();

    return 0;
}

void command(LPARAM &widgets){
    if(smessage.isMe(widgets)){
        int icon_id=icon.getIndex();
        if(icon_id==CB_ERR){
            window->message(L"Не выбран тип значка",L"Упс!",ERROR_ICO);
            return;
        }icon_id*=0x10;

        int button_id= button.getIndex();
        if(button_id==CB_ERR){
            window->message(L"Не выбраны кнопки ответа",L"Упс!",ERROR_ICO);
            return;
        }
        MessageBoxW(NULL,text.getText(),caption.getText(),icon_id|button_id);
    }
}

void resize(RECT* newpos,int state){
    UNUSED(newpos);
    int q= window->height()-40;q/=6;
    int width=window->width();

    label.move(0,0)->resize(width,q);
    caption.move(0,q)->resize(width,q);
    text.move(0,q*2)->resize(width,q);
    icon.move(0,q*3)->resize(width-40,q+50);
    button.move(0,q*4)->resize(width-40,q+100);
    smessage.move(0,q*5)->resize(width,q);
    if(state==SIZE_MINIMIZED)window->show();
}
