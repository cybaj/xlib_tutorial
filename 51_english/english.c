#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <unistd.h>

int main()
{
       Display         *dpy;
       Window          w;
       Font            f;
       GC              gc;
       XSetWindowAttributes xswa;

       xswa.override_redirect = True;
       dpy = XOpenDisplay ( NULL);
       w   = XCreateSimpleWindow( dpy, RootWindow( dpy, 0 ), 50, 50,
                                       400, 300, 5, BlackPixel( dpy, 0 ),
                                               WhitePixel( dpy, 0 ) );
       XChangeWindowAttributes ( dpy, w, CWOverrideRedirect, &xswa );

       XMapWindow ( dpy, w );

       /* ----------------- 여기서부터가 본격적으로 중요한 부분 ----- */
       gc = XCreateGC( dpy, w, 0L, ( XGCValues * ) NULL );     /* [1] */
       f  = XLoadFont( dpy, "fixed" );                         /* [2] */
       XSetFont ( dpy, gc, f );                                /* [3] */

       /* 폰트 등록이 된 GC 를 가지고 전경색으로 문자열 출력 */
       XDrawString( dpy, w, gc, 100, 130, 
                       "Hello, Linuxers! Never Seen :)", 16 ); /* [4] */ 
       /* ----------------------------------------------------------- */

       XFlush( dpy );
       getchar();

       /* 뒷처리 */
       XUnloadFont( dpy, f );
       XFreeGC( dpy, gc );
       XDestroyWindow( dpy, w );
       XCloseDisplay( dpy );
}
