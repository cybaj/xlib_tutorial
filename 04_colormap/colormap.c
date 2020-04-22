#include <X11/Xlib.h>
#include <unistd.h> 

int main()
{
       Display *d;
       Window Root, w;
       /* 색상값을 알아낼 때 쓸 변수들 */
       Colormap CMap;
       XColor color, color_exact;
       unsigned long White, Black, Blue, Yellow;

       d = XOpenDisplay ( NULL );

       /* 원하는 색상 검정/파랑을 얻는 부분 */
       CMap = XDefaultColormap ( d, 0 );
       XAllocNamedColor ( d, CMap, "white", &color, &color_exact );
       White = color.pixel;
       // XAllocNamedColor ( d, CMap, "blue",  &color, &color_exact );
       // Blue  = color.pixel;
       XAllocNamedColor ( d, CMap, "yellow", &color, &color_exact );
       Yellow = color.pixel;

       Root = DefaultRootWindow ( d );
       w = XCreateSimpleWindow ( d, Root, 100, 100, 600, 400,
                                       10, White, Yellow );

       XMapWindow ( d, w );
       XFlush ( d );
       sleep(10);

       XDestroyWindow ( d, w );
       XCloseDisplay ( d );

       return 0;
}
