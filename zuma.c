#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

int lim, altlim, p1, p2, px, py, snarx, snary, score, i;
double targetTime;
char balls[100][100], dirarr, sn;

void again();
void checkballs();

void stop()
{
    i = 0;
    Sleep(500);
}

void verifyps(int *pfrontx, int *pfronty)
{
    if (*pfrontx == (lim / 2) - 1 && *pfronty == altlim - 2){
        printf("\nYou LOST. Better luck next time. Your Score was %d", score);
        stop();
    }
    else if (((*pfrontx == 0 || *pfrontx == 1) && *pfronty == altlim - 2) || (*pfrontx > 1 && *pfrontx < lim - 3 && *pfronty == 2))
        (*pfrontx)++;
    else if ((*pfrontx == 0 && *pfronty < altlim - 2) || (*pfrontx == lim - 3 && *pfronty > 1 && *pfronty < altlim - 2))
    {
        (*pfronty)++;
    }
    else if (*pfronty == 0 || (*pfronty == altlim - 2 && *pfrontx < lim - 2 && *pfrontx > 2))
    {
        (*pfrontx)--;
    }
    else if (*pfrontx == lim - 1 || *pfrontx == 2)
        (*pfronty)--;
}

void colouring(char symbol, int v){
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    switch(symbol){
        case 'R':
            SetConsoleTextAttribute(h, FOREGROUND_RED);
            break;
        case 'G':
            SetConsoleTextAttribute(h, FOREGROUND_GREEN);
            break;
        case 'B':
            SetConsoleTextAttribute(h, FOREGROUND_BLUE);
            break;
        case 'Y':
            SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN);
            break;
    }
    if(v==0)
        printf(" %c", dirarr);
    else printf(" %c", symbol);
    SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void init()
{
    COORD coord;
    coord.X = 0;
    coord.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    printf("\tScore: %d\n", score);
    printf("-");
    for (int i = 0; i < lim; i++)
    {
        if (i > 0 && i < lim)
        {
            printf("|");
        }
        else
        {
            for (int j = 0; j < altlim + 1; j++)
            {
                printf("--");
            }
            printf("\n|");
        }

        for (int j = 0; j < altlim; j++)
        {
            if (i == px && j == py)
            {
                colouring(sn, 0);
            }

            else if (i == (lim / 2) - 1 && j == altlim - 2)
                printf(" O");
            else {
                colouring(balls[i][j], 1);
            }

            if (j == altlim - 1)
                printf(" |");
        }
        printf("\n");
    }
    for (int j = 0; j < altlim + 1; j++)
        printf("--");
}

void backtrack(int *pback1, int *pback2)
{
    if (((*pback1 > 0 && *pback1 <= 2) && *pback2 == altlim - 2) || (*pback1 > 2 && *pback1 < lim - 2 && *pback2 == 2))
        (*pback1)--;
    else if ((*pback1 == 0 && *pback2 > 0 && *pback2 < altlim - 1) || (*pback1 == lim - 3 && *pback2 > 1 && *pback2 < altlim - 1))
        (*pback2)--;
    else if ((*pback2 == 0 && *pback1 < lim - 1) || (*pback2 == altlim - 2 && *pback1 < lim - 3 && *pback1 > 2))
        (*pback1)++;
    else if (*pback1 == lim - 1 || *pback1 == 2)
        (*pback2)++;
}

void checkwin(){
    int win=1;
    for (int i = 0; i < 100 && win==1; i++)
    {
        for (int j = 0; j < 100 && win==1; j++)
        {
            if(balls[i][j] != ' ')
                win=0;
        }
    }
    if(win==1){
        printf("\nCongratulations, you WON with a Score of %d!", score);
        stop();
    }
}

void destroy(char *b1, char *b2, char *b3, char *b4, int tempp1, int tempp2, double *chainR, int nr){
    int timeoob=10, contor=3, save1=tempp1, save2=tempp2;
    *b1='X';
    *b2='X';
    *b3='X';
    if(nr==4){
        *b4='X';
        timeoob=25;
        contor=4;
    }
    init();
    Sleep(150);
    *b1=' ';
    *b2=' ';
    *b3=' ';
    if(nr==4)
        *b4=' ';
    if(targetTime<=timeoob)
        score+=timeoob/targetTime*(*chainR);
    else score+=1*(*chainR);
    (*chainR)+=0.25;
    init();
    Sleep(150);

    while(contor!=0){
        init();
        Sleep(25);
        while(tempp1!=p1 || tempp2!=p2){
            int tp1=tempp1, tp2=tempp2;
            verifyps(&tempp1, &tempp2);
            balls[tp1][tp2]=balls[tempp1][tempp2];
        }
        init();
        Sleep(25);
        tempp1=save1;
        tempp2=save2;
        contor--;
    }
    backtrack(&p1, &p2);
    backtrack(&p1, &p2);
    backtrack(&p1, &p2);
    if(nr==4)
        backtrack(&p1, &p2);
    if(balls[tempp1][tempp2]!=' ')
        checkballs(&tempp1, &tempp2, chainR);
}

void checkballs(int *ballingx, int *ballingxy, double *chainR){
    int back1x=*ballingx, back1y=*ballingxy;
    backtrack(&back1x, &back1y);
    int back2x=back1x, back2y=back1y;
    backtrack(&back2x, &back2y);
    int back3x=back2x, back3y=back2y;
    backtrack(&back3x, &back3y);

    int front1x=*ballingx, front1y=*ballingxy;
    verifyps(&front1x, &front1y);
    int front2x=front1x, front2y=front1y;
    verifyps(&front2x, &front2y);
    int front3x=front2x, front3y=front2y;
    verifyps(&front3x, &front3y);

    char p = balls[*ballingx][*ballingxy];
    if(balls[back1x][back1y]==p && balls[back2x][back2y]==p && balls[back3x][back3y]==p)
    {
        destroy(&balls[*ballingx][*ballingxy], &balls[back1x][back1y], &balls[back2x][back2y], &balls[back3x][back3y], back3x, back3y, chainR, 4);
    }
    else if(balls[front1x][front1y]==p && balls[back1x][back1y]==p && balls[back2x][back2y]==p){
        destroy(&balls[front1x][front1y], &balls[*ballingx][*ballingxy], &balls[back1x][back1y], &balls[back2x][back2y], back2x, back2y, chainR, 4);
    }
    else if(balls[front2x][front2y]==p && balls[front1x][front1y]==p && balls[back1x][back1y]==p){
        destroy(&balls[front2x][front2y], &balls[front1x][front1y], &balls[*ballingx][*ballingxy], &balls[back1x][back1y], back1x, back1y, chainR, 4);
    }
    else if(balls[front3x][front3y]==p && balls[front2x][front2y]==p && balls[front1x][front1y]==p){
        destroy(&balls[front3x][front3y], &balls[front2x][front2y], &balls[front1x][front1y], &balls[*ballingx][*ballingxy], *ballingx, *ballingxy, chainR, 4);
    }
    else if(balls[back1x][back1y]==p && balls[back2x][back2y]==p){
        destroy(&balls[*ballingx][*ballingxy], &balls[back1x][back1y], &balls[back2x][back2y], NULL, back2x, back2y, chainR, 3);
    }
    else if(balls[front1x][front1y]==p && balls[back1x][back1y]==p){
        destroy(&balls[front1x][front1y], &balls[*ballingx][*ballingxy], &balls[back1x][back1y], NULL, back1x, back1y, chainR, 3);
    }
    else if(balls[front2x][front2y]==p && balls[front1x][front1y]==p){
        destroy(&balls[front2x][front2y], &balls[front1x][front1y], &balls[*ballingx][*ballingxy], NULL, *ballingx, *ballingxy, chainR, 3);
    }
    *chainR=1;
}

void addball()
{
    int pf1, pf2;
    int pb1 = p1;
    int pb2 = p2;
    while (pb1 != snarx || pb2 != snary)
    {
        if (p1 == (lim / 2) - 1 && p2 == altlim - 2){
            printf("\nYou LOST. Better luck next time. Your Score was %d", score);
            stop();
            break;
        }
        pf1 = pb1;
        pf2 = pb2;
        backtrack(&pb1, &pb2);
        balls[pf1][pf2] = balls[pb1][pb2];
    }
}

void convertrand(int *temprand, char *randball){
    switch (*temprand)
        {
        case 0:
            *randball = 'R';
            break;
        case 1:
            *randball = 'G';
            break;
        case 2:
            *randball = 'B';
            break;
        case 3:
            *randball = 'Y';
            break;
        default:
            *randball = '?';
        }
}

int checkColour(){
    for(int k1=0; k1<100; k1++){
        for(int k2=0; k2<100; k2++){
            if(balls[k1][k2]==sn)
                return 1;
        }
    }
    return 0;
}

void checkNewColours(int ending){
    while(ending==1){
        if(checkColour()==0){
            int temp = rand()%4;
            convertrand(&temp, &sn);
        }
        else break;
    }
}

void shoot(int ending)
{
    snarx = px;
    snary = py;
    while ((balls[snarx][snary] == ' ' || balls[snarx][snary] == balls[px][py]) && snarx < lim-1 && snarx > 0 && snary > 0 && snary < altlim - 1)
    {
        switch (dirarr)
        {
        case 'V':
            snarx++;
            break;
        case 'A':
            snarx--;
            break;
        case '<':
            snary--;
            break;
        case '>':
            snary++;
            break;
        }
        if (balls[snarx][snary] != ' ')
        {
            addball();
            if(i!=0){
                balls[snarx][snary] = sn;

                verifyps(&p1, &p2);
                double chainR=1;

                int whytho = rand()%4;
                convertrand(&whytho, &sn);
                checkNewColours(ending);

                checkballs(&snarx, &snary, &chainR);
                checkwin();
                init();
            }
        }
        else
        {
            balls[snarx][snary] = sn;
            init();
            Sleep(5);
            balls[snarx][snary] = ' ';
            if(snarx==lim-1 || snarx==0 || snary==altlim-1 || snary==0){
                int whytho = rand()%4;
                convertrand(&whytho, &sn);
                checkNewColours(ending);
            }
        }
    }
}

void keying(char *chkb, int ending)
{
    switch (*chkb)
    {
    case 'W':
    case 'w':
        if (px > 3 && balls[px-1][py]!='O')
            px--;
        break;
    case 'A':
    case 'a':
        if (py > 3 && balls[px][py-1]!='O')
            py--;
        break;
    case 'S':
    case 's':
        if (px < lim - 4 && balls[px+1][py]!='O')
            px++;
        break;
    case 'D':
    case 'd':
        if (py < altlim - 3 && balls[px][py+1]!='O')
            py++;
        break;
    case 'I':
    case 'i':
        dirarr = 'A';
        break;
    case 'J':
    case 'j':
        dirarr = '<';
        break;
    case 'K':
    case 'k':
        dirarr = 'V';
        break;
    case 'L':
    case 'l':
        dirarr = '>';
        break;
    case ' ':
        shoot(ending);
        break;
    }
}

void call(clock_t *timeS, int ending)
{
    if (kbhit())
    {
        char chkb = getch();
        if ((int)chkb == 27)
        {
            printf("\nGame Exited. We already miss you!");
            stop();
        }
        else
        {
            keying(&chkb, ending);
            if(i!=0){
                init();
                again(timeS, ending);
            }
        }
    }
}

void again(clock_t *timeS, int ending)
{
    while ((clock() - *timeS) < targetTime*1000 && i!=0)
    {
        call(timeS, ending);
    }
}

int startingInput(char *scanned, int *finalScore){
    switch(*scanned){
        case 't':case 'T':
            printf("\nHow big do you want the table? (minimal admissible values 4 6)(default and also recommended are 12 12):");
            scanf("%d %d", &lim, &altlim);
            printf("\nDone!");
            Sleep(500);
            break;
        case 'w':case 'W':
            printf("\nAt how many points do you want the game to stop creating any more balls? (default 269 points):");
            scanf("%d", finalScore);
            printf("\nDone!");
            Sleep(500);
            break;
        case 's':case 'S':
            printf("\nHow fast do you want the game to create balls? (default 2 seconds):");
            scanf("%lf", &targetTime);
            printf("\nDone!");
            Sleep(500);
            break;
        case 13:
            return 1;
        case 27:
            stop();
            printf("\nGame Exited. We already miss you!");
            return 1;
        default:{printf("\nInvalid input, try again");Sleep(500);return 0;}
    }
    return 0;
}

void startGame(){
    srand((int)time(NULL));

    clock_t timeS;
    int finalScore=269, tempInp=0, whytho = rand()%4, ending=0;
    char scanned;
    
    score=0;
    i = 1;
    targetTime=2;
    lim=12; altlim=12;
    p1 = lim - 1;
    p2 = altlim - 1;
    px = lim / 2;
    py = altlim / 2;
    dirarr = 'V';
    
    while(tempInp==0){
        system("cls");
        printf("Controls: Use W, A, S, D to WALK in the respective direction. Use I, J, K, L to LOOK in the respective direction. Use SPACE to shoot. Use ESC to exit the game.\n\nTo change the table size: Press T\n\t\tWin score: Press W\n\t\tTime Speed: Press S\nPress ENTER if you are ready to start:");
        scanned=getch();
        system("cls");
        tempInp = startingInput(&scanned, &finalScore);
    }
    if(i!=0){
        convertrand(&whytho, &sn);
        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 100; j++)
            {
                balls[i][j] = ' ';
            }
        }

        init();
        while (i != 0)
        {
            timeS = clock();
            again(&timeS, ending);
            int temprand;
            char randball;
            if(i!=0){
                int tempr1=p1, tempr2=p2, temprsave1, temprsave2;
                while(tempr1!=lim-1 || tempr2!=altlim-1){
                    temprsave1=tempr1;
                    temprsave2=tempr2;
                    backtrack(&tempr1,&tempr2);
                    balls[temprsave1][temprsave2]=balls[tempr1][tempr2];
                }
                if(score<finalScore)
                {
                    while(1){
                        temprand = rand() % 4;
                        convertrand(&temprand, &randball);
                        if(balls[lim-1][altlim-1]==balls[lim-1][altlim-2] && balls[lim-1][altlim-1]==balls[lim-1][altlim-3] && balls[lim-1][altlim-1]==randball)
                            continue;
                        else break;
                    }
                }else {
                    randball=' ';
                    ending=1;
                    checkwin();
                }
                if(i!=0){
                    balls[lim-1][altlim-1]=randball;
                    init();
                    verifyps(&p1, &p2);
                    if(targetTime>1)
                        targetTime-=0.03;
                    else targetTime-=0.006;
                }
            }
        }
    }

    printf("\n\n\n\tDo you want to play again? Press ENTER. Otherwise press ESC:");
    char scn;
    while(1){//this was done to prevent missclicks after the game was finished in case it was very sudden.
        scn=getch();
        if((int)scn==13){
            startGame();
            break;
        }
        else if((int)scn==27){
            printf("\n\nThank you for playing, bye! <3");
            break;
        }
    }
}

int main()
{
    startGame();
}