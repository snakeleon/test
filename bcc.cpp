#include<stdio.h>
#include<dos.h>
#include<conio.h>
#include<math.h>
#include<libbcc.h>
#include<windows.h>
#include<unistd.h>
#define PI 3.1415926

int main()
{
    int X=300,Y=250,R=100,RR=130;
    int X_HOUR,X_MINUTE,X_SECOND;
    int Y_HOUR,Y_MINUTE,Y_SECOND;
    int X_DRAW=0,Y_DRAW=0,R_DRAW=120;
    int NUM=0;
    SYSTEMTIME T;
    int gdriver=DETECTX,gmode=0;
    //detectgraph(gdriver,gmode);
    initgraph(&gdriver,&gmode,"  ");
    setlinestyle(0,1,3);
    setcolor(LIGHTGRAY);
    circle(X,Y,RR);
    setlinestyle(0,1,1);
    for(NUM=0;NUM<12;NUM++)
    {
        setcolor(11);
        X_DRAW=X+R_DRAW*cos(NUM*2*PI/12);
        Y_DRAW=Y+R_DRAW*sin(NUM*2*PI/12);
        circle(X_DRAW,Y_DRAW,5);
        setfillstyle(1,11);
        if((NUM%3)==0)
            floodfill(X_DRAW,Y_DRAW,11);
    }
    while(!kbhit())
    {
        GetLocalTime(&T);
        X_HOUR=X+(R/2)*cos(T.wHour*2*PI/12+T.wMinute*2*PI/(60*12)-PI/2);
        X_MINUTE=X+R*cos(T.wMinute*2*PI/60-PI/2)*3/4;
        X_SECOND=X+R*cos(T.wSecond*2*PI/60-PI/2);
        Y_HOUR=X+(R/2)*sin(T.wHour*2*PI/12+T.wMinute*2*PI/(60*12)-PI/2);
        Y_MINUTE=Y+R*sin(T.wMinute*2*PI/60-PI/2)*3/4;
        Y_SECOND=Y+R*sin(T.wSecond*2*PI/60-PI/2);
        setcolor(YELLOW);
        line(X,Y,X_HOUR,Y_HOUR);
        setcolor(RED);
        line(X,Y,X_MINUTE,Y_MINUTE);
        setcolor(BLUE);
        line(X,Y,X_SECOND,Y_SECOND);
        setcolor(BLACK);
        Sleep(1000);
        line(X,Y,X_HOUR,Y_HOUR);
        line(X,Y,X_MINUTE,Y_MINUTE);
        line(X,Y,X_SECOND,Y_SECOND);
    }
    getch();
    closegraph();
    return 0;
}
