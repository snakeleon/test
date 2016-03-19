/************************************************************/
/*　　chess.c 五子棋之人机对战　　　　　　　　　　　　　　　*/
/*　　2004.11  ver 1.0　　　　　　　　　　　　　　　　　　　*/
/*    Creater By Rock.yu                                    */
/************************************************************/

/*************************************************************/
/********　　　　　　　函数库调用模块　　　　　　　　********/

#include <conio.h>
#include <libbcc.h>        /*     图形函数库 　  */
#include <dos.h>          /*  DOS 功能函数库    */
#include <string.h>      /*  字符处理函数库    */
#include <stdlib.h>     /*  数据类型转换函数  */
#include <stdio.h>     /*　输入输出函数库　　*/
#include <windows.h>



struct Chess_unit
{
    int x;
    int y;
    int flag;
};
/**************************************************************/
/********　　　　　　　全局变量声明　　　　　　　　　　********/

void far *image,*next_image,*image_null;     /* image -- 棋子过后的图象， next_image -- 棋子要下的位置  image_null -- 最初保存的空图像只有棋盘 */
int Mg_top=70,limit_flag=0;                   /* Mg_top  Message 区域的当前输出位置 */
int Coording[16][16]= {};
FILE *fp_out=NULL;      /* 保存下子的位置及对象的文件指针 在INIT()中打开 在 END() 中关闭该文件 */

/**************************************************************/
/********　　　　　　　自定义函数声明　　　　　　　　　********/

void Init(void);                      /*　界面初始化函数　*/
int *Think(int x,int y);               /* AI 部分        */
void Computer(int column,int row);    /*　电脑走棋函数　　*/
void Message(char *string);           /*　　弹出式消息框　　*/
int  Getkey(void);                    /*　取得键盘 AICSS 码　*/
void UP(int column,int row);          /*　棋子向上移动　　*/
void DOWN(int column,int row);        /*　棋子向下移动　　*/
void LIFT(int column,int row);        /*　棋子向左移动　　*/
void RIGHT(int column,int row);       /*　棋子向右移动　　　*/
void Trace(int flag,int data);        /*　棋子轨迹跟踪　*/
void Move_chessman(void);             /*　走棋大循环　　*/
int  SAVE(int column,int row,int flag);/*　保存棋局　　*/
int  Limit(int flag,int data);        /*　棋子位置极限分析　*/
int  Victory(int LandForm[8][6]);  /* 判断是否获胜*/
void END();                           /*　结束游戏　*/


/*****************************************/
/*  界面初始化函数                       */

void Init(void)
{
    int Driver=VGA,Mode=VGAHI,count,size=0;
    char letter[16]= {"ABCDEFGHIJKLMNO"};
    fp_out=fopen("d:/database.txt","a+");    /*　以追加的方式打开文件　*/
    if(fp_out==NULL)
    {
        printf("Load File Error!");
        //getch();
        exit(0);
    }
    initgraph(&Driver,&Mode,"");
    setcolor(RED);
    line(0,0,640,0);                  /* 画大的边框*/
    line(0,0,0,480);
    line(0,480,640,480);
    line(640,0,640,480);
    setcolor(7);
    line(5,5,635,5);                   /* 画小的边框*/
    line(5,5,5,480);
    line(5,479,635,479);
    line(635,5,635,480);
    line(490,5,490,480);
    line(490,395,635,395);
    line(563,395,563,480);
    line(490,65,635,65);

    setfillstyle(SOLID_FILL,DARKGRAY);  /* 设置底色为青灰色*/
    setcolor(CYAN);
    bar(20,20,470,470);
    rectangle(19,19,471,471);           /* 棋盘边框*/
    setcolor(CYAN);
    for(count=0; count<17; count++)     /* 画棋盘*/
    {
        line(count*30+5,0+20,count*30+5,470);
        line(0+20,count*30+5,470,count*30+5);
    }


    settextstyle(SMALL_FONT,0,6);    /* 初始化棋盘 1~15 的行号 既 Y 坐标 */
    setcolor(CYAN);
    outtextxy(10,27,"1");
    outtextxy(8,57,"2");
    outtextxy(8,87,"3");
    outtextxy(8,117,"4");
    outtextxy(8,147,"5");
    outtextxy(8,177,"6");
    outtextxy(8,207,"7");
    outtextxy(8,237,"8");
    outtextxy(8,267,"9");
    settextstyle(SMALL_FONT,0,4);    /* 因以下数字占2个位置，所以用4号字 ( 8*10 ) */
    outtextxy(8,300,"10");
    outtextxy(8,330,"11");
    outtextxy(8,360,"12");
    outtextxy(8,390,"13");
    outtextxy(8,420,"14");
    outtextxy(8,450,"15");

    settextstyle(SMALL_FONT,0,6);    /* 初始化棋盘 A~O 的列号 既 X 坐标 */
    outtextxy(32,4,"A");
    outtextxy(62,4,"B");
    outtextxy(92,4,"C");
    outtextxy(122,4,"D");
    outtextxy(152,4,"E");
    outtextxy(182,4,"F");
    outtextxy(212,4,"G");
    outtextxy(242,4,"H");
    outtextxy(272,4,"I");
    outtextxy(302,4,"J");
    outtextxy(332,4,"K");
    outtextxy(362,4,"L");
    outtextxy(392,4,"M");
    outtextxy(422,4,"N");
    outtextxy(452,4,"O");

    settextstyle(SMALL_FONT,0,4);       /* 输出版本信息*/
    setcolor(LIGHTGREEN);
    outtextxy(500,10,"Welcome User System");
    outtextxy(500,25,"Copyright Rock.yu");

    size=imagesize(20,20,50,50);          /* 测试要保存图象的大小 */

    /*  按照 SIZE+100 的大小分配内存 如果不使用次函数就会出现内存不足的错误信息 */
    image=(void far *)malloc(size+100);
    next_image=(void far *)malloc(size+100);

    /* Init Trace() 初始化轨迹显示函数 */
    settextstyle(SMALL_FONT,0,5);
    setcolor(BROWN);

    outtextxy(500,400,"Chesser");
    outtextxy(510,420,"X:");
    outtextxy(510,440,"Y:");

    outtextxy(570,400,"Computer");
    outtextxy(580,420,"X:");
    outtextxy(580,440,"Y:");

    setcolor(LIGHTBLUE);
    outtextxy(530,420,"A");
    outtextxy(530,440,"1");

    outtextxy(600,420,"A");
    outtextxy(600,440,"1");

    return  ;
}

/***********************************************/

int SAVE(int column,int row,int flag)     /* 保存当前的棋子坐标及颜色 1--电脑  2--人*/
{
    int x,y;
    x=64+(column-5)/30;
    y=(row-5)/30;
    fprintf(fp_out," -> %c,%d,%d\n",x,y,flag);
    return 1;
}


/****************************************************/
/* 判断是否赢棋的函数   待完成 */
/* 具体的方法是 ： 分黑白两次完成， 遇到棋子加 1  ，遇到空格清0 ，直到出现 5则为胜 */


int Victory(int LandForm[8][6])
{
    int x,y,count1=0,count2=0,Temp[4][9]= {};
    for(x=1; x<5; x++)          /* 本循环用来把传来的8个方向的数组转化为4个方向*/
        for(y=0; y<4; y++)
        {
            Temp[x-1][y]=LandForm[x*2-2][5-y];
            Temp[x-1][3+y]=LandForm[x*2-1][y];
        }



    for(x=0; x<4; x++)
    {
        for(y=0; y<9; y++)
        {
            /*printf(" %d ",Temp[x][y]);*/
        }
        printf("\n");
    }

    /*for(x=0;x<4;x++)
      for(y=0;y<9;y++)
      {
      if(Temp[x][y]==1&&(Temp[][])) */
    return 1;

}

/****************************************************/
/*  本函数用来完成游戏的 AI  部分， 为游戏的核心部分*/
/*  以人下子的地方为中心，扫描八个方位5步之内的棋型
    并将结果存入  LandForm[][] 数组。                   */

int *Think(int x,int y)
{
    int Coor[2]= {},LandForm[8][6]= {},m=0,n=0,t=0;
    struct Chess_unit *TK_unit,Current;

    Current.x=x;                             /* 将当前的棋子坐标存到 current 结构体中 */
    Current.y=y;

    for(m=y; m>y-5; m--)                     /* 向上扫描 */
    {
        n++;
        if(m<0)  break;
        LandForm[0][n]=Coording[x][m];
        fprintf(fp_out," %d:%d=%d ",x,m,LandForm[0][n]);
    }
    fprintf(fp_out,"\n");
    n=0;
    for(m=y; m<y+5; m++)                    /* 向下扫描 */
    {
        n++;
        if(m>15) break;
        LandForm[1][n]=Coording[x][m];
        fprintf(fp_out," %d:%d=%d ",x,m,LandForm[1][n]);
    }
    fprintf(fp_out,"\n");
    n=0;
    for(m=x; m>x-5; m--)                    /* 向左扫描 */
    {
        n++;
        if(m<0) break;
        LandForm[2][n]=Coording[m][y];
        fprintf(fp_out," %d:%d=%d ",m,y,LandForm[2][n]);
    }
    fprintf(fp_out,"\n");
    n=0;
    for(m=x; m<x+5; m++)                   /* 向右扫描 */
    {
        n++;
        if(m>15)  break;
        LandForm[3][n]=Coording[m][y];
        fprintf(fp_out," %d:%d=%d ",m,y,LandForm[3][n]);
    }
    fprintf(fp_out,"\n");
    n=0;
    for(m=x,t=y; m>x-5; m--,t--)           /* 向左上扫描 */
    {
        n++;
        if(m<0||t<0) break;
        LandForm[4][n]=Coording[m][t];
        fprintf(fp_out," %d:%d=%d ",m,t,LandForm[4][n]);
    }
    fprintf(fp_out,"\n");
    n=0;
    for(m=x,t=y; m<x+5; m++,t++)           /* 向右下扫描 */
    {
        n++;
        if(m>15||t>15)  break;
        LandForm[5][n]=Coording[m][t];
        fprintf(fp_out," %d:%d=%d ",m,t,LandForm[5][n]);
    }
    fprintf(fp_out,"\n");
    n=0;
    for(m=x,t=y; m<x+5; m++,t--)           /* 向右上扫描 */
    {
        n++;
        if(m>15||t<0)  break;
        LandForm[6][n]=Coording[m][t];
        fprintf(fp_out," %d:%d=%d ",m,t,LandForm[6][n]);
    }
    fprintf(fp_out,"\n");
    n=0;
    for(m=x,t=y; m>x-5; m--,t++)           /* 向左下扫描 */
    {
        n++;
        if(m<0||t>15)  break;
        LandForm[7][n]=Coording[m][t];
        fprintf(fp_out," %d:%d=%d ",m,t,LandForm[7][n]);
    }
    fprintf(fp_out,"\n");

    Victory(LandForm);   /* 调用本函数判断是否赢棋 */



    Coor[0]=(1+rand()%14)*30+5;
    Coor[1]=(1+rand()%14)*30+5;
    return Coor;
}

/***********************************************/

void Computer(int column,int row)
{
    int flag=2,C_row,C_col,*Coorp;
    int x,y/*,color=WHITE*/;
    SAVE(column,row,2);  /* 把当前玩家的棋子坐标和下棋方存到文件  1--电脑  2--人 */
    C_col=(column-5)/30;
    C_row=(row-5)/30;
    Coording[C_col][C_row]=flag;

    Coorp=Think(C_col,C_row);    /* 分析棋局的函数   用数组传回 x y 坐标*/

    flag=1;
    /* x=rand()%5;
       y=rand()%5; */

    x=*Coorp;
    y=*(Coorp+1);

    /*SAVE(column+x*30,row+y*30,1);*/

    SAVE(x,y,1);

    /*C_col=(column+x*30-5)/30;
      C_row=(row+y*30-5)/30; */


    C_col=(x-5)/30;
    C_row=(y-5)/30;
    Coording[C_col][C_row]=flag;
    /*color=getcolor();*/
    setfillstyle(SOLID_FILL,BLACK);
    setcolor(BLACK);

    /*sector(column+x*30,row+y*30,0,360,15,15);*/

    sector(x,y,0,360,15,15);
    setcolor(WHITE);
    return ;
}

/***********************************************/
/*    清除 MESSAGE 的内容 MESSAGE 的坐标为 {(490,65) (635,395)} */

void Clear_Mg(void)
{
    int color;
    Mg_top=70;
    color=getcolor();
    setcolor(BLACK);
    setfillstyle(SOLID_FILL,BLACK);
    bar(492,67,633,393);
    setcolor(color);
    setfillstyle(SOLID_FILL,WHITE);
}
/***********************************************/
/*  信息显示函数 坐标：(490,65)  (635,395)     */

void Message(char *string)
{
    setcolor(LIGHTGREEN);
    settextstyle(SMALL_FONT,0,4);
    outtextxy(500,Mg_top,string);
    Mg_top+=15;                   /* 每行信息显示完后行数加 15 Mg_top 是当前的信息坐标 */
    if(Mg_top>380)

        Clear_Mg();

    return ;
}

/***********************************************/


/***********************************************/
/*      得到当前的按键 ASCII 码                   */

int Getkey(void)
{
    int key=0;
    while(kbhit())
    {
        key=getch();
    }
    return key;
}

/*************************************************/

void UP(int column,int row)
{
    int x=0,y=0;
    x=column;
    y=row;
    putimage(x-15,y+15,image,0);
    getimage(x-15,y-15,x+15,y+15,next_image);
    sector(x,y,0,360,15,15);
    image=next_image;
    return ;

}

/*************************************************/

void DOWN(int column,int row)
{
    int x=0,y=0;
    x=column;
    y=row;
    if(y==455&&limit_flag==1)
    {
        putimage(x-15,35-15,image,0);
        sector(x,35,0,360,15,15);
        return;
    }

    if(y==35&&limit_flag==0)
        limit_flag=1;
    putimage(x-15,y-45,image,0);
    getimage(x-15,y-15,x+15,y+15,next_image);
    sector(x,y,0,360,15,15);
    image=next_image;
    return ;

}

/*************************************************/

void LIFT(int column,int row)
{
    int x=0,y=0;
    x=column;
    y=row;
    if(column==35&&limit_flag==0)
    {
        limit_flag=1;
    }
    if(column==35&&limit_flag==1)
    {
        putimage(x-15,y+15,image_null,0);
        sector(x,y,0,360,15,15);

        limit_flag=0;
        return;
    }
    putimage(x+15,y-15,image,0);
    getimage(x-15,y-15,x+15,y+15,next_image);
    sector(x,y,0,360,15,15);
    image=next_image;
    return ;
}

/*************************************************/

void RIGHT(int column,int row)
{
    int x=0,y=0;
    x=column;
    y=row;
    if(column==455&&limit_flag==0)
    {
        limit_flag=1;
    }
    if(column==455&&limit_flag==1)
    {
        putimage(x-15,y+15,image_null,0);
        sector(x,y,0,360,15,15);

        limit_flag=0;
        return;
    }
    putimage(x-45,y-15,image,0);
    getimage(x-15,y-15,x+15,y+15,next_image);
    sector(x,y,0,360,15,15);
    image=next_image;
    return ;
}

/*************************************************/
/*     本函数检查棋子坐标是否超出棋盘            */
/* 函数中使用了 char * itoa(int value,char *string,int radix) 函数 */
/* 把 int 数据转化为字符串 value -- 要转化的数据   */
/*                         *string -- 转化后的串的存放数组名  */
/*                          radix -- 按哪个进制转化 2=二进制 10=十进制 */


int Limit(int flag,int data)
{
    int updata=data;
    if(flag==72)
    {
        if(data>35)
            updata-=30;

        else
            updata=35;
    }

    if(flag==80)
    {
        if(data<455)
            updata+=30;
        else
            updata=455;
    }
    if(flag==75)
    {
        if(data>35)
            updata-=30;

        else
            updata=35;
    }

    if(flag==77)
    {
        if(data<455)
            updata+=30;
        else
            updata=455;
    }

    return updata;

}

/*************************************************/
/*   本函数显示当前下棋者棋子的坐标              */

void Trace(int flag,int data)
{
    char *str=0;
    int color=0;
    data=(data-5)/30;
    if(flag==72||flag==80)
    {
        setcolor(BLACK);
        setfillstyle(SOLID_FILL,BLACK);
        bar(530,440,555,452);
        color=getcolor();
        setcolor(LIGHTBLUE);
        itoa(data,str,10);
        outtextxy(530,440,str);
        Message(str);
        setcolor(color);
    }
    if(flag==75||flag==77)
    {
        setcolor(BLACK);
        setfillstyle(SOLID_FILL,BLACK);
        bar(530,420,555,432);
        color=getcolor();
        setcolor(LIGHTBLUE);
        sprintf(str,"%c",data+64);
        /*itoa(data,str,10);*/
        outtextxy(530,420,str);
        setcolor(color);
    }

    setcolor(WHITE);                     /* 恢复白棋操作颜色 （人） */
    setfillstyle(SOLID_FILL,WHITE);
    return ;

}

/*************************************************/
/*   本函数用来完成下棋者的棋子移动操作          */

void Move_chessman(void)
{
    int row=35,column=35,count=0,key=0,flag=1;
    void far *image1=0,*image2=0;
    setcolor(WHITE);
    setfillstyle(SOLID_FILL,WHITE);
    sector(column,row,0,360,15,15);
    getimage(50,50,80,80,image);
    image_null=image;

    while(key!=27)
    {
        key=Getkey();
        switch(key)
        {
            case 72 :
                row=Limit(72,row);
                UP(column,row);
                Trace(72,row);
                break;
            case 80 :
                row=Limit(80,row);
                DOWN(column,row);
                Trace(80,row);
                break;
            case 75 :
                column=Limit(75,column);
                LIFT(column,row);
                Trace(75,column);
                break;
            case 77 :
                column=Limit(77,column);
                RIGHT(column,row);
                Trace(77,column);
                break;
            case 13 :
                Computer(column,row);
                Move_chessman();
                break;
            case 27 :
                END();
                break;
            default :
                break;
        }


    }


}
/************************************************/

void END()
{
    //    struct date *cur_datep;
    //    struct time *timep;
    //    getdate(cur_datep);
    //    gettime(timep);
    SYSTEMTIME time;
    GetSystemTime(&time);
    closegraph();
    printf("Game Over!");
    fprintf(fp_out,"\n******* End Report ******\n");
    fprintf(fp_out,"** %d.%d.%d&%d:%d:%d **\n", time.wYear, time.wMonth,
            time.wDay, time.wHour,
            time.wMinute, time.wSecond);
    printf("%d.%d\n",time.wMonth, time.wDay);
    fclose(fp_out);
    //getch();
    exit(0);
}
/************************************************/
/*                 主函数部分                   */

int main()
{
    Init();
    Move_chessman();
    END();
    return 0;
}

