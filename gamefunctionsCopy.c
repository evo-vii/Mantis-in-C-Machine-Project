/******************************************************************************
 *  Description     : This is the primary file housing the game flow functions and is normally accessed via
                      playing the actual game. Cannot be accessed otherwise in other main menu options.
 *  Author/s        : Kabigting, Derrell Maiko V.
 *                    Sanico, Lance Matthew G.
 *  Section         : S12A
 *  Last Modified   : 03/11/2026
 *  Acknowledgments : <list of references used in the making of this project>
******************************************************************************/

#include "defs.h"


// PRIMARY GAME FUNCTIONS

/**
    The function playerInit() initializes the player list for the remainder of the match's duration.
    This includes initializing the game's player count, player creation, and saving the new players
    in a text file.

    Precondition: When inputting a username for a new player, no spaces are to be used.

    @param currPlayers - The player list containing all players for a running match.
    @param fPtr - The file pointer accessing "players.txt".
*/
int playerInit(PlayerData currPlayers[], FILE* fPtr)
{

    int nStructIdx = 0; // Struct Index Number
    int nCount; // Total Count of Players
    int nCtr; // General Loop Counter
    int nCtr2;

    int nChoice; // User choice when asked to choose in creating or selecting player.
    PlayerData BufferList[3]; // Buffer list of players pending to be selected.
    int nCurrIdx; // Struct Index for the Current Players structure.
    int nPrintCtr; // Space Counter for appending players.

    // Initial asking for player count.
    do
    {
        printf("How many players?: ");
        scanf("%d", &nCount);
    } while (nCount > 6 || nCount < 3);

    nCurrIdx = 0;

    for (nCtr = 0; nCtr < nCount; nCtr++)
    {
        nStructIdx = 0;

        printf("\nP%d: ?\n\n", nCtr+1);
        
        printf("Select Player %d\n", nCtr+1);

        // Cylces through player list.
        for (nCtr2 = 0; nCtr2 < 3; nCtr2++)
        {
            if (nCtr2 == 0)
                printf("[%d] <Add new player>\n", nCtr2);
            
            else
            {
                // Stores list of players into a short list before being picked by the player to be transferred to the official structure used in game.
                
                fscanf(fPtr, "%s", BufferList[nStructIdx].playerName);

                fseek(fPtr, USERCHAR_MAX-sizeof(BufferList[nStructIdx].playerName), SEEK_CUR);
                fscanf(fPtr, "%d", &BufferList[nStructIdx].nGameWins);

                fseek(fPtr, 5, SEEK_CUR);
                fscanf(fPtr, "%d", &BufferList[nStructIdx].nScoreMax);
            
                printf("[%d] %s\n", nCtr2, BufferList[nStructIdx].playerName);

                nStructIdx++;
            }
        }

        do
        {
            printf("\n>> ");
            scanf("%d", &nChoice);
        } while (nChoice > 2 || nChoice < 0);

        if (nChoice == 0) // If player chooses to create a new player.
        {
            do
            {
                printf("\n\nEnter New Player Username: ");
                scanf("%s", currPlayers[nCurrIdx].playerName);
            } while (strlen(currPlayers[nCurrIdx].playerName) > USERCHAR_MAX);

            // Adds new player to current roster of players.
            currPlayers[nCurrIdx].nPNum = nCtr;
            currPlayers[nCurrIdx].nScoreMax = 0;
            currPlayers[nCurrIdx].nGameWins = 0;

            // Appends new data to players.txt.
            fclose(fPtr);
            fPtr = fopen("players.txt", "a");
            
            // Writes the new player into players.txt.
            fprintf(fPtr, "\n%s", currPlayers[nCurrIdx].playerName);

            for (nPrintCtr = 0; nPrintCtr < (USERCHAR_MAX - (strlen(currPlayers[nCurrIdx].playerName) - 1)); nPrintCtr++)
                fprintf(fPtr, " ");

            fprintf(fPtr, "%d", currPlayers[nCurrIdx].nGameWins);

            for (nPrintCtr = 0; nPrintCtr < 5; nPrintCtr++)
                fprintf(fPtr, " ");

            fprintf(fPtr, "%d", currPlayers[nCurrIdx].nScoreMax);

            fclose(fPtr);
            fPtr = fopen("players.txt", "r");

            nCurrIdx++;
        }
        else
        {
            // Find a way to load the character data from the text file to the character sheet. Use Player Tag to determine player choice.

            if (nChoice == 1)
            {
                currPlayers[nCurrIdx].nPNum = nCtr;
                strcpy(currPlayers[nCurrIdx].playerName, BufferList[0].playerName);
                currPlayers[nCurrIdx].nGameWins = BufferList[0].nGameWins;
                currPlayers[nCurrIdx].nScoreMax = BufferList[0].nScoreMax;

                nCurrIdx++;
            }
            else if (nChoice == 2)
            {
                currPlayers[nCurrIdx].nPNum = nCtr;
                strcpy(currPlayers[nCurrIdx].playerName, BufferList[1].playerName);
                currPlayers[nCurrIdx].nGameWins = BufferList[1].nGameWins;
                currPlayers[nCurrIdx].nScoreMax = BufferList[1].nScoreMax;
                
                nCurrIdx++;
            }
        }
        
    }

    // SUMMATION OF RESULTS (FOR DEBUGGING/FINAL DISPLAY):

    printf("\n\nThese are the Players for this match: \n");

    for(nCurrIdx = 0; nCurrIdx < nCount; nCurrIdx++)
    {
        printf("[%d] %s, All-time Wins: %d, All-time High Score: %d \n", nCurrIdx, currPlayers[nCurrIdx].playerName, currPlayers[nCurrIdx].nGameWins, currPlayers[nCurrIdx].nScoreMax);
    }

    return nCount;
}



/*
    The function deckInit() // DEVNOTE-Lance: WARNING! LINE 50-142 IS AI GENERATED CODE, PLEASE RE-PROGRAM AS SOON AS POSSIBLE!
*/
void deckInit(int nCount, FILE* fPtr, PlayerData currPlayers[], GameState theGame) 
{

    int nDeckIdx = 0; // Index of card deck
    int nCardBackIdx; // Index of the card's back colors
    char cTemp; // Placeholder for reading newlines.

    int nSeed = randomInt(); // Randomizer Seed
    int nCtr; // A local counter variable for looping

    // Read mantis.txt, and store all cards to the game's deck array.
    while (feof(fPtr) == 0)
    { 
        nCardBackIdx = 0;

        if (nDeckIdx != 0)
            fseek(fPtr, 0, SEEK_CUR);

        fscanf(fPtr, "%c", &theGame.deck[nDeckIdx].cFront);
        fseek(fPtr, 3, SEEK_CUR);
        fscanf(fPtr, "%c", &theGame.deck[nDeckIdx].cBack[nCardBackIdx]);

        nCardBackIdx++;
        fscanf(fPtr, "%c", &theGame.deck[nDeckIdx].cBack[nCardBackIdx]);
        nCardBackIdx++;
        fscanf(fPtr, "%c", &theGame.deck[nDeckIdx].cBack[nCardBackIdx]);

        fseek(fPtr, 1, SEEK_CUR);
        fscanf(fPtr, "%d", &theGame.deck[nDeckIdx].nPointVal);
        fscanf(fPtr, "%c", &cTemp);

        nDeckIdx++;
    }

    // Perform deck shuffle

    shuffle(theGame.deck, MAX_CARDS, sizeof(Card), nSeed);

    // DEBUGGING PRINTS
    nDeckIdx = 0;

    while (nDeckIdx != MAX_CARDS)
    {
        nCardBackIdx = 0;
        printf("CARD IDX %d: Front: %c, Back: %c, %c, %c, Point Value: %d\n", nDeckIdx, theGame.deck[nDeckIdx].cFront, theGame.deck[nDeckIdx].cBack[nCardBackIdx], theGame.deck[nDeckIdx].cBack[nCardBackIdx+1], theGame.deck[nDeckIdx].cBack[nCardBackIdx+2], theGame.deck[nDeckIdx].nPointVal);
        nDeckIdx++;
    }

    // Distribute the cards to the players' TANK PILE

    nDeckIdx = 0;

    for (nCtr = 0; nCtr < CARD_DEAL; nCtr++)
    {
        
    }
    
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


int main() // THIS IS A TEST MAIN FUNCTION FOR DEBUGGING PURPOSES ONLY. TO BE REMOVED ON FINAL DEVELOPMENT.
{
    
    FILE* fPlayers;
    FILE* fCards;
    PlayerData currPlayers[PLAYER_MAX];
    GameState theGame;

    initRandom();

    fPlayers = fopen("players.txt", "r");
    theGame.nPlyrCtr = playerInit(currPlayers, fPlayers);
    fclose(fPlayers);

    printf("\nTOTAL PLAYER COUNT: %d\n", theGame.nPlyrCtr); // To be removed.

    fCards = fopen("mantis.txt", "r");
    deckInit(theGame.nPlyrCtr, fCards, currPlayers, theGame);
    fclose(fCards);


    // Player Count Variable
    
    // GameState game;

    // deckinit(&game, nPlyrCnt);
    // displayState(&game);

    // Actual Game Run


    return 0;
}