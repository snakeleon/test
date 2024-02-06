/*==========================================================================
#     FileName :	SDL_Clock.cpp
#  Description :	CLOCK
#       Author :	SiFe
#       E-Mail :	snakeleon@gmail.com
#	  HomePage :	https://github.com/snakeleon
#      Version :	0.0.1
#   LastChange :	2020-02-11 19:49:39
#      History :
==========================================================================*/
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#ifdef  _WIN32
#include <windows.h>
#elif defined __linux
#include <time.h>
#endif
#include <stdio.h>
#include <string.h>


#define WIDTH   400
#define HEIGHT  400
#define Dia int(WIDTH/2)

#define I_ZOOM  HEIGHT/360

const int center[2] = { WIDTH / 2 , HEIGHT / 2 };

int getCenterX(int width)
{
    return width/2;
}

int GetCenterY(int height)
{
    return height/2;
}

int lenSecond = WIDTH / 2 ;

void DrawHand(SDL_Renderer *renderer, int hour, int minute, int second)
{
    double a_hour,  a_min,   a_sec,  a_sec1;
    int    x_hour,  y_hour,
           x_min,   y_min,
           x_sec,   y_sec,
           x1_sec,  y1_sec;
    a_sec  = second  * 2 * M_PI / 60;
    a_sec1 = (second > 30 ? second-30 : second+30) * 2 * M_PI / 60;
    a_min  = minute  * 2 * M_PI / 60 + a_sec / 60;
    a_hour = hour    * 2 * M_PI / 12 + a_min / 12;

    x_sec  = WIDTH/2  + (int)(HEIGHT/2 * 0.95 * sin(a_sec));
    y_sec  = HEIGHT/2 - (int)(HEIGHT/2 * 0.95 * cos(a_sec));
    x1_sec = WIDTH/2  + (int)(HEIGHT/2 * 0.20 * sin(a_sec1));
    y1_sec = HEIGHT/2 - (int)(HEIGHT/2 * 0.20 * cos(a_sec1));
    x_min  = WIDTH/2  + (int)(HEIGHT/2 * 0.85 * sin(a_min));
    y_min  = HEIGHT/2 - (int)(HEIGHT/2 * 0.85 * cos(a_min));
    x_hour = WIDTH/2  + (int)(HEIGHT/2 * 0.65 * sin(a_hour));
    y_hour = HEIGHT/2 - (int)(HEIGHT/2 * 0.65 * cos(a_hour));

    aalineRGBA(renderer, WIDTH/2, HEIGHT/2, x_hour, y_hour,
                  0, 0, 255, 255);
    aalineRGBA(renderer, WIDTH/2, HEIGHT/2, x_min, y_min,
                  0, 255, 0, 255);
    aalineRGBA(renderer, x1_sec, y1_sec, x_sec, y_sec,
                  255, 0, 0, 255);

    filledCircleRGBA(renderer, WIDTH/2, HEIGHT/2, I_ZOOM*8, 255, 160, 255, 240);
}

void DrawPlate(SDL_Renderer *renderer)
{
    int w=5, l=8;
    for (int i=0; i<8; i++)
    {
        aacircleRGBA(renderer, WIDTH/2, HEIGHT/2, HEIGHT/2-i, 255, 154, 69, 255);
    }

    for (int i = 0 ; i < 60 ; i++ )
    {
        int x1 = int(WIDTH/2) + int(Dia * cos( i * 6 * M_PI/180 )) ;
        int y1 = int(HEIGHT/2) + int(Dia * sin( i * 6 * M_PI/180 )) ;
        int x2 = int(WIDTH/2) +  int((Dia-l) * cos( i * 6 * M_PI/180 )) ;
        int y2 = int(HEIGHT/2) + int((Dia-l) * sin( i * 6 * M_PI/180 )) ;
//        for (int j=-2 ; j<2 ; j++)
//        {
//            int o_x1 = j+ x1;
//            int o_y1 = j+ y1;
//            int o_x2 = j+ x2;
//            int o_y2 = j+ y2;
//            aalineRGBA(renderer, o_x1, o_y1, o_x2, o_y2, 111, 123, 75, 255);
//
//        }
        aalineRGBA(renderer, x1, y1, x2, y2, 111, 123, 75, 255);
     }

}

char *Week(int n_week)
{
    char *c_week = (char *)malloc(sizeof("AAA"));
    switch(n_week)
    {
        case 0:
            strcpy(c_week,"SUN");
            break;
        case 1:
            strcpy(c_week,"MON");
            break;
        case 2:
            strcpy(c_week,"TUE");
            break;
        case 3:
            strcpy(c_week,"WED");
            break;
        case 4:
            strcpy(c_week,"THU");
            break;
        case 5:
            strcpy(c_week,"FRI");
            break;
        case 6:
            strcpy(c_week,"SAT");
            break;
    }
    return c_week;
}

int main ( int argc, char *argv[] )
{
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

    SDL_Window *window = SDL_CreateWindow("SDL_TEST", 80, 80, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return 3;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL)
    {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return 4;
    }
    SDL_RenderClear(renderer);


#ifdef _WIN32
    SYSTEMTIME t;
#elif defined __linux
    time_t now;
    struct tm *t = NULL;
#endif

    bool Quit = false;
    SDL_Event event;
    while(!Quit)
    {
        while(SDL_PollEvent(&event))
            switch(event.type)
            {
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_ESCAPE)
                        Quit = true;
                    break;
                case SDL_QUIT:
                    Quit = true;
                    break;
                default:
                    break;
            }
        SDL_Surface *ClockPlate   = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 0);
        SDL_Renderer *PlateRender = SDL_CreateSoftwareRenderer(ClockPlate);
        DrawPlate(PlateRender);
        SDL_Texture *TexturePlate = SDL_CreateTextureFromSurface(renderer, ClockPlate);
        SDL_FreeSurface(ClockPlate);
        SDL_DestroyRenderer(PlateRender);

        SDL_Color DayColor = { 255, 0, 255, 255 };
        SDL_Rect DayXY = { WIDTH/2+75, HEIGHT/2-18, 80, 36 };

#ifdef _WIN32
        TTF_Font *DayFont = TTF_OpenFont("Digital-Regular.ttf", 60);
#elif defined __linux
        TTF_Font *DayFont = TTF_OpenFont("/home/snakeleon/.local/share/fonts/DIGITAL-Regular.ttf", 60);
#endif

        if (!DayFont)
        {
            std::cout << "ERROR for Open TTF_Font : " << "DayFont" << std::endl;
            return 21;
        }

        SDL_Surface *SurfaceDay = NULL;
        SDL_Texture *TextureDay = NULL;
        char Day[6];

        SDL_Color NumColor = { 0, 255, 255, 255 };
        SDL_Rect NumXY     = { WIDTH/2-50, 280, 100, 40 };

#ifdef _WIN32
        TTF_Font *NumFont = TTF_OpenFont("Digital-Regular.ttf", 30);
#elif defined __linux
        TTF_Font *NumFont = TTF_OpenFont("/home/snakeleon/.local/share/fonts/Digital-Regular.ttf", 30);
#endif

        if (!NumFont)
        {
            std::cout << "ERROR for Open TTF_Font : " << NumFont << std::endl;
            return 22;
        }

        SDL_Surface *NumClock   = NULL;
        SDL_Texture *TextureNum = NULL;
        char Num[9];

        SDL_Color LogoColor = { 255, 0, 0, 255 };
        SDL_Rect LogoXY     = { WIDTH/2-80, 70, 160, 40 };

#ifdef _WIN32
        TTF_Font *LogoFont = TTF_OpenFont("KhmerUIb.ttf", 30);
#elif defined __linux
        TTF_Font *LogoFont = TTF_OpenFont("/home/snakeleon/.local/share/fonts/Hack-Regular.ttf", 30);
#endif

        if (!LogoFont)
        {
            std::cout << "ERROR for Open TTF_Font : "<< LogoFont << std::endl;
            return 23;
        }

        SDL_Surface *SurfaceLogo = TTF_RenderUTF8_Blended(LogoFont, "HAMILTON", LogoColor);
        SDL_Texture *TextureLogo = SDL_CreateTextureFromSurface(renderer, SurfaceLogo);
        SDL_FreeSurface(SurfaceLogo);
        TTF_CloseFont(LogoFont);

#ifdef _WIN32
        GetLocalTime(&t);
#elif defined __linux
        time(&now);
        t=localtime(&now);
#endif

        SDL_RenderCopy(renderer, TexturePlate, NULL, NULL);
        SDL_RenderCopy(renderer, TextureLogo, NULL, &LogoXY);

#ifdef _WIN32
        sprintf(Day, "%.2d  %s", t.wDay, Week(t.wDayOfWeek));
#elif defined __linux
        sprintf(Day, "%.2d  %s", t->tm_mday, Week(t->tm_wday));
#endif

        SurfaceDay = TTF_RenderUTF8_Blended(DayFont, Day, DayColor);
        TextureDay = SDL_CreateTextureFromSurface(renderer, SurfaceDay);
        SDL_FreeSurface(SurfaceDay);
        SDL_RenderCopy(renderer, TextureDay, NULL, &DayXY);
        SDL_DestroyTexture(TextureDay);

#ifdef _WIN32
        sprintf(Num, "%.2d:%.2d:%.2d", t.wHour, t.wMinute, t.wSecond);
#elif defined __linux
        sprintf(Num, "%.2d:%.2d:%.2d", t->tm_hour, t->tm_min, t->tm_sec);
#endif

        NumClock   = TTF_RenderUTF8_Blended(NumFont, Num, NumColor);
        TextureNum = SDL_CreateTextureFromSurface(renderer, NumClock);
        SDL_FreeSurface(NumClock);
        SDL_RenderCopy(renderer, TextureNum, NULL, &NumXY);
        SDL_DestroyTexture(TextureNum);

#ifdef _WIN32
        DrawHand(renderer, t.wHour, t.wMinute, t.wSecond);
#elif defined __linux
        DrawHand(renderer, t->tm_hour, t->tm_min, t->tm_sec);
#endif

        SDL_RenderPresent(renderer);
        SDL_DestroyTexture(TextureLogo);
        SDL_DestroyTexture(TexturePlate);
        TTF_CloseFont(NumFont);

    }

    return 0;
}
