//------------------------------------------------------------------------------

#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <dos.h>


#define BEEP 7
#define BACKSPACE 8
#define ESC 27
#define ENTER 13


//==============================================================================
//窗口陰影模式
enum Mode
{
    LEFT,
    RIGHT,
    LLEFT,
    LRIGHT,
};
//______________________________________________________________________________
//窗口線型
enum LineMode
{
    NONE=-1,
    ONE,
    TWO,
};

int Line[2][6]=
{
    {218,191,196,179,192,217},
    {201,187,205,186,200,188}

};

//==============================================================================



char *Main_Menu[]=
{
    "&Open       Ctrl+O",
    "&Save       Ctrl+S",
    "Save &As...       ",
    "&Print...         ",
    "Print S&etup      ",
    "&Window           ",
    "Sea&rch...        ",
    "Opt&ions...       ",
    "Por&ject          ",
    "E&xit       Alt+X ",
};




//______________________________________________________________________________
void TextWindow(int X,int Y,int R,int B,int ShadowMode,int ShadowColor,int LineMode,int LineColor,int BackColor,int TitleColor,char *Title,int TextColor)
{
    //判斷窗口陰影頫uFFFD型及陰影的顔色
    int i=0;
    textbackground(ShadowColor);
    switch (ShadowMode)
    {
        case 0:
            window(X-1,Y+1,R-1,B+1);
            break;
        case 1:
            window(X+1,Y+1,R+1,B+1);
            break;
        case 2:
            window(X-1,Y-1,R-1,B-1);
            break;
        case 3:
            window(X+1,Y-1,R+1,B-1);
            break;
    }
    clrscr();
    window(X,Y,R,B);
    textbackground(BackColor);
    textcolor(LineColor);
    clrscr();

    //------------------------------------------------------------------------------
    //绘制窗口边框
    if (LineMode != -1)
    {
        putch(Line[LineMode][0]);
        for(i=1; i<(R-X); ++i)
            putch(Line[LineMode][2]);
        putch(Line[LineMode][1]);
        gotoxy(1,B-Y+1);
        putch(Line[LineMode][4]);
        for(i=1; i<(R-X); ++i)
            putch(Line[LineMode][2]);
        putch(Line[LineMode][5]);
        for(i=1;i<B-Y;i++)
        {
            gotoxy(1,i+1);
            putch(Line[LineMode][3]);
            gotoxy(R-X+1,i+1);
            putch(Line[LineMode][3]);

        }
    }






    //------------------------------------------------------------------------------
    //判断窗口定义的际题
    if (Title != NULL)
    {
        gotoxy((R-X-strlen(Title))/2,1);
        textcolor(TitleColor);
        cputs(Title);
    }
    //------------------------------------------------------------------------------
    //繪制窗口的用戶有效區域
    window(X+1,Y+1,R-1,B-1);
    textcolor(TextColor);
    clrscr();
}

//______________________________________________________________________________

char *GetPass(char ch,char *Mesg)
{
    static char Buffer[128];
    int i=0;
    char Temp = NULL;
    cprintf (Mesg);
    while ((i<127)&&(Temp!=ENTER))
    {
        Temp = getch();
        if (Temp == ESC)
        {
            Buffer[0] = NULL;
            i = 0;
            putchar('\n');
        }

        else if (Temp == BACKSPACE)
        {
            if (i>0)
            {
                Buffer[--i] = NULL;
                if (ch != NULL)
                {
                    putchar(BACKSPACE);
                    putchar(' ');
                    putchar(BACKSPACE);
                }
            }
            else putchar(BEEP);
        }

        else if (Temp != ENTER)
        {
            Buffer[i++] = Temp;
            if (ch != NULL)	putchar(ch);
        }

    }
    Buffer[i] = NULL;
    return(Buffer);
}

//==============================================================================



//輸出菜單項目
void CoutMenu(int HighColor,int TextColor,char *Menu)
{
    char p=Menu[0];
    int i=0;
    for(i=0; i<strlen(Menu); i++)
    {
        if(p=='&')
        {
            ++p;
            textcolor(HighColor);
            putchar(p);
            textcolor(TextColor);
        }
        p++;
        putchar(p);
    }
}





//繪制菜單
void DisplayMenu(int X,int Y,char *Menu[],int ShadowMode,int ShadowColor,int LineMode,int LineColor,int MenuColor,int TextColor,int HighColor,int Count)
{
    int i=0;
    TextWindow(X,Y,X+strlen(Menu[0])+3,Y+Count+1,ShadowMode,ShadowColor,LineMode,LineColor,MenuColor,NULL,NULL,TextColor);

    for(i=0; i<Count; i++)
    {
        gotoxy(2,i+1);
        CoutMenu(HighColor,TextColor,Menu[i]);
    }

}
//==============================================================================


//繪制按紐
void Button(int X,int Y,char *Title,int ShadowMode,int ShadowColor,int ButtonColor,int TextColor,int MainWindowColor)
{
    int i=0;
    window(X+1,Y,X+strlen(Title)+5,Y+1);
    textbackground(MainWindowColor);
    textcolor(ShadowColor);
    gotoxy(1,1);
    for(i=0; i<(strlen(Title)+4); i++)	putchar(220);
    gotoxy(1,2);
    for(i=0; i<(strlen(Title)+4); i++)	putchar(223);
    window(X,Y,X+strlen(Title)+3,Y);
    textbackground(ButtonColor);
    textcolor(TextColor);
    clrscr();
    gotoxy(3,1);
    cprintf(Title);
}


int main(void)
{
    char *P,Buffer[255];
    textmode(C80);
    clrscr();
    textbackground(7);
    clrscr();
    TextWindow(2,2,77,22,RIGHT,0,TWO,3,10,5,"[ Snake.Leon ]",0);
    DisplayMenu(10,6,Main_Menu,RIGHT,BLACK,ONE,8,5,7,4,10);
    Button(20,21,"Search",LEFT,BLACK,1,8,2);

    //P=GetPass('X',"Please Enter The PassWord:");
    //cprintf("\n\r%s\n\r",P);
    //P=GetPass(NULL,"Plaese Enter The PassWord:");
    //cprintf("\n\r%s\n\r",P);
    getch();
    return 0;
}
//==============================================================================
