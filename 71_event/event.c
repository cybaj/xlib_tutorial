#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main( int argc, char* argv[] )
{
    Display *dpy;
    Window  w;
    Font    f;
    GC      gc;
    XEvent  xe;

    dpy = XOpenDisplay( NULL);
    w   = XCreateSimpleWindow( dpy, RootWindow( dpy, 0 ), 50, 50,
                                    100, 50, 5, BlackPixel( dpy, 0 ),
                                    WhitePixel( dpy, 0 ) );
    gc = XCreateGC( dpy, w, 0L, ( XGCValues * ) NULL );
    f  = XLoadFont( dpy, "fixed" );
    XSetFont( dpy, gc, f );
    XSetLineAttributes( dpy, gc, 5, LineSolid, 
                         CapRound, JoinRound );

    XSelectInput( dpy, w, ExposureMask | ButtonPressMask | EnterWindowMask 
                           | LeaveWindowMask );

    XMapWindow( dpy, w );

    XFlush( dpy );

    while ( True )
    {
            XNextEvent( dpy, &xe );

            switch ( xe.type )      {
            case Expose:
                printf("Expose 이벤트가 발생하였습니다.\n");
                XSetForeground( dpy, gc, BlackPixel( dpy, 0 ) );
                XDrawString( dpy, w, gc, 40, 30, "O K", 3 );
                break;
            case ButtonPress:
                printf("버튼을 누르셨습니다!\n");
                exit(1);
                break;
            case EnterNotify:
                printf("마우스가 창 안으로 들어왔습니다.\n");
                XSetForeground( dpy, gc, BlackPixel( dpy, 0 ) );
                XDrawRectangle( dpy, w, gc, 10, 10, 80, 30 );
                break;
            case LeaveNotify:
                printf("마우스가 창 밖으로 나갔습니다.\n");
                XSetForeground( dpy, gc, WhitePixel( dpy, 0 ) );
                XDrawRectangle( dpy, w, gc, 10, 10, 80, 30 );
                break;
            default:
                printf("모르는 이벤트입니다. 무시합니다.\n");
                break;
            }
    }
        return 0;
}
