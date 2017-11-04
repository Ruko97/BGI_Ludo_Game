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
#define GREEN_COUNTER 1
#define RED_COUNTER 8
#define BLUE_COUNTER 64
#define YELLOW_COUNTER 512

struct point
{
    int x, y;
};

struct player
{
    char name[100];
    int color;
    int markers[4];
    int countersAtHome, countersAtEnd;
};

typedef struct point Point;
typedef struct player Player;

const int colors[] = { GREEN, RED, BLUE, YELLOW };
const int counterValues[] = { GREEN_COUNTER, RED_COUNTER, BLUE_COUNTER, YELLOW_COUNTER };
void* board_image;

Player players[4];
int presentPlayer;

unsigned int locations[93];

int presentPlayersDie;

#if BOGI
/** counterLocation[i][0] contains the location occupied, counterLocation[i][1] */
int counterLocations[93][2];
#endif // BOGI

int getCorrespondingCounterValueForColor(int color)
{
    if (color == GREEN) return GREEN_COUNTER;
    else if (color == RED) return RED_COUNTER;
    else if (color == BLUE) return BLUE_COUNTER;
    else if (color == YELLOW) return YELLOW_COUNTER;
}

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
    setfillstyle(BOARD_FILL_STYLE,RED);
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

void drawMarkers(int location )
{
    unsigned int locationsValue = locations[location];
    unsigned int totalNumberOfMarkersAtThatLocation = 0, numberOfMarkersAtThatLocation;
    int i,colorOfTheMarker;
    bool willDraw=false;

    for (i = 0; i < 4; i++)
    {
        if (((locationsValue >> 3 * i) & 7) != 0)
        {
            colorOfTheMarker = colors[i];
            totalNumberOfMarkersAtThatLocation += ((locationsValue >> 3 * i) & 7);
            willDraw = true;
        }
    }
    if (!willDraw) return;

    printf("Total Number Of Markers: %d\n", totalNumberOfMarkersAtThatLocation);
    if (totalNumberOfMarkersAtThatLocation % 2 != 0)
    {
        int P = ((int)totalNumberOfMarkersAtThatLocation) / 2;
        int j = 0 - P, k=0, colorOfTheMarker = colors[k];
        int presentAnalysis = locationsValue & 7;

        for (i = 0; i < 4; i++)
        {
            if (((locationsValue >> 3 * i) & 7) != 0)
            {
                colorOfTheMarker = colors[i];
                numberOfMarkersAtThatLocation += ((locationsValue >> 3 * i) & 7);
                for( k=0; k<numberOfMarkersAtThatLocation; k++ )
                {
                    drawOneMarker( location, colorOfTheMarker, 3*j++ );
                    if( j>P ) break;
                }
            }

        }
    }
    else
    {

        int P = ((int)totalNumberOfMarkersAtThatLocation) / 2;
        int j = 0 - P, k=0;
        int presentAnalysis = locationsValue & 7;
        for (i = 0; i < 4; i++)
        {
            if (((locationsValue >> 3 * i) & 7) != 0)
            {
                colorOfTheMarker = colors[i];
                numberOfMarkersAtThatLocation += ((locationsValue >> 3 * i) & 7);
                for( k=0; k<numberOfMarkersAtThatLocation; k++ )
                {
                    if(j!=0)
                    {
                        drawOneMarker( location, colorOfTheMarker, 3*j++ );
                    }
                    else
                    {
                        j++;
                    }
                    if( j> P) break;
                }
            }
        }
    }
}

void drawAllMarkers()
{
    int i, j;
    for( i=1; i<=92; i++ )
    {
        if (locations[i] > 0)
        {
            drawMarkers(i);
        }
    }
}

void initPlayer( Player* player, int color, char name[] )
{
    int i, offset, counterValue;
    player->color = color;

    if (color == GREEN)
    {
        offset = 77;
    }
    else if (color == RED)
    {
        offset = 81;
    }
    else if (color == BLUE)
    {
        offset = 85;
    }
    else if (color == YELLOW)
    {
        offset = 89;
    }

    strcpy( player->name, name );
    player->countersAtHome=4;
    player->countersAtEnd=0;

    for (i = 0; i < 4; i++)
    {
        locations[offset + i] += getCorrespondingCounterValueForColor(color);
        markers[i] = offset+i;
    }
}

void initGame()
{
    srand(time(NULL));

    int i;

    memset(locations, 0, sizeof(locations));
    for( i=0; i<4; i++ )
    {
        initPlayer( &players[i], colors[i], "Player" );
    }



    presentPlayer = 0;
    settextstyle(COMPLEX_FONT, HORIZ_DIR, TEXT_SIZE);
}



void drawDice( bool showNumber, Player* player )
{
    Point analysing = getLocationOfPlayersDie( player );
    setcolor( WHITE );
    setfillstyle( SOLID_FILL, WHITE );

    rectangle( analysing.x, analysing.y, analysing.x+DIE_SIZE, analysing.y+DIE_SIZE );
    floodfill(analysing.x+1, analysing.y+1, WHITE);
    if (showNumber)
    {
        int number = presentPlayersDie;
        setfillstyle(SOLID_FILL, BLACK);
        switch (number)
        {
        case 1:
            FILL_ELLIPSE(analysing.x + 22, analysing.y + 22, DIE_POINT_RADIUS);
            break;
        case 2:
            FILL_ELLIPSE(analysing.x + 10, analysing.y + 10, DIE_POINT_RADIUS);
            FILL_ELLIPSE(analysing.x + 35, analysing.y + 35, DIE_POINT_RADIUS);
            break;
        case 3:
            FILL_ELLIPSE(analysing.x + 10, analysing.y + 10, DIE_POINT_RADIUS);
            FILL_ELLIPSE(analysing.x + 22, analysing.y + 22, DIE_POINT_RADIUS);
            FILL_ELLIPSE(analysing.x + 35, analysing.y + 35, DIE_POINT_RADIUS);
            break;
        case 4:
            FILL_ELLIPSE(analysing.x + 12, analysing.y + 12, DIE_POINT_RADIUS);
            FILL_ELLIPSE(analysing.x + 33, analysing.y + 12, DIE_POINT_RADIUS);
            FILL_ELLIPSE(analysing.x + 12, analysing.y + 33, DIE_POINT_RADIUS);
            FILL_ELLIPSE(analysing.x + 33, analysing.y + 33, DIE_POINT_RADIUS);
            break;
        case 5:
            FILL_ELLIPSE(analysing.x + 10, analysing.y + 10, DIE_POINT_RADIUS);
            FILL_ELLIPSE(analysing.x + 22, analysing.y + 22, DIE_POINT_RADIUS);
            FILL_ELLIPSE(analysing.x + 35, analysing.y + 35, DIE_POINT_RADIUS);
            FILL_ELLIPSE(analysing.x + 35, analysing.y + 10, DIE_POINT_RADIUS);
            FILL_ELLIPSE(analysing.x + 10, analysing.y + 35, DIE_POINT_RADIUS);
            break;
        case 6:
            FILL_ELLIPSE(analysing.x + 10, analysing.y + 10, DIE_POINT_RADIUS);
            FILL_ELLIPSE(analysing.x + 35, analysing.y + 10, DIE_POINT_RADIUS);
            FILL_ELLIPSE(analysing.x + 10, analysing.y + 22, DIE_POINT_RADIUS);
            FILL_ELLIPSE(analysing.x + 35, analysing.y + 22, DIE_POINT_RADIUS);
            FILL_ELLIPSE(analysing.x + 10, analysing.y + 35, DIE_POINT_RADIUS);
            FILL_ELLIPSE(analysing.x + 35, analysing.y + 35, DIE_POINT_RADIUS);
            break;
        }
    }
}

void drawDiceOfAllPlayers()
{
    int i;

    for( i=0; i<4; i++ )
    {
        drawDice(i==presentPlayer, &players[i]);
    }
}

void drawLudoBoard()
{
    putimage(0, 0, board_image, COPY_PUT);
    drawAllMarkers();
    drawAllTextBoxes();
    //drawDice(&players[presentPlayer]);
    drawDiceOfAllPlayers();
}

int rollDice()
{
    int interim=rand()%14;
    if( interim<8 ) presentPlayersDie=(interim/2)+1;
    else presentPlayersDie=(interim+7)/3;
    return presentPlayersDie;
}

void putBackOneToStart(int location, int color, Player* player)
{
    int i, offset, counterValue, markerToBeReturned;
    if (color == GREEN)
    {
        offset = 77;
    }
    else if (color == RED)
    {
        offset = 81;
    }
    else if (color == BLUE)
    {
        offset = 85;
    }
    else if (color == YELLOW)
    {
        offset = 89;
    }

    for( i=0; i<4; i++ )
    {
        if( player->markers[i]==location )
        {
            markerToBeReturned = i;
            break;
        }
    }

    for (i = offset; i < offset + 4; i++)
    {
        if (locations[i] == 0)
        {
            locations[location]-=getCorrespondingCounterValueForColor(color);
            locations[i] += getCorrespondingCounterValueForColor(color);
            player->markers[markerToBeReturned] = i;
            break;
        }
    }
}

void eatCounter( int location, Player* self )
{
#if 0
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
    int self_shift, color = self->color, numberOfCounters, i, j;
    if (color == GREEN)
    {
        self_shift = 0;
    }
    else if (color == RED)
    {
        self_shift = 1;
    }
    else if (color == BLUE)
    {
        self_shift = 2;
    }
    else if (color == YELLOW)
    {
        self_shift = 3;
    }

    for (i = 0; i < 4; i++)
    {
        if (i != self_shift)
        {
            numberOfCounters = (locations[location] >> 3 * i) & 7;
            for (j = 0; j < numberOfCounters; j++)
            {
                putBackOneToStart(location, colors[i], &players[i] );
            }
        }
    }
}

void putACounterFromHereToThere(int startLocation, int destinationLocation, int counterValue, Player* player)
{
    int i;
    locations[startLocation] -= counterValue;
    locations[destinationLocation] += counterValue;
    for( i=0; i<4; i++ )
    {
        if( player->markers[i]==startLocation )
        {
            player->markers[i]=destinationLocation;
            break;
        }
    }
    if (destinationLocation != 1 && destinationLocation != 14 && destinationLocation != 27 && destinationLocation != 40)
    {
        eatCounter(destinationLocation, player);
    }
}

void moveCounter( Player* player, int counterLocation )
{
    int color = player->color;
    int counterValue;
    int moves = presentPlayersDie;
    switch( color )
    {
    case GREEN:
        counterValue = GREEN_COUNTER;
        if( counterLocation<=72)
        {
            if( counterLocation>=46 && counterLocation<=51 && counterLocation+moves>51 )
            {
                if (counterLocation + moves != 57) putACounterFromHereToThere(counterLocation, counterLocation + moves + 1, counterValue, player);
                else
                {
                    putACounterFromHereToThere(counterLocation, 73, counterValue, player);
                    player->countersAtEnd++;
                }
            }
            else if( counterLocation>=53 && counterLocation<=57 )
            {
                if( counterLocation+moves==58 )
                {
                    putACounterFromHereToThere(counterLocation, 73, counterValue, player);
                    player->countersAtEnd++;
                }
                else if( counterLocation+moves<58 )
                {
                    putACounterFromHereToThere(counterLocation, counterLocation+moves, counterValue, player);
                }
            }
            else
            {
                putACounterFromHereToThere(counterLocation, counterLocation + moves, counterValue, player);
            }
        }
        break;

    case RED:
        counterValue = RED_COUNTER;
        if( counterLocation<=72 )
        {
            if( counterLocation>46 && counterLocation<=52 && counterLocation+moves>52 )
            {
                putACounterFromHereToThere(counterLocation, counterLocation+moves-52, counterValue, player);
            }
            else if ( counterLocation>6 && counterLocation<=12 && counterLocation+moves>12 )
            {
                if( counterLocation+moves!=18 ) putACounterFromHereToThere(counterLocation, counterLocation+moves+45, counterValue, player);
                else
                {
                    putACounterFromHereToThere(counterLocation, 74, counterValue, player);
                    player->countersAtEnd++;
                }
            }
            else if ( counterLocation>=58 && counterLocation<=62 )
            {
                if( counterLocation+moves==63 )
                {
                    putACounterFromHereToThere(counterLocation, 74, counterValue, player);
                    player->countersAtEnd++;
                }
                else if ( counterLocation+moves<63 )
                {
                    putACounterFromHereToThere(counterLocation, counterLocation+moves, counterValue, player);
                }
            }
            else
            {
                putACounterFromHereToThere(counterLocation, counterLocation+moves, counterValue, player);
            }
        }
        break;

    case BLUE:
        counterValue = BLUE_COUNTER;
        if( counterLocation<=72 )
        {
            if( counterLocation>46 && counterLocation<=52 && counterLocation+moves>52 )
            {
                putACounterFromHereToThere(counterLocation, counterLocation+moves-52, counterValue, player);
            }
            else if ( counterLocation>19 && counterLocation<=25 && counterLocation+moves>25 )
            {
                if( counterLocation+moves!=31 ) counterLocation = counterLocation+moves+37;
                else
                {
                    putACounterFromHereToThere(counterLocation, 75, counterValue, player);
                    player->countersAtEnd++;
                }
            }
            else if ( counterLocation>=63 && counterLocation<=67 )
            {
                if( counterLocation+moves==68 )
                {
                    putACounterFromHereToThere(counterLocation, 75, counterValue, player);
                    player->countersAtEnd++;
                }
                else if ( counterLocation+moves<68 )
                {
                    putACounterFromHereToThere(counterLocation, counterLocation+moves, counterValue, player);
                }
            }
            else
            {
                putACounterFromHereToThere(counterLocation, counterLocation+moves, counterValue, player);
            }
        }
        break;

    case YELLOW:
        counterValue = YELLOW_COUNTER;
        if( counterLocation<=72 )
        {
            if( counterLocation>46 && counterLocation<=52 && counterLocation+moves>52 )
            {
                putACounterFromHereToThere( counterLocation, counterLocation+moves-52, counterValue, player);
            }
            else if ( counterLocation>32 && counterLocation<=38 && counterLocation+moves>38 )
            {
                if( counterLocation+moves!=44 ) putACounterFromHereToThere(counterLocation, counterLocation+moves+29, counterValue, player);
                else
                {
                    putACounterFromHereToThere(counterLocation, 76, counterValue, player);
                    player->countersAtEnd++;
                }
            }
            else if ( counterLocation>=68 && counterLocation<=72 )
            {
                if( counterLocation+moves==73 )
                {
                    putACounterFromHereToThere(counterLocation, 76, counterValue, player);
                    player->countersAtEnd++;
                }
                else if ( counterLocation+moves<73 )
                {
                    putACounterFromHereToThere(counterLocation, counterLocation+moves, counterValue, player);
                }
            }
            else
            {
                putACounterFromHereToThere(counterLocation, counterLocation+moves, counterValue, player);
            }
        }
        break;
    }


}

void moveCounterFromHomeToPlay( Player* player, int location )
{
    int color = player->color;
    int counterToBeMoved, i, target;

    if( color==GREEN ) target=1;
    else if( color==RED ) target=14;
    else if( color==BLUE ) target=27;
    else if( color==YELLOW ) target=40;

    if( locations[location]!=0 )
    {
        putACounterFromHereToThere(location, target, getCorrespondingCounterValueForColor(color), player);
    }
}

void gotoNextPlayer()
{
    presentPlayer=(presentPlayer+1)%4;
}

Point getPointOfClick()
{
    Point output;
    while( !ismouseclick(WM_LBUTTONDOWN) );
    getmouseclick( WM_LBUTTONDOWN, output.x, output.y );
    //clearmouseclick( WM_LBUTTONDOWN );
    printf("%d--%d\n", output.x, output.y);
    return output;
}

int getLocationWhereClickHasBeenMade( Point pointOfClick )
{
    int i;
    Point analyzing;
    printf("%d-----%d\n", pointOfClick.x, pointOfClick.y);

    for( i=1; i<=92; i++ )
    {
        analyzing = getPointOfLocation(i);
        if( pointOfClick.x-analyzing.x<=35 && pointOfClick.x-analyzing.x>=0
                && pointOfClick.y-analyzing.y<=35 && pointOfClick.y-analyzing.y>=0 )
        {
            printf("%d--%d\n", analyzing.x, analyzing.y);
            return i;
        }
    }
    return -1;
}

int getIndexOfPlayerWhoseDiceIsClicked( Point pointOfClick )
{
    int i;
    Point analyzing;

    for( i=0; i<4; i++ )
    {
        analyzing = getLocationOfPlayersDie(&players[i]);
        if( pointOfClick.x-analyzing.x<=50 && pointOfClick.x-analyzing.x>=0
                && pointOfClick.y-analyzing.y<=50 && pointOfClick.y-analyzing.y>=0 )
        {
            printf("We got %d\n", i);
            return i;
        }
    }
    return -1;
}

bool atHome( Player* player, int location )
{
    int offset, color=player->color;

    if( color==GREEN ) offset=77;
    else if( color==BLUE ) offset=81;
    else if( color==RED ) offset=85;
    else if( color==YELLOW ) offset=89;

    if( location-offset>=0 && location-offset<4 && locations[location]>0 ) return true;
    else return false;
}

bool isThereACounterOfThatPlayer(int location, Player* player)
{
    int color = player->color, self_shift;
    if (color == GREEN)
    {
        self_shift = 0;
    }
    else if (color == RED)
    {
        self_shift = 1;
    }
    else if (color == BLUE)
    {
        self_shift = 2;
    }
    else if (color == YELLOW)
    {
        self_shift = 3;
    }

    return (((locations[location] >> 3 * self_shift) & 7) > 0);
}

void displayInfoAboutAllPlayersLocation()
{
    int i;
    for( i=1; i<=92; i++ )
    {
        printf("%15d: %o%c", i, locations[i], ( i%3==0 ) ? '\n' : '\t' );
    }
}

//void display in
