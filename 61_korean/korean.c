#include <X11/Xlib.h>
#include <stdio.h>
#include <unistd.h>

// int convert_ks_to_display(char *str, XChar2b *buf, int n);
/* 한텀 소스에서 인용 */

int convert_ks_to_display(char *str, XChar2b *buf, int n)
{
  int i, j;

  for (i = 0, j = 0; i < n;) {
    buf[j].byte1 = str[i] - 0x80;
    buf[j].byte2 = str[i+1] - 0x80;
    i += 2, j++;
  }
  return j;
}

int main()
{
        Display *dpy;
        int screen;
        Window w;
        Font hanFont, engFont;
        GC gc;
        XChar2b HStrBuf[256];
        int n;

        dpy = XOpenDisplay( NULL );

        screen = DefaultScreen( dpy );
        w = XCreateSimpleWindow(dpy, DefaultRootWindow(dpy), 0, 0, 400, 300, 2, 
                        BlackPixel( dpy, screen ), WhitePixel( dpy, screen ));
        XMapWindow( dpy, w );
        XFlush(dpy);

        sleep(4);       /* 왜 넣었을까요? */

        gc = XCreateGC ( dpy, w, 0L, (XGCValues *) NULL );
        // hanFont = XLoadFont ( dpy, 
        //                 "-daewoo-mincho-*-r-normal--16-*-*-*-c-*-*-*" );
        hanFont = XLoadFont ( dpy, 
                        "hangle16st" );

        engFont = XLoadFont ( dpy, "fixed" );

        XSetFont( dpy, gc, hanFont );
        n = convert_ks_to_display("안녕하세요리눅서", HStrBuf, 10);
        XDrawString16(dpy, w, gc, 100, 100, HStrBuf, n);
        sleep(4);       /* 왜 넣었을까요? */

        XSetFont( dpy, gc, engFont );
        XDrawString(dpy, w, gc, 100, 150, "Welcome to Linux!", 17 );

        XFlush(dpy);
        getchar();
}

