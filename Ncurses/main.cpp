/*==========================================================================
#     FileName :	main.cpp
#  Description :
#       Author :	SiFe
#       E-Mail :	snakeleon@gmail.com
#	  HomePage :	https://github.com/snakeleon
#      Version :	0.0.2
#   LastChange :	2016-07-17 23:27:34
#      History :
==========================================================================*/

#include <ncursesw/ncurses.h>
#include <stdlib.h>


int dayofmonth[13]= {0,31,28,31,30,31,30,31,31,30,31,30,31};

class Date
{
    private:
        int     year=0;
        int     month=0;
        int     day=0;
    public:
        void    SetDate(int yy,int mm,int dd);
        bool    IsLeap(int year);
        bool    IsEndofYear();
        void    ShowDate();
        int     getdays(int year,int month,int dat);
        void    showweek();
        void	printyear();
        void    printmonth();
};

void Date::SetDate(int yy,int mm,int dd)
{
    year=yy;
    month=mm;
    if(year<1)
    {
        printw("Year value error!\n");
        refresh();
        getch();
        endwin();
        exit(1);
    }
    if(month<1||month>12)
    {
        printw("Month value error!\n");
        refresh();
        getch();
        endwin();
        exit(1);
    }
    switch(month)
    {
        case 4:
        case 6:
        case 9:
        case 11:
            {
                if(dd>=1&&dd<=30)   day=dd;
                else
                {
                    printw("Day value error!\n");
                    refresh();
                    getch();
                    endwin();
                    exit(1);
                }
            }
            break;
        case 2:
            {
                if(IsLeap(year))
                {
                    if(dd>=1&&dd<=29)       day=dd;
                    else
                    {
                        printw("Day value error!\n");
                        refresh();
                        getch();
                        endwin();
                        exit(1);
                    }
                }
                else
                {
                    if(dd>=1&&dd<=28)       day=dd;
                    else
                    {
                        printw("Day value error!\n");
                        refresh();
                        getch();
                        endwin();
                        exit(1);
                    }
                }
            }
            break;

        default:
            {
                if(dd>=1&&dd<=31)       day=dd;
                else
                {
                    printw("Day value error!\n");
                    refresh();
                    getch();
                    exit(1);
                }
            }
    }
}

bool Date::IsLeap(int year)
{
    if(year%400==0||(year%100!=0&&year%4==0))       return 1;
    else return 0;
}

void Date::ShowDate()
{
    printw("%d-%d-%d  ",year,month,day);
}

int Date::getdays(int year,int month,int day)
{
    int i,sum=0;
    for(i=1; i<year; i++)
    {
        if(IsLeap(i))       sum+=366;
        else sum+=365;
    }
    if(IsLeap(year))        dayofmonth[2]=29;
    for(i=1; i<month; i++)  sum+=dayofmonth[i];
    sum+=day;
    return sum;
}

void Date::showweek()
{
    int s;
    s=getdays(year,month,day)%7;
    switch(s)
    {
        case 0:
            printw("Sunday\n");
            break;
        case 1:
            printw("Monday\n");
            break;
        case 2:
            printw("Tuesday\n");
            break;
        case 3:
            printw("Wednesday\n");
            break;
        case 4:
            printw("Thursday\n");
            break;
        case 5:
            printw("Friday\n");
            break;
        case 6:
            printw("Saturday\n");
            break;
    }
}

void Date::printyear(void)
{
    WINDOW *monthtab[11];
    for(int y=0,start_y=0,start_x=0; y<12; y++,start_x+=22)
    {
        if(start_x>70)
        {
            start_y+=8;
            start_x=0;
        }
        monthtab[y]=newwin(8,22,start_y,start_x);
        if(monthtab[y]==NULL)
        {
            printw("Create Window Error!");
            exit(1);
        }
        getch();
        start_color();
        init_pair(1,COLOR_RED,COLOR_BLACK);
        wprintw(monthtab[y],"%11d  %d\n",year,y+1);
        wattron(monthtab[y],COLOR_PAIR(1)|A_BOLD);
        wprintw(monthtab[y]," S ");
        wattroff(monthtab[y],COLOR_PAIR(1)|A_BOLD);
        wprintw(monthtab[y]," M  T  W  T  F ");
        wattron(monthtab[y],COLOR_PAIR(1)|A_BOLD);
        wprintw(monthtab[y]," S \n");
        wattroff(monthtab[y],COLOR_PAIR(1)|A_BOLD);
        int s=getdays(year,y+1,1);
        s=s%7;
        for(int m=0; m<s; m++)      wprintw(monthtab[y],"   ");
        if(s==0||s==6)
        {
            wattron(monthtab[y],COLOR_PAIR(1)|A_BOLD);
            wprintw(monthtab[y]," 1 ");
            wattroff(monthtab[y],COLOR_PAIR(1)|A_BOLD);
        }
        else wprintw(monthtab[y]," 1 ");
        if(IsLeap(year))            dayofmonth[2]=29;
        int yue=dayofmonth[y+1];
        for(int i=2; i<=7-s; i++)
        {
            if(i%7==0||i==(7-s))
            {
                wattron(monthtab[y],COLOR_PAIR(1)|A_BOLD);
                wprintw(monthtab[y],"%2d ",i);
                wattroff(monthtab[y],COLOR_PAIR(1)|A_BOLD);
            }
            else wprintw(monthtab[y],"%2d ",i);
        }
        wprintw(monthtab[y],"\n");



        for(int i=8-s,j=1; i<=yue; i++,j++)
        {
            if(j==1)
            {
                wattron(monthtab[y],COLOR_PAIR(1)|A_BOLD);
                wprintw(monthtab[y],"%2d ",i);
                wattroff(monthtab[y],COLOR_PAIR(1)|A_BOLD);
            }
            else if(j%7==0)
            {
                j++;
                wattron(monthtab[y],COLOR_PAIR(1)|A_BOLD);
                wprintw(monthtab[y],"%2d \n",i++);
                if(i<=yue)	wprintw(monthtab[y],"%2d ",i);
                wattroff(monthtab[y],COLOR_PAIR(1)|A_BOLD);
            }
            else wprintw(monthtab[y],"%2d ",i);

        }
        wrefresh(monthtab[y]);
        delwin(monthtab[y]);
        getch();

    }
}

void Date::printmonth()
{
    start_color();
    init_pair(1,COLOR_RED,COLOR_BLACK);
    printw("%13d  %d\n",year,month);
    attron(COLOR_PAIR(1)|A_BOLD);
    printw("Su  ");
    attroff(COLOR_PAIR(1)|A_BOLD);
    printw("Mo  Tu  We  Th  Fr  ");
    attron(COLOR_PAIR(1)|A_BOLD);
    printw("Sa  \n");
    attroff(COLOR_PAIR(1)|A_BOLD);
    int s=getdays(year,month,1);
    s=s%7;
    for(int m=0; m<s; m++)      printw("    ");
    if(s==0||s==6)
    {
        attron(COLOR_PAIR(1)|A_BOLD);
        printw(" 1  ");
        attroff(COLOR_PAIR(1)|A_BOLD);
    }
    else printw(" 1  ");
    if(IsLeap(year))            dayofmonth[2]=29;
    int yue=dayofmonth[month];
    for(int i=2; i<=7-s; i++)
    {
        if(i%7==0||i==(7-s))
        {
            attron(COLOR_PAIR(1)|A_BOLD);
            printw("%2d  ",i);
            attroff(COLOR_PAIR(1)|A_BOLD);
        }
        else printw("%2d  ",i);
    }
    printw("\n");


    for(int i=8-s,j=1; i<=yue; i++,j++)
    {
        if(j==1)
        {
            attron(COLOR_PAIR(1)|A_BOLD);
            printw("%2d  ",i);
            attroff(COLOR_PAIR(1)|A_BOLD);
        }
        else if(j%7==0)
        {
            j++;
            attron(COLOR_PAIR(1)|A_BOLD);
            printw("%2d \n",i++);
            if(i<=yue) 	printw("%2d  ",i);
            attroff(COLOR_PAIR(1)|A_BOLD);
        }
        else printw("%2d  ",i);

    }
    printw("\n\n");
}




int main()
{
    int yy=0,mm=0,dd=0;
    printf("Please input YEAR,MONTH,DAY:");
    if (scanf("%d %d %d",&yy, &mm, &dd)!=3)
        {
            printf("Value format error!\nExample: 2015 2 27\n");
            exit(1);
        }

    initscr();
    nocbreak();
//    printw("Please input YEAR,MONTH,DAY:");
//    refresh();
//    scanw("%d %d %d",&yy,&mm,&dd);
//
    Date mydate;
    mydate.SetDate(yy,mm,dd);

    mydate.ShowDate();
    mydate.showweek();
    mydate.printmonth();
    printw("Do you want print %d's calendar? [Y/N] ",yy);
    refresh();
    int choice=getch();
    endwin();

    initscr();
    clear();
    if(choice=='y'||choice=='Y')
        mydate.printyear();

    refresh();
    getch();
    endwin();
    return 0;
}
