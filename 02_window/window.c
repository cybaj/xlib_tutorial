#include <X11/Xlib.h>

main()
{
       Display *d ;
       Window   w, root ;

       d = XOpenDisplay(NULL) ;

       root = XDefaultRootWindow (d);
       w = XCreateSimpleWindow ( d, root, 50, 50, 400, 300,
                                 2, BlackPixel (d,0), WhitePixel(d,0) );
       XMapWindow (d, w);
       XFlush (d);

       getchar();

       XCloseDisplay (d);
}
