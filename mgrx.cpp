#include <string.h>
#include <mgrx.h>
#include <mgrxkeys.h>

int main()
{
    char *message = "Hello, MGRX world";
    int x, y;
    GrTextOption grt;
    GrEvent ev;

    GrSetMode( GR_default_graphics );
    GrEventInit();

    grt.txo_font = &GrDefaultFont;
    grt.txo_fgcolor.v = GrWhite();
    grt.txo_bgcolor.v = GrBlack();
    grt.txo_direct = GR_TEXT_RIGHT;
    grt.txo_xalign = GR_ALIGN_CENTER;
    grt.txo_yalign = GR_ALIGN_CENTER;
    grt.txo_chrtype = GR_BYTE_TEXT;

    GrBox( 0,0,GrMaxX(),GrMaxY(),GrWhite() );
    GrBox( 4,4,GrMaxX()-4,GrMaxY()-4,GrWhite() );

    x = GrMaxX()/2;
    y = GrMaxY()/2;
    GrDrawString( message,strlen( message ),x,y,&grt );

    GrEventWaitKeyOrClick(&ev);

    GrEventUnInit();
    return 0;
}
