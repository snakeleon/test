/*==========================================================================
#     FileName :	main.cpp
#  Description :    Calendar
#       Author :	SiFe
#       E-Mail :	snakeleon@gmail.com
#	  HomePage :	https://github.com/snakeleon
#      Version :	0.0.2
#   LastChange :	2020-02-11 19:41:34
#      History :
==========================================================================*/

#include <ncurses.h>
#include <stdlib.h>


int dayofmonth[13]= {0,31,28,31,30,31,30,31,31,30,31,30,31};

class Date
{
    private:
        int     year  = 0;
        int     month = 0;
        int     day   = 0;
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
    year  = yy;
    month = mm;
    if(year<1)
    {
        printf("Year value error!\nERROR CODE: 1\n");
        refresh();
        getch();
        endwin();
        exit(1);
    }
    if(month<1||month>12)
    {
        printf("Month value error!\r\nERROR CODE: 2\n");
        getch();
        exit(2);
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
                    printf("Day value error!\r\nERROR CODE: 3\n");
                    getch();
                    exit(2);
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
                        printf("Day value error!\r\nERROR CODE: 3\n");
                        getch();
                        exit(3);
                    }
                }
                else
                {
                    if(dd>=1&&dd<=28)       day=dd;
                    else
                    {
                        printf("Day value error!\r\nERROR CODE: 3\n");
                        getch();
                        exit(3);
                    }
                }
            }
            break;

        default:
            {
                if(dd>=1&&dd<=31)       day=dd;
                else
                {
                    printf("Day value error!\r\nERROR CODE: 3\n");
                    getch();
                    exit(3);
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
    int sum=0;
    for(int i=1; i<year; i++)
    {
        if(IsLeap(i))       sum+=366;
        else sum+=365;
    }
    if(IsLeap(year))        dayofmonth[2]=29;
    for(int i=1; i<month; i++)  sum+=dayofmonth[i];
    sum+=day;
    return sum;
}

void Date::showweek()
{
    int s = getdays(year,month,day)%7;
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
    WINDOW *w_monthtab[11];
    for(int y=0,start_y=0,start_x=0; y<10; y++,start_x+=22)
    {
        if(start_x>60)
        {
            start_y += 8;
            start_x  = 0;
        }
        w_monthtab[y]=newwin(8,22,start_y,start_x);
        if(w_monthtab[y]==NULL)
        {
            printw("Create Window Error!");
            exit(1);
        }
//        getch();
        start_color();
        init_pair(1,COLOR_RED,COLOR_BLACK);
        wprintw(w_monthtab[y],"%11d  %d\n",year,y+1);
        wattron(w_monthtab[y],COLOR_PAIR(1)|A_BOLD);
        wprintw(w_monthtab[y]," S ");
        wattroff(w_monthtab[y],COLOR_PAIR(1)|A_BOLD);
        wprintw(w_monthtab[y]," M  T  W  T  F ");
        wattron(w_monthtab[y],COLOR_PAIR(1)|A_BOLD);
        wprintw(w_monthtab[y]," S \n");
        wattroff(w_monthtab[y],COLOR_PAIR(1)|A_BOLD);
        int s=getdays(year,y+1,1);
        s=s%7;
        for(int m=0; m<s; m++)      wprintw(w_monthtab[y],"   ");
        if(s==0||s==6)
        {
            wattron(w_monthtab[y],COLOR_PAIR(1)|A_BOLD);
            wprintw(w_monthtab[y]," 1 ");
            wattroff(w_monthtab[y],COLOR_PAIR(1)|A_BOLD);
        }
        else wprintw(w_monthtab[y]," 1 ");
        if(IsLeap(year))            dayofmonth[2]=29;
        int MM=dayofmonth[y+1];
        for(int i=2; i<=7-s; i++)
        {
            if(i%7==0||i==(7-s))
            {
                wattron(w_monthtab[y],COLOR_PAIR(1)|A_BOLD);
                wprintw(w_monthtab[y],"%2d ",i);
                wattroff(w_monthtab[y],COLOR_PAIR(1)|A_BOLD);
            }
            else wprintw(w_monthtab[y],"%2d ",i);
        }
        wprintw(w_monthtab[y],"\n");


        for(int i=8-s,j=1; i<=MM; i++,j++)
        {
            if(j==1)
            {
                wattron(w_monthtab[y],COLOR_PAIR(1)|A_BOLD);
                wprintw(w_monthtab[y],"%2d ",i);
                wattroff(w_monthtab[y],COLOR_PAIR(1)|A_BOLD);
            }
            else if(j%7==0)
            {
                j++;
                wattron(w_monthtab[y],COLOR_PAIR(1)|A_BOLD);
                wprintw(w_monthtab[y],"%2d \n",i++);
                if(i<=MM)	wprintw(w_monthtab[y],"%2d ",i);
                wattroff(w_monthtab[y],COLOR_PAIR(1)|A_BOLD);
            }
            else wprintw(w_monthtab[y],"%2d ",i);

        }
        wrefresh(w_monthtab[y]);
        if(w_monthtab[y])
            delwin(w_monthtab[y]);
    }

}

void Date::printmonth()
{
    start_color();
    init_pair(1,COLOR_RED,COLOR_BLACK);
    printw("%13d  %d\n",year,month);
    attron(COLOR_PAIR(1)|A_BOLD);
    printw("Su  ");
    attroff(COLOR_PAIR(2)|A_BOLD);
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
    int MM = dayofmonth[month];
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


    for(int i=8-s,j=1; i<=MM; i++,j++)
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
            if(i<=MM) 	printw("%2d  ",i);
            attroff(COLOR_PAIR(1)|A_BOLD);
        }
        else printw("%2d  ",i);

    }
    printw("\n\n");
}




int main(void)
{
    int yy = 0, mm = 0, dd = 0;
    printf("Please input YEAR,MONTH,DAY:");
    if (scanf("%d %d %d",&yy, &mm, &dd)!=3)
    {
        printf("Value format error!\nExample: 2015 2 27\n");
        exit(1);
    }


    //    printw("Please input YEAR,MONTH,DAY:");
    //    refresh();
    //    scanw("%d %d %d",&yy,&mm,&dd);
    //
    Date mydate;
    mydate.SetDate(yy,mm,dd);

    initscr();
    nocbreak();
    scrollok(stdscr,TRUE);

    mydate.ShowDate();
    mydate.showweek();
    mydate.printmonth();
    printw("Do you want print %d's calendar? [Y/N] ",yy);
    refresh();
    int choice=getch();
//    endwin();

//    initscr();
//    clear();
    if(choice=='y'||choice=='Y')
        mydate.printyear();

    getch();
    getch();

    endwin();

    return 0;
}
