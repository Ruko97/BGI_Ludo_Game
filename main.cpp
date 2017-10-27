#include <graphics.h>
#include <stdio.h>
#include <iostream>
using namespace std;
#define HOMEBOARDSIZE 210
#define HOMEBOARDDISTANCE 105
#define EACHSQUAREDISTANCE 35
#define DARKYELLOW COLOR(189, 183, 107)
#define CHARCOAL COLOR(54, 69, 79)
#define BOGI 0
#define BOARD_FILL_STYLE INTERLEAVE_FILL
#define COUNTER_FILL_STYLE SOLID_FILL
#define COUNTER_RADIUS 14
#define DARKYELLOWCOLOR 20
#define HOME_COURT_SQUARE_RADIUS 85

struct point {
    int x, y;
};

struct player {
    int markers[4];
    char name[100];
    int color;
};

typedef struct point Point;
typedef struct player Player;

void* board_image;

Point getPointOfLocation( int location ) {
    Point output;

    if( location>=1 && location<=5 ) {      /* Normal locations */
        location--;
        output.x = 390;
        output.y = 535-location*35;
    } else if( location<=11 ) {
        location-=6;
        output.x = 355-location*35;
        output.y = 360;
    } else if( location<=13 ) {
        location-=11;
        output.x = 180;
        output.y = 360-location*35;
    } else if( location<=18 ) {
        location-=13;
        output.x = 180+location*35;
        output.y = 290;
    } else if( location<=24 ) {
        location-=19;
        output.x = 390;
        output.y = 255-location*35;
    } else if( location<=26 ) {
        location-=24;
        output.x = 390+location*35;
        output.y = 80;
    } else if( location<=31 ) {
        location-=26;
        output.x = 460;
        output.y = 80+location*35;
    } else if( location<=37 ) {
        location-=32;
        output.x = 495+location*35;
        output.y = 290;
    } else if( location<=39 ) {
        location-=37;
        output.x = 670;
        output.y = 290+location*35;
    } else if( location<=44 ) {
        location-=39;
        output.x = 670-location*35;
        output.y = 360;
    } else if( location<=50 ) {
        location-=45;
        output.x = 460;
        output.y = 395+location*35;
    } else if( location<=52 ) {
        location-=50;
        output.x = 460-location*35;
        output.y = 570;
    } else if( location<=57 ) {     /* Start of pucca gutis */
        location-=53;
        output.x = 425;
        output.y = 535-location*35;
    } else if( location<=62 ) {
        location-=58;
        output.x = 215+location*35;
        output.y = 325;
    } else if( location<=67 ) {
        location-=63;
        output.x = 425;
        output.y = 115+location*35;
    } else if( location<=72 ) {
        location-=68;
        output.x = 635-location*35;
        output.y = 325;
    } else if( location==73 ) {     /* start of gutis in center */
        output.x = 425;
        output.y = 360;
    } else if( location==74 ) {
        output.x = 390;
        output.y = 325;
    } else if( location==75 ) {
        output.x = 425;
        output.y = 290;
    } else if( location==76 ) {
        output.x = 460;
        output.y = 325;
    } else if( location==77 ) {     /* start of green home points */
        output.x = 215+10;
        output.y = 430+10;
    } else if( location==78 ) {
        output.x = 320-10;
        output.y = 430+10;
    } else if( location==79 ) {
        output.x = 215+10;
        output.y = 535-10;
    } else if( location==80 ) {
        output.x = 320-10;
        output.y = 535-10;
    } else if( location==81 ) {     /* start of red home points */
        output.x = 215+10;
        output.y = 115+10;
    } else if( location==82 ) {
        output.x = 320-10;
        output.y = 115+10;
    } else if( location==83 ) {
        output.x = 215+10;
        output.y = 220-10;
    } else if( location==84 ) {
        output.x = 315-10;
        output.y = 220-10;
    } else if( location==85 ) {     /* start of blue home points */
        output.x = 530+10;
        output.y = 115+10;
    } else if( location==86 ) {
        output.x = 635-10;
        output.y = 115+10;
    } else if( location==87 ) {
        output.x = 530+10;
        output.y = 220-10;
    } else if( location==88 ) {
        output.x = 635-10;
        output.y = 220-10;
    } else if( location==89 ) {     /* start of yellow home points */
        output.x = 530+10;
        output.y = 430+10;
    } else if( location==90 ) {
        output.x = 635-10;
        output.y = 430+10;
    } else if( location==91 ) {
        output.x = 530+10;
        output.y = 540-10;
    } else if( location==92 ) {
        output.x = 635-10;
        output.y = 540-10;
    }

    return output;
}

void initLudoBoard() {
    #if BOGI
    setcolor(CHARCOAL);
    setfillstyle(BOARD_FILL_STYLE, CHARCOAL);
    rectangle(180, 80, 705, 605);
    floodfill(200, 100, CHARCOAL);
    #endif
    /*Each home board is 210px
        each square is 35px
        distance between one home board to the other is 105 px*/
    setcolor(LIGHTRED);
    setfillstyle(BOARD_FILL_STYLE ,RED);
    rectangle(180, 80, 180+HOMEBOARDSIZE-1, 80+HOMEBOARDSIZE-1);
    floodfill(190, 90, LIGHTRED);
    circle(180+105, 80+105, HOME_COURT_SQUARE_RADIUS);
    setcolor(LIGHTBLUE);
    setfillstyle(BOARD_FILL_STYLE, BLUE);
    rectangle(495+1, 80, 495+HOMEBOARDSIZE, 80+HOMEBOARDSIZE-1);
    floodfill(500, 100, LIGHTBLUE);
    circle(495+1+105, 80+105, HOME_COURT_SQUARE_RADIUS);
    setcolor(LIGHTGREEN);
    setfillstyle(BOARD_FILL_STYLE, GREEN);
    rectangle(180, 395+1, 180+HOMEBOARDSIZE-1, 395+HOMEBOARDSIZE);
    floodfill(200, 400, LIGHTGREEN);
    circle(180+105, 395+1+105, HOME_COURT_SQUARE_RADIUS);
    setcolor(YELLOW);
    setfillstyle(BOARD_FILL_STYLE, DARKYELLOW);
    rectangle(495+1, 395+1, 495+HOMEBOARDSIZE, 395+HOMEBOARDSIZE);
    floodfill(500, 400, YELLOW);
    circle(495+1+105, 395+105, HOME_COURT_SQUARE_RADIUS);

    setcolor(WHITE);
    line(390, 80, 390, 605);
    line(495, 80, 495, 605);
    line(180, 290, 705, 290);
    line(180, 395, 705, 395);
    line(390, 80, 495, 80);
    line(390, 605, 495, 605);
    line(180, 290, 180, 395);
    line(705, 290, 705, 395);
    line(390, 290, 495, 395);
    line(495, 290, 390, 395);
    int i,j;
    for(i=35; i<105; i+=35) {
        line(390+i, 80, 390+i, 290);
        line(390+i, 395, 390+i, 605);
        line(180, 290+i, 390, 290+i);
        line(495, 290+i, 705, 290+i);
    }
    for(i=35; i<210; i+=35) {
        line(390, 80+i, 495, 80+i);
        line(180+i, 290, 180+i, 395);
    }
    for(i=35; i<210; i+=35) {
        line(390, 395+i, 495, 395+i);
        line(495+i, 290, 495+i, 395);
    }

    setfillstyle(BOARD_FILL_STYLE, GREEN);
    floodfill(415, 555, WHITE);
    floodfill(450, 370, WHITE);
    setfillstyle(BOARD_FILL_STYLE, RED);
    floodfill(240, 300, WHITE);
    floodfill(410, 335, WHITE);
    setfillstyle(BOARD_FILL_STYLE, BLUE);
    floodfill(480, 135, WHITE);
    floodfill(450, 310, WHITE);
    setfillstyle(BOARD_FILL_STYLE, DARKYELLOW);
    floodfill(650, 375, WHITE);
    floodfill(480, 335, WHITE);
    for(i=35;i<210;i+=35)
    {
        setfillstyle(BOARD_FILL_STYLE, GREEN);
        floodfill(435, 390+i, WHITE);
        setfillstyle(BOARD_FILL_STYLE, RED);
        floodfill(185+i, 330, WHITE);
        setfillstyle(BOARD_FILL_STYLE, BLUE);
        floodfill(435, 85+i, WHITE);
        setfillstyle(BOARD_FILL_STYLE, DARKYELLOW);
        floodfill(480+i, 330, WHITE);
    }

    board_image = malloc(imagesize(0, 0, getmaxx(), getmaxy()));
    getimage(0, 0, getmaxx(), getmaxy(), board_image);
}

/**




              60 61 62   74 Center
        ...   8  7  6       73
                        5   .
             79   80    4   .
              Green     3   .    Yellow
              Court     2   54    Court
             77   78    1   53
                        52  51  50
*/
void drawOneMarker( int location, int color, int offset=0 ) {
    int border_color, counter_color;

    if( color!=YELLOW ) {
            border_color=color+8;
            counter_color=color;
    } else {
        border_color=color;
        counter_color = DARKYELLOW;
    }

    setcolor(border_color);
    setfillstyle(COUNTER_FILL_STYLE, counter_color);
    #if BOGI
    if( location>=1 && location<=5 ) {
        circle(408+offset, 552+35-location*35, COUNTER_RADIUS);
        floodfill(408+offset, 552+35-location*35, border_color);
    } else if ( location<=11 ) {
        location-=6;
        circle(390-17-location*35+offset, 395-17, COUNTER_RADIUS);
        floodfill(390-17-location*35+offset, 395-17, border_color);
    } else if( location<=13 ) {
        location-=11;
        circle(390-17-5*35+offset, 395-17-location*35, COUNTER_RADIUS);
        floodfill(390-17-5*35+offset, 395-17-location*35, border_color);
    } else if ( location<=18 ) {
        location-=13;
        circle( 198+location*35+offset ,308, COUNTER_RADIUS );
        floodfill( 198+location*35+offset ,308, border_color );
    } else if( location<=24 ) {
        location-=19;
        circle(390+17+offset, 290-17-location*35, COUNTER_RADIUS);
        floodfill(390+17+offset, 290-17-location*35, border_color);
    } else if( location<=26 ) {
        location-=24;
        circle(407+location*35+offset, 98, COUNTER_RADIUS);
        floodfill(407+location*35+offset, 98, border_color);
    } else if( location<=31 ) {
        location-=26;
        circle( 477+offset, 98+location*35, COUNTER_RADIUS );
        floodfill(477+offset, 98+location*35, border_color);
    } else if( location<=37 ) {
        location-=32;
        circle(495+17+offset+location*35, 308, COUNTER_RADIUS);
        floodfill(495+17+offset+location*35, 308, border_color);
    } else if( location<=39 ) {
        location-=37;
        circle(687+offset, 308+location*35, COUNTER_RADIUS);
        floodfill(687+offset, 308+location*35, border_color);
    } else if( location<=44 ) {
        location-=39;
        circle(687+offset-location*35, 378, COUNTER_RADIUS);
        floodfill(687+offset-location*35, 378, border_color);
    } else if( location<=50 ) {
        location-=45;
        circle(460+17+offset, 395+17+location*35, COUNTER_RADIUS);
        floodfill(460+17+offset, 395+17+location*35, border_color);
    } else if( location<=52 ) {
        location-=50;
        circle(477+offset-location*35, 587, COUNTER_RADIUS);
        floodfill(477+offset-location*35, 587, border_color);
    } else if( location<=57 ) {
        location-=53;
        circle(425+17+offset, 535+17-location*35, COUNTER_RADIUS);
        floodfill(425+17+offset, 535+17-location*35, border_color);
    } else if( location<=62 ) {
        location-=58;
        circle(215+17+offset+location*35, 325+17, COUNTER_RADIUS);
        floodfill(215+17+offset+location*35, 325+17, border_color);
    } else if( location<=67 ) {
        location-=63;
        circle(425+17+offset, 115+17+location*35, COUNTER_RADIUS);
        floodfill(425+17+offset, 115+17+location*35, border_color);
    } else if( location<=72 ) {
        location-=68;
        circle(635+17+offset-location*35, 325+17, COUNTER_RADIUS);
        floodfill(635+17+offset-location*35, 325+17, border_color);
    }
    #endif // BOGI
    Point target = getPointOfLocation(location);
    printf("%d %d\n", target.x, target.y);
    circle( target.x+offset+17, target.y+17, COUNTER_RADIUS );
    floodfill( target.x+offset+17, target.y+17, border_color );
}

void drawMarkers( Player players[] ) {
    int i, j;
    for( i=0; i<4; i++ ) {
        for( j=0; j<4; j++ ) {
            drawOneMarker( players[i].markers[j], players[i].color );
        }
    }
}

void initPlayer( Player* player, int color ) {
    int i, offset;
    player->color = color;

    if( color==GREEN ) offset=77;
    else if( color==RED ) offset=81;
    else if( color==BLUE ) offset=85;
    else if( color==YELLOW ) offset=89;

    for( i=0; i<4; i++ ) {
            player->markers[i] = i+offset;
    }
}

void initGame( Player players[], Player* presentPlayer ) {
    int colors[] = {GREEN, RED, BLUE, YELLOW};
    int i;

    for( i=0; i<4; i++ ) {
        initPlayer( &players[i], colors[i] );
    }

    presentPlayer = &players[0];
}

void drawLudoBoard( Player players[] ) {
    putimage(0, 0, board_image, COPY_PUT);
    drawMarkers( players );
}

int main() {
    int gd = DETECT, gm;
    int x, y;
    Player players[4];
    Player presentPlayer;
    int location = 71;
    int color = BLUE;
    initwindow(900, 700);
    initLudoBoard();
    initGame( players, &presentPlayer );





    while( location<=95 ) {
        clearviewport();
        drawLudoBoard(players);
        //test.location++;
        drawOneMarker(location, color);
        delay(1000);
        location++;

        getmouseclick(WM_LBUTTONDOWN, x, y);
        cout << "The mouse was clicked at: ";

        cout << "x=" << x;

        cout << " y=" << y << endl;
    }

    closegraph();
}
