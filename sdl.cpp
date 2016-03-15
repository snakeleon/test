#include <stdio.h>
#include <stdlib.h>
#include <sdl2/sdl.h>
#include <sdl2/sdl_image.h>

#undef main

int main()
{
    SDL_Window *p = NULL;/*窗口*/
    SDL_Renderer *px = NULL;/*渲染器*/
    SDL_Surface *t = NULL;
    SDL_Texture *ps = NULL;/*硬件加速器*/
    SDL_Init(SDL_INIT_EVERYTHING);
    p = SDL_CreateWindow("Hello World!", 100, 100, 600, 500, SDL_WINDOW_RESIZABLE);/*能让我们绘制的窗口前两个参数控制窗口位置，然后是窗口大小 再然后是位标（falg）*/
    t = IMG_Load("2.jpg");
    px = SDL_CreateRenderer(p, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);/*渲染器 第一个位标表示显卡 -1表示从显卡中挑一个 第二个表示以显示器的刷新率来刷新画面*/
    ps = SDL_CreateTextureFromSurface(px, t);/*使用硬件加速*/
    SDL_FreeSurface(t );
    SDL_RenderClear(px); /*清空屏幕*/
    SDL_RenderCopy(px, ps , NULL, NULL); /*显示*/
    SDL_RenderPresent(px );/*更新屏幕*/
    SDL_Delay(20000);
    SDL_DestroyTexture(ps);/*释放内存*/
    SDL_DestroyRenderer(px );
    SDL_DestroyWindow(p );
    SDL_Quit();
    return 0;
}
