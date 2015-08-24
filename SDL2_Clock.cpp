/*==========================================================================
#     FileName :	SDL2_Clock.cpp
#  Description :
#       Author :	SiFe
#       E-Mail :	snakeleon@sina.com
#	  HomePage :	https://github.com/snakeleon
#      Version :	0.0.1
#   LastChange :	2015-06-15 14:02:44
#      History :
==========================================================================*/
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <math.h>
#include <conio.h>
#include <windows.h>

#define WIDTH	400
#define HEIGHT	400
#define I_ZOOM  HEIGHT/360

void DrawHand(SDL_Renderer *renderer, int hour, int minute, int second)
{
    double a_hour, a_min, a_sec;
    int x_hour, y_hour,
        x_min,  y_min,
        x_sec,  y_sec;
    a_sec = second  * 2 * M_PI / 60;
    a_min = minute  * 2 * M_PI / 60 + a_sec / 60;
    a_hour= hour    * 2 * M_PI / 12 + a_min / 12;

    x_sec = WIDTH/2  + (int)(HEIGHT/2 * 0.95 * sin(a_sec));
    y_sec = HEIGHT/2 - (int)(HEIGHT/2 * 0.95 * cos(a_sec));
    x_min = WIDTH/2  + (int)(HEIGHT/2 * 0.85 * sin(a_min));
    y_min = HEIGHT/2 - (int)(HEIGHT/2 * 0.85 * cos(a_min));
    x_hour= WIDTH/2  + (int)(HEIGHT/2 * 0.65 * sin(a_hour));
    y_hour= HEIGHT/2 - (int)(HEIGHT/2 * 0.65 * cos(a_hour));

    thickLineRGBA(renderer, WIDTH/2, HEIGHT/2, x_hour, y_hour, I_ZOOM*5,
                  0, 0, 255, 255);
    thickLineRGBA(renderer, WIDTH/2, HEIGHT/2, x_min, y_min, I_ZOOM*4,
                  0, 255, 0, 255);
    thickLineRGBA(renderer, WIDTH/2, HEIGHT/2, x_sec, y_sec, I_ZOOM*1,
                  255, 0, 0, 255);
}

void CleanDrawHand(SDL_Renderer *renderer, int hour, int minute, int second)
{
    double a_hour, a_min, a_sec;
    int x_hour, y_hour,
        x_min,  y_min,
        x_sec,  y_sec;
    a_sec = second  * 2 * M_PI / 60;
    a_min = minute  * 2 * M_PI / 60 + a_sec / 60;
    a_hour= hour    * 2 * M_PI / 12 + a_min / 12;

    x_sec = WIDTH/2  + (int)(HEIGHT/2 * 0.90 * sin(a_sec));
    y_sec = HEIGHT/2 - (int)(HEIGHT/2 * 0.90 * cos(a_sec));
    x_min = WIDTH/2  + (int)(HEIGHT/2 * 0.80 * sin(a_min));
    y_min = HEIGHT/2 - (int)(HEIGHT/2 * 0.80 * cos(a_min));
    x_hour= WIDTH/2  + (int)(HEIGHT/2 * 0.65 * sin(a_hour));
    y_hour= HEIGHT/2 - (int)(HEIGHT/2 * 0.65 * cos(a_hour));

    thickLineRGBA(renderer, WIDTH/2, HEIGHT/2, x_hour, y_hour, I_ZOOM*5,
                  0, 0, 0, 255);
    thickLineRGBA(renderer, WIDTH/2, HEIGHT/2, x_min, y_min, I_ZOOM*4,
                  0, 0, 0, 255);
    thickLineRGBA(renderer, WIDTH/2, HEIGHT/2, x_sec, y_sec, I_ZOOM*1,
                  0, 0, 0, 255);
}

void DrawPlate(SDL_Renderer *renderer)
{
    int w, l, x1, x2, y1, y2;
    filledCircleRGBA(renderer, WIDTH/2, HEIGHT/2, HEIGHT/2, 255, 154, 69, 255);
    filledCircleRGBA(renderer, WIDTH/2, HEIGHT/2, HEIGHT/2-I_ZOOM*10, 0, 0, 0, 255);
    for(int i=0; i<60; i++)
    {
        if(i%5==0)
        {
            w=4*I_ZOOM;
            l=15*I_ZOOM;
        }
        else
        {
            w=2*I_ZOOM;
            l=10*I_ZOOM;
        }
        x1=HEIGHT/2*sin(i*6*M_PI/180)+WIDTH/2;
        y1=HEIGHT/2*cos(i*6*M_PI/180)+HEIGHT/2;
        x2=(HEIGHT/2-l)*sin(i*6*M_PI/180)+WIDTH/2;
        y2=(HEIGHT/2-l)*cos(i*6*M_PI/180)+HEIGHT/2;
        thickLineRGBA(renderer, x1, y1, x2, y2, w, 111, 123, 75, 255);
    }
}

/* void DrawLogo(SDL_Renderer *renderer)
 * {
 *     SDL_Color logoColor = { 255, 0, 0, 255 };
 *     TTF_Font *logoFont = TTF_OpenFont("C:/Windows/Fonts/KhmerUIb.ttf",500);
 *     SDL_Surface *Logo = TTF_RenderUTF8_Blended(logoFont,"HAMILTON", logoColor);
 *     SDL_Texture *textLogo = SDL_CreateTextureFromSurface(renderer, Logo);
 *     SDL_Rect logoXY = { WIDTH/2-55, 70, 120, 30 };
 *     SDL_RenderCopy(renderer, textLogo, NULL, &logoXY);
 *     SDL_FreeSurface(Logo);
 *     SDL_DestroyTexture(textLogo);
 *     TTF_CloseFont(logoFont);
 * }
 */


/*
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{

    SYSTEMTIME t;
    if ( SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 2;
    }

    if(TTF_Init() == -1)
    {
        std::cout << "TTF_Init: " << TTF_GetError() << std::endl;
        return 7;
    }

    SDL_Window *window = SDL_CreateWindow("Tetris", 80, 80, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return 3;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return 4;
    }
    SDL_RenderClear(renderer);


    SDL_Color logoColor = { 255, 0, 0, 255 };
    TTF_Font *logoFont = TTF_OpenFont("C:/Windows/Fonts/KhmerUIb.ttf",500);
    SDL_Surface *Logo = TTF_RenderUTF8_Blended(logoFont,"HAMILTON", logoColor);
    SDL_Texture *textLogo = SDL_CreateTextureFromSurface(renderer, Logo);
    SDL_Rect logoXY = { WIDTH/2-60, 70, 120, 30 };
    DrawPlate(renderer);

    bool bQuit = false;
    SDL_Event event;
    while(!bQuit)
    {
        while(SDL_PollEvent(&event))
            switch(event.type)
            {
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        bQuit = true;
                    }
                    break;
                case SDL_QUIT:
                    bQuit = true;
                    break;
                default:
                    break;
            }
        GetLocalTime(&t);
        filledCircleRGBA(renderer, WIDTH/2, HEIGHT/2, HEIGHT/2-I_ZOOM*10, 0, 0, 0, 255);
        DrawHand(renderer, t.wHour, t.wMinute, t.wSecond);
        filledCircleRGBA(renderer, WIDTH/2, HEIGHT/2, I_ZOOM*8, 255, 160, 255, 240);
        SDL_RenderCopy(renderer, textLogo, NULL, &logoXY);
        SDL_RenderPresent(renderer);
        //SDL_Delay(3000);
        // CleanDrawHand(renderer, t.wHour, t.wMinute, t.wSecond);
        //SDL_Delay(3000);
    }
    SDL_FreeSurface(Logo);
    SDL_DestroyTexture(textLogo);
    TTF_CloseFont(logoFont);
    TTF_Quit();
    SDL_Quit();
    return 0;
}				/* ----------  end of function main  ---------- */
