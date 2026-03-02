/*

GAME PROPER FUNCTIONS FILE.

*/

#include "defs.h"


int playerInit()
{
    int nCount = 0;
    
    do
    {
        printf("How many players?: ");
        scanf("%d", &nCount);
    } while (nCount > 6 || nCount < 3);



    return 999;
}

void deckInit(int nPlyrCnt)
{

}

int scoreFlow()
{

    return 999;
}

int stealFlow()
{


    return 999;
}

void runGame()
{

}


int main()
{

    playerInit();


    return 0;
}