#include "graphics.h"
#include <conio.h>
#include <stdlib.h>
#include <memory.h>

int gcW = 20, gcColor[] = {DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN,
    LIGHTRED, LIGHTMAGENTA,MAGENTA, YELLOW};
struct tetris {
    int _pool[16][32], (*pool)[32], tmap[8][4][16];
    int x, y, s, st, t;
}gt;

void trsInit() {
    int sp[8][4] = {{15,4369},{23,785,116,547},{71,275,113,802},
        {39,305,114,562},{54,561},{99,306},{51,51},{-1}};
    int *p, i, j, b;
    for (p = sp[0]; *p >= 0; ++p) if ( *p == 0 ) *p = p[-2];
    gt.pool = &gt._pool[4];
    for (j = 0; j < 7; ++j)
        for (i = 0; i < 4; ++i)
            for (b = 0; b < 16; ++b)
                gt.tmap[j+1][i][b] = (sp[j][i] & 1) * (j + 1),
                    sp[j][i] >>= 1;
    memset(gt._pool, -1, sizeof(gt._pool));
    for (i = 0; i < 10; ++i)
        memset(&gt.pool[i], 0, sizeof(int[21]));
    return ;
}

int trsCopy(int sp[], int x, int y, int c) {
    int m[] = {0,32,64,96,1,33,65,97,2,34,66,98,3,35,67,99}, i, cx, cy;
    for (i = 0; i < 16; ++i) if (sp[i]) {
        cx = x + (m[i] >> 5), cy = y + (m[i] & 31);
        if (gt.pool[cx][cy]) if (c == 2) gt.pool[cx][cy] = 0; else return 0;
        if (c==1) gt.pool[cx][cy] = sp[i];
    }
    return 1;
}

int trsScene() {
    int x, y = 0;
    gt.s = random(7) + 1, gt.st = gt.t = 0;
    gt.x = 4, gt.y = 0;
    for (--gt.t ; ; delay(10), --gt.t) {
        int k = 0;
        while (kbhit()) {
            k = getch();
            if (k == 27) return 0;
            if (k == 'A' || k == 'a') {
                if (trsCopy(gt.tmap[gt.s][gt.st], gt.x-1, gt.y, 0)) --gt.x;
            } else if (k == 'D' || k == 'd') {
                if (trsCopy(gt.tmap[gt.s][gt.st], gt.x+1, gt.y, 0)) ++gt.x;
            } else if (k == 'W' || k == 'w') {
                if (trsCopy(gt.tmap[gt.s][(gt.st+1) % 4], gt.x, gt.y, 0))
                    gt.st = (gt.st+1) % 4;
            }
        }
        if (k == 'S' || k == 's' || gt.t < 0) {
            if (trsCopy(gt.tmap[gt.s][gt.st], gt.x, gt.y+1, 0))++gt.y,gt.t=50;
            else {
                trsCopy(gt.tmap[gt.s][gt.st], gt.x, gt.y, 1);
                for (--y; y > 0; --y) {
                    for (x = 0; gt.pool[x][y] > 0; ++x);
                    if (gt.pool[x][y] < 0)
                        for (k = y++; k > 0; --k)
                            for (x = 0; gt.pool[x][0] >= 0; ++x)
                                gt.pool[x][k] = gt.pool[x][k-1];
                }
                return 1;
            }
        }
        trsCopy(gt.tmap[gt.s][gt.st], gt.x, gt.y, 1);
        for (x = 0; gt.pool[x][0] >= 0; ++x) {
            for (y = 1; gt.pool[x][y] >= 0; ++y) {
                setfillstyle(1, gcColor[gt.pool[x][y]]);
                bar(201 + x*gcW, 1 + y*gcW, 200 + gcW + x*gcW, gcW + y*gcW);
            }
        }
        trsCopy(gt.tmap[gt.s][gt.st], gt.x, gt.y, 2);
    }
}

int main() {
    int g = DETECT, m = 0;
    initgraph(&g, &m, "");
    randomize();
    trsInit();
    while (trsScene());
    return 0;
}
