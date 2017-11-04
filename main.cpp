#include <graphics.h>
#include <iostream>
#include "ludo.h"
using namespace std;
#define TESTING 1
#define I_HATE_TESTING 0

Point click_point;

int gameLoop() {

    do {
        click_point = getPointOfClick();
    } while( getIndexOfPlayerWhoseDiceIsClicked(click_point) !=  presentPlayer );

    rollDice();
    printf("%d\n", presentPlayersDie);

    drawLudoBoard();
    displayInfoAboutAllPlayersLocation();
	/*do {
		click_point = getPointOfClick();
	} while (!isThereACounterOfThatPlayer(getLocationWhereClickHasBeenMade(click_point), &presentPlayer));
    */
	//moveCounter(presentPlayer, getLocationWhereClickHasBeenMade(click_point));
    gotoNextPlayer();
    //delay(1000);
}

int main()
{
    initwindow(900, 700);
    int active=1;
    initGame();
    initLudoBoard();
    drawLudoBoard();
    printf("%d", 8 & 7);

#if TESTING
    int i=1;
    locations[77] = 10;
    //for( i=0; i<4; i++ ) moveCounterFromHomeToPlay(&players[i], 78+4*i);
	//for (i = 77; i <= 92; i++) {

	//}

#endif // TESTING

    //printf("%d\n", DARKYELLOW);
    while( 1 )
    {
        setvisualpage(1-active);
        setactivepage(active);
        cleardevice();


#if I_HATE_TESTING
        rollDice(&players[0]);
        moveCounter( &players[0], 0);
#endif // I_HATE_TESTING


        //test.location++;
        //drawOneMarker(location, color);

/*
        location++;
        j++;
        for( i=0; i<4; i++ )
        {
            rollDice( &players[i] );
            moveCounter( &players[i], 1 );
        }

        delay(500);
        */
        //if( j==6 ) putBackToStart(&players[3], 1);
        /*
        getmouseclick(WM_LBUTTONDOWN, x, y);
        cout << "The mouse was clicked at: ";

        cout << "x=" << x;

        cout << " y=" << y << endl;
        */

        gameLoop();

        active=1-active;
    }

    closegraph();
}
