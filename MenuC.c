#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <string.h>

char    *menu[]= {" File "," Edit "," Help "},
        *file[]= {" New "," Open... "," Save "," Save As... "," Exit "},
        *edit[]= {" Cut "," Copy "," Paste "," Clear "},
        *help[]= {" Commands... "," About... "};

char    buffer0[7*14*2],buffer1[9*6*2],buffer2[15*4*2], /*存放原始菜单*/
        temp0[14*7*2],temp1[9*6*2],temp2[15*4*2];
int     ISGETTEXT=-1; /*哪个菜单被显示过*/

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

/*---选项Help->About的实现---*/
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

/*---在被选项上盖上黑条---*/
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

/*---操作菜单---*/
void BlackMenu(int x)
{
    int whichmenu; /*哪个菜单被选中*/
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

/*---实现菜单选项的功能---*/
void DealFunction(int whichmenu,int item)
{
    RedrawMenu();
    Recover();
    switch(whichmenu)
    {
    case 0:
        switch(item)
        {
        case 4: /*单击了File->Exit选项*/
            textcolor(WHITE);/*还原为TC原有前景和背景颜色*/
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

/*---画出原始菜单---*/
void DrawInitmenu(int xchars,int rows,int startposition,int whichmenu)
{
    int i,j,subnumber;
    char **submenu;
    clrscr();
    for(i=2; i<2+rows; i++) /*清空菜单占用的区域*/
    {
        gotoxy(startposition,i);
        for(j=0; j<xchars; j++)
            putch(0x20);
    }
    gotoxy(startposition,2);
    putch(0xffda); /*边框左上角*/
    for(i=0; i<xchars-2; i++) /*画上边边框*/
        putch(0xffc4);
    putch(0xffbf); /*边框右上角*/
    gotoxy(startposition,1+rows);
    putch(0xffc0); /*边框左下角*/
    for(i=0; i<xchars-2; i++) /*画下边边框*/
        putch(0xffc4);
    putch(0xffd9); /*边框右下角*/
    for(j=3; j<1+rows; j++) /*画左右边框*/
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

/*---初始界面---*/
void InitScreen()
{
    int i;
    textmode(C80);
    textattr(BLACK+LIGHTGRAY<<4);
    DrawInitmenu(14,7,2,0); /*画File菜单*/
    _conio_gettext(2,2,15,8,buffer0);
    DrawInitmenu(9,6,8,1); /*画Edit菜单*/
    _conio_gettext(8,2,16,7,buffer1);
    DrawInitmenu(15,4,14,2); /*画Help菜单*/
    _conio_gettext(14,2,28,5,buffer2);
    textbackground(BLUE);
    clrscr();
    textattr(BLACK+LIGHTGRAY<<4);
    for(i=0; i<80; i++)
        putch(0x20); /*用空格填白菜单横条*/
    RedrawMenu();
    ShowCursor(0); /*隐藏光标*/
}

/*---还原到初始状态---*/
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

/*---重画菜单---*/
void RedrawMenu()
{
    int i;
    textattr(BLACK+LIGHTGRAY<<4);
    gotoxy(3,1);
    for(i=0; i<3; i++)
        cprintf("%s",menu[i]);
}

/*---显示/隐藏光标---*/
void ShowCursor(int status)
{
    union REGS r;
    if(status==1) /*显示光标*/
        r.h.ch=0x01;
    else /*隐藏光标*/
        r.h.ch=0x20;
    r.h.ah=0x01;
    r.h.cl=0x01;
    int86(0x10,&r,&r);
}

/*---显示菜单---*/
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

/*---用户操作---*/
void UserOperate()
{
    while(1)  /*循环进行鼠标单击事件的捕获*/
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

/*---主函数---*/
int main(void)
{
    InitScreen();
    UserOperate();
    return 0;
}
