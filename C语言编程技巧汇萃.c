/* 
C语言编程技巧汇萃(包含大量实用函数）

编程函数集，详细内容如下：

读键盘扫描码
获取机器日期
将浮点数转化为字符串
清除屏幕
显示时间
打印一个矩形
砍掉字符串中所有空格
取子字符串
从文件中读取字符
字符串左靠齐
取左字符串
向文件写数据
取右字符串
打开或关闭光标
喇叭发声
时间延迟
正点报时
写整数于文件中
从文件中读取整数
报警
字符串右靠齐
字符串居中
删除子字符串
查找指定字符串
产生空格
产生字符串
砍掉字符串左边空格
砍掉字符串右边空格
显示一个字符串
定义屏幕颜色
显示提示窗口显示警告窗口
得到文件长度
窗口滚屏
扫描键盘
插入字符串 
检测磁盘是否准备就绪
检测磁盘是否写保护
修改文件的某一行
成批拷贝文件
拷贝一个文件
建立目录
得到目录
得到文件名
任意两个正整数相加(<80位)
任意两个正整数相乘


注意：该函数集省略了不少TC标准头文件，读者使用时要自行添加。而且由于该函数集内部函数间有的有调用关系，读者拆卸时要谨慎。

*/

/*编程技巧荟萃*/

/*从键盘中读取字符 功能：按下普通键时，返回其ASCII码 扫描码CODE=0*/
int INKEY(int *code)
{
int m;
while(!bioskey(1))/*可加入无按键时代码*/;
*code=bioskey(0);
m=*code*255;
if(!m) m=*code>>8;
*code=*code&255;
return m;
}

/*获取机器日期*/
int DATE(char *s,char type)
{
char dat[30];
int num;
struct tm *tblock;
time_t t;
t=time(NULL);
tblock=localtime(&t);
strcpy(dt,asctime(tblock));
strcpy(s,"");
switch(type)
{
case 'N':
num=(*tblock).tm_year+1900;
itoa(num,s,10);
break;
case 'Y':
num=(*tblock).tm_mon+1;
itoa(num,s,10);
break;
case 'R':
num=(*tblock).tm_mday;
itoa(num,s,10);
break;
case 'S':
strcpy(dt,asctime(tblock));
MID(s,dt,12,8);
break;
}
}
return num;
}

/*将浮点数转化为字符串*/
/* 参数说明 data:需转换的浮点数；s:输出字符串；len:转换后的长度*/
void f_to_s(double data,char *s,int len)
{
int dec,sign,i;
char *s1,s2[100],s3[100];
s1=0;
s2[0]=0;
s3[0]=0;
s1=fcvt(data,len,&dec,&sign);
if (!sign&&data>=1)
{
MID(s2,s1,dec+1,-1);
MID(s3,s1,1,dec);
strcpy(s,"+");
strcat(s,s3);
strcat(s,".");
strcat(s,s2);
}
if (sign&&fabs(data)>=1)
{
MID(s2,s1,dec+1,-1);
strcpy(s,"-");
MID(s3,s1,1,dec);
strcat(s,s3);
strcat(s,".");
strcat(s,s2);
}
if (!sign&&dec==0)
{
strcpy(s,"+0.");
strcat(s,s1);
}
if (sign&&dec==0)
{
strcpy(s,"-0.");
strcat(s,s1);
}
if (!sign&&dec<0)
{
strcpy(s,"+0.");
for(i=1;i<=fabs(dec);i++)
strcat(s,"0");
strcat(s,s1);
}
if (sign&&dec<0)
{
strcpy(s,"-0.");
for(i=1;i<=fabs(dec);i++)
strcat(s,"0");
strcat(s,s1);
}
if (strlen(s)>len) s[len]=0;
}

/*清除屏幕*/
void CLSXY(int color,int x,int y,int xl,int yl)
{
int x1,y1;
union REGS r;
if(x<1||y<1) return;
y--;
x--;
y1=y+yl-1;
x1=x+xl-1;
if (y1>25||x1>80)
return;
r.h.ah=6; /*子功能号*/
r.h.al=0; /*滚动行数*/
r.h.ch=y;
r.h.cl=x;
r.h.dh=y1;
r.h.dl=x1;
r.h.bh=color*16;
int86(16,&r,&r);
}


/*显示时间*/
void display_time(int color,int back_color,int y,int x)
{
static char oldtime[9]="";
char newtime[9];
if(y<1||x<1) return;
settextstyle(1,0,1);
DATA(newtime,'S');
back_color=7;
if(strcmp(newtime,oldtime))
{
setfillstyle(1,back_color);
setcolor(color);
bar(535,458,635,475);
outtextxy(x,y,newtime);
strcpy(oldtime,newtime);
}
}


/*打印一个矩形*/
void PRINT_KJ(int x,int y,int wide,int high)
{
int i;
for(i=x;i<x+wide;i+=2)
{
gotoxy(i,y);
cprintf("");
}
gotoxy(x,y+high);
cprintf("");
gotoxy(x+wide,y+high);
cprintf("");
gotoxy(x,y);
cprintf("");
gotoxy(x+wide,y);
cprintf("");
for(i=x+2;i<x+wide;i+=2)
{
gotoxy(i,y+high);
cprintf("");
}
for(i=y+1;i<y+high;i++)
{
gotoxy(x,i);
cprintf("");
}
for(i=y+1;i<y+high;i++)
{
gotoxy(x+wide,i);
cprintf("");
}
}

/*砍掉字符串中所有空格*/
void CUT_ALL_SPC(char *s)
{
int i,n;
char d[10000];
n=0;
for(i=0;i<strlen(s);i++)
if(s[i]!=32)
{
d[n]=s[i];
n++;
}
d[n]=0;
strcpy(s,d);
}


/*取子字符串*/
void MID(char *s,char *t,int n,int m)
{
int i,j,p;
if(n<1) n=1;
i=strlen(s);
if(i<n) m=0;
if(m<0) m=i;
else m=n+m-1;
if(m>i) m=i;
p=m-n+1;
if(p<0) p=0;
for(i=n-1,j=0;i<m;i++,j++)
t[j]=s[i];
t[p]=0;
}


/*从文件中读取字符*/
int READ_STR(char *s,FILE *fp)
{
int i=0;
if(!fp) return 0;
if(fgets(s,10000,fp)) i=1;
s[strlen(s)-1]=0;
return i;
}

/*字符串左靠齐*/
void MOVE_LEFT(char *d,char *s,int n)
{
int i,l;
l=strlen(s);
if(n>l) n=l;
for(i=0;i<l;i++)
*d++=*s++;
*d=0;
}

/*取左字符串*/
void LEFT(char *d,char *s,int n)
{
int i,l;
i=0;
l=strlen(s);
if(n>l) n=l;
for(i=0;i<n;i++)
d[i]=s[i];
d[n]=0;
}


/*向文件写数据*/
void WRITE_STR(char *s,FILE *fp)
{
char c=10;
if(!fp) return;
fputs(s,fp);
fputc(c,fp);
}

/*取右字符串*/
void RIGHT(char *dest,char *source,int num)
{
int i,j;
if (num<1) num=0;
num=strlen(source)-num;
if (num<0) num=0;
for(i=0,j=num;j<=strlen(source);i++,j++) dest[i]=source[j];
}


/*打开或关闭光标*/
void CURSOR(int on2off)
{
union REGS r;
if (on2off!=OFF) on2off=10;
r.h.ah=1;
r.h.ch=3;
r.h.cl=on2off;
int86(16,&r,&r);
}

/*喇叭发声*/
void SOUND(int frequency,int time)
{
int i;
i=time*50;
if (i>30000) i=30000;
if (i<50) i=50;
sound(frequency);
MYDELAY(i);
nosound();
}

/*时间延迟*/
void MYDELAY(long t)
{
time_t OldTime;
long t0;
t0=t/55;
if (t0<1) t0=1;
OldTime=clock();
while(clock()-OldTime<t0);
}


/*正点报时*/
void REPORT_CLOCK(void)
{
int i;
for(i=0;i<5;i++);
{
SOUND(500,10);
MYDELAY(1000);
}
SOUND(800,10);
}


/*写整数于文件中*/
void WRITE_INT(int num,FILE *p)
{
char s[20],a=10;
if (!p) return;
itoa(num,s,10);
fputs(s,p);
fputc(a,p);
}


/*从文件中读取整数*/
int READ_INT(int *num,FILE *p)
{
int i;
char s[30]="";
if (!p) return 0;
if (fgets(s,10000,p))
{
i=-1;
s[strlen(s)-1]=0;
*num=atoi(s);
}
else i=0;
return i;
}


/*报警 */
void WARN(void)
{
SOUND(300,1);
SOUND(100,1);
}


/*字符串右靠齐*/
void MOVE_RIGHT(char *s,int wide)
{
int i,l,n;
l=strlen(s);
n=wide-l;
if (n>0)
{
for(i=l;i>-1;i--) s[i+n]=s[i];
for(i=0;i<n;i++) s[i]=32;
}
}


/*字符串居中*/
void MOVE_MIDDLE(char *s,int wide)
{
int i,l,n;
l=strlen(s);
if (wide>l)
{
wide=wide-1;
n=wide/2;
wide=wide-n;
for(i=l;i>-1;i--) s[i+n]=s[i];
for(i=0;i<n;i++) s[i]=32;
for(i=0;i<wide;i++) s[l+n+i]=32;
s[l+n+i]=0;
}
}

/*删除子字符串*/
void Delete_SubString(char *source,int start,int num)
{
int i,l;
l=strlen(source);
if (num>l-start+1||num==-1) num=l-start+1;
if (start<1||start>1) return;
for(i=start;i<l-num+2;i++)
source[i-1]=source[i+num-1];
}

/*查找指定字符串*/
int INSTR(int n,char *source,char *dest)
{
int i,j,k1,k2,p;
int start=0;
if (n==0) n=1;
k1=strlen(source);
k2=strlen(dest);
if (n<0)
{
char s[100];
n=-n;
MID(s,source,n,k2);
if (strcmp(s,dest)) return 0;
return n;
}
if (k1-n+1<k2) return start;
for(i=n-1;i<k1;i++)
{
p=0;
for(j=0;j<k2;j++)
if (source[i+j]!=dest[j]) break;
else p++;
if (p==k2)
{
start=i+1;
break;
}
}
return start;
}


/*产生空格*/
void SPACE(char *s,int n)
{
int i;
if (n<0) n=0;
for(i=0;i<n;i++) *s++=32;
*s=0;
}


/*产生字符串*/
void STRING(int n,char *s1,char *s2)
{
int i;
if (n<0) n=0;
s1[0]=0;
for(i=1;i<=n;i++) strcat(s1,s2);
}


/*砍掉字符串左边空格*/
void CUT_LEFT_SPACE(char *s)
{
int i,j,k=0;
i=strlen(s)+1;
for(j=0;j<i;j++) if (s[j]!=' ') break;
for(k=0;j<i;k++,j++) s[k]=s[j];
}


/*砍掉字符串右边空格*/
void CUT_RIGHT_SPACE(char *s)
{
int i,j;
i=strlen(s)-1;
for(j=i;j>-1;j--) if (s[j]!=' ') break;
s[j+1]=0;
}

/*显示一个字符串*/
void DISPLAY(char *s)
{
union REGS regs;
int color,x,y;
x=wherex();
y=wherey();
color=16*bjys+qjys;
while(*s)
{
if(x>80) break;
regs.h.ah=9;
regs.h.al=*s;
regs.h.bh=0;
regs.h.bl=color;
regs.x.cx=1; /*显示的次数,不改变光标位置*/
int86(16,&regs,&regs);
x++;
if(x>80)
{
x=1;
y++;
if(y>25) y=25;
}
gotoxy(x,y);
s++;
}
}

/*定义屏幕颜色*/
void COLOR(int ForeColor,int BackColor)
{
if(ForeColor<0||ForeColor>15) return;
if(BackColor<0||BackColor>15) return;
qjys=ForeColor;
bjys=BackColor;
}

/*显示提示窗口*/
void quit_YesNo(char *s1,char *s2)
{
char buffer[2000],jx;
gettext(30,8,76,16,buffer);
textbackground(3);
CLSXY(8,32,9,30,6);
CLSXY(4,30,8,30,6);
COLOR(15,4);
gotoxy(35,10);
DISPLAY(s1);
gotoxy(35,12);
DISPLAY(s2);
gotoxy(35+strlen(s2)+1,12);
jx=getch();
puttext(30,8,76,16,buffer);
if (jx=='n'||jx=='N') return;
textbackground(0);
textcolor(15);
clrscr();
CURSOR(ON);
exit(0);
}

/*显示警告窗口*/
void warn_message(char *s1,char *s2)
{
char buffer[2000];
gettext(30,8,76,16,buffer);
CLSXY(8,32,9,30,6);
CLSXY(4,30,8,30,6);
COLOR(15,4);
gotoxy(35,10);
DISPLAY(s1);
gotoxy(35,12);
DISPLAY(s2);
gotoxy(40,13);
DISPLAY("按任意键继续...");
getch();
puttext(30,8,76,16,buffer);
}

/*得到文件长度*/
long GetFileLength(char *file)
{
FILE *fp;
int i;
if ((fp=fopen(file,"rb"))==NULL)
{
clrscr();
printf("Can't open the file %s .",file);
return 0;
}
i=0;
while(!feof(fp))
{
i++;
fgetc(fp);
}
fclose(fp);
return (i-1);
}

/*窗口滚屏*/
void WINDOW_ROLL(int y1,int x1,int yl,int xl,int direct)
{
union REGS regs;
int x2,y2;
x1--;
y1--;
x2=x1+xl-1;
y2=y1+yl-1;
regs.h.ah=5+direct; /*ah=06h 向上滚动当前页*/
/*ah=07h 向下。。。 */
regs.h.al=1;
regs.h.bh=16*pmbj+pmqj;
regs.h.ch=y1; /*左上角行*/
regs.h.cl=x1; /*列*/
regs.h.dh=y2; /*右下角行*/
regs.h.dl=x2; /*列*/
int86(16,&regs,&regs);
}

/*扫描键盘*/
int scan_keyboard(int *m)
{
union inkey
{
unsigned char ch[2];
int ii;
}cc;
while(!bioskey(1))
{;}
cc.ii=bioskey(0);
*m=cc.ch[1];
return cc.ch[0];
}

/*插入字符串*/
void INSERT_STRING(char *ds,char *ss,int n)
{
char s[100];
MID(ds,s,n,-1);
ds[n-1]=0;
strcat(ds,ss);
strcat(ds,s);
}
void STR_ADD_CHAR(char *s,char ch)
{
char s1[2];
s1[0]=ch;
s1[1]=0;
strcat(s,s1);
}

/*检测磁盘是否准备就绪*/
int CheckDiskReading(int n)
{
int result;
char buffer[512];
result=biosdisk(4,n,0,0,0,1,buffer);
result=result&0x02;
if (result!=0x02) return 0;
return 1;
}

/*检测磁盘是否写保护*/
int CheckDiskWriteProf(void)
{
int result;
char buffer[512];
result=biosdisk(5,0,0,0,0,1,buffer);
if (result==0x03) return 0;
return 1;
}

/*修改文件的某一行*/
int ModifyFileLine(char *filename,char *s,int n)
{
char data[20][80];
int i;
FILE *fp;
if ((fp=fopen(filename,"r"))==NULL) return 0;
i=0;
while(READ_STR(data[i],fp))
i++;
fclose(fp);
fp=fopen(filename,"w");
strcpy(data[n-1],s);
n=i-1;
for(i=0;i<=n;i++)
WRITE_STR(data[i],fp);
fclose(fp);
return 1;
}

/*成批拷贝文件*/
int CopyFile(char *sfile,char *dfile,int f2d,int barlong,int height,int x,int y)
{
int Copyfile(char *sf,char *df);
int MakeNdir(char *Dir);
char filename[200][13],d[40],s[40],s1[40];
struct ffblk ffblk;
int done,i,j,l,len;
i=0;
done=findfirst(sfile,&ffblk,0);
if (!done) strcpy(filename[i],ffblk.ff_name);
while(!done)
{
done=findnext(&ffblk);
if (!done)
{
i++;
strcpy(filename[i],ffblk.ff_name);
}
}
if (f2d)
{
Copyfile(sfile,dfile);
return 1;
}
strcpy(s,sfile);
l=strlen(sfile);
for(j=l-1;j>=0;j--)
if (s[j]=='\\')
{
s[j+1]=0;
break;
} 

/*拷贝一个文件*/
int Copyfile(char *sf,char *df)
{
FILE *in,*out;
char ch;
in=0;
out=0;
if ((in=fopen(sf,"rb"))==NULL)
exit(0);
if ((out=fopen(df,"wb"))==NULL)
exit(0);
while(!feof(in))
{
ch=fgetc(in);
if (ferror(in)) return 0;
fputc(ch,out);
if (ferror(out)) return 0;
}
fclose(in);
fclose(out);
return 1;
}

/*建立目录*/
int MakeNdir(char *Dir)
{
int i,l,j;
char s[10][40];
j=0;
l=strlen(Dir);
for(i=0;i<l;i++)
if (Dir[i]=='\\')
{
LEFT(s[j],Dir,i);
j++;
}
strcpy(s[j],Dir);
for(i=0;i<=j;i++)
if (access(s[i],0)) mkdir(s[i]);
return 1;
}

/*得到目录*/
int GetDir(char *dirF,char dataK[][14])
{
struct ffblk ffblk;
int done;
int i;
i=0;
done=findfirst(dirF,&ffblk,FA_DIREC);
while(!done)
{
if (ffblk.ff_attrib==16||ffblk.ff_attrib==17)
{
strcpy(dataK[i],ffblk.ff_name);
strcat(dataK[i],"\\");
i++;
}
done=findnext(&ffblk);
}
return i;
}

/*得到文件名*/
int GetFile(char *dirF,char dataK[][14])
{
struct ffblk ffblk;
int done;
int i;
i=0;
done=findfirst(dirF,&ffblk,0);
while(!done)
{
strcpy(dataK[i],ffblk.ff_name);
done=findnext(&ffblk);
i++;
}
return i;
}

/*任意两个正整数相加(<80位)*/
/*参数说明:numA,numB分别为加数和被加数,result存放相加后的结果*/
void add(char *numA,char *numB,char *result)
{
int i,j,a,b,c,jw,Alen,Blen; /*定义变量*/
char num[81];
char numC[81]; /*定义新的字串,长度与numA相同*/
char ch;
char s[1];
num[0]=0;
numC[0]=0;
if (strlen(numA)>=80) return;
if (strlen(numB)>=80) return;
for(i=0;i<strlen(numA);i++) /*判断输入数是否非法*/
if (!isdigit(numA[i])) return; /*如果非法返回结果为空*/
for(i=0;i<strlen(numB);i++)
if (!isdigit(numB[i])) return;
if (strlen(numA)<strlen(numB)) /*将较大的数放入numA中*/
{
strcpy(num,numA);
strcpy(numA,numB);
strcpy(numB,num);
num[0]=0;
}
Alen=strlen(numA);
Blen=strlen(numB);
strcpy(numC,numB);
for(i=0;i<Alen;i++)
numC[Alen-i-1]=numC[Blen-i-1];
for(i=0;i<Alen-Blen;i++) /*在numC中插入n个0,使其长度等于numA*/
numC[i]='0';
jw=0; /*进位*/
for(i=0;i<Alen;i++)
{
s[0]=numA[Alen-i-1];
s[1]=0;
a=atoi(s);
s[0]=numC[Alen-i-1];
s[1]=0;
b=atoi(s);
c=a+b+jw;
if (c>=10)
{
jw=1;
c=c-10;
}
else jw=0;
itoa(c,s,10);
num[i]=s[0];
}
if (jw==1) {num[i]='1';num[i+1]=0;}
else num[i]=0;
j=strlen(num);
for(i=0;i<j/2;i++)
{
ch=num[i];
num[i]=num[j-i-1]; /*将num反转*/
num[j-i-1]=ch;
}
strcpy(result,num);
return; /*返回相加结果*/
}

/*任意两个正整数相乘*/
/*参数说明:numA,numB 分别为乘数和被乘数,resultm存放积*/
void mult(char *numA,char *numB,char *resultm)
{
int i,j,k,l,m,a,b,c,jw,Alen,Blen,f; /*定义变量*/
char resulta[82];
char num[161];
char ch;
char s[1];
num[0]=0;
f=0;
if (strlen(numA)>=80) return;
if (strlen(numB)>=80) return;
for(i=0;i<strlen(numA);i++) /*判断输入数是否非法*/
if (!isdigit(numA[i])) return; /*如果非法返回结果为空*/
for(i=0;i<strlen(numB);i++)
if (!isdigit(numB[i])) return;
if (strlen(numA)<strlen(numB)) /*将较大的数放入numA中*/
{
strcpy(num,numA);
strcpy(numA,numB);
strcpy(numB,num);
num[0]=0;
}
Alen=strlen(numA);
Blen=strlen(numB);
strcpy(resultm,"0");
for(i=0;i<Blen;i++)
{
s[0]=numB[Blen-i-1];
s[1]=0;
c=atoi(s);
strcpy(resulta,numA);
if (c==0) strcpy(resulta,"0");
for(j=0;j<c-1;j++) {add(resulta,numA,resulta);}
l=strlen(resulta);
for(k=0;k<i;k++)
{
resulta[l+k]='0';
resulta[l+k+1]=0;
}
add(resultm,resulta,resultm);
}
}
