/*
又一个编程函数集(包含大量实用函数）

编程函数集，详细内容如下：


格式化字符串转换
鼠标驱动
西文模式下输出汉字(BGI)
三维窗体
时钟中断服务
取得键盘扫描码
文本模式光标定位
显示的关闭与开启
文本模式的直接写屏技术
TVGA直接写屏图形引擎

*/

/*-------------------------------------------------------------------------*/
/* Head */
/*-------------------------------------------------------------------------*/

#include <stdio.h>
#include <conio.h>
#include <stdarg.h>
#include <dos.h>
#include <graphics.h>
#include <stdio.h>
#include <iostream.h>
#include <stdlib.h>
#include <time.h>
#include <bios.h>
#include <string.h>
#include <math.h>


/*---------------------------格式化字符串转换------------------------------*/

int vsprint(char *buffer,char *fmt, ...)
{
va_list argptr;
int cnt;
va_start(argptr, fmt);
cnt = vsprintf(buffer, fmt, argptr);
va_end(argptr);
return(cnt);
}

/*-------------------------------鼠标驱动----------------------------------*/

int mouse(int a,int b,int c,int d)
{
asm mov ax,a
asm mov bx,b
asm mov cx,c
asm mov dx,d
asm int 33h
return _AX;
}

#if defined(MOUSESHAPE) //光标形状设定
typedef struct
{
unsigned int shape[32];
char hotx;
char hoty;
}SHAPE;

SHAPE pen1={{0x0fff,0x07ff,0x03ff,0x01ff,0x80ff,0xc07f,0xe03f,0xf01f,
0xf80f,0xfc07,0xfe03,0xff01,0xff80,0xffc1,0xffe3,0xfff7,
0xf000,0xe800,0xd400,0xaa00,0x5500,0x2a80,0x1540,0x0aa0,
0x0550,0x02a8,0x0154,0x00aa,0x0055,0x002a,0x0014,0x0008},0,0 };
SHAPE pen2={{0xe1ff,0xe1ff,0xe1ff,0xe1ff,0xe000,0xe000,0xe000,0xe000,
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
0x1e00,0x1200,0x1200,0x1200,0x1200,0x13ff,0x1249,0x1249,
0x1249,0x9001,0x9001,0x9001,0x8001,0x8001,0x8001,0xffff},5,0};


void mouseshape(SHAPE sp)
{
_BX=sp.hotx;
_CX=sp.hoty;
_ES=FP_SEG(&sp.shape);
_DX=FP_OFF(&sp.shape);
_AX=0x09;
geninterrupt(0x33);
}
#endif

/*--------------------------西文模式下输出汉字(BGI)------------------------*/

void initgraphics(int gdriver,int gmode,char *drvpath="")
{
initgraph(&gdriver,&gmode,drvpath);
}

couttextxy(FILE *library,int x,int y,unsigned char far *string,char color)
{
register int i,j;
unsigned long int locate;
int k=0;
char l=0,buffer[32];
if(library==NULL) return 0;
while(string[k]!='\0')
{
locate=(string[k]-161)*94+string[k+1]-161;
fseek(library,(long int)locate*32,SEEK_SET);
fread(buffer,32,sizeof(char),library);
k+=2;
for(i=0;i<16;i++)
for(j=0;j<2;j++)
{
l=buffer[i*2+j];
if((l&0x80)!=0) putpixel(x+j*8,y+i,color);
if((l&0x40)!=0) putpixel(x+j*8+1,y+i,color);
if((l&0x20)!=0) putpixel(x+j*8+2,y+i,color);
if((l&0x10)!=0) putpixel(x+j*8+3,y+i,color);
if((l&0x08)!=0) putpixel(x+j*8+4,y+i,color);
if((l&0x04)!=0) putpixel(x+j*8+5,y+i,color);
if((l&0x02)!=0) putpixel(x+j*8+6,y+i,color);
if((l&0x01)!=0) putpixel(x+j*8+7,y+i,color);
}
x+=16;
}
return 1;
}

/*-------------------------------三维窗体----------------------------------*/

void window3d(int x,int y,int length,int width,char *title)
{
setcolor(7);
line(x,y,x+length,y);
line(x,y,x,y+width);
setcolor(0);
line(x,y+width,x+length,y+width);
line(x+length,y,x+length,y+width);
setcolor(15);
line(x+1,y+1,x+length-1,y+1);
line(x+1,y+1,x+1,y+width-1);
setcolor(8);
line(x+1,y+width-1,x+length-1,y+width-1);
line(x+length-1,y+1,x+length-1,y+width-1);
setfillstyle(1,7);
bar(x+2,y+2,x+length-2,y+width-2);
setfillstyle(1,1);
bar(x+4,y+4,x+length-4,y+20);
setcolor(15);
outtextxy(x+8,y+8,title);
}

void textwindow3d(int x,int y,int length,int width,char *title,int bargin)
{
window3d(x,y,length,width,title);
setfillstyle(1,15);
bar(x+bargin,y+bargin+20,x+length-bargin,y+width-bargin);
setcolor(0);
line(x+bargin-1,y+bargin+19,x+length-bargin+1,y+bargin+19);
line(x+bargin-1,y+bargin+19,x+bargin-1,y+width-bargin+1);
setcolor(7);
line(x+length-bargin+1,y+bargin+19,x+1+length-bargin,y+width-bargin+1);
line(x+bargin-1,y+width-bargin+1,x+1+length-bargin,y+width-bargin+1);
setcolor(8);
line(x+bargin-2,y+bargin+18,x+2+length-bargin,y+18+bargin);
line(x+bargin-2,y+18+bargin,x+bargin-2,y+2+width-bargin);
setcolor(15);
line(x+2+length-bargin,y+18+bargin,x+2+length-bargin,y+2+width-bargin);
line(x+bargin-2,y+2+width-bargin,x+2+length-bargin,y+2+width-bargin);
}

/*-----------------------------时钟中断服务--------------------------------*/

#if defined(INTERRUPT)
void interrupt (*old)();
//void interrupt hand(){(*old)();}

void uninstall()
{
disable();
setvect(0x1c,(*old));
enable();
}

void install()
{
disable();
old=getvect(0x1c);
setvect(0x1c,hand);
enable();
}
#endif

/*-----------------------------取得键盘扫描码------------------------------*/

int keydown()
{
int key;
if(bioskey(1)==0) return -1;
else 
key=bioskey(0);
key=key&0xff?key&0xff:key>>8;
return key;
}

/*----------------------------文本模式光标定位-----------------------------*/

void goto_xy(char x,char y)
{
asm mov ah,2
asm mov dl,x
asm mov dh,y
asm mov bh,0
asm int 10h
}

/*----------------------------显示的关闭与开启-----------------------------*/

#define CLOSE 0x1201
#define OPEN 0x1200
void video(int mode)
{
asm mov bl,36h
asm mov ax,mode
asm int 10h
}

/*---------------------------文本模式的直接写屏技术------------------------*/

int video_mode(void)
{
union REGS r;
r.h.ah=15;
return int86(0x10,&r,&r)&255;
}

char far *set_v_ptr()
{
int vmode;
char far *vid_mem;
vmode=video_mode();
if((vmode!=2)&&(vmode!=3)&&(vmode!=7))
{
printf("Video must be in 80 column text mode!");
exit(1);
}
if(vmode==7) vid_mem=(char far *)0xb0000000;
else vid_mem=(char far *)0xb8000000;
return vid_mem;
}

void write_char(char far *vid_mem,int x,int y,char ch,int attrib)
{
char far *v;
v=vid_mem;
v+=(y*160)+x*2;
*v++=ch;
*v=attrib;
}

void write_string(char far *vid_mem,int x,int y,char *string,int color)
{
int i;
for(i=0;i<strlen(string);i++)
write_char(vid_mem,x+i,y,*(string+i),color);
}

int read_color(char far *vid_mem,int x,int y)
{
char far *v;
v=vid_mem;
v+=(y*160)+x*2;
return *(++v);
}

char read_char(char far *vid_mem,int x,int y)
{
char far *v;
v=vid_mem;
v+=(y*160)+x*2;
return *v;
}

/*-------------------------TVGA直接写屏图形引擎--------------------------*/

void _setgraphmode(int mode,int *xmax,int *ymax)
{
union REGS regs;
unsigned char video;
switch(mode)
{
case 0: video=0x5c;
*xmax=640;
*ymax=400;break; //640x400
case 1: video=0x5d;
*xmax=640;
*ymax=480;break; //640x480
case 2: video=0x5e;
*xmax=800;
*ymax=600;break; //800x600
case 3: video=0x62;
*xmax=1024;
*ymax=768;break; //1024x768
default:video=0x5d;
*xmax=640;
*ymax=480;break; //Default: 640x480
}
regs.h.ah=0;
regs.h.al=video;
int86(0x10,&regs,&regs);
outportb(0x3c4,0x0b);
inportb(0x3c5);
return;
}

void _putpixel(int x,int y,int color,int xmax)
{
unsigned long int result=y;
char far *offset;
char temp;
result*=xmax;
result+=x;
offset=(char far *)MK_FP(0xa000,(unsigned)result&0xffff);
outportb(0x3c4,0x0e);
temp=((result>>16)&0x0f)^0x02;
outportb(0x3c5,temp);
temp=*offset;
*offset=(char)color;
return;
}

int _getpixel(int x,int y,int xamx)
{
unsigned long int result=y;
char far *offset;
char temp;
result*=xmax;
result+=x;
offset=(char far *)MK_FP(0xa000,(unsigned)result&0xffff);
outportb(0x3c4,0x0e);
temp=((result>>16)&0x0f)^0x02;
outportb(0x3c5,temp);
temp=*offset;
return (int)temp;
}

void _closegraph()
{
union REGS regs;
regs.h.ah=0x00;
regs.h.al=0x03;
int86(0x10,&regs,&regs);
return;
}

void _outtextxy(int x,int y,char far *string,int color,int xmax)
{
register int i,j;
char huge *ptr;
int k=0;
while(string[k]!='\0')
{
ptr=(char huge *)MK_FP(0xf000,0xfa6e+(string[k]<<3));
for(i=0;i<8;i++)
for(j=0;j<8;j++)
if((ptr[i]&(0x80>>j))!=0)
_putpixel(x+(k<<3)+j,y+i,color,xmax);
k++;
}
return;
}

int _couttextxy(FILE *library,int x,int y,unsigned char far *string,char color,int xmax)
{
register int i,j;
unsigned long int locate;
int k=0;
char l=0,buffer[32];
if(library==NULL) return 0;
while(string[k]!='\0')
{
locate=(string[k]-161)*94+string[k+1]-161;
fseek(library,(long int)locate*32,SEEK_SET);
fread(buffer,32,sizeof(char),library);
k+=2;
for(i=0;i<16;i++)
for(j=0;j<2;j++)
{
l=buffer[i*2+j];
if((l&0x80)!=0) _putpixel(x+j*8,y+i,color,xmax);
if((l&0x40)!=0) _putpixel(x+j*8+1,y+i,color,xmax);
if((l&0x20)!=0) _putpixel(x+j*8+2,y+i,color,xmax);
if((l&0x10)!=0) _putpixel(x+j*8+3,y+i,color,xmax);
if((l&0x08)!=0) _putpixel(x+j*8+4,y+i,color,xmax);
if((l&0x04)!=0) _putpixel(x+j*8+5,y+i,color,xmax);
if((l&0x02)!=0) _putpixel(x+j*8+6,y+i,color,xmax);
if((l&0x01)!=0) _putpixel(x+j*8+7,y+i,color,xmax);
}
x+=16;
}
return 1;
}

#if defined(TVGAMOUSE)
char image[55];
char cursorshape[55]={14,14,14,14,0,14,
14,0,0,14,14,0,
0,0,14,14,0,0,
0,0,14,14,0,0,
0,0,0,14,14,0,
0,0,0,0,0,14,14,
0,0,0,0,0,0,0,14,
14,14,14,14,14,14,
14,14,14,14};

void _putimage(int x,int y)
{
int i,j,k=0;
for(j=y;j<y+10;j++)
for(i=x;i-x<j-y+1;i++)
{
_putpixel(i,j,image[k++]);
}
return;
}

void cursor(int x,int y)
{
static int cf=0,oldx=-1,oldy=-1;
if(!cf) cf=1;
else if(x!=oldx||y!=oldy) _putimage(oldx,oldy);
if(x!=oldx||y!=oldy) draw(x,y);
oldx=x;oldy=y;
return;
}
#endif

/*-------------------------------------------------------------------------*/


