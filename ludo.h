#include <graphics.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
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
#define COUNTER_RADIUS 15
#define DARKYELLOWCOLOR 20
#define HOME_COURT_SQUARE_RADIUS 85
#define TEXT_SIZE 3
#define DIE_SIZE 45
#define DIE_POINT_RADIUS 5
#define FILL_ELLIPSE(X, Y, Z) fillellipse(X, Y, Z, Z)

struct point
{
    int x, y;
};

struct player
{
    int markers[4];
    char name[100];
    int color;
    int die;
    int movesToBeMade[4];
    int presentNoOfMove, countersAtHome, countersAtEnd;
};

typedef struct point Point;
typedef struct player Player;

void* board_image;

Player players[4];
Player* presentPlayer;

#if BOGI
/** counterLocation[i][0] contains the location occupied, counterLocation[i][1] */
int counterLocations[93][2];
#endif // BOGI

Point getLocationOfPlayersName( Player* player )
{
    Point output;

    if( player->color==GREEN ) output.x=35, output.y=425;
    else if( player->color==RED ) output.x=35, output.y=110;
    else if( player->color==BLUE ) output.x=740, output.y=110;
    else if( player->color==YELLOW ) output.x=740, output.y=425;

    return output;
}

Point getLocationOfPlayersDie( Player* player )
{
    Point output;

    if( player->color==GREEN ) output.x=70, output.y=460;
    else if( player->color==RED ) output.x=70, output.y=145;
    else if( player->color==BLUE ) output.x=775, output.y=145;
    else if( player->color==YELLOW ) output.x=775, output.y=460;

    return output;
}

Point getPointOfLocation( int location )
{
    Point output;

    if( location>=1 && location<=5 )        /* Normal locations */
    {
        location--;
        output.x = 390;
        output.y = 535-location*35;
    }
    else if( location<=11 )
    {
        location-=6;
        output.x = 355-location*35;
        output.y = 360;
    }
    else if( location<=13 )
    {
        location-=11;
        output.x = 180;
        output.y = 360-location*35;
    }
    else if( location<=18 )
    {
        location-=13;
        output.x = 180+location*35;
        output.y = 290;
    }
    else if( location<=24 )
    {
        location-=19;
        output.x = 390;
        output.y = 255-location*35;
    }
    else if( location<=26 )
    {
        location-=24;
        output.x = 390+location*35;
        output.y = 80;
    }
    else if( location<=31 )
    {
        location-=26;
        output.x = 460;
        output.y = 80+location*35;
    }
    else if( location<=37 )
    {
        location-=32;
        output.x = 495+location*35;
        output.y = 290;
    }
    else if( location<=39 )
    {
        location-=37;
        output.x = 670;
        output.y = 290+location*35;
    }
    else if( location<=44 )
    {
        location-=39;
        output.x = 670-location*35;
        output.y = 360;
    }
    else if( location<=50 )
    {
        location-=45;
        output.x = 460;
        output.y = 395+location*35;
    }
    else if( location<=52 )
    {
        location-=50;
        output.x = 460-location*35;
        output.y = 570;
    }
    else if( location<=57 )         /* Start of pucca gutis */
    {
        location-=53;
        output.x = 425;
        output.y = 535-location*35;
    }
    else if( location<=62 )
    {
        location-=58;
        output.x = 215+location*35;
        output.y = 325;
    }
    else if( location<=67 )
    {
        location-=63;
        output.x = 425;
        output.y = 115+location*35;
    }
    else if( location<=72 )
    {
        location-=68;
        output.x = 635-location*35;
        output.y = 325;
    }
    else if( location==73 )         /* start of gutis in center */
    {
        output.x = 425;
        output.y = 360;
    }
    else if( location==74 )
    {
        output.x = 390;
        output.y = 325;
    }
    else if( location==75 )
    {
        output.x = 425;
        output.y = 290;
    }
    else if( location==76 )
    {
        output.x = 460;
        output.y = 325;
    }
    else if( location==77 )         /* start of green home points */
    {
        output.x = 215+10;
        output.y = 430+10;
    }
    else if( location==78 )
    {
        output.x = 320-10;
        output.y = 430+10;
    }
    else if( location==79 )
    {
        output.x = 215+10;
        output.y = 535-10;
    }
    else if( location==80 )
    {
        output.x = 320-10;
        output.y = 535-10;
    }
    else if( location==81 )         /* start of red home points */
    {
        output.x = 215+10;
        output.y = 115+10;
    }
    else if( location==82 )
    {
        output.x = 320-10;
        output.y = 115+10;
    }
    else if( location==83 )
    {
        output.x = 215+10;
        output.y = 220-10;
    }
    else if( location==84 )
    {
        output.x = 320-10;
        output.y = 220-10;
    }
    else if( location==85 )         /* start of blue home points */
    {
        output.x = 530+10;
        output.y = 115+10;
    }
    else if( location==86 )
    {
        output.x = 635-10;
        output.y = 115+10;
    }
    else if( location==87 )
    {
        output.x = 530+10;
        output.y = 220-10;
    }
    else if( location==88 )
    {
        output.x = 635-10;
        output.y = 220-10;
    }
    else if( location==89 )         /* start of yellow home points */
    {
        output.x = 530+10;
        output.y = 430+10;
    }
    else if( location==90 )
    {
        output.x = 635-10;
        output.y = 430+10;
    }
    else if( location==91 )
    {
        output.x = 530+10;
        output.y = 540-10;
    }
    else if( location==92 )
    {
        output.x = 635-10;
        output.y = 540-10;
    }

    return output;
}

void drawTextBoxes( Player* player )
{
    Point analysing = getLocationOfPlayersName(player);
    setcolor( WHITE );

    outtextxy( analysing.x, analysing.y, player->name );
}

void drawAllTextBoxes()
{
    int i;
    for( i=0; i<4; i++ )
    {
        drawTextBoxes(&players[i]);
    }
}

void initLudoBoard()
{
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
    for(i=35; i<105; i+=35)
    {
        line(390+i, 80, 390+i, 290);
        line(390+i, 395, 390+i, 605);
        line(180, 290+i, 390, 290+i);
        line(495, 290+i, 705, 290+i);
    }
    for(i=35; i<210; i+=35)
    {
        line(390, 80+i, 495, 80+i);
        line(180+i, 290, 180+i, 395);
    }
    for(i=35; i<210; i+=35)
    {
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
    for(i=35; i<210; i+=35)
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

    drawAllTextBoxes();

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
void drawOneMarker( int location, int color, int offset=0 )
{
    int border_color, counter_color;

    if( color!=YELLOW )
    {
        border_color=color+8;
        counter_color=color;
    }
    else
    {
        border_color=color;
        counter_color = DARKYELLOW;
    }

    setcolor(border_color);
    setfillstyle(COUNTER_FILL_STYLE, counter_color);

    Point target = getPointOfLocation(location);
    //printf("%d %d\n", target.x, target.y);
    circle( target.x+offset+17, target.y+17, COUNTER_RADIUS );
    floodfill( target.x+offset+17, target.y+17, border_color );
}

void drawMarkers()
{
    int i, j;
    for( i=0; i<4; i++ )
    {
        for( j=0; j<4; j++ )
        {
            drawOneMarker( players[i].markers[j], players[i].color );
        }
    }
}

void initPlayer( Player* player, int color )
{
    int i, offset;
    player->color = color;
    player->presentNoOfMove = -1;

    if( color==GREEN ) offset=77;
    else if( color==RED ) offset=81;
    else if( color==BLUE ) offset=85;
    else if( color==YELLOW ) offset=89;

    for( i=0; i<4; i++ )
    {
        player->markers[i] = i+offset;
        strcpy( player->name, "ADF" );
        player->countersAtHome=4;
        player->countersAtEnd=0;
    }
}

void initGame()
{
    srand(time(NULL));
    int colors[] = {GREEN, RED, BLUE, YELLOW};
    int i;

    for( i=0; i<4; i++ )
    {
        initPlayer( &players[i], colors[i] );
        players[i].die = 0;
    }

    presentPlayer = &players[0];
    settextstyle(COMPLEX_FONT, HORIZ_DIR, TEXT_SIZE);
}



void drawDice( Player* player )
{
    Point analysing = getLocationOfPlayersDie(player);
    setcolor( WHITE );
    setfillstyle( SOLID_FILL, WHITE );

    rectangle( analysing.x, analysing.y, analysing.x+DIE_SIZE, analysing.y+DIE_SIZE );
    floodfill(analysing.x+1, analysing.y+1, WHITE);
    int number = player->die;
    setfillstyle( SOLID_FILL, BLACK );
    switch( number )
    {
    case 1:
        FILL_ELLIPSE(analysing.x+22, analysing.y+22, DIE_POINT_RADIUS);
        break;
    case 2:
        FILL_ELLIPSE(analysing.x+10, analysing.y+10, DIE_POINT_RADIUS);
        FILL_ELLIPSE(analysing.x+35, analysing.y+35, DIE_POINT_RADIUS);
        break;
    case 3:
        FILL_ELLIPSE(analysing.x+10, analysing.y+10, DIE_POINT_RADIUS);
        FILL_ELLIPSE(analysing.x+22, analysing.y+22, DIE_POINT_RADIUS);
        FILL_ELLIPSE(analysing.x+35, analysing.y+35, DIE_POINT_RADIUS);
        break;
    case 4:
        FILL_ELLIPSE(analysing.x+12, analysing.y+12, DIE_POINT_RADIUS);
        FILL_ELLIPSE(analysing.x+33, analysing.y+12, DIE_POINT_RADIUS);
        FILL_ELLIPSE(analysing.x+12, analysing.y+33, DIE_POINT_RADIUS);
        FILL_ELLIPSE(analysing.x+33, analysing.y+33, DIE_POINT_RADIUS);
        break;
    case 5:
        FILL_ELLIPSE(analysing.x+10, analysing.y+10, DIE_POINT_RADIUS);
        FILL_ELLIPSE(analysing.x+22, analysing.y+22, DIE_POINT_RADIUS);
        FILL_ELLIPSE(analysing.x+35, analysing.y+35, DIE_POINT_RADIUS);
        FILL_ELLIPSE(analysing.x+35, analysing.y+10, DIE_POINT_RADIUS);
        FILL_ELLIPSE(analysing.x+10, analysing.y+35, DIE_POINT_RADIUS);
        break;
    case 6:
        FILL_ELLIPSE(analysing.x+10, analysing.y+10, DIE_POINT_RADIUS);
        FILL_ELLIPSE(analysing.x+35, analysing.y+10, DIE_POINT_RADIUS);
        FILL_ELLIPSE(analysing.x+10, analysing.y+22, DIE_POINT_RADIUS);
        FILL_ELLIPSE(analysing.x+35, analysing.y+22, DIE_POINT_RADIUS);
        FILL_ELLIPSE(analysing.x+10, analysing.y+35, DIE_POINT_RADIUS);
        FILL_ELLIPSE(analysing.x+35, analysing.y+35, DIE_POINT_RADIUS);
        break;
    }
}

void drawDiceOfAllPlayers()
{
    int i;

    for( i=0; i<4; i++ )
    {
        drawDice(&players[i]);
    }
}

void drawLudoBoard()
{
    putimage(0, 0, board_image, COPY_PUT);
    drawMarkers();
    drawAllTextBoxes();
    drawDiceOfAllPlayers();
}

int rollDice( Player* player )
{
    int interim=rand()%14;
    if( interim<8 ) player->die=(interim/2)+1;
    else player->die=(interim+7)/3;
    player->movesToBeMade[++(player->presentNoOfMove)] = player->die;
    return player->die;
}

void putBackToStart( Player* whoseToBeReturned, int serialToBeReturned )
{
    int color = whoseToBeReturned->color;
    int i, j, offset;
    bool found;

    if( color==GREEN ) offset=77;
    else if( color==RED ) offset=81;
    else if( color==BLUE ) offset=85;
    else if( color==YELLOW ) offset=89;

    for( i=offset; i<offset+4; i++ )
    {
        found=false;
        for( j=0; j<4; j++ )
        {
            if( whoseToBeReturned->markers[j]==i )
            {
                found=true;
            }
        }
        if( !found )
        {
            whoseToBeReturned->markers[serialToBeReturned]=i;
        }
    }
}

void eatCounter( int location, Player* self )
{
#if 1
    int i, j;
    for( i=0; i<4; i++ )
    {
        if( players[i].color != self->color )
        {
            for( j=0; j<4; j++ )
            {
                //if( !(location==1 || location==14 || location==27 || location==40 || location>72) ) {
                if( players[i].markers[j] == location && !(location==1 || location==14 || location==27 || location==40 || location>72) )
                {
                    printf("i=%d\t\tj=%d\n", i, j);
                    putBackToStart(&players[i], j);
                }
                //}
            }
        }
    }
#endif // BOGI


}

void moveCounter( Player* player, int counterSerial )
{
    int color = player->color;
    int moves = player->movesToBeMade[(player->presentNoOfMove)--];
    int *targetMarker = &(player->markers[counterSerial]);
    switch( color )
    {
    case GREEN:
        if( *targetMarker<=72)
        {
            if( *targetMarker>=46 && *targetMarker<=51 && *targetMarker+moves>51 )
            {
                if( *targetMarker+moves!=57 ) *targetMarker = *targetMarker+moves+1;
                else
                {
                    *targetMarker=73;
                    player->countersAtEnd++;
                }
            }
            else if( *targetMarker>=53 && *targetMarker<=57 )
            {
                if( *targetMarker+moves==58 )
                {
                    *targetMarker=73;
                    player->countersAtEnd++;
                }
                else if( *targetMarker+moves<58 )
                {
                    *targetMarker+=moves;
                }
            }
            else
            {
                *targetMarker+=moves;
            }
        }
        break;

    case RED:
        if( *targetMarker<=72 )
        {
            if( *targetMarker>46 && *targetMarker<=52 && *targetMarker+moves>52 )
            {
                *targetMarker = *targetMarker+moves-52;
            }
            else if ( *targetMarker>6 && *targetMarker<=12 && *targetMarker+moves>12 )
            {
                if( *targetMarker+moves!=18 ) *targetMarker = *targetMarker+moves+45;
                else
                {
                    *targetMarker==74;
                    player->countersAtEnd++;
                }
            }
            else if ( *targetMarker>=58 && *targetMarker<=62 )
            {
                if( *targetMarker+moves==63 )
                {
                    *targetMarker=74;
                    player->countersAtEnd++;
                }
                else if ( *targetMarker+moves<63 )
                {
                    *targetMarker+=moves;
                }
            }
            else
            {
                *targetMarker+=moves;
            }
        }
        break;

    case BLUE:
        if( *targetMarker<=72 )
        {
            if( *targetMarker>46 && *targetMarker<=52 && *targetMarker+moves>52 )
            {
                *targetMarker = *targetMarker+moves-52;
            }
            else if ( *targetMarker>19 && *targetMarker<=25 && *targetMarker+moves>25 )
            {
                if( *targetMarker+moves!=31 ) *targetMarker = *targetMarker+moves+37;
                else
                {
                    *targetMarker=75;
                    player->countersAtEnd++;
                }
            }
            else if ( *targetMarker>=63 && *targetMarker<=67 )
            {
                if( *targetMarker+moves==68 )
                {
                    *targetMarker=75;
                    player->countersAtEnd++;
                }
                else if ( *targetMarker+moves<68 )
                {
                    *targetMarker+=moves;
                }
            }
            else
            {
                *targetMarker+=moves;
            }
        }
        break;

    case YELLOW:
        if( *targetMarker<=72 )
        {
            if( *targetMarker>46 && *targetMarker<=52 && *targetMarker+moves>52 )
            {
                *targetMarker = *targetMarker+moves-52;
            }
            else if ( *targetMarker>32 && *targetMarker<=38 && *targetMarker+moves>38 )
            {
                if( *targetMarker+moves!=44 ) *targetMarker = *targetMarker+moves+29;
                else
                {
                    *targetMarker=76;
                    player->countersAtEnd++;
                }
            }
            else if ( *targetMarker>=68 && *targetMarker<=72 )
            {
                if( *targetMarker+moves==73 )
                {
                    *targetMarker=76;
                    player->countersAtEnd++;
                }
                else if ( *targetMarker+moves<73 )
                {
                    *targetMarker+=moves;
                }
            }
            else
            {
                *targetMarker+=moves;
            }
        }
        break;
    }

    eatCounter( *targetMarker, player );
}

void moveCounterFromHomeToPlay( Player* player, int location )
{
    int color = player->color;
    int counterToBeMoved, i, target;
    for( i=0; i<4; i++ )
    {
        if( player->markers[i]==location )
        {
            counterToBeMoved = i;
            break;
        }
    }
    if( color==GREEN ) target=1;
    else if( color==RED ) target=14;
    else if( color==BLUE ) target=27;
    else if( color==YELLOW ) target=40;

    player->markers[counterToBeMoved] = target;
}
