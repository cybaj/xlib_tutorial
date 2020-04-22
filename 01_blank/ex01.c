#include <X11/Xlib.h>
#include <unistd.h> 
#include <assert.h>

#define NIL (0)

void main()
{
	Display *d = XOpenDisplay(0);
        assert(d);
        Window w = XCreateWindow(d, DefaultRootWindow(d), 0, 0, 
  			       200, 100, 0, 
  			       CopyFromParent, CopyFromParent, CopyFromParent,
  			       NIL, 0);
        XMapWindow(d, w);
        XFlush(d);
	sleep(3);
	XCloseDisplay(d);
}
