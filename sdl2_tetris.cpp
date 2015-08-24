/*==========================================================================
#     FileName :	sdl2_tetris.cpp
#  Description :
#       Author :	SiFe
#       E-Mail :	snakeleon@sina.com
#	  HomePage :	https://github.com/snakeleon
#      Version :	0.0.1
#   LastChange :	2015-03-10 14:21:41
#      History :
==========================================================================*/
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <iostream>


#define WIDTH	14
#define HEIGHT	24

#define Block  20   //方块大小
#define Shadow  1   //阴影宽度

int Now_Bricks[4][4];
int Show_Bricks[4][4];

int I[4][4] =
{
    { 0, 1, 0, 0 },
    { 0, 1, 0, 0 },
    { 0, 1, 0, 0 },
    { 0, 1, 0, 0 }
},
    L[4][4] =
{
    { 0, 1, 1, 0 },
    { 0, 0, 1, 0 },
    { 0, 0, 1, 0 },
    { 0, 0, 0, 0 }
},
    J[4][4] =
{
    { 0, 1, 1, 0 },
    { 0, 1, 0, 0 },
    { 0, 1, 0, 0 },
    { 0, 0, 0, 0 }
},
    S[4][4] =
{
    { 0, 0, 0, 0 },
    { 0, 1, 1, 0 },
    { 1, 1, 0, 0 },
    { 0, 0, 0, 0 }
},
    Z[4][4] =
{
    { 0, 0, 0, 0 },
    { 1, 1, 0, 0 },
    { 0, 1, 1, 0 },
    { 0, 0, 0, 0 }
},
    O[4][4] =
{
    { 0, 0, 0, 0 },
    { 0, 1, 1, 0 },
    { 0, 1, 1, 0 },
    { 0, 0, 0, 0 }
},
    T[4][4] =
{
    { 0, 0, 0, 0 },
    { 1, 1, 1, 0 },
    { 0, 1, 0, 0 },
    { 0, 0, 0, 0 }
};


//画立体块，i-阴影的像素宽度
void Draw3DBlock(SDL_Renderer *renderer,
                 int x, int y, int w, int h, int i,
                 Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    //阴影色初始化
    Uint8 tr=0, tg=0, tb=0,     //顶边
          lr=0, lg=0, lb=0,     //左边、右边
          br=0, bg=0, bb=0;     //下边
    //计算阴影色值 擦除时不做阴影
    if( (r+g+b)>0 )
    {
        tr = r>155? r : r+100;
        tg = g>155? g : g+100;
        tb = b>155? b : b+100;
        lr = r>205? r : r+50;
        lg = g>205? g : g+50;
        lb = b>205? b : b+50;
        br = r<50?  r : r-50;
        bg = g<50?  g : g-50;
        bb = b<50?  b : b-50;
    }

    //画底色
    boxRGBA(renderer, x, y, x+w, y+h, r, g, b, a);
    //画四边阴影
    //顶边阴影
    filledTrigonRGBA(renderer,
                     x+i,  y+i,  x+w-i,  y+i,  x+w,  y,
                     tr, tg, tb, a);
    filledTrigonRGBA(renderer,
                     x+i, y+i, x, y, x+w, y,
                     tr, tg, tb, a);
    //左边阴影
    filledTrigonRGBA(renderer,
                     x+i, y+i, x+i, y+h-i, x, y,
                     lr, lg, lb, a);
    filledTrigonRGBA(renderer,
                     x, y, x, y+h, x+i, y+h-i,
                     lr, lg, lb, a);
    //右边阴影
    filledTrigonRGBA(renderer,
                     x+w, y, x+w-i, y+i, x+w, y+h,
                     lr, lg, lb, a);
    filledTrigonRGBA(renderer,
                     x+w-i, y+i, x+w-i, y+h-i, x+w, y+h,
                     lr, lg, lb, a);
    //下边阴影
    filledTrigonRGBA(renderer,
                     x, y+h, x+i, y+h-i, x+w-i, y+h-i,
                     br, bg, bb, a);
    filledTrigonRGBA(renderer,
                     x, y+h, x+w, y+h, x+w-i, y+h-i,
                     br, bg, bb, a);
}

//画方块积木
void DrawBricks(SDL_Renderer *renderer,
                int x, int y, int bw, int i,
                Uint8 r, Uint8 g, Uint8 b, Uint8 a, int bricks[4][4])
{
    for ( int v=0; v<4; v++ )
        for (int h=0; h<4; h++)
            if(bricks[v][h]==1)
                Draw3DBlock(renderer, x+bw*h, y+bw*v, bw, bw, i, r, g, b, a);
}
//旋转方块积木(顺时针)Shadow
//void CWBricks(SDL_Renderer *renderer,
//                  int x, int y, int bw, int width,
//                  Uint8 r, Uint8 g, Uint8 b, Uint8 a, int bricks[4][4])
//{
//    int temp[4][4] = {};
//    for (int nh=0; nh<4; nh++)
//        for(int nv=0; nv<4; nv++)
//            temp[nh][nv] = bricks[3-nv][nh];
//    DrawBricks(renderer, x, y, bw, width, r, g , b, a, temp);
//}

//旋转积木（顺时针）
void CWBricks(int o_bricks[4][4], int n_bricks[4][4])
{
    int temp[4][4] = {};
    for (int nv=0; nv<4; nv++)
        for (int nh=0; nh<4; nh++)
            temp[nv][nh] = o_bricks[nv][nh];
    for (int nv=0; nv<4; nv++)
        for(int nh=0; nh<4; nh++)
            n_bricks[nv][nh] = temp[3-nh][nv];
}

void DrawBoard(SDL_Renderer *renderer, int w, int h, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    for( int i=0; i<(2+h); i++ )
        Draw3DBlock(renderer,
                    0, i*Block, Block, Block, 10,
                    r, g, b, a);
    for( int i=0; i<(2+h); i++ )
        Draw3DBlock(renderer,
                    Block+w*Block, i*Block, Block, Block, 10,
                    r, g, b, a);
    for( int i=0; i<w; i++ )
        Draw3DBlock(renderer,
                    i*Block+Block, 0, Block, Block, 10,
                    r, g, b, a);
    for( int i=0; i<w; i++)
        Draw3DBlock(renderer,
                    i*Block+Block, Block+h*Block, Block, Block, 10,
                    r, g, b, a);
}
/*
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{

    if ( SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 2;
    }

    SDL_Window *window = SDL_CreateWindow("Tetris", 20, 20, 800, 600, SDL_WINDOW_SHOWN);
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
    //SDL_SetRenderDrawColor(renderer,0x77, 0x77, 0x77, 0x77);
    SDL_RenderClear(renderer);
    DrawBricks(renderer, 0, 0, Block, Shadow, 120, 120, 120, 255, I);
    DrawBricks(renderer, 0, 100, Block, Shadow, 50, 120, 120, 255, L);
    DrawBricks(renderer, 0, 200, Block, Shadow, 190, 120, 120, 255, J);
    DrawBricks(renderer, 0, 300, Block, Shadow, 40, 150, 120, 255, S);
    DrawBricks(renderer, 0, 400, Block, Shadow, 0, 120, 60, 255, O);
    DrawBricks(renderer, 0, 500, Block, Shadow, 120, 120, 120, 255, Z);
    DrawBricks(renderer, 0, 600, Block, Shadow, 120, 0, 20, 255, T);
    CWBricks(Z, Show_Bricks);
    CWBricks(Show_Bricks, Now_Bricks);
    DrawBricks(renderer, 100, 0, Block, Shadow, 16, 130, 70, 255, Now_Bricks);
    SDL_RenderPresent(renderer);
    SDL_Delay(2000);
    DrawBricks(renderer, 0, 0, Block, Shadow, 0, 0, 0, 255, I);
    DrawBricks(renderer, 0, 200, Block, Shadow, 0, 0, 0, 255, J);
    SDL_RenderPresent(renderer);
    SDL_Delay(3000);
    DrawBoard(renderer, WIDTH, HEIGHT, 50, 60, 150, 255);

    SDL_RenderPresent(renderer);
    SDL_Delay(10000);
    return 0;
}				/* ----------  end of function main  ---------- */
