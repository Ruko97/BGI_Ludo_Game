#include <graphics.h>
#include <iostream>
#include "ludo.h"
using namespace std;
#define TESTING 1


int main() {
    int gd = DETECT, gm;
    int x, y;
    int location = 71;
    int color = BLUE;
    initwindow(900, 700);

    initGame();
    initLudoBoard();

    #if TESTING
    int roll;
    int i;
    players[3].markers[3]=40;
    players[2].markers[2]=27;
    players[1].markers[1]=14;
    players[0].markers[0]=1;
    #endif // TESTING

    //printf("%d\n", DARKYELLOW);
    while( location<=95 ) {
        clearviewport();
        #if 0
        rollDice(&players[0]);
        moveCounter( &players[0], 0);
        #endif // TESTING

        drawLudoBoard();
        //test.location++;
        drawOneMarker(location, color);
        delay(1000);
        location++;
        for( i=0; i<4; i++ ) {
            rollDice( &players[i] );
        }
        for( i=0; i<4; i++ ) {
            moveCounter( &players[i], i );
        }

        getmouseclick(WM_LBUTTONDOWN, x, y);
        cout << "The mouse was clicked at: ";

        cout << "x=" << x;

        cout << " y=" << y << endl;
    }

    closegraph();
}
