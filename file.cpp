//////////////////////////////////////////////////////////////
//          ���ƣ�   ����˹���� ��ɫ��	1.1.0				//
//          ���ԣ�   C����									//
//		��һ�汾��   ����˹���� ��ɫ��	1.0.0				//
//		���ӹ��ܣ�   ���ӹؿ� �� ��߷�						//
//          ������   Microsoft Visual C++ 6.0				//
//          ���ߣ�   �������								//
//          ���ڣ�   2015��1��19��							//
//////////////////////////////////////////////////////////////
#include<stdio.h>
#include <windows.h>
#include<conio.h>
#include<time.h>
void gotoxy(int x,int y);//���ƹ�ꡣX��ʾ�����꣬Y��ʾ������
void console();//���ÿ���̨���ڴ�С��Ϊ���ó������еø��ÿ�
void my_print();//���ý���
void my_randout();//������ַ��飬����ӡ����ʾ��
void my_printblock();//��ӡ 4*4 �ķ�������ʾ����
void my_up();//��ת
void my_down();//����
void my_lift();//����
void my_right();//����
void my_exit();//�˳�ǰ������߷�
void clear();//��������
void gameover();//��Ϸ����
void my_stop();//��Ϸ��ͣ
int  tem[4][4];//��4*4�ķ��������Ʒ���Ĳ�������ʾ �����Ϊ��ֵý��
int  block[4][4];//��ʾ���ķ���
int  BLOCK[4][4];//��������ķ���
int  scope[25][34] = {0};//�����ķ�Χ ����Ҫע�⣬һ��������ռ���������굥λ��
int  point_x , point_y;//��������Ͻ�����
int  fen = 0;//�÷�
int  pass = 1;//�ؿ�  ����
int  hang = 0;//������������
int  max_fen = 0;//��߷� ����
FILE *fp;
bool check = true;//��鷽�黹�ܲ�������
int  block0[4][4] = {
    {0,1,1,0},
    {0,0,1,0},
    {0,0,1,0},
    {0,0,0,0}
};// 7 ������ �������ʾ ����7��
int  block1[4][4] = {
    {0,1,1,0},
    {0,1,0,0},
    {0,1,0,0},
    {0,0,0,0}
};// ����7��
int  block2[4][4] = {
    {0,0,0,0},
    {0,0,1,1},
    {0,1,1,0},
    {0,0,0,0}
};// ����z��
int  block3[4][4] = {
    {0,0,0,0},
    {1,1,0,0},
    {0,1,1,0},
    {0,0,0,0}
};// ����z��
int  block4[4][4] = {
    {0,0,0,0},
    {0,1,0,0},
    {1,1,1,0},
    {0,0,0,0}
};// ����T��
int  block5[4][4] = {
    {0,0,0,0},
    {0,1,1,0},
    {0,1,1,0},
    {0,0,0,0}
};// ������
int  block6[4][4] = {
    {0,0,0,0},
    {0,0,0,0},
    {1,1,1,1},
    {0,0,0,0}
};// ֱ��

int main()
{
    if ((fp = fopen("test.txt","r") )== NULL)
    {
        fp = fopen("test.txt","w+");//���ļ� ���û�оʹ���
    }
    srand((unsigned)time(NULL));//�������������
    char key;
    int  i , j;
    fscanf(fp, "%d", &i);
    max_fen = max_fen>i?max_fen:i;//����߷ָ���max_fen
    fclose(fp);//�ر��ļ�
    int time;//��������ʱ��
    console();
    my_print();
    my_randout();
    while( true )//��ѭ��
    {
        if( check )//���û����������ķ����ִ��if�����
        {
            check = false;
            point_x = 14;//����������ֵĵط�
            point_y = 0;
            for( i=0 ; i < 4 ; i++)
            {
                for( j = 0 ; j < 4 ; j++)
                {
                    BLOCK[i][j] = block[i][j];//����ʾ���ķ������鴫������ķ�������
                }
            }
            my_printblock();//��point_x,point_y��ʾ���顣
            my_randout();//��ʾ�������һ������
        }
        if (kbhit()) //��⣬����а�����ִ��if�����
        {
            key = getch();//���񰴼�
            switch( key )
            {
                case 72:my_up();//��
                        break;
                case 75:my_lift();//��
                        break;
                case 77:my_right();//��
                        break;
                case 80:my_down();//��
                        break;
                case 32:my_stop();//�ո� ��ͣ��ʼ
                        break;
                case 27:my_exit();//Esc �˳�
                default: ;
            }
        }
        Sleep(30);//�ȴ�0.03�� 0.03�����ִ��һ������ Ҳ����CPU
        if( 0 == ++time % (32 - pass*3))//���������ʱ��=30*30����
        {
            my_down();//ʱ�䵽�Զ�����һ��
        }
        if( true == check)//����������ʱ
        {
            for( i=0 ; i < 4 ; i++)
            {
                for( j = 0 ; j < 4 ; j++)
                {
                    if( 1 == BLOCK[i][j])
                        scope[point_x / 2 + j][point_y + i] = BLOCK[i][j];//������ķ��鸳ֵ��������������
                    //�����point_x����2����Ϊһ��С����ռ����������
                }
            }
            my_printblock();
            clear();//�����ĳһ�����˾�����
        }
    }
    return 0;
}



//���ô���λ�úʹ�С��Ϊ���ó������еø��ÿ�
void console()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);	// ��ȡ��׼����豸���
    CONSOLE_SCREEN_BUFFER_INFO bInfo; // ���ڻ�������Ϣ
    GetConsoleScreenBufferInfo(hOut, &bInfo );	// ��ȡ���ڻ�������Ϣ
    SetConsoleTitle("����˹���� C��"); // ���ô��ڵı���
    COORD size = {80, 32};//����С��Ĭ�ϴ�С��80��25��
    SetConsoleScreenBufferSize(hOut,size); // �������û�������С*/
    SMALL_RECT rc = {0,0, 63, 31}; //���ܴ��ڻ�������С
    SetConsoleWindowInfo(hOut,true ,&rc);	// ���ô��ڴ�С
}

void my_print()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_INTENSITY);//�ڵ������֡�
    for(int i = 1 ; i < 30 ; i++)
        printf("��\t\t\t\t�� |                           |\n");
    printf("���������������������������������� |---------------------------|\n");//���
    gotoxy(36,0);
    printf("---------------------------");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN | FOREGROUND_RED |FOREGROUND_INTENSITY);//�ڵ������֡�
    gotoxy(40,2);
    printf("��  ���� %d",pass);
    gotoxy(40,3);
    printf("��  ���� %d",fen);
    gotoxy(40,4);
    printf("��߷֣� %d",max_fen);
    gotoxy(36,6);
    printf("��һ�����飺");
    gotoxy(36,14);
    printf("����������");
    gotoxy(40,16);
    printf("������ת ��������");
    gotoxy(40,18);
    printf("�������� ��������");
    gotoxy(39,20);
    printf("�ո������ʼ / ��ͣ");
    gotoxy(39,22);
    printf("    Esc���˳�");
    gotoxy(36,25);
    printf("�� �ڣ�");
    gotoxy(40,26);
    printf("����˹���� 1.1.0");
    gotoxy(49,27);
    printf("���ߣ��������");
    gotoxy(50,28);
    printf("2015��1��19��");
}


//���ù�������λ�ú��������겻��Ϊ����
void gotoxy(int x,int y)//X��ʾ�����꣬Y��ʾ�����ꡣ
{
    HANDLE app;
    COORD  pos;
    pos.X=x;
    pos.Y=y;
    app=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(app,pos);
}
//��ת ��4*4����˳ʱ����ת
void my_up()
{
    int i,j;
    for( i=0 ; i < 4 ; i++)
    {
        for( j = 0 ; j < 4 ; j++)
        {
            tem[i][j] = BLOCK[i][j];
            if( 1 == BLOCK[i][j])
            {
                gotoxy(point_x + j*2 , point_y + i);
                printf("  ");
            }
        }
    }
    for( i=0 ; i < 4 ; i++)
    {
        for( j = 0 ; j < 4 ; j++)
        {
            BLOCK[j][3-i] = tem[i][j];
        }
    }
    //����Ϊ��ת��
    //����Ϊ��ֹ��ת�󳬳���ܷ�Χ
    for( j = 0 ; j < 2 ; j++)
    {
        for( i = 0 ; i < 4 ; i++)
        {
            if (1 == BLOCK[i][j] && point_x < 2)
            {
                point_x+=2;
            }
            else if (1 == BLOCK[i][3-j] && point_x > 24)
            {
                point_x-=2;
            }
        }
    }
    my_printblock();//��ת֮��������ʾ����
}
//����
void my_lift()
{
    int i , j ;
    for(  i = 0 ; i < 3 ; i++ )
        for( j = 0 ; j < 4 ; j++ )
        {
            if(1 == BLOCK[j][i] && (point_x+2*i-1 < 2 || 1 == scope[point_x / 2 + i - 1][point_y + j]))
            {
                return ;//�������Ե ����������Ѿ����˷���
            }
        }
    for( i = 0 ; i  < 4 ; i++ )
        for( j = 0 ; j < 4 ; j++ )
            if( 1 == BLOCK[i][j])
            {
                gotoxy(point_x + j*2 , point_y + i);
                printf("  ");//��֮ǰ�Ĳ���
            }
    point_x -= 2;
    my_printblock();
}

void my_right()
{
    int i , j ;
    for(  i = 3 ; i > 0 ; i-- )
        for( j = 0 ; j < 4 ; j++ )
        {
            if(1 == BLOCK[j][i] && ( point_x+2*i+2 > 30 || 1 == scope[point_x / 2 + i + 1][point_y + j]))
            {
                return ;//�������Ե �������ұ��Ѿ����˷���
            }
        }
    for( i = 0 ; i  < 4 ; i++ )
        for( j = 0 ; j < 4 ; j++ )
            if( 1 == BLOCK[i][j])
            {
                gotoxy(point_x + j*2 , point_y + i);
                printf("  ");//��֮ǰ�Ĳ���
            }
    point_x += 2;
    my_printblock();
}

void my_down( )
{
    int i , j ;
    if( true == check)
    {
        return ;//��������ֱ�Ӳ�ִ��
    }
    gotoxy(point_x,point_y);
    for( i = 3 ; i > 0 ; i-- )//���÷����ܲ�������
        for( j = 0 ; j  < 4 ; j++ )
            if ( 1 == BLOCK[i][j] )
            {
                if (1 == scope[point_x / 2 + j][point_y + i + 1] || point_y + i + 1 > 28 ) //�����±߻��������Ѿ��з���
                {
                    check = true;
                    return ;
                }
            }
    for( i = 0 ; i  < 4 ; i++ )
        for( j = 0 ; j < 4 ; j++ )
            if( 1 == BLOCK[i][j])
            {
                gotoxy(point_x + j*2 , point_y + i);
                printf("  ");//�����䣬������ǰ�ķ���
            }
    point_y++;
    my_printblock();//����һ����ʾ
}
//��ͣ
void my_stop()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_INTENSITY);
    gotoxy(10,10);	printf("              ");
    gotoxy(10,11);	printf("  ����������  ");
    gotoxy(10,12);	printf("  ��      ��  ");
    gotoxy(10,13);	printf("  ��      ��  ");
    gotoxy(10,14);	printf("  ����������  ");
    gotoxy(10,15);	printf("  ��          ");
    gotoxy(10,16);	printf("  ��           ");
    gotoxy(10,17);	printf("  ��          ");
    gotoxy(10,18);	printf("              ");
    if ( 32 == getch()) //�õȴ������ַ�ʵ����ͣ 32Ϊ�ո�
    {
        gotoxy(10,10);	printf("              ");
        gotoxy(10,11);	printf("  ����������  ");
        gotoxy(10,12);	printf("          ��  ");
        gotoxy(10,13);	printf("          ��  ");
        gotoxy(10,14);	printf("  ����������  ");
        gotoxy(10,15);	printf("          ��  ");
        gotoxy(10,16);	printf("          ��  ");
        gotoxy(10,17);	printf("  ����������  ");
        gotoxy(10,18);	printf("              ");
        Sleep(1000);
        gotoxy(10,10);	printf("              ");
        gotoxy(10,11);	printf("  ����������  ");
        gotoxy(10,12);	printf("          ��  ");
        gotoxy(10,13);	printf("          ��  ");
        gotoxy(10,14);	printf("  ����������  ");
        gotoxy(10,15);	printf("  ��          ");
        gotoxy(10,16);	printf("  ��          ");
        gotoxy(10,17);	printf("  ����������  ");
        gotoxy(10,18);	printf("              ");
        Sleep(1000);
        gotoxy(10,10);	printf("              ");
        gotoxy(10,11);	printf("      ����    ");
        gotoxy(10,12);	printf("    ������    ");
        gotoxy(10,13);	printf("      ����    ");
        gotoxy(10,14);	printf("      ����    ");
        gotoxy(10,15);	printf("      ����    ");
        gotoxy(10,16);	printf("      ����    ");
        gotoxy(10,17);	printf("    ��������  ");
        gotoxy(10,18);	printf("              ");
        Sleep(1000);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_INTENSITY);
        for(int i = 0 ; i < 9 ; i++)//����ͣ�ڸǵķ����ٴ���ʾ����
        {
            gotoxy(10  , 10 + i );
            for(int j = 0 ; j < 7 ; j++ )
            {
                if (1 == scope[5 + j][10 + i])
                {
                    printf("��");
                }
                else
                {
                    printf("  ");
                }
            }
        }
    }
}
//����
void clear()
{
    int i , j , k , m = 0;
    for(i = point_y + 3 ; i >= point_y ; i-- )
    {
        for( j = 1 ; j < 16 ; j++ )
        {
            if( 0 == scope[j][i] )
            {
                break ;
            }
        }
        if ( 16 == j )
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_INTENSITY);
            m++;
            for(k=i;k>3;k--)
            {
                for( j = 1 ; j < 16 ; j++ )
                {
                    scope[j][k] = scope[j][k - 1];
                    gotoxy(j*2 , k );
                    if (1 == scope[j][k])
                    {
                        printf("��");
                    }
                    else
                    {
                        printf("  ");
                    }
                }
            }
            for( j = 1 ; j < 16 ; j++ )
            {
                scope[j][4] = 0;
            }
            i++;
        }
    }
    switch(m) {//�ж�һ�������˼��У������õ÷���
        case 1: fen+=100;
                break;
        case 2: fen+=230;
                break;
        case 3: fen+=438;
                break;
        case 4: fen+=854;
                break;
        default: ;
    }
    hang += m ;
    if( hang > 10 )//ÿ10����һ��
    {
        hang = 0 ;
        pass++;
    }
    max_fen = max_fen>fen?max_fen:fen;//������߷�
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN | FOREGROUND_RED |FOREGROUND_INTENSITY);//�ڵ�����ɫ�֡�
    gotoxy(40,2);
    printf("��  ���� %d",pass);
    gotoxy(40,3);
    printf("��  ���� %d",fen);
    gotoxy(40,4);
    printf("��߷֣� %d",max_fen);
    for( j = 7 ; j < 11 ; j++ )
    {
        if(1 == scope[j][4])
            gameover();
    }
}
//������ַ���
void my_randout()
{
    int i,j;
    switch( rand()%7 )
    {
        case 0:for(i=0 ; i < 4 ; i++)
                   for(j = 0 ; j < 4 ; j++)
                       block[i][j] = block0[i][j];
               break;
        case 1: for(i=0 ; i < 4 ; i++)
                    for(j = 0 ; j < 4 ; j++)
                        block[i][j] = block1[i][j];
                break;
        case 2: for(i=0 ; i < 4 ; i++)
                    for(j = 0 ; j < 4 ; j++)
                        block[i][j] = block2[i][j];
                break;
        case 3: for(i=0 ; i < 4 ; i++)
                    for(j = 0 ; j < 4 ; j++)
                        block[i][j] = block3[i][j];
                break;
        case 4: for(i=0 ; i < 4 ; i++)
                    for( j = 0 ; j < 4 ; j++)
                        block[i][j] = block4[i][j];
                break;
        case 5: for( i=0 ; i < 4 ; i++)
                    for( j = 0 ; j < 4 ; j++)
                        block[i][j] = block5[i][j];
                break;
        case 6: for( i=0 ; i < 4 ; i++)
                    for( j = 0 ; j < 4 ; j++)
                        block[i][j] = block6[i][j];
                break;
        default: ;
    }
    for( i=0 ; i < 4 ; i++)
    {
        for( j = 0 ; j < 4 ; j++)
        {
            tem[i][j] = block[i][j];
        }
    }
    switch( rand()%4 )//�����������ת�ķ���
    {
        case 0 :
            break;
        case 1 : for( i=0 ; i < 4 ; i++)//˳ʱ��90��
                 {
                     for( j = 0 ; j < 4 ; j++)
                     {
                         block[j][3-i] = tem[i][j];
                     }
                 }
                 break;
        case 2 : for( i=0 ; i < 4 ; i++)//˳180��
                 {
                     for( j = 0 ; j < 4 ; j++)
                     {
                         block[3-i][3-j] = tem[i][j];
                     }
                 }
                 break;
        case 3 : for( i=0 ; i < 4 ; i++)//˳270��
                 {
                     for( j = 0 ; j < 4 ; j++)
                     {
                         block[3-j][i] = tem[i][j];
                     }
                 }
                 break;
        default: ;
    }
    //��ӡ��ʾ���ķ���
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_INTENSITY);//�ڵ������֡�
    for( i=0 ; i < 4 ; i++)
    {
        gotoxy(44 , 8 + i);
        for( j = 0 ; j < 4 ; j++)
        {
            if(1 == block[i][j])
            {
                printf("��");
            }
            else
            {
                printf("  ");
            }
        }
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//�ڵװ���
}

//��ʾ����
void my_printblock()
{
    int  i , j ;
    for( i=0 ; i < 4 ; i++)
    {
        for( j = 0 ; j < 4 ; j++)
        {
            if (point_x / 2 + j > 0  )
            {
                if ( 1 == scope[point_x / 2 + j][point_y + i])
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_INTENSITY);
                    gotoxy(point_x + j*2 , point_y + i);
                    printf("��");
                }
                else if (1 == BLOCK[i][j])
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
                    gotoxy(point_x + j*2 , point_y + i);
                    printf("��");
                }
            }
        }
    }
}
void gameover()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
    gotoxy(4,10);	printf("                                                        ");
    gotoxy(4,11);	printf("    ������      ��      ��      ��������      ��������  ");
    gotoxy(4,12);	printf("  ��      ��    ��      ��      ��            ��    ��  ");
    gotoxy(4,13);	printf("  ��      ��      ��  ��        ��������      ��������  ");
    gotoxy(4,14);	printf("  ��      ��      ��  ��        ��            ����      ");
    gotoxy(4,15);	printf("    ������          ��          ��������      ��  ��    ");
    gotoxy(4,16);	printf("                                                        ");
    gotoxy(32,17);	printf("�ո��������\tEsc���˳�");
    switch( getch() )
    {
        case 32: system("cls");//����
                 console();
                 my_print();//�������
                 my_randout();
                 memset(scope, 0, sizeof(int) * 25 * 34);//��������
                 fen = 0;
                 hang = 0;
                 pass = 1;
                 break;
        case 27: my_exit();
                 break;
        default:;
    }
}
void my_exit()//�˳�ǰ������߷�
{
    fp = fopen("test.txt","w");
    fprintf(fp, "%d\n", max_fen);
    fclose(fp);
    exit(0);
}
