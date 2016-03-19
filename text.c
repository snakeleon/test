/************************************************************/
/*����chess.c ������֮�˻���ս������������������������������*/
/*����2004.11  ver 1.0��������������������������������������*/
/*    Creater By Rock.yu                                    */
/************************************************************/

/*************************************************************/
/********�����������������������ģ�顡��������������********/

#include <conio.h>
#include <libbcc.h>        /*     ͼ�κ����� ��  */
#include <dos.h>          /*  DOS ���ܺ�����    */
#include <string.h>      /*  �ַ���������    */
#include <stdlib.h>     /*  ��������ת������  */
#include <stdio.h>     /*��������������⡡��*/
#include <windows.h>



struct Chess_unit
{
    int x;
    int y;
    int flag;
};
/**************************************************************/
/********��������������ȫ�ֱ���������������������������********/

void far *image,*next_image,*image_null;     /* image -- ���ӹ����ͼ�� next_image -- ����Ҫ�µ�λ��  image_null -- �������Ŀ�ͼ��ֻ������ */
int Mg_top=70,limit_flag=0;                   /* Mg_top  Message ����ĵ�ǰ���λ�� */
int Coording[16][16]= {};
FILE *fp_out=NULL;      /* �������ӵ�λ�ü�������ļ�ָ�� ��INIT()�д� �� END() �йرո��ļ� */

/**************************************************************/
/********���������������Զ��庯������������������������********/

void Init(void);                      /*�������ʼ��������*/
int *Think(int x,int y);               /* AI ����        */
void Computer(int column,int row);    /*���������庯������*/
void Message(char *string);           /*��������ʽ��Ϣ�򡡡�*/
int  Getkey(void);                    /*��ȡ�ü��� AICSS �롡*/
void UP(int column,int row);          /*�����������ƶ�����*/
void DOWN(int column,int row);        /*�����������ƶ�����*/
void LIFT(int column,int row);        /*�����������ƶ�����*/
void RIGHT(int column,int row);       /*�����������ƶ�������*/
void Trace(int flag,int data);        /*�����ӹ켣���١�*/
void Move_chessman(void);             /*�������ѭ������*/
int  SAVE(int column,int row,int flag);/*��������֡���*/
int  Limit(int flag,int data);        /*������λ�ü��޷�����*/
int  Victory(int LandForm[8][6]);  /* �ж��Ƿ��ʤ*/
void END();                           /*��������Ϸ��*/


/*****************************************/
/*  �����ʼ������                       */

void Init(void)
{
    int Driver=VGA,Mode=VGAHI,count,size=0;
    char letter[16]= {"ABCDEFGHIJKLMNO"};
    fp_out=fopen("d:/database.txt","a+");    /*����׷�ӵķ�ʽ���ļ���*/
    if(fp_out==NULL)
    {
        printf("Load File Error!");
        //getch();
        exit(0);
    }
    initgraph(&Driver,&Mode,"");
    setcolor(RED);
    line(0,0,640,0);                  /* ����ı߿�*/
    line(0,0,0,480);
    line(0,480,640,480);
    line(640,0,640,480);
    setcolor(7);
    line(5,5,635,5);                   /* ��С�ı߿�*/
    line(5,5,5,480);
    line(5,479,635,479);
    line(635,5,635,480);
    line(490,5,490,480);
    line(490,395,635,395);
    line(563,395,563,480);
    line(490,65,635,65);

    setfillstyle(SOLID_FILL,DARKGRAY);  /* ���õ�ɫΪ���ɫ*/
    setcolor(CYAN);
    bar(20,20,470,470);
    rectangle(19,19,471,471);           /* ���̱߿�*/
    setcolor(CYAN);
    for(count=0; count<17; count++)     /* ������*/
    {
        line(count*30+5,0+20,count*30+5,470);
        line(0+20,count*30+5,470,count*30+5);
    }


    settextstyle(SMALL_FONT,0,6);    /* ��ʼ������ 1~15 ���к� �� Y ���� */
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
    settextstyle(SMALL_FONT,0,4);    /* ����������ռ2��λ�ã�������4���� ( 8*10 ) */
    outtextxy(8,300,"10");
    outtextxy(8,330,"11");
    outtextxy(8,360,"12");
    outtextxy(8,390,"13");
    outtextxy(8,420,"14");
    outtextxy(8,450,"15");

    settextstyle(SMALL_FONT,0,6);    /* ��ʼ������ A~O ���к� �� X ���� */
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

    settextstyle(SMALL_FONT,0,4);       /* ����汾��Ϣ*/
    setcolor(LIGHTGREEN);
    outtextxy(500,10,"Welcome User System");
    outtextxy(500,25,"Copyright Rock.yu");

    size=imagesize(20,20,50,50);          /* ����Ҫ����ͼ��Ĵ�С */

    /*  ���� SIZE+100 �Ĵ�С�����ڴ� �����ʹ�ôκ����ͻ�����ڴ治��Ĵ�����Ϣ */
    image=(void far *)malloc(size+100);
    next_image=(void far *)malloc(size+100);

    /* Init Trace() ��ʼ���켣��ʾ���� */
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

int SAVE(int column,int row,int flag)     /* ���浱ǰ���������꼰��ɫ 1--����  2--��*/
{
    int x,y;
    x=64+(column-5)/30;
    y=(row-5)/30;
    fprintf(fp_out," -> %c,%d,%d\n",x,y,flag);
    return 1;
}


/****************************************************/
/* �ж��Ƿ�Ӯ��ĺ���   ����� */
/* ����ķ����� �� �ֺڰ�������ɣ� �������Ӽ� 1  �������ո���0 ��ֱ������ 5��Ϊʤ */


int Victory(int LandForm[8][6])
{
    int x,y,count1=0,count2=0,Temp[4][9]= {};
    for(x=1; x<5; x++)          /* ��ѭ�������Ѵ�����8�����������ת��Ϊ4������*/
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
/*  ���������������Ϸ�� AI  ���֣� Ϊ��Ϸ�ĺ��Ĳ���*/
/*  �������ӵĵط�Ϊ���ģ�ɨ��˸���λ5��֮�ڵ�����
    �����������  LandForm[][] ���顣                   */

int *Think(int x,int y)
{
    int Coor[2]= {},LandForm[8][6]= {},m=0,n=0,t=0;
    struct Chess_unit *TK_unit,Current;

    Current.x=x;                             /* ����ǰ����������浽 current �ṹ���� */
    Current.y=y;

    for(m=y; m>y-5; m--)                     /* ����ɨ�� */
    {
        n++;
        if(m<0)  break;
        LandForm[0][n]=Coording[x][m];
        fprintf(fp_out," %d:%d=%d ",x,m,LandForm[0][n]);
    }
    fprintf(fp_out,"\n");
    n=0;
    for(m=y; m<y+5; m++)                    /* ����ɨ�� */
    {
        n++;
        if(m>15) break;
        LandForm[1][n]=Coording[x][m];
        fprintf(fp_out," %d:%d=%d ",x,m,LandForm[1][n]);
    }
    fprintf(fp_out,"\n");
    n=0;
    for(m=x; m>x-5; m--)                    /* ����ɨ�� */
    {
        n++;
        if(m<0) break;
        LandForm[2][n]=Coording[m][y];
        fprintf(fp_out," %d:%d=%d ",m,y,LandForm[2][n]);
    }
    fprintf(fp_out,"\n");
    n=0;
    for(m=x; m<x+5; m++)                   /* ����ɨ�� */
    {
        n++;
        if(m>15)  break;
        LandForm[3][n]=Coording[m][y];
        fprintf(fp_out," %d:%d=%d ",m,y,LandForm[3][n]);
    }
    fprintf(fp_out,"\n");
    n=0;
    for(m=x,t=y; m>x-5; m--,t--)           /* ������ɨ�� */
    {
        n++;
        if(m<0||t<0) break;
        LandForm[4][n]=Coording[m][t];
        fprintf(fp_out," %d:%d=%d ",m,t,LandForm[4][n]);
    }
    fprintf(fp_out,"\n");
    n=0;
    for(m=x,t=y; m<x+5; m++,t++)           /* ������ɨ�� */
    {
        n++;
        if(m>15||t>15)  break;
        LandForm[5][n]=Coording[m][t];
        fprintf(fp_out," %d:%d=%d ",m,t,LandForm[5][n]);
    }
    fprintf(fp_out,"\n");
    n=0;
    for(m=x,t=y; m<x+5; m++,t--)           /* ������ɨ�� */
    {
        n++;
        if(m>15||t<0)  break;
        LandForm[6][n]=Coording[m][t];
        fprintf(fp_out," %d:%d=%d ",m,t,LandForm[6][n]);
    }
    fprintf(fp_out,"\n");
    n=0;
    for(m=x,t=y; m>x-5; m--,t++)           /* ������ɨ�� */
    {
        n++;
        if(m<0||t>15)  break;
        LandForm[7][n]=Coording[m][t];
        fprintf(fp_out," %d:%d=%d ",m,t,LandForm[7][n]);
    }
    fprintf(fp_out,"\n");

    Victory(LandForm);   /* ���ñ������ж��Ƿ�Ӯ�� */



    Coor[0]=(1+rand()%14)*30+5;
    Coor[1]=(1+rand()%14)*30+5;
    return Coor;
}

/***********************************************/

void Computer(int column,int row)
{
    int flag=2,C_row,C_col,*Coorp;
    int x,y/*,color=WHITE*/;
    SAVE(column,row,2);  /* �ѵ�ǰ��ҵ�������������巽�浽�ļ�  1--����  2--�� */
    C_col=(column-5)/30;
    C_row=(row-5)/30;
    Coording[C_col][C_row]=flag;

    Coorp=Think(C_col,C_row);    /* ������ֵĺ���   �����鴫�� x y ����*/

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
/*    ��� MESSAGE ������ MESSAGE ������Ϊ {(490,65) (635,395)} */

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
/*  ��Ϣ��ʾ���� ���꣺(490,65)  (635,395)     */

void Message(char *string)
{
    setcolor(LIGHTGREEN);
    settextstyle(SMALL_FONT,0,4);
    outtextxy(500,Mg_top,string);
    Mg_top+=15;                   /* ÿ����Ϣ��ʾ��������� 15 Mg_top �ǵ�ǰ����Ϣ���� */
    if(Mg_top>380)

        Clear_Mg();

    return ;
}

/***********************************************/


/***********************************************/
/*      �õ���ǰ�İ��� ASCII ��                   */

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
/*     ������������������Ƿ񳬳�����            */
/* ������ʹ���� char * itoa(int value,char *string,int radix) ���� */
/* �� int ����ת��Ϊ�ַ��� value -- Ҫת��������   */
/*                         *string -- ת����Ĵ��Ĵ��������  */
/*                          radix -- ���ĸ�����ת�� 2=������ 10=ʮ���� */


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
/*   ��������ʾ��ǰ���������ӵ�����              */

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

    setcolor(WHITE);                     /* �ָ����������ɫ ���ˣ� */
    setfillstyle(SOLID_FILL,WHITE);
    return ;

}

/*************************************************/
/*   ������������������ߵ������ƶ�����          */

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
/*                 ����������                   */

int main()
{
    Init();
    Move_chessman();
    END();
    return 0;
}

