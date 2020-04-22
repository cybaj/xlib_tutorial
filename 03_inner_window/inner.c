#include <X11/Xlib.h>
#include <unistd.h> 

int main()
{
    Display *d ;
    Window root, p, w1, w2, w3 ; 
    unsigned long Black, White ;

    d = XOpenDisplay (NULL);

    /* 주 프로그램 부분 시작 */
    root = DefaultRootWindow(d);
    Black = BlackPixel(d,0);
    White = WhitePixel(d,0);

    p  = XCreateSimpleWindow (d, root, 100, 100,
                                    600, 400, 2, Black, White );
    w1 = XCreateSimpleWindow (d, p, 50, 50,
                                    200, 150, 2, Black, White );
    w2 = XCreateSimpleWindow (d, p, 200, 100,
                                    200, 150, 2, Black, White );
    w3 = XCreateSimpleWindow (d, p, 350, 200,
                                    200, 150, 2, Black, White );
    XMapWindow(d, p);
    XMapWindow(d, w1);
    XMapWindow(d, w2);
    XMapWindow(d, w3);

    XFlush(d);
    sleep(3);

    XDestroySubwindows(d, p);
    XDestroyWindow(d, p);
    /* 주 프로그램 부분 끝 */

    XCloseDisplay (d);

    return 0;
}
