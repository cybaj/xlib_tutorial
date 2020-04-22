/* 창의 색상 변화와 Geometry 변화 */

#include <X11/Xlib.h>
#include <stdio.h>
#include <unistd.h>

/* 함수 선언 */
unsigned long UsrColorPixel( Display*, char* );

int main()
{
        Display *d;
        Window w0, w1, w2; /* One TopLevel Window & Two Child Windows */
        unsigned long black_pixel;
        int w_X1, w_Y1, w_X2, w_Y2;    /* 두 자식창의 위치 좌표 */
        unsigned int width, height, I; /* 자식창의 폭 & 높이 */ 

        /* 서버와 접속하기 그리고 변수들을 초기화 */
        d = XOpenDisplay ( NULL );

        black_pixel = BlackPixel ( d, 0 );
        width = 200; height = 100;
        w_X1 = 10; w_Y1 = 10; w_X2 = width - 10; w_Y2 = height - 10;

        /* 자, 시작해볼까요? */
        printf( "I will make windows.\n" );
        sleep( 2 );


        /* 창 하나 그리고 자식창 2개 생성 */
        w0 = XCreateSimpleWindow ( d, DefaultRootWindow( d ),
                                  100, 100, width*2, height*2, 1,
                                  black_pixel, WhitePixel( d, 0 ) );
        w1 = XCreateSimpleWindow ( d, w0, w_X1, w_Y1, width, height, 1,
                                  black_pixel, UsrColorPixel( d, "magenta" ) );
        w2 = XCreateSimpleWindow ( d, w0, w_X2, w_Y2, width, height, 3,
                                  black_pixel, UsrColorPixel( d, "blue" ) );

        /* 창과 자식창을 화면상에 표시 */
        XMapWindow( d, w0 );
        XMapSubwindows( d, w0 );
        XFlush( d );

        printf( "Unmap & Map.\n" );
        sleep( 3 );



        /* 창 하나를 UNMAP, MAP */
        XUnmapWindow( d, w1 ); XFlush( d );
        sleep( 1 );
        XMapWindow( d, w1 ); XFlush ( d );
        printf( "I will change the color of windows.\n" );
        sleep( 3 );



        /* 창 하나의 색상을 변경 */
        XSetWindowBorder( d, w2, UsrColorPixel( d, "red" ) );
        XSetWindowBackground( d, w2, UsrColorPixel( d, "green" ) );
        XClearWindow( d, w2 );
        XFlush( d ); sleep( 1 );
        XSetWindowBackground( d, w0, UsrColorPixel( d, "yellow" ) );
        XClearWindow( d, w0 );
        XFlush( d );
        printf( "I will move windows.\n" );
        sleep( 3 );



        /* 창 하나씩 이동 */ 
        for ( ; w_X1 < width - 10 ; )
        {
                XMoveWindow( d, w1, w_X1++, w_Y1 );
                XFlush( d );
        }
        for ( ;  w_X1 > 10 ; )
        {
                XMoveWindow( d, w1, w_X1--, w_Y1 );
                XFlush( d );
        }
        for ( ;  w_Y2 > 10 ; )
        {
                XMoveWindow( d, w2, w_X2, w_Y2-- );
                XFlush( d );
        }
        for ( ;  w_Y2 < height - 10 ; )
        {
                XMoveWindow( d, w2, w_X2, w_Y2++ );
                XFlush( d );
        }
        printf( "I will change the size of windows.\n" );
        sleep( 3 );



        /* 창의 크기를 확장/축소 */
        XResizeWindow ( d, w1, width + 100, height + 50 );
        XMoveResizeWindow ( d, w2, w_X2 + 50, w_Y1 + 20, 
                                width - 100, height - 50 );
        /* XMoveResize !!! */
        XFlush ( d );
        printf( "At last, I will change the width of borders.\n" );
        sleep( 3 );



        /* 창의 테두리 확장 */
        for ( I = 1 ; I < 20 ; I++ )
        {
                XSetWindowBorderWidth ( d, w2, I );
                XFlush( d );
        }
        printf( "Jobs done. Merci.\n" );
        sleep( 3 );



        /* 창 파괴 & 서버와의 접속 해제 */
        XUnmapWindow( d, w0 );
        XUnmapSubwindows( d, w0 );
        XDestroySubwindows( d, w0 );
        XDestroyWindow( d, w0 );

        XCloseDisplay( d );


        return 0; /* 성공적으로 프로그램을 수행 */
}


/*

  UsrColorPixel() : 주어진 이름의 색상에 대한 기본 컬러맵의 픽셀값 반환

*/

unsigned long UsrColorPixel( display, name )
Display *display;
char *name;
{
        Colormap cmap;
        XColor c0, c1;

        cmap = DefaultColormap( display, 0 );

        XAllocNamedColor( display, cmap, name, &c0, &c1 );
        /* 여기서 우리는 c1 을 아직 이용하지 않습니다. */

        return ( c0.pixel );
}
