#include <graphics.h>
#include <iostream>
#include "ludo.h"
#include "init_game_loading.h"


using namespace std;

#define TESTING 0
#define I_HATE_TESTING 0

int main()
{
    for( i=0; i<4; i++ ) {
        memset( names[i], 0, sizeof(names[i]) );
    }
    /*for(int i=0; i<4; i++)
    {
        printf("Input Player %d's Name:\n",i+1);
        scanf("%[^\n]%*c", names[i]);
    }*/
    cout << "Press any key to enter game:" << endl;
    getchar();
    while( !kbhit );
    initwindow(getmaxwidth(), getmaxheight());
    //init_game_loading();
    menu_mechanism();
    showWinners();
}
