#define OnClick clicked
#include "../APIfunc.h"
#include "../FIGURES.h"

struct point{
    double x,y;
};
point vertex[3];
unsigned short clicks=0;

int paint(){
    window->setTitle(L"Click me!")->resize(500,500)->show();
    return 0;
}

double lineLength(point& begin,point& end){
    return sqrt(pow(begin.x-end.x,2)+pow(begin.y-end.y,2));
}

void clicked(unsigned key,int x, int y){
    if(key!=MK_LBUTTON||clicks==3)restart();
    vertex[clicks].x = x;
    vertex[clicks].y = y;
    clicks++;
    Circle c;
    c.place(x-3,y-3)->color(RANDOM)->resize(6,6)->show();
    if(clicks==2)
        drawLine(window,vertex[0].x,vertex[0].y,
                vertex[1].x,vertex[1].y, RED);
    if(clicks==3){
        window->setTitle(L"Triangle created!");
        drawLine(window,vertex[1].x,vertex[1].y,
                vertex[2].x,vertex[2].y, GREEN);
        drawLine(window,vertex[2].x,vertex[2].y,
                vertex[0].x,vertex[0].y, BLUE);
        double lines[3];
        lines[0]=lineLength(vertex[0],vertex[1]);
        lines[1]=lineLength(vertex[1],vertex[2]);
        lines[2]=lineLength(vertex[2],vertex[0]);
        double p=lines[0]+lines[1]+lines[2];p/=2;
        double s=sqrt(p*(p-lines[0])*(p-lines[1])*(p-lines[2]));
        Box result(window,"Area of triangle:");
        result.setNum(s)->show();
        if(s==0)result.setText("That's not triangle")->show();
    }
}
