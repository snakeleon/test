#include <stdio.h>
#include <libbcc.h>
#include <conio.h>
#include <math.h>
#include <windows.h>

#define PI 3.1415926
#define X(a,b,c) x=a*cos(b*c*pi/180-pi/2)+300
#define Y(a,b,c) y=a*sin(b*c*pi/180-pi/2)+240
#define d(a,b,c) X(a,b,c);Y(a,b,c);line(300,240,x,y)


void DrawHand(int hour, int minute, int second)
{
    double a_hour, a_min, a_sec;// ʱ���֡�����Ļ���ֵ
    int x_hour, y_hour, x_min, y_min, x_sec, y_sec;// ʱ���֡������ĩ��λ��
    // ����ʱ���֡�����Ļ���ֵ
    a_sec = second * 2 * PI / 60;
    a_min = minute * 2 * PI / 60 + a_sec / 60;
    a_hour= hour * 2 * PI / 12 + a_min / 12;
    // ����ʱ���֡������ĩ��λ��
    x_sec = 320 + (int)(155 * sin(a_sec));
    y_sec = 240 - (int)(155 * cos(a_sec));
    x_min = 320 + (int)(130 * sin(a_min));
    y_min = 240 - (int)(130 * cos(a_min));
    x_hour= 320 + (int)(100 * sin(a_hour));
    y_hour= 240 - (int)(100 * cos(a_hour));
    // ��ʱ��
    setlinestyle(PS_SOLID, 1, 5);
    setcolor(GREEN);
    line(320, 240, x_hour, y_hour);
    // ������
    setlinestyle(PS_SOLID, 1, 3);
    setcolor(YELLOW);
    line(320, 240, x_min, y_min);
    // ������
    setlinestyle(PS_SOLID, 1, 1);
    setcolor(RED);
    line(320, 240, x_sec, y_sec);

}

void NumClock(int H, int M, int S)
{
    char time[9];
    setwritemode(COPY_PUT);
    settextstyle(installuserfont("luct12.fnt"), HORIZ_DIR, 4);

    sprintf(time, "%.2d:%.2d:%.2d", H, M, S);
    setcolor(15);
    outtextxy((640/2-3*6), 300, time);
    setwritemode(XOR_PUT);

}

void CleanNumClock(int H, int M, int S)
{
    char time[9];
    setwritemode(COPY_PUT);
    settextstyle(installuserfont("luct12.fnt"), HORIZ_DIR, 1);
    sprintf(time, "%.2d:%.2d:%.2d", H, M, S);
    setcolor(0);
    outtextxy((640/2-3*6), 300, time);
    setwritemode(XOR_PUT);

}

void Day(int n_week, int n_day)
{
    char day[7], week[4];
    setwritemode(COPY_PUT);
    settextstyle(installuserfont("ncen15.fnt"), HORIZ_DIR, 2);
    switch(n_week)
    {
        case 0:
            strcpy(week,"SUN");
            break;
        case 1:
            strcpy(week,"MON");
            break;
        case 2:
            strcpy(week,"TUE");
            break;
        case 3:
            strcpy(week,"WED");
            break;
        case 4:
            strcpy(week,"THU");
            break;
        case 5:
            strcpy(week,"FRI");
            break;
        case 6:
            strcpy(week,"SAT");
            break;
    }
    sprintf(day,"%s %3d",week, n_day);
    setcolor(12);
    outtextxy(400, 240-8, day);
    setwritemode(XOR_PUT);
}

void CleanDay(int n_week, int n_day)
{
    char day[7], week[4];
    setwritemode(COPY_PUT);
    settextstyle(installuserfont("ncen15.fnt"), HORIZ_DIR, 2);
    switch(n_week)
    {
        case 0:
            strcpy(week,"SUN");
            break;
        case 1:
            strcpy(week,"MON");
            break;
        case 2:
            strcpy(week,"TUE");
            break;
        case 3:
            strcpy(week,"WED");
            break;
        case 4:
            strcpy(week,"THU");
            break;
        case 5:
            strcpy(week,"FRI");
            break;
        case 6:
            strcpy(week,"SAT");
            break;
    }
    sprintf(day,"%s %3d",week, n_day);
    setcolor(0);
    outtextxy(400, 240-8, day);
    setwritemode(XOR_PUT);
}

void DrawPlate()
{
    // ����һ���򵥵ı���
    int i,l,x1,x2,y1,y2;
    setcolor(RED);
    circle(320, 240, 5);
    setfillstyle(SOLID_FILL, WHITE);
    floodfill(320, 240, RED);
    setlinestyle(SOLID_LINE, 0, 2);

    setcolor(CYAN);
    circle(320, 240, 160);
    circle(320, 240, 163);
    setfillstyle(SOLID_FILL, 5);
    floodfill(320+161,240,CYAN);
    setlinestyle(SOLID_LINE, 0, 1);
    circle(320, 240, 152);
    setfillstyle(SOLID_FILL,1);
    floodfill(320+157, 240, CYAN);

    settextstyle(installuserfont("pc6x8.fnt"), HORIZ_DIR, 0);
    setcolor(LIGHTBLUE);
    outtextxy(640/2-strlen("QUARTZ MOVEMENT")/2*6, 350, "QUARTZ MOVEMENT");

    settextstyle(installuserfont("xm12x20b.fnt"), HORIZ_DIR, 0);
    setcolor(BROWN);
    outtextxy(640/2-strlen("HAMILTON")/2*12, 135, "HAMILTONG");

    //���ӵ��ϵĶ���
    for(i=0; i<60; i++)
    {
        if(i%5==0)
        {
            setcolor(3);
            setlinestyle(SOLID_LINE, 0, 4);
            l=16;
        }
        else
        {
            setcolor(8);
            setlinestyle(SOLID_LINE, 0, 2);
            l=8;
        }
        x1=160*sin(i*6*PI/180)+320;
        y1=160*cos(i*6*PI/180)+240;
        x2=(160-l)*sin(i*6*PI/180)+320;
        y2=(160-l)*cos(i*6*PI/180)+240;
        line(x1,y1,x2,y2);
    }
    //����ʱ�����
    setlinestyle(SOLID_LINE, 0, 1);
    setcolor(LIGHTGREEN);
    line(296,300,350,300);
    lineto(350,314);
    lineto(296,314);
    lineto(296,300);
    //�����������
    setcolor(3);
    line(395,232,448,232);
    lineto(448,246);
    lineto(395,246);
    lineto(395,232);
    line(428,232,428,246);
}

int main()
{
    int driver=WIN32 , gmode=7,errorcode;
    char *path=0;
    SYSTEMTIME ti;// ����������浱ǰʱ��
    set_BGI_mode_whc(&driver, &gmode, 640, 480, 16);
    initgraph(&driver,&gmode,path);// ��ʼ����ͼ����
    errorcode=graphresult();
    if(errorcode != grOk)
    {
        printf(" Graphics System Error: %s\n", grapherrormsg(errorcode) );
        getch();
        exit (1);
    }

    setwritemode(XOR_PUT);// ���� XOR ��ͼģʽ
    DrawPlate();//������

    void *buffer=malloc(imagesize(320-163,240-163,320+163,240+163));
    getimage(320-163,240-163,320+163,240+163,buffer); //�����̱���Ϊͼ��

    // ���Ʊ���
    while(!kbhit()) // ��������˳��ӱ����
    {
        GetLocalTime(&ti);//��ȡ��ʱʱ��

        // ������
        Day(ti.wDayOfWeek, ti.wDay);
        NumClock(ti.wHour,ti.wMinute,ti.wSecond);
        DrawHand(ti.wHour, ti.wMinute, ti.wSecond);

        Sleep(1000);// ��ʱ 1 ��
        putimage(320-163,240-163,buffer,COPY_PUT); //��������ı���ͼ�񸲸ǵ�ǰ����

        /* 		// ������
         * 		CleanDay(ti.wDayOfWeek, ti.wDay); //�ַ���Ϊ�ǵ���������ͼ��ģʽ�²���ʹ��������
         * 		CleanNumClock(ti.wHour,ti.wMinute,ti.wSecond); //��ʹ�ñ���ɫ����
         * 		DrawHand(ti.wHour, ti.wMinute, ti.wSecond);
         */

    }
    closegraph();
    return 0;
}
