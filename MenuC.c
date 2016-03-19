#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <string.h>

char    *menu[]= {" File "," Edit "," Help "},
        *file[]= {" New "," Open... "," Save "," Save As... "," Exit "},
        *edit[]= {" Cut "," Copy "," Paste "," Clear "},
        *help[]= {" Commands... "," About... "};

char    buffer0[7*14*2],buffer1[9*6*2],buffer2[15*4*2], /*���ԭʼ�˵�*/
        temp0[14*7*2],temp1[9*6*2],temp2[15*4*2];
int     ISGETTEXT=-1; /*�ĸ��˵�����ʾ��*/

void About();
void BlackItem(int,int);
void BlackMenu(int);
void DealFunction(int,int);
void DrawInitmenu(int,int,int,int);
void InitScreen();
void Recover();
void RedrawMenu();
void ShowCursor(int);
void ShowMenu(int,int);
void UserOperate();

/*---ѡ��Help->About��ʵ��---*/
void About()
{
    int i,j;
    char aboutbuffer[51*11*2];
    _conio_gettext(15,8,65,18,aboutbuffer);
    textcolor(WHITE);
    gotoxy(15,8);
    for(i=0; i<50; i++)
        putch(0xffdb);
    textcolor(BLACK);
    textbackground(LIGHTGRAY);
    for(i=9; i<18; i++)
    {
        gotoxy(15,i);
        for(j=0; j<50; j++)
            putch(0x20);
        putch(0xffdb);
    }
    gotoxy(16,18);
    for(i=0; i<50; i++)
        putch(0xffdb);
    gotoxy(20,10);
    cprintf("This is only a sample,select the Exit in");
    gotoxy(20,11);
    cprintf("File menu can quit this programme,others ");
    gotoxy(20,12);
    cprintf("selections will call this about dialog.");
    gotoxy(32,14);
    cprintf("Written by dibkn");
    textattr(BLACK+WHITE<<4);
    gotoxy(32,8);
    cprintf("About the sample");
    gotoxy(37,16);
    cprintf("%c OK %c",0x10,0x11);
    while(1)
    {
        union REGS r;
        r.x.ax=0x05;
        r.x.bx=0;
        int86(0x33,&r,&r);
        if(r.x.ax&0xffff)
        {
            int x,y;
            x=r.x.cx/8+1;
            y=r.x.dx/8+1;
            if(x>=37&&x<=42&&y==16)
            {
                puttext(15,8,65,18,aboutbuffer);
                return;
            }
        }
    }
}

/*---�ڱ�ѡ���ϸ��Ϻ���---*/
void BlackItem(int whichmenu,int item)
{
    textcolor(LIGHTGRAY);
    textbackground(BLACK);
    switch(whichmenu)
    {
    case 0:
        gotoxy(3,item+3);
        cprintf("%-12s",file[item]);
        break;
    case 1:
        gotoxy(9,item+3);
        cprintf("%-7s",edit[item]);
        break;
    case 2:
        gotoxy(15,item+3);
        cprintf("%-13s",help[item]);
        break;
    }
}

/*---�����˵�---*/
void BlackMenu(int x)
{
    int whichmenu; /*�ĸ��˵���ѡ��*/
    int menu0len=6,menu1len=6;
    textattr(BLACK+LIGHTGRAY<<4);
    RedrawMenu();
    textcolor(LIGHTGRAY);
    textbackground(BLACK);
    if(x<=8)
    {
        gotoxy(3,1);
        cprintf("%s",menu[0]);
        whichmenu=0;
    }
    else if(x<=14)
    {
        gotoxy(3+menu0len,1);
        cprintf("%s",menu[1]);
        whichmenu=1;
    }
    else
    {
        gotoxy(3+menu0len+menu1len,1);
        cprintf("%s",menu[2]);
        whichmenu=2;
    }
    ShowMenu(whichmenu,0);
}

/*---ʵ�ֲ˵�ѡ��Ĺ���---*/
void DealFunction(int whichmenu,int item)
{
    RedrawMenu();
    Recover();
    switch(whichmenu)
    {
    case 0:
        switch(item)
        {
        case 4: /*������File->Exitѡ��*/
            textcolor(WHITE);/*��ԭΪTCԭ��ǰ���ͱ�����ɫ*/
            textbackground(BLACK);
            clrscr();
            exit(0);
        default:
            About();
        }
        break;
    default:
        About();
    }
}

/*---����ԭʼ�˵�---*/
void DrawInitmenu(int xchars,int rows,int startposition,int whichmenu)
{
    int i,j,subnumber;
    char **submenu;
    clrscr();
    for(i=2; i<2+rows; i++) /*��ղ˵�ռ�õ�����*/
    {
        gotoxy(startposition,i);
        for(j=0; j<xchars; j++)
            putch(0x20);
    }
    gotoxy(startposition,2);
    putch(0xffda); /*�߿����Ͻ�*/
    for(i=0; i<xchars-2; i++) /*���ϱ߱߿�*/
        putch(0xffc4);
    putch(0xffbf); /*�߿����Ͻ�*/
    gotoxy(startposition,1+rows);
    putch(0xffc0); /*�߿����½�*/
    for(i=0; i<xchars-2; i++) /*���±߱߿�*/
        putch(0xffc4);
    putch(0xffd9); /*�߿����½�*/
    for(j=3; j<1+rows; j++) /*�����ұ߿�*/
    {
        gotoxy(startposition,j);
        putch(0xffb3);
        gotoxy(startposition+xchars-1,j);
        putch(0xffb3);
    }
    switch(whichmenu)
    {
    case 0:
        submenu=file;
        subnumber=5;
        break;
    case 1:
        submenu=edit;
        subnumber=4;
        break;
    case 2:
        submenu=help;
        subnumber=2;
        break;
    }
    for(i=0; i<subnumber; i++)
    {
        gotoxy(startposition+1,i+3);
        cprintf("%s",submenu[i]);
    }
}

/*---��ʼ����---*/
void InitScreen()
{
    int i;
    textmode(C80);
    textattr(BLACK+LIGHTGRAY<<4);
    DrawInitmenu(14,7,2,0); /*��File�˵�*/
    _conio_gettext(2,2,15,8,buffer0);
    DrawInitmenu(9,6,8,1); /*��Edit�˵�*/
    _conio_gettext(8,2,16,7,buffer1);
    DrawInitmenu(15,4,14,2); /*��Help�˵�*/
    _conio_gettext(14,2,28,5,buffer2);
    textbackground(BLUE);
    clrscr();
    textattr(BLACK+LIGHTGRAY<<4);
    for(i=0; i<80; i++)
        putch(0x20); /*�ÿո���ײ˵�����*/
    RedrawMenu();
    ShowCursor(0); /*���ع��*/
}

/*---��ԭ����ʼ״̬---*/
void Recover()
{
    switch(ISGETTEXT)
    {
    case 0:
        puttext(2,2,15,8,temp0);
        break;
    case 1:
        puttext(8,2,16,7,temp1);
        break;
    case 2:
        puttext(14,2,28,5,temp2);
        break;
    }
    ISGETTEXT=-1;
}

/*---�ػ��˵�---*/
void RedrawMenu()
{
    int i;
    textattr(BLACK+LIGHTGRAY<<4);
    gotoxy(3,1);
    for(i=0; i<3; i++)
        cprintf("%s",menu[i]);
}

/*---��ʾ/���ع��---*/
void ShowCursor(int status)
{
    union REGS r;
    if(status==1) /*��ʾ���*/
        r.h.ch=0x01;
    else /*���ع��*/
        r.h.ch=0x20;
    r.h.ah=0x01;
    r.h.cl=0x01;
    int86(0x10,&r,&r);
}

/*---��ʾ�˵�---*/
void ShowMenu(int whichmenu,int item)
{
    Recover();
    switch(whichmenu)
    {
    case 0:
        _conio_gettext(2,2,15,8,temp0);
        puttext(2,2,15,8,buffer0);
        break;
    case 1:
        _conio_gettext(8,2,16,7,temp1);
        puttext(8,2,16,7,buffer1);
        break;
    case 2:
        _conio_gettext(14,2,28,5,temp2);
        puttext(14,2,28,5,buffer2);
        break;
    }
    ISGETTEXT=whichmenu;
    BlackItem(whichmenu,item);
}

/*---�û�����---*/
void UserOperate()
{
    while(1)  /*ѭ��������굥���¼��Ĳ���*/
    {
        union REGS r;
        r.x.ax=0x05;
        r.x.bx=0;
        int86(0x33,&r,&r);
        if(r.x.ax&0xffff)
        {
            int x,y;
            x=r.x.cx/8+1;
            y=r.x.dx/8+1;
            if(y==1)
            {
                int i;
                if(x>2&&x<=2+18)
                    BlackMenu(x);
            }
            else if(ISGETTEXT!=-1&&y>2)
            {
                int whichmenu,item,status=0;
                switch(ISGETTEXT)
                {
                case 0:
                    if(x>2&&x<15&&y<8)
                    {
                        whichmenu=0;
                        item=y-3;
                        status=1;
                    }
                    break;
                case 1:
                    if(x>8&&x<16&&y<7)
                    {
                        whichmenu=1;
                        item=y-3;
                        status=1;
                    }
                    break;
                case 2:
                    if(x>14&&x<28&&y<5)
                    {
                        whichmenu=2;
                        item=y-3;
                        status=1;
                    }
                    break;
                }
                if(status)
                {
                    ShowMenu(whichmenu,item);
                    DealFunction(whichmenu,item);
                }
                else
                {
                    RedrawMenu();
                    Recover();
                }
            }
        }
    }
}

/*---������---*/
int main(void)
{
    InitScreen();
    UserOperate();
    return 0;
}
