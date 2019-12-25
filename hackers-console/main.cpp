#define OnTimer 20
#include <iostream>
#include <conio.h>
#include "../APIfunc.h"

#define ROWS 24
#define COLS 60

char nums[COLS][ROWS];
void print();
bool IsProcessRun(const char * processName);
#define rand01 (rand()%2)
#define randE01 (rand()%6-4)

int paint(){//start function
    loop(COLS,x)loop(ROWS,y)nums[x][y]=-1;
    window= new Window(GetConsoleWindow());
    window->maximize();

    system("color 0A&&start");
    window= new Window(GetForegroundWindow());
    window->resize(screen->width()/2,screen->height()/2)->teleport(0,screen->height()/2,6000);
    return 0;
}

void timer(){//logic function

    loop(COLS,x)if(nums[x][0]<0 && randE01==0)
            nums[x][0]=rand01;

    for(short y=ROWS-1; y>0; y--)
        loop(COLS,x)if(nums[x][y-1]>-1){
                nums[x][y]=rand01;nums[x][y-1]=-1;}

    loop(COLS,x)nums[x][ROWS-1]=-1;
    print();
}

void print(){//print matrix function
    system("cls");
    loop(ROWS,y){
        loop(COLS,x){
            if(nums[x][y]<0){printf(" ");continue;}
            printf("%d",(short)nums[x][y]);
        }
        printf("\n");
    }
}
