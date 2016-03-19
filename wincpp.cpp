#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>


class Windows
{
public:
    int     SetLineMode( int linemode );
    int     SetShadowMode( int shadowmode );
    int     SetLineColor( int linecolor );
    int     SetBackGroundColor( int backgroundcolor );
    int     SetTextColor( int textcolor );
    void    SetTitle( char *title );
    void    CreatWindow( int x,int y,int b,int t);

private:
    void    DrawWindow( );



protected:
    int     X, Y, B, T,
    LineMode, ShadowMode,
    BackGroundColor, LineColor, TextColor;
    char	*Title;

};

enum    eLine   { OFF=-1, ONE, TWO };
enum    eShadow { NONE, TLEFT, TRIGHT, BLEFT, BRIGHT };

static int Line[2][8] =
{
    { 0xDA, 0xBF, 0xC4, 0xB3, 0xC0, 0xD9, 0xC3, 0xB4 },
    { 0xC9, 0xBB, 0xCD, 0xBA, 0xC8, 0xBC, 0xCC, 0xB9 }
};


//=============================================================================
int Windows::SetLineMode(int linemode)
{
    LineMode=linemode;
    return LineMode ;
};

int Windows::SetShadowMode(int shadowmode)
{
    ShadowMode=shadowmode;
    return ShadowMode;
};

int Windows::SetLineColor(int linecolor)
{
    LineColor=linecolor;
    return LineColor;
};

int Windows::SetBackGroundColor(int backgroundcolor)
{
    BackGroundColor=backgroundcolor;
    return BackGroundColor;
};

int Windows::SetTextColor(int textcolor)
{
    TextColor=textcolor;
    return TextColor;
};

void Windows::CreatWindow( int x, int y, int b, int t )
{
    X=x;
    Y=y;
    B=b;
    T=t;
    DrawWindow();
};

void Windows::SetTitle(char *title)
{
    Title=title;
};


void Windows::DrawWindow()
{
    if (ShadowMode!=NONE)
    {
        switch (ShadowMode)
        {
        case    TLEFT:
            window(X-2,Y-1,B-2,T-1);
            break;
        case   TRIGHT:
            window(X+2,Y-1,B+2,T-1);
            break;
        case   BLEFT:
            window(X-2,Y+1,B-2,T+1);
            break;
        case   BRIGHT:
            window(X+2,Y+1,B+2,T+1);
            break;
        default:
            window(X+2,Y+1,B+2,T+1);
            break;
        }
        textbackground(BLACK);
        clrscr();
    }

    window(X,Y,B,T);
    textbackground(BackGroundColor);
    //clrscr();


    if (LineMode!=OFF)
    {
        textcolor(LineColor);
        clrscr();
        putch(Line[LineMode][0]);
        for (    int i=1; i<(B-X);  i++  )       putch(Line[LineMode][2]);
        putch(Line[LineMode][1]);
        //gotoxy(1,2);
        putch(Line[LineMode][3]);
        for (    int j=2; j<=(T-Y); j++  )
        {
            gotoxy(1,j+1);
            putch(Line[LineMode][3]);
            gotoxy((B-X)+1,j);
            putch(Line[LineMode][3]);
        }
        putch(Line[LineMode][4]);
        for (   int i=1;        i<(B-X);        i++     )       putch(Line[LineMode][2]);
        printf("%c",Line[LineMode][5]);
    }

    if (Title!=NULL)
    {
        int lenght=strlen(Title);

        gotoxy((B-X-lenght)/2,1);
        cprintf("%s",Title);
    }
    //textcolor(LineColor);
    //clrscr();

};

class Menus:public Windows
{
public:
    void    SetMenus( int index, char  *item );
    void    CreatMenus( int x, int y, int b, int t );

private:
    void    DrawMenus();

protected:
    int     Index;
    char    *Item;

};

void    Menus::SetMenus( int index, char *item )
{
    Index=index;
    Item=item;
    DrawMenus();
};

void Menus::CreatMenus( int x, int y, int b, int t )
{
    SetLineMode(ONE);
    SetLineColor(14);
    SetTextColor(12);
    SetBackGroundColor(7);
    SetTitle(NULL);
    CreatWindow(x,y,b,t);
}


void    Menus::DrawMenus()
{
    gotoxy(2,1+Index);
    cprintf("%s",Item);
}

//==============================================================================

int main(void)
{
    textmode(C80);
    textbackground(6);
    window(1,1,80,25);
    clrscr();
    Windows      *myWindow;
    myWindow->SetLineMode(ONE);
    myWindow->SetShadowMode(BRIGHT);
    myWindow->SetBackGroundColor(2);
    myWindow->SetLineColor(4);
    myWindow->SetTextColor(6);
    myWindow->SetTitle("Snake.Leon");
    myWindow->CreatWindow(5,3,60,20);
    Menus        *myMenu;
    myMenu->CreatMenus(10,7,25,14);
    myMenu->SetMenus(3,"I Love You!");
    myMenu->SetMenus(5,"I Fuck You!");

    getch();
    return 0;
}



//=============================================================================
