#include <graphics.h>
#include <iostream>
using namespace std;
#define HOMEBOARDSIZE 210
#define HOMEBOARDDISTANCE 105
#define EACHSQUAREDISTANCE 35
#define DARKYELLOW COLOR(189, 183, 107)
#define CHARCOAL COLOR(54, 69, 79)
#define BOGI 0

struct marker {
    int location;
    int color;
};

void drawLudoBoard() {
    #if BOGI
    setcolor(CHARCOAL);
    setfillstyle(SOLID_FILL, CHARCOAL);
    rectangle(180, 80, 705, 605);
    floodfill(200, 100, CHARCOAL);
    #endif
    /*Each home board is 210px
        each square is 35px
        distance between one home board to the other is 105 px*/
    setcolor(LIGHTRED);
    setfillstyle(SOLID_FILL ,RED);
    rectangle(180, 80, 180+HOMEBOARDSIZE-1, 80+HOMEBOARDSIZE-1);
    floodfill(190, 90, LIGHTRED);
    circle(180+105, 80+105, 80);
    setcolor(LIGHTBLUE);
    setfillstyle(SOLID_FILL, BLUE);
    rectangle(495+1, 80, 495+HOMEBOARDSIZE, 80+HOMEBOARDSIZE-1);
    floodfill(500, 100, LIGHTBLUE);
    circle(495+1+105, 80+105, 80);
    setcolor(LIGHTGREEN);
    setfillstyle(SOLID_FILL, GREEN);
    rectangle(180, 395+1, 180+HOMEBOARDSIZE-1, 395+HOMEBOARDSIZE);
    floodfill(200, 400, LIGHTGREEN);
    circle(180+105, 395+1+105, 80);
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, DARKYELLOW);
    rectangle(495+1, 395+1, 495+HOMEBOARDSIZE, 395+HOMEBOARDSIZE);
    floodfill(500, 400, YELLOW);
    circle(495+1+105, 395+105, 80);

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

    setfillstyle(SOLID_FILL, GREEN);
    floodfill(415, 555, WHITE);
    floodfill(450, 370, WHITE);
    setfillstyle(SOLID_FILL, RED);
    floodfill(240, 300, WHITE);
    floodfill(410, 335, WHITE);
    setfillstyle(SOLID_FILL, BLUE);
    floodfill(480, 135, WHITE);
    floodfill(450, 310, WHITE);
    setfillstyle(SOLID_FILL, DARKYELLOW);
    floodfill(650, 375, WHITE);
    floodfill(480, 335, WHITE);
    for(i=35;i<210;i+=35)
    {
        setfillstyle(SOLID_FILL, GREEN);
        floodfill(435, 390+i, WHITE);
        setfillstyle(SOLID_FILL, RED);
        floodfill(185+i, 330, WHITE);
        setfillstyle(SOLID_FILL, BLUE);
        floodfill(435, 85+i, WHITE);
        setfillstyle(SOLID_FILL, DARKYELLOW);
        floodfill(480+i, 330, WHITE);
    }

    //circle(395,400,10);
}

void drawMarker() {

}

int main() {
    int gd = DETECT, gm;
    int x, y;
    initwindow(900, 700);

    while( !kbhit() ) {
        drawLudoBoard();
        while(!ismouseclick(WM_LBUTTONDOWN));
        getmouseclick(WM_LBUTTONDOWN, x, y);

        cout << "The mouse was clicked at: ";

        cout << "x=" << x;

        cout << " y=" << y << endl;
    }
    closegraph();
}
