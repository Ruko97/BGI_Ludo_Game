#include <graphics.h>
#include <iostream>
#include "ludo.h"
using namespace std;
#define TESTING 1
#define I_HATE_TESTING 0


int main()
{
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
    int active=1;
    players[3].markers[0]=40;
    players[2].markers[0]=27;
    players[1].markers[0]=14;
    players[0].markers[0]=1;
#endif // TESTING

    //printf("%d\n", DARKYELLOW);
    while( 1 )
    {
        drawLudoBoard();
        setvisualpage(1-active);
        setactivepage(active);
        cleardevice();


#if I_HATE_TESTING
        rollDice(&players[0]);
        moveCounter( &players[0], 0);
#endif // I_HATE_TESTING


        //test.location++;
        //drawOneMarker(location, color);

        location++;
        for( i=0; i<4; i++ )
        {
            rollDice( &players[i] );
            moveCounter( &players[i], 0 );
        }

        delay(1000);

        getmouseclick(WM_LBUTTONDOWN, x, y);
        cout << "The mouse was clicked at: ";

        cout << "x=" << x;

        cout << " y=" << y << endl;


        active=1-active;
    }

    closegraph();
}
