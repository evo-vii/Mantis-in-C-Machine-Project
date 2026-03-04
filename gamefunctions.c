/*

GAME PROPER FUNCTIONS FILE.

*/

#include "defs.h"


// SUPLEMENTARY GAME FUNCTIONS

// DEVNOTE-Lance: This is widely experimental and not yet to be implemented.
void displayDeck()
{

}

// PRIMARY GAME FUNCTIONS

/*
    The function playerInit() is the first stage of the game proper. (TBC)

    // DEVNOTE-Lance: Players are hard-coded in this version of the game function, adding new players, usernames and file handling will be added in the future.
*/
int playerInit(int nPlyrCnt)
{
    int nCount = 0;
    int nCtr;

    // Inserted temporary usernames while file handling is not yet set.
    Username plyrUN[6] = {"Antioch", "Constantinople", "Ur", "Northumbria", "Gaul", "Prussia"};
    
    do
    {
        printf("How many players?: ");
        scanf("%d", &nCount);
    } while (nCount > 6 || nCount < 3);

    for (nCtr = 0; nCtr < nCount; nCtr++)
    {
        printf("P%d: %s\n", nCtr+1, plyrUN[nCtr]);
    }

    return nCount;
}

/*
    The function deckInit()...
*/
void deckInit(int nPlyrCnt)
{



}

/*
    The function scoreFlow()...
*/
int scoreFlow()
{

    return 999;
}

/*
    The function stealFlow()...
*/
int stealFlow()
{


    return 999;
}

/*
    The function runGame()...
*/
void runGame()
{

}


int main()
{
    
    // Player Count Variable
    int nPlyrCnt;

    // Pre-game Preparations
    nCount = playerInit(&nPlyrCnt);
    deckInit(nPlyrCnt);

    // Actual Game Run


    return 0;
}