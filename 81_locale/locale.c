#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
/*
#include <locale.h>
*/
#include <X11/Xlocale.h>
#include <stdlib.h>

void DrawCenteredMbString ( Display *, Window, XFontSet, GC, char*, int, int,
                                int, int, int );

int
main (argc, argv)
        int argc;
        char *argv[];
{
        Display *dpy;
        Window  w;
        XFontSet fontset;
        char **missing_charsets;
        int num_missing_charsets;
        char *default_string;
        int i;
        GC      gc;
        XEvent  xe;

        char *program_name = argv[0];

        if ( setlocale (LC_ALL,"") == NULL )       {
                (void) fprintf (stderr, "%s: cannot set locale.\n",
                program_name );
                exit (1);
        }

        if ( !XSupportsLocale () ) {
                (void) fprintf (stderr,"%s: X does not support locale %s.\n",
                program_name, setlocale( LC_ALL, NULL ) );
                exit (1);
        }

        if ( XSetLocaleModifiers("") == NULL )    {
                (void) fprintf (stderr,
                        "%s: Warning: cannot set locale modifiers.\n",
                        program_name);
        }

        dpy = XOpenDisplay ( NULL);
        w   = XCreateSimpleWindow ( dpy, RootWindow( dpy, 0 ), 50, 50,
                                        200, 50, 5, BlackPixel( dpy, 0 ),
                                        WhitePixel( dpy, 0 ) );
        gc = XCreateGC ( dpy, w, 0L, ( XGCValues * ) NULL );

        fontset = XCreateFontSet (dpy, "-*-*-*-*-*-*-16-*-*-*-*-*-*-*",
                        &missing_charsets, &num_missing_charsets,
                        &default_string);
        if ( num_missing_charsets > 0 ) {
                (void) fprintf (stderr,
                        "%s: The following charsets are missing:\n",
                        program_name);
                for ( i=0; i < num_missing_charsets; i++ )
                        (void)fprintf (stderr, "%s:   %s\n", program_name,
                                missing_charsets[i]);
                (void) fprintf (stderr, "%s: The string is %s", program_name,
                                default_string);
                (void) fprintf (stderr, 
                                "%s: of any characters from those sets.\n",
                                program_name);
                XFreeStringList (missing_charsets);
        }

        XSetLineAttributes ( dpy, gc, 5, LineSolid, CapRound, JoinRound );

        XSelectInput ( dpy, w, ExposureMask | ButtonPressMask 
                        | EnterWindowMask | LeaveWindowMask );

        XMapWindow ( dpy, w );

        XFlush ( dpy );

        while ( True )
        {
                XNextEvent ( dpy, &xe );

                switch ( xe.type )      {

                case Expose:
                        printf ("Expose 이벤트가 발생했습니다.\n");
                        XSetForeground ( dpy, gc, BlackPixel( dpy, 0 ) );
                        DrawCenteredMbString ( dpy, w, fontset, gc, 
                                        "안녕 Hello",
                                        20, 0, 0, 200, 50 );
                        break;
                case ButtonPress:
                        printf ("버튼을 누르셨습니다!\n");
                        exit (1);
                        break;
                case EnterNotify:
                        printf ("마우스가 창 안으로 들어왔습니다.\n");
                        XSetForeground ( dpy, gc, BlackPixel( dpy, 0 ) );
                        XDrawRectangle ( dpy, w, gc, 0, 0, 200, 50 );
                        break;
                case LeaveNotify:
                        printf ("마우스가 창 밖으로 나갔습니다.\n");
                        XSetForeground ( dpy, gc, WhitePixel( dpy, 0 ) );
                        XDrawRectangle ( dpy, w, gc, 0, 0, 200, 50 );
                        break;
                default:
                        printf ("모르는 이벤트입니다. 무시합니다.\n");
                        break;
                }
        }
        return 0;
}

void
DrawCenteredMbString (dpy, w, fontset, gc, str, num_bytes, x, y, width, height )
        Display *dpy;
        Window w;
        XFontSet fontset;
        GC gc;
        char *str;
        int num_bytes;
        int x,y, width, height;
{
        XRectangle boundingbox;
        XRectangle dummy;
        int originx, originy;

        (void) XmbTextExtents (fontset, str, num_bytes, &dummy, &boundingbox);

        originx = x + ( width - boundingbox.width )/2 - boundingbox.x;
        originy = y + ( height - boundingbox.height)/2 - boundingbox.y;

        XmbDrawString (dpy, w, fontset, gc, originx, originy, str, num_bytes);
}
