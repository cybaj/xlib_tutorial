#include <X11/Xlib.h>
#include <unistd.h>

/* 색상 이름에 해당하는 픽셀값 반환하는 함수 */
unsigned long UsrColorPixel( Display*, char* );
/* 요청을 플러쉬하고 지정된 초만큼 지연시키는 함수 */
void    Pause( Display*, int );

static XPoint points[] = {{ 200, 50 },{ 100, 150 },{ 300, 150 },{ 200, 50 }};
static XSegment segs[] = {{ 10, 10, 390, 190 },{ 10, 190, 390, 10 }};
static char dash_list[] = { 20, 5, 10, 5 };

int main()
{
        Display *d;
        Window w; /* One TopLevel Window & Two Child Windows */
        GC gc;
        XGCValues gv;

        /* 서버와 접속하기 그리고 변수들을 초기화 */
        d = XOpenDisplay ( NULL );

        /* 자, 시작해볼까요? */

        w = XCreateSimpleWindow ( d, DefaultRootWindow( d ),
                                  100, 100, 400, 200, 1,
                                  BlackPixel(d,0), WhitePixel(d,0) );
        XMapWindow( d, w );
        Pause( d, 2 );



/*
 *      [1] 점(Point)을 찍어봅니다. XDrawPoint(s) 함수 사용
 */
        gv.foreground = UsrColorPixel( d, "red" );
        gc = XCreateGC( d, w, GCForeground, &gv );
        XDrawPoint ( d, w, gc, 200, 100 );
        Pause( d, 3 );

        gv.foreground = UsrColorPixel( d, "blue" );
        XChangeGC ( d, gc, GCForeground, &gv );
        XDrawPoints ( d, w, gc, points, 3, CoordModeOrigin );
        Pause( d, 3 );

/*
 *      고해상도에서는 뭐 거의 안보일 정도로 RED색의 작은 점 하나,
 *      그리고 나서 BLUE색의 점 3개를 찍고 있습니다. 정말로 집중해서
 *      보셔야 할 겁니다. 모니터가 더러우면 먼지와 구별이 안될지도... :)
 */
        XClearWindow( d, w );
        {
            int i, j;
            for ( j = 0; j < 200 ; j++ )
                for ( i = 0; i < 400 ; i++ )
                {
                    XDrawPoint( d, w, gc, i, j );
                    XFlush ( d );
                }
        }
        Pause( d, 3 );

/*
 *      BLUE 점으로 창 하나 가득히 칠해봅니다. XFlush 함수를 고의로 써서
 *      그 과정을 알아볼 수 있도록 하였습니다. 생각보다 빠르게 찍힐 겁니다.
 *      리눅스는 완전한 의미의 32비트 OS 이니까요.
 */



/*
 *      [2] 선(Line)을 그려봅니다.
 */

        XSetWindowBackground ( d, w, UsrColorPixel( d, "blue" ) );
        gv.foreground = WhitePixel( d, 0 );
        gv.background = UsrColorPixel( d, "red" );
        gv.line_width = 20;
        XChangeGC( d, gc, GCForeground|GCBackground|GCLineWidth, &gv );
        XDrawLine ( d, w, gc, 20, 20, 380, 180 ); /* CapButt */
        Pause ( d, 3 );

        gv.cap_style = CapRound;
        XChangeGC( d, gc, GCCapStyle, &gv );
        XClearWindow( d, w );
        XDrawLine ( d, w, gc, 380, 20, 20, 180 );
        Pause ( d, 3 );

        gv.cap_style = CapProjecting;
        XChangeGC( d, gc, GCCapStyle, &gv );
        XClearWindow( d, w );
        XDrawLine ( d, w, gc, 20, 20, 380, 180 );
        Pause ( d, 3 );

/*
 *      여기까지는 XDrawLine 함수를 사용하였습니다. 캡 스타일(Cap)이 서로
 *      어떻게 다른지 확인해 보십시요.  
 */

        XSetLineAttributes ( d, gc, 10, LineDoubleDash, CapRound, JoinRound );
        XSetDashes( d, gc, 0, dash_list, 4 );
        XClearWindow( d, w );
        XDrawSegments ( d, w, gc, segs, 2 );
        Pause ( d, 3 );

        XClearWindow ( d, w );
        XSetLineAttributes ( d, gc, 15, LineOnOffDash, CapButt, JoinBevel );
        XDrawLines( d, w, gc, points, 4, CoordModeOrigin );
        Pause ( d, 3 );

/*
 *      선끝점 스타일에는 CapButt, CapRound, CapProjecting 3 가지가 있습니다.
 *      선과 선이 만나는 방식에도 세 가지가 있습니다. JoinMiter, JoinRound,
 *      그리고 JoinBevel 이 그것이죠.
 *      중요한 것! 선의 스타일에는 그냥 LineSolid, LineOnOffDash, LineDouble-
 *      Dash 가 있습니다.
 *      XSetLineAttributes(), XSetDashes()는 연구과제입니다.
 */




/*
 *      [3] 이제 2차원으로 가봅시다. 사각형부터 시작!
 */

        XClearWindow( d, w );
        XSetLineAttributes ( d, gc, 5, LineSolid, CapButt, JoinRound );
        XDrawRectangle( d, w, gc, 50 /* X */, 50 /* Y */,
                                300 /* width */, 100 /* height */ );
        Pause( d, 3 );

        {
            XRectangle rect[7];
            int i;

            for ( i = 0; i < 7 ; i ++ )
            {
                rect[i].x = 10 + i * 50; rect[i].y = 20;
                rect[i].width = 40 ; rect[i].height = 150;
            }
            XClearWindow( d, w );
            XSetLineAttributes(d,gc,1,LineDoubleDash,CapProjecting,JoinMiter);
            XDrawRectangles ( d, w, gc, rect, 7 );
            Pause ( d, 3 );
        } 

/*
 *      자, XDrawRectangle(s)의 사용법을 아셨나요? 그렇다면 연구과제가 있스
 *      니다. 이들 대신에 XFillRectangle(s)를 써보십시요. 어떤 일이 일어납
 *      니까?
 */



/*
 *      [4] 둥그런 것도 그려봅시다.
 */

        {
            int i, radi;
            XArc arc[2];

            XClearWindow ( d, w );
            XSetLineAttributes(d,gc,10,LineSolid,CapRound,JoinRound);
            for ( radi = 0 ; radi <= 360 ; radi += 90 )
            {
                XDrawArc ( d, w, gc, 10, 10, 380, 180, 0 * 64, radi * 64 );
                Pause( d, 1 );
            }
            for ( i = 0 ; i < 2 ; i ++ ) {
                arc[i].x = 30 + 200 * i;
                arc[i].y = 30;
                arc[i].width = arc[i].height = 100;
                arc[i].angle1 = 0 * 64;
                arc[i].angle2 = 90 * ( i + 1 ) * 64;
            }
            XClearWindow ( d, w );
            XDrawArcs( d, w, gc, arc, 2 );
            Pause( d, 1 );
            XSetForeground( d, gc, UsrColorPixel(d,"yellow") );
            for ( i = 0 ; i < 2 ; i ++ ) {
                XClearWindow ( d, w );
                XSetArcMode ( d, gc, i == 0 ? ArcPieSlice : ArcChord );
                for ( radi = 0 ; radi <= 360 ; radi += 90 )
                {
                    XFillArc ( d, w, gc, 10, 10, 380, 180, 0 * 64, radi * 64 );
                    Pause( d, 1 );
                }
                XClearWindow( d, w );
                XFillArcs( d, w, gc, arc, 2 );
                Pause( d, 1 );
            }
        }



        /* GC, 창 파괴 & 서버와의 접속 해제 */
        XFreeGC( d, gc );
        XUnmapWindow( d, w );
        XDestroyWindow( d, w );

        XCloseDisplay( d );

        return 0;
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

        return ( c0.pixel );
}

void Pause( Display *d, int secs )
{
        XFlush ( d );
        sleep( secs );
}
