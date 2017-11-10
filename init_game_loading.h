//#include "highscores.h"

#define GREEN_HACKOS COLOR(256, 240, 256)
#define RED_BLOOD COLOR(240, 256, 256)
#define BLUE_SKY COLOR(256, 256, 220)
#define TEXT_SIZE 3


Point click_point;
int location, i;
int roll_count=0, roll_num=0;
char names[4][100];
FILE *score_file;
int logs[3][3];
int logi;
struct ranks
{
    int ranking, score;
    char name[100];
} presentRanks[4], globalRanks[5];

void high_score_show();
int menu_mechanism();

void init_game_loading()
{
    ///BG IMAGE
    readimagefile("BG.jpg",0,0,getmaxwidth(),getmaxheight());
    /** THIS PART IS DRAWING "L" */
    setcolor(GREEN_HACKOS);
    for(int L=0; L<110; L+=2)
    {
        line(150,250+L,200,250+L);
        line(150,250+L+1,200,250+L+1);
        delay(1);
    }
    for(int L=0; L<=40; L+=2)
    {
        line(150,360+L,250,360+L);
        line(150,360+L+1,250,360+L+1);
        delay(1);
    }

    /** THIS PART IS DRAWING "U" */
    setcolor(RED_BLOOD);
    for(int L=1; L<=40; L+=2)
    {
        line(280,400-L,430,400-L);
        line(280,400-L+1,430,400-L+1);
        delay(1);
    }
    for(int L=1; L<=110; L+=2)
    {
        line(280,360-L,330,360-L);
        line(280,360-L+1,330,360-L+1);
        line(380,360-L,430,360-L);
        line(380,360-L+1,430,360-L+1);
        delay(1);
    }

    /** THIS PART IS DRAWING "D" */
    setcolor(YELLOW);
    for(int L=0; L<=25; L++)
    {
        line(485+L,250,485+L,400);
        line(485-L,250,485-L,400);
        delay(1);
    }
    for(int L=0; L<40; L+=2)
    {
        line(510+L,250,510+L,290);
        line(510+L+1,250,510+L+1,290);
        line(510+L,360,510+L,400);
        line(510+L+1,360,510+L+1,400);
        delay(1);
    }
    for(int L=0; L<=25; L++)
    {
        line(560+L,265,560+L,385);
        line(560-L,265,560-L,385);
        delay(1);
    }

    /** THIS PART IS DRAWING "O" */
    setcolor(BLUE_SKY);
    for(int L=0; L<50; L+=2)
    {
        line(620+L,250,620+L,400);
        line(620+L+1,250,620+L+1,400);
        delay(1);
    }
    for(int L=0; L<40; L+=2)
    {
        line(670+L,250,670+L,290);
        line(670+L+1,250,670+L+1,290);
        line(670+L,360,670+L,400);
        line(670+L+1,360,670+L+1,400);
        delay(1);
    }
    for(int L=0; L<50; L+=2)
    {
        line(710+L,250,710+L,400);
        line(710+L+1,250,710+L+1,400);
        delay(1);
    }
    delay(500);

    /** CREDITS */

    setcolor(GREEN_HACKOS);
    ///C
    for(int L=0; L<5; L++)
    {
        line(1110+L,605,1110+L,645);
        line(1115,600+L,1145,600+L);
        line(1115,650-L,1145,650-L);
    }
    ///R
    for(int L=0; L<5; L++)
    {
        line(1155+L,605,1155+L,650);
        line(1160,600+L,1185,600+L);
        line(1160,625-L,1185,625-L);
        line(1182+L,600,1182+L,620);
        line(1182+L,626,1182+L,650);
    }
    ///E
    for(int L=0; L<5; L++)
    {
        line(1200+L,605,1200+L,620);
        line(1200+L,625,1200+L,645);
        line(1205,600+L,1235,600+L);
        line(1205,625-L,1220,625-L);
        line(1205,650-L,1235,650-L);
    }
    ///D
    for(int L=0; L<5; L++)
    {
        line(1250+L,600,1250+L,650);
        line(1255,600+L,1285,600+L);
        line(1255,650-L,1285,650-L);
        line(1285+L,605,1285+L,645);
    }
    ///I
    for(int L=0; L<5; L++)
    {
        line(1300+L,600,1300+L,640);
        line(1300+L,645,1300+L,650);
    }
    ///T
    for(int L=0; L<5; L++)
    {
        line(1325+L,600,1325+L,650);
        line(1310,600+L,1345,600+L);
    }
    delay(500);

    ///NAMES
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 2);
    setcolor(RED_BLOOD);
    line(1110,660,1350,660);
    setcolor(WHITE);
    outtextxy(1110,665,"SAMNAN RAHEE");
    setcolor(RED_BLOOD);
    line(1110,690,1375,690);
    setcolor(WHITE);
    outtextxy(1110,695,"ISHTIAQUE ZAHID");
    delay(500);

    ///LOADING
    /*
    settextstyle(GOTHIC_FONT,HORIZ_DIR,3);
    outtextxy(130,695,"Loading . . .");
    line(0,720,getmaxwidth(),720);
    line(0,721,getmaxwidth(),721);
    line(0,722,getmaxwidth(),722);
    line(0,742,getmaxwidth(),742);
    line(0,743,getmaxwidth(),743);
    line(0,744,getmaxwidth(),744);
    setcolor(BLUE_SKY);
    outtextxy(getmaxwidth()/2-100,750,"CSEDU");
    outtextxy(getmaxwidth()/2-107,780,"Batch 23");
    setcolor(WHITE);
    bool wait=true;
    for(int L=0; L<=getmaxwidth(); L+=15)
    {
        for(int K=0;K<15;K++)
        {
            line(L+K,722,L+K,742);
            if(wait) delay(1);
        }
        if(wait) wait=false;
        else wait=true;
    }*/
}


int diceRollLoop()
{
    //drawInstruction( TELL_TO_ROLL );
    click_point = getPointOfClick();
    if(!isDicePressed(click_point))
        return diceRollLoop();
}

int counterInputLoop()
{
    int Y;
    //drawInstruction(TELL_TO_MOVE);
    click_point = getPointOfClick();
    if( !(thereIsACounterOfPlayerInThatLocation(&players[presentPlayer],getLocationWhereClickHasBeenMade(click_point), &Y)
          && canMoveAParticularCounter( &players[presentPlayer], presentPlayersDie, Y )) )
            return counterInputLoop();
    logs[logi][0] = presentPlayer;
    logs[logi][1] = Y;
    logs[logi][2] = players[presentPlayer].markers[Y];
    moveCounter( &players[presentPlayer], Y, presentPlayersDie );
}

void game_loop()
{
    int active=1;
    float bogi=0.0;
    int show=0;
    logi=0;
    bool firsttime=true;
    while( 1 )
    {
        setvisualpage(1-active);
        setactivepage(active);
        cleardevice();
#if 1



        if( bogi==0 || bogi==5 )
        {
            //cleardevice();
            //if( show==0 )
            drawLudoBoard( false, TELL_TO_ROLL );
            // else
            //drawLudoBoard( false, NO_MOVE_AVALIABLE );
            //else if()
        }
        else if( bogi==1.5 || bogi==2.5 )
        {
            //cleardevice();
            drawLudoBoard( false, NO_MOVE_AVALIABLE );
        }
        else
        {
            //cleardevice();
            drawLudoBoard( true, TELL_TO_MOVE );
        }

        if( bogi==0 )
        {

            //clearmouseclick(WM_LBUTTONDOWN);
            if(players[presentPlayer].countersAtEnd==4)
            {
                bogi=4;
            }
            else
            {
                drawInstruction(TELL_TO_ROLL);
                diceRollLoop();
                bogi=1;
            }
        }
        else if( bogi==1 )
        {
            roll_num = rollDice();
            if( roll_num==6 && roll_count==2 )
            {
                for( int j=0; j<=logi; j++ ) players[logs[j][0]].markers[logs[j][1]] = logs[j][2];
                logi=0, bogi=4;
            }
            /*if(players[presentPlayer].countersAtHome==4 && roll_num!=6)
            {
                bogi=4;
                drawLudoBoard();
                setcolor(WHITE);
                settextstyle(4,HORIZ_DIR,4);
                outtextxy(1020,600,"Oh, no counter can be moved!");
                delay(1000);
            }*/
            else
            {
                if( !canMoveAnyCounter( &players[presentPlayer], presentPlayersDie ) )
                {
                    bogi=2.5;
                    show=1;
                    //drawLudoBoard( true, NO_MOVE_AVALIABLE );
                    drawDice( presentPlayersDie );
                    drawInstruction( NO_MOVE_AVALIABLE );
                    //getPointOfClick();
                }
                else
                {
                    bogi=2;
                    drawLudoBoard( true, TELL_TO_MOVE );
                }
            }
        }
        else if ( bogi==2 )
        {
            //drawInstruction(TELL_TO_MOVE);
            counterInputLoop();
            bogi=3;
        }
        else if (bogi==3)
        {
            if(roll_num==6 && roll_count==0) roll_count++, bogi=5, logi++;
            else if(roll_num==6 && roll_count==1) roll_count++, bogi=5, logi++;
            else if(roll_num==6 && roll_count==2) roll_count=0, bogi=4, logi=0;
            else bogi=4, logi=0;
        }
        else if ( bogi==4 )
        {
            gotoNextPlayer();
            roll_count=0;
            bogi=5;
        }
        else if( bogi==5 )
        {
            if( isWin() )
            {
                break;
            }
            bogi=0;
            show=0;
            firsttime=false;
        }
        else if( bogi==2.5 )
        {
            getPointOfClick();
            //clearmouseclick(WM_LBUTTONDOWN);
            bogi=4;
        }
#endif

#if 0
        if( bogi==0 || bogi==1 )
        {
            drawLudoBoard( false, TELL_TO_ROLL );
        }
        else if ( bogi==3 || bogi==4 )
        {
            drawLudoBoard( true, NO_MOVE_AVALIABLE );
        }
        else
        {
            drawLudoBoard( true, TELL_TO_MOVE );
        }

        if( bogi==0 )
        {
            if( players[presentPlayer].countersAtEnd==4 )
            {
                bogi=5;
            }
            else
            {
                bogi=1;
                diceRollLoop();
            }
        }
        else if ( bogi==1 )
        {
            rollDice();
            if( !canMoveAnyCounter( &players[presentPlayer], presentPlayersDie ) )
            {
                bogi=3;
            }
            else
            {
                bogi=2;
            }
        }
        else if( bogi==2 )
        {
            counterInputLoop();
            bogi=5;
        }
        else if ( bogi==3 )
        {
            bogi=0;
            getPointOfClick();
            //bogi=0;
        }
        else if( bogi==5 )
        {
            if(roll_num==6 && roll_count==0) roll_count++, bogi=7;
            else if(roll_num==6 && roll_count==1) roll_count++, bogi=7;
            else if(roll_num==6 && roll_count==2) roll_count=0, bogi=6;
            else bogi=6;
        }
        else if( bogi==6 )
        {
            gotoNextPlayer();
            roll_count=0;
            bogi=7;
        }
        else if( bogi==7 )
        {
            if( isWin() ) break;
            bogi=0;
        }
#endif

        active=1-active;
    }
    setvisualpage(active);
    setactivepage(active);
}

void mainGame()
{
    cleardevice();
    initGame(names[0],names[1],names[2],names[3]);
    initLudoBoard();
    drawLudoBoard( false, TELL_TO_ROLL );
    game_loop();
}

void write4PlayersNames()
{
    int i;
    char output[100],
         cleardevice();
    settextstyle( GOTHIC_FONT, HORIZ_DIR, 4 );
    outtextxy( 420, 80, "Enter the names of 4 players" );
    for( i=0; i<4; i++ )
    {
        sprintf(output, "Player %d: ", i+1 );
        outtextxy( 185, 280+100*i, output );
        outtextxy( 420, 280+100*i, names[i] );
    }
}

void names_input()
{
    cleardevice();
    int i=0, presentInput=0;
    char input[2]= {'\0'};
    char inputChar;
    write4PlayersNames();
    setcolor( WHITE );
    do
    {
        //while(!kbhit());
        inputChar = (char) getch();
        printf( "--%c--\n", inputChar );
        if( inputChar=='\r' )
        {
            i++;
        }
        input[0] = inputChar;
        strcat( names[i], input );
        write4PlayersNames();
        /*printf("Printing name:\n");
        for( int j=0; j<4; j++ ) {
            printf("%s\n", names[i]);
        }*/
    }
    while (i<4);
    delay( 200 );
    mainGame();
}

///STARTING GAME
void start_game_anim()
{
    setcolor(WHITE);
    settextstyle(GOTHIC_FONT,HORIZ_DIR,4);
    outtextxy(getmaxwidth()/2-230,getmaxheight()/2-50,"STARTING GAME .");
    delay(300);
    cleardevice();
    outtextxy(getmaxwidth()/2-230,getmaxheight()/2-50,"STARTING GAME . .");
    delay(300);
    cleardevice();
    outtextxy(getmaxwidth()/2-230,getmaxheight()/2-50,"STARTING GAME . . .");
    delay(300);
    cleardevice();
    outtextxy(getmaxwidth()/2-230,getmaxheight()/2-50,"STARTING GAME .");
    delay(300);
    cleardevice();
    outtextxy(getmaxwidth()/2-230,getmaxheight()/2-50,"STARTING GAME . .");
    delay(300);
    cleardevice();
}


int menu_mechanism()
{
    ///MAIN MENU
    int active=0;
    void* image;
    bool first=true;
    while(1)
    {
        //setvisualpage(active);
        //setactivepage(1-active);
        //cleardevice();
        readimagefile("main_menu.jpg",getmaxwidth()/2-400,getmaxheight()/2-253,getmaxwidth()/2+400,getmaxheight()/2-120);
        readimagefile("new_game.jpg",getmaxwidth()/2-300,getmaxheight()/2-120,getmaxwidth()/2+300,getmaxheight()/2-20);
        readimagefile("high_score.jpg",getmaxwidth()/2-300,getmaxheight()/2-20,getmaxwidth()/2+300,getmaxheight()/2+80);
        readimagefile("quit_game.jpg",getmaxwidth()/2-300,getmaxheight()/2+80,getmaxwidth()/2+300,getmaxheight()/2+180);
        int xx=mousex(),yy=mousey();
        first=true;
        if(xx>=getmaxwidth()/2-300 && xx<=getmaxwidth()/2+300 && yy>=getmaxheight()/2-120 && yy<=getmaxheight()/2-20)
        {
            /*if( first )
            {
                readimagefile("main_menu.jpg",getmaxwidth()/2-400,getmaxheight()/2-253,getmaxwidth()/2+400,getmaxheight()/2-120);
                readimagefile("new_game_hover.jpg",getmaxwidth()/2-300,getmaxheight()/2-120,getmaxwidth()/2+300,getmaxheight()/2-20);
                readimagefile("high_score.jpg",getmaxwidth()/2-300,getmaxheight()/2-20,getmaxwidth()/2+300,getmaxheight()/2+80);
                readimagefile("quit_game.jpg",getmaxwidth()/2-300,getmaxheight()/2+80,getmaxwidth()/2+300,getmaxheight()/2+180);
                //first=false;
            }//while( !ismouseclick(WM_LBUTTONDOWN) );
            */
            if (ismouseclick(WM_LBUTTONDOWN))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                //while( !ismouseclick(WM_LBUTTONDOWN) );
                //delay(50);
                names_input();
                //mainGame();
            }
        }
        else if(xx>=getmaxwidth()/2-300 && xx<=getmaxwidth()/2+300 && yy>=getmaxheight()/2-20 && yy<=getmaxheight()/2+80)
        {
            /*if( first )
            {
                readimagefile("main_menu.jpg",getmaxwidth()/2-400,getmaxheight()/2-253,getmaxwidth()/2+400,getmaxheight()/2-120);
                readimagefile("new_game.jpg",getmaxwidth()/2-300,getmaxheight()/2-120,getmaxwidth()/2+300,getmaxheight()/2-20);
                readimagefile("high_score_hover.jpg",getmaxwidth()/2-300,getmaxheight()/2-20,getmaxwidth()/2+300,getmaxheight()/2+80);
                readimagefile("quit_game.jpg",getmaxwidth()/2-300,getmaxheight()/2+80,getmaxwidth()/2+300,getmaxheight()/2+180);
                //first=false;
            }*/
            if (ismouseclick(WM_LBUTTONDOWN))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                high_score_show();
                closegraph();
            }
        }
        else if(xx>=getmaxwidth()/2-300 && xx<=getmaxwidth()/2+300 && yy>=getmaxheight()/2+80 && yy<=getmaxheight()/2+180)
        {
            /*if( first ) {
            readimagefile("main_menu.jpg",getmaxwidth()/2-400,getmaxheight()/2-253,getmaxwidth()/2+400,getmaxheight()/2-120);
            readimagefile("new_game.jpg",getmaxwidth()/2-300,getmaxheight()/2-120,getmaxwidth()/2+300,getmaxheight()/2-20);
            readimagefile("high_score.jpg",getmaxwidth()/2-300,getmaxheight()/2-20,getmaxwidth()/2+300,getmaxheight()/2+80);
            readimagefile("quit_game_hover.jpg",getmaxwidth()/2-300,getmaxheight()/2+80,getmaxwidth()/2+300,getmaxheight()/2+180);
            //first=false;
            }if (ismouseclick(WM_LBUTTONDOWN))
            */
            {
                clearmouseclick(WM_LBUTTONDOWN);
                closegraph();
                break;
            }
        }
        else
        {
            first=true;
        }
        //active=1-active;
    }
    cleardevice();
}

void copyRanks( struct ranks* destination, const struct ranks* source )
{
    destination->ranking=source->ranking;
    destination->score=source->score;
    strcpy( destination->name, source->name );
}

void showWinners()
{
    int i, j, k;
    cleardevice();

    if(isWin()) cout << "WON THE GAME" << endl;
    //char rankings[5][100]
    settextstyle(3,HORIZ_DIR,8);
    outtextxy(getmaxwidth()/2-200, getmaxheight()/2-300,"GAME OVER!");
    settextstyle(3,HORIZ_DIR,5);
    outtextxy(getmaxwidth()/2-300, getmaxheight()/2-200,"Rank    Player            Eatings");
    settextstyle(4,HORIZ_DIR,4);
    for(int loop=1; loop<5; loop++)
    {
        for(int player_num=0; player_num<4; player_num++)
        {
            if(players[player_num].ranking==loop)
            {
                char output_result[100];
                sprintf(output_result, "%-8d%-15s%-7d", players[player_num].ranking, players[player_num].name, players[player_num].eaten);
                presentRanks[loop-1].ranking=players[player_num].ranking;
                presentRanks[loop-1].score=players[player_num].eaten+(4-loop);
                strcpy( presentRanks[loop-1].name, players[player_num].name );
                outtextxy(getmaxwidth()/2-300, getmaxheight()/2-200+loop*100, output_result);
            }
        }
    }
    for(int player_num=0; player_num<4; player_num++)
    {
        if(players[player_num].ranking==0)
        {
            char output_result[100];
            sprintf(output_result, "%-8d%-15s%-7d", 4, players[player_num].name, players[player_num].eaten);
            presentRanks[3].ranking=4;
            presentRanks[3].score=players[player_num].eaten;
            strcpy( presentRanks[3].name, players[player_num].name );
            outtextxy(getmaxwidth()/2-300, getmaxheight()/2-200+4*100, output_result);
        }
    }
    //cout << players[0].ranking << " " << players[0].name << " " << players[0].eaten << endl;
    //cout << players[1].ranking << " " << players[1].name << " " << players[1].eaten << endl;
    //cout << players[2].ranking << " " << players[2].name << " " << players[2].eaten << endl;
    //cout << players[3].ranking << " " << players[3].name << " " << players[3].eaten << endl;
    score_file = fopen( "high_score.txt", "r" );
    for(i=0; i<5; i++)
    {
        globalRanks[i].ranking = i+1;
        fscanf(score_file,"%s%*c",globalRanks[i].name);
        fscanf(score_file,"%d\n",&globalRanks[i].score);
        //printf("%s\n",__out__);
        //outtextxy(getmaxwidth()/2-300,getmaxheight()/2-200+80*(i+1),__out__);
        //outtextxy(getmaxwidth()/2-200,getmaxheight()/2-200+80*(i+1),s);
        //outtextxy(getmaxwidth()/2-000,getmaxheight()/2-200+80*(i+1),score);
    }
    fclose(score_file);
    for(i=0; i<4; i++)
    {
        for(j=0; j<5; j++)
        {
            if(presentRanks[i].score>globalRanks[j].score)
            {
                for( k=3; k>=j; k-- )
                {
                    copyRanks( &globalRanks[k+1], &globalRanks[k] );
                }
                copyRanks( &globalRanks[j], &presentRanks[i] );
            }
        }
    }
    score_file = fopen("high_score.txt", "w");
    for(i=0; i<5; i++)
    {
        fprintf(score_file, "%s %d\n", globalRanks[i].name, globalRanks[i].score);
    }
    fclose(score_file);
    delay(5000);
    menu_mechanism();
}



void high_score_show()
{
    cleardevice();

    score_file = fopen( "high_score.txt", "r" );
    int score;
    settextstyle(3, HORIZ_DIR, 7);
    setcolor(WHITE);
    outtextxy(getmaxwidth()/2-300,getmaxheight()/2-200,"RANK");
    outtextxy(getmaxwidth()/2-200,getmaxheight()/2-200,"NAME");
    outtextxy(getmaxwidth()/2-000,getmaxheight()/2-200,"SCORE");
    for(int i=0; i<5; i++)
    {
        char s[100],__out__[1000];
        //cout << "OKKK" << endl;
        fscanf(score_file,"%s%*c",s);
        fscanf(score_file,"%d\n",&score);
        //printf("%s -- %d\n",s,score);
        sprintf(__out__,"%d. %-20s%d",i+1,s,score);
        //printf("%s\n",__out__);
        outtextxy(getmaxwidth()/2-300,getmaxheight()/2-200+80*(i+1),__out__);
        //outtextxy(getmaxwidth()/2-200,getmaxheight()/2-200+80*(i+1),s);
        //outtextxy(getmaxwidth()/2-000,getmaxheight()/2-200+80*(i+1),score);
    }
    outtextxy( 30, getmaxheight()-60, "Press any key to go back to start." );
    while( !kbhit() );
    fclose(score_file);
    cleardevice();
    menu_mechanism();
}
