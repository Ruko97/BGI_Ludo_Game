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

    rollDice( &players[presentPlayer] );
    printf("%d\n", players[presentPlayer].die);

    drawLudoBoard();
    moveCounter( &players[presentPlayer], 1 );
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

#if TESTING
    int i;
    //for( i=0; i<4; i++ ) moveCounterFromHomeToPlay(&players[i], 78+4*i);

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
