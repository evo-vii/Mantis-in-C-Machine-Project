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

    Returns nCount - The total number of players that will participate in a match.
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
            if (nChoice == 1)
            {
                currPlayers[nCurrIdx].nPNum = nCtr+1;
                strcpy(currPlayers[nCurrIdx].playerName, BufferList[0].playerName);
                currPlayers[nCurrIdx].nGameWins = BufferList[0].nGameWins;
                currPlayers[nCurrIdx].nScoreMax = BufferList[0].nScoreMax;

                nCurrIdx++;
            }
            else if (nChoice == 2)
            {
                currPlayers[nCurrIdx].nPNum = nCtr+1;
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

/**
 
    The function displayDeck() cycles through the current players' card's front face
    to sort the cards into a respective player's array of color-coded cards. This function
    acts as a snapshot update of the players' card list and does not dynamically update
    as the game runs. This function is to be called after every move and changes the
    amount of cards a player has.

    Precondition: This is a helper function, thus, there are no other values to be changed.

    @param currPlayers - The player list containing all players for a running match.
    @param theGame - This is the main control structure of the game, containing relevant information such as the game's deck and player count.

*/
void displayDeck(PlayerData currPlayers[], GameState theGame) // CONTAINS ERRORS, DOUBLES CARD COUNT
{
    int nPlyrIdx;
    int nCtr;

    printf("\n");

    // To avoid overcounting, nColorCards is set to 0 at every call before checking card colors.

    for (nPlyrIdx = 0; nPlyrIdx < theGame.nPlyrCtr; nPlyrIdx++)
    {
        for (nCtr = 0; nCtr < COLORS; nCtr++)
        {
            currPlayers[nPlyrIdx].theDeck.nColorCards[nCtr] = 0;
        }
    }

    for(nPlyrIdx = 0; nPlyrIdx < theGame.nPlyrCtr; nPlyrIdx++)
    {
        for (nCtr = 0; nCtr < currPlayers[nPlyrIdx].theDeck.nTankAmt; nCtr++)
        {
            switch (currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cFront)
            {
                case 'R': currPlayers[nPlyrIdx].theDeck.nColorCards[0] += 1;
                    break;
                case 'O': currPlayers[nPlyrIdx].theDeck.nColorCards[1] += 1;
                    break;
                case 'Y': currPlayers[nPlyrIdx].theDeck.nColorCards[2] += 1;
                    break;
                case 'G': currPlayers[nPlyrIdx].theDeck.nColorCards[3] += 1;
                    break;
                case 'B': currPlayers[nPlyrIdx].theDeck.nColorCards[4] += 1;
                    break;
                case 'I': currPlayers[nPlyrIdx].theDeck.nColorCards[5] += 1;
                    break;
                case 'V': currPlayers[nPlyrIdx].theDeck.nColorCards[6] += 1;
                    break;
            }
        }

        printf("P%d => [ R: %d | O: %d | Y: %d | G: %d | B: %d | I: %d | V: %d ] // S:%d\n", currPlayers[nPlyrIdx].nPNum, currPlayers[nPlyrIdx].theDeck.nColorCards[0], currPlayers[nPlyrIdx].theDeck.nColorCards[1], currPlayers[nPlyrIdx].theDeck.nColorCards[2], currPlayers[nPlyrIdx].theDeck.nColorCards[3], currPlayers[nPlyrIdx].theDeck.nColorCards[4], currPlayers[nPlyrIdx].theDeck.nColorCards[5], currPlayers[nPlyrIdx].theDeck.nColorCards[6], currPlayers[nPlyrIdx].theDeck.nCurrScore);
    }

    printf("\n");
}

/** 
    The function deckInit() utilizes the mantis.txt text file and imports the data into the
    game's internal card deck and shuffles it. Then, the first tank cards are distributed to each 
    of the players by an amount defined by the constant "CARD_DEAL".

    @param nCount - Total number of players in a match.
    @param fPtr - The file pointer accessing "mantis.txt".
    @param currPlayers - The player list containing all players for a running match.
    @param theGame - This is the main control structure of the game, containing relevant information such as the game's deck and player count.

    Returns nCardNum - The index of the game's deck to continue incrementing after removing the dealt cards at initialization.

*/
int deckInit(int nCount, FILE* fPtr, PlayerData currPlayers[], GameState *theGame) // Check for seed settings
{

    int nDeckIdx = 0; // Index of card deck
    int nCardBackIdx; // Index of the card's back colors
    char cTemp; // Placeholder for reading newlines.
    int nPlyrIdx = 0; // Index of player roster.

    int nSeed = randomInt(); // Randomizer Seed
    int nCtr; // A local counter variable for looping
    int nCardNum; // Remaining cards within the game deck.

    // Read mantis.txt, and store all cards to the game's deck array.
    while (feof(fPtr) == 0)
    { 
        nCardBackIdx = 0;

        if (nDeckIdx != 0)
            fseek(fPtr, 0, SEEK_CUR);

        fscanf(fPtr, "%c", &theGame->deck[nDeckIdx].cFront);
        fseek(fPtr, 3, SEEK_CUR);
        fscanf(fPtr, "%c", &theGame->deck[nDeckIdx].cBack[nCardBackIdx]);

        nCardBackIdx++;
        fscanf(fPtr, "%c", &theGame->deck[nDeckIdx].cBack[nCardBackIdx]);
        nCardBackIdx++;
        fscanf(fPtr, "%c", &theGame->deck[nDeckIdx].cBack[nCardBackIdx]);

        fseek(fPtr, 1, SEEK_CUR);
        fscanf(fPtr, "%d", &theGame->deck[nDeckIdx].nPointVal);
        fscanf(fPtr, "%c", &cTemp);

        nDeckIdx++;
    }

    // Perform deck shuffle

    shuffle(theGame->deck, MAX_CARDS, sizeof(Card), nSeed);

    // Distribute the cards to the players' TANK PILE

    nDeckIdx = 0;

    for (nPlyrIdx = 0; nPlyrIdx < theGame->nPlyrCtr; nPlyrIdx++)
    {
        currPlayers[nPlyrIdx].theDeck.nTankAmt = 0;
        
        for (nCtr = 0; nCtr < CARD_DEAL; nCtr++)
        {
            nCardBackIdx = 0;
            
            currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cFront = theGame->deck[nDeckIdx].cFront;
            currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx] = theGame->deck[nDeckIdx].cBack[nCardBackIdx];
            currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx+1] = theGame->deck[nDeckIdx].cBack[nCardBackIdx+1];
            currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx+2] = theGame->deck[nDeckIdx].cBack[nCardBackIdx+2];
            currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].nPointVal = theGame->deck[nDeckIdx].nPointVal;


            theGame->deck[nDeckIdx].cFront = '\0';
            theGame->deck[nDeckIdx].cBack[nCardBackIdx] = '\0';
            theGame->deck[nDeckIdx].cBack[nCardBackIdx + 1] = '\0';
            theGame->deck[nDeckIdx].cBack[nCardBackIdx + 2] = '\0';
            theGame->deck[nDeckIdx].nPointVal = 0;

            currPlayers[nPlyrIdx].theDeck.nTankAmt++;
            nDeckIdx++;
        }
    }
    
    nCardNum = nDeckIdx;

    // Initializing additional variables
    
    for (nPlyrIdx = 0; nPlyrIdx < theGame->nPlyrCtr; nPlyrIdx++)
    {
        currPlayers[nPlyrIdx].theDeck.nScoreAmt = 0;
        currPlayers[nPlyrIdx].theDeck.nCurrScore = 0;
    }

    // Showing Final Status of Player Tanks (For UI)

    displayDeck(currPlayers, *theGame);

    return nCardNum;
}


/*
    The function scoreFlow()...
*/
void scoreFlow(PlayerData currPlayers[], GameState theGame, int nPlyrIdx, int nDeckIdx/*, int *nScoreIdx*/) // DEVNOTE-LANCE: Make sure to make print debug statements to check the status of array members.
{
    int nCardBackIdx = 0;
    int nCtr;

    int nChecker = currPlayers[nPlyrIdx].theDeck.nScoreAmt; // Compares against current nScoreAmt after STAGE I is complete.
    int nFlag = 0; // Stays 0 at STAGE II if the tank card was not slotted into a nulled slot. This means, the next empty tank index slot is to be utilized. If non-zero, card was successfully slotted at a null slot.

    int nDeckTester; // FOR DEBUGGING PURPOSES
    int nScoreIdx = 0;

    printf("Resolving turn for Player %d...\n", currPlayers[nPlyrIdx].nPNum);
    printf("- %s draws a card and it is: %c\n", currPlayers[nPlyrIdx].playerName, theGame.deck[nDeckIdx].cFront);

    // STAGE I: Checks if drawn card is present in any of the player's tank pile.

    for (nCtr = 0; nCtr < currPlayers[nPlyrIdx].theDeck.nTankAmt; nCtr++)
    {
        if (currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cFront == theGame.deck[nDeckIdx].cFront) // If a tank card is similar to the drawn card.
        {
            currPlayers[nPlyrIdx].theDeck.nScoreAmt++; // Increments the amount of cards in the score pile.
            
            // Slots the tank card into the score pile.
            currPlayers[nPlyrIdx].theDeck.scorePile[nScoreIdx].cFront = currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cFront;
            currPlayers[nPlyrIdx].theDeck.scorePile[nScoreIdx].cBack[nCardBackIdx] = currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx];
            currPlayers[nPlyrIdx].theDeck.scorePile[nScoreIdx].cBack[nCardBackIdx+1] = currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx+1];
            currPlayers[nPlyrIdx].theDeck.scorePile[nScoreIdx].cBack[nCardBackIdx+2] = currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx+2];
            currPlayers[nPlyrIdx].theDeck.scorePile[nScoreIdx].nPointVal = currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].nPointVal;

            // Adds the point value of the eligible tank card in the player's score.
            currPlayers[nPlyrIdx].theDeck.nCurrScore += currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].nPointVal;

            nScoreIdx++;

            // "Nulls" the eligible tank card from the player.

            currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cFront = '\0';
            currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx] = '\0';
            currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx+1] = '\0';
            currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx+2] = '\0';
            currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].nPointVal = 0;
        }    
    }

    // ==========================================
    // DEBUGGING PRINTS 4 (TO BE REMOVED)

    nDeckTester = 0;
    printf("\n\nPlayer Deck at Stage I\n");
    while (nDeckTester != currPlayers[nPlyrIdx].theDeck.nScoreAmt)
    {
        nCardBackIdx = 0;
        printf("CARD IDX %d: Front: %c, Back: %c, %c, %c, Point Value: %d\n", nDeckTester, currPlayers[nPlyrIdx].theDeck.scorePile[nDeckTester].cFront, currPlayers[nPlyrIdx].theDeck.scorePile[nDeckTester].cBack[nCardBackIdx], currPlayers[nPlyrIdx].theDeck.scorePile[nDeckTester].cBack[nCardBackIdx+1], currPlayers[nPlyrIdx].theDeck.scorePile[nDeckTester].cBack[nCardBackIdx+2], currPlayers[nPlyrIdx].theDeck.scorePile[nDeckTester].nPointVal);
        nDeckTester++;
    }
    // ==========================================
    
    // STAGE II: Check if eligible tank card was present, if yes, add drawn card to score pile, otherwise, add to tank pile.

    if (nChecker < currPlayers[nPlyrIdx].theDeck.nScoreAmt) // If the score changes, it means there was an increase in the score pile.
    {
        // Slots the drawn card to the score pile.

        currPlayers[nPlyrIdx].theDeck.nScoreAmt++; // Increments the amount of cards in the score pile.
        // nScoreIdx++;

        currPlayers[nPlyrIdx].theDeck.scorePile[nScoreIdx].cFront = theGame.deck[nDeckIdx].cFront;
        currPlayers[nPlyrIdx].theDeck.scorePile[nScoreIdx].cBack[nCardBackIdx] = theGame.deck[nDeckIdx].cBack[nCardBackIdx];
        currPlayers[nPlyrIdx].theDeck.scorePile[nScoreIdx].cBack[nCardBackIdx+1] = theGame.deck[nDeckIdx].cBack[nCardBackIdx+1];
        currPlayers[nPlyrIdx].theDeck.scorePile[nScoreIdx].cBack[nCardBackIdx+2] = theGame.deck[nDeckIdx].cBack[nCardBackIdx+2];
        currPlayers[nPlyrIdx].theDeck.scorePile[nScoreIdx].nPointVal = theGame.deck[nDeckIdx].nPointVal;
        
        currPlayers[nPlyrIdx].theDeck.nCurrScore += theGame.deck[nDeckIdx].nPointVal; // Adds the point value of the drawn card.
        
        // ==========================================
        // DEBUGGING PRINTS 4 (TO BE REMOVED)

        nDeckTester = 0;
        printf("\n\nPlayer Deck at Stage II: A SIDE\n");
        while (nDeckTester != currPlayers[nPlyrIdx].theDeck.nScoreAmt)
        {
            nCardBackIdx = 0;
            printf("CARD IDX %d: Front: %c, Back: %c, %c, %c, Point Value: %d\n", nDeckTester, currPlayers[nPlyrIdx].theDeck.scorePile[nDeckTester].cFront, currPlayers[nPlyrIdx].theDeck.scorePile[nDeckTester].cBack[nCardBackIdx], currPlayers[nPlyrIdx].theDeck.scorePile[nDeckTester].cBack[nCardBackIdx+1], currPlayers[nPlyrIdx].theDeck.scorePile[nDeckTester].cBack[nCardBackIdx+2], currPlayers[nPlyrIdx].theDeck.scorePile[nDeckTester].nPointVal);
            nDeckTester++;
        }
        // ==========================================


    }
    else // If score doesn't change, it means that the drawn card is to be added to the tank cards.
    {
        
        // Checks null spaces to occupy first before incrementing to the next empty tank index.
        for (nCtr = 0; nCtr < currPlayers[nPlyrIdx].theDeck.nTankAmt; nCtr++)
        {
            if (currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cFront == '\0' && currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx] == '\0' && currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx+1] == '\0' && currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx+2] == '\0' && currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].nPointVal == 0)
            {
                currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cFront = theGame.deck[nDeckIdx].cFront;
                currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx] = theGame.deck[nDeckIdx].cBack[nCardBackIdx];
                currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx+1] = theGame.deck[nDeckIdx].cBack[nCardBackIdx+1];
                currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx+2] = theGame.deck[nDeckIdx].cBack[nCardBackIdx+2];
                currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].nPointVal = theGame.deck[nDeckIdx].nPointVal;

                nFlag++;
            }
        }

        // ==========================================
        // DEBUGGING PRINTS 5 (TO BE REMOVED)

        nDeckTester = 0;
        printf("\n\nPlayer Deck at Stage II: B SIDE SCORE\n");
        while (nDeckTester != currPlayers[nPlyrIdx].theDeck.nScoreAmt)
        {
            nCardBackIdx = 0;
            printf("CARD IDX %d: Front: %c, Back: %c, %c, %c, Point Value: %d\n", nDeckTester, currPlayers[nPlyrIdx].theDeck.scorePile[nDeckTester].cFront, currPlayers[nPlyrIdx].theDeck.scorePile[nDeckTester].cBack[nCardBackIdx], currPlayers[nPlyrIdx].theDeck.scorePile[nDeckTester].cBack[nCardBackIdx+1], currPlayers[nPlyrIdx].theDeck.scorePile[nDeckTester].cBack[nCardBackIdx+2], currPlayers[nPlyrIdx].theDeck.scorePile[nDeckTester].nPointVal);
            nDeckTester++;
        }
        // ==========================================

        // Otherwise, add the drawn card to the next empty tank index slot.

        if (nFlag == 0)
        {
            currPlayers[nPlyrIdx].theDeck.nTankAmt++; // Increments amount of tank cards in the pile.

            currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cFront = theGame.deck[nDeckIdx].cFront;
            currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx] = theGame.deck[nDeckIdx].cBack[nCardBackIdx];
            currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx+1] = theGame.deck[nDeckIdx].cBack[nCardBackIdx+1];
            currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx+2] = theGame.deck[nDeckIdx].cBack[nCardBackIdx+2];
            currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].nPointVal = theGame.deck[nDeckIdx].nPointVal;

            // ==========================================
            // DEBUGGING PRINTS 6 (TO BE REMOVED)

            nDeckTester = 0;
            printf("\n\nPlayer Deck at Stage II: B SIDE TANK\n");
            while (nDeckTester != currPlayers[nPlyrIdx].theDeck.nTankAmt)
            {
                nCardBackIdx = 0;
                printf("CARD IDX %d: Front: %c, Back: %c, %c, %c, Point Value: %d\n", nDeckTester, currPlayers[nPlyrIdx].theDeck.tankPile[nDeckTester].cFront, currPlayers[nPlyrIdx].theDeck.tankPile[nDeckTester].cBack[nCardBackIdx], currPlayers[nPlyrIdx].theDeck.tankPile[nDeckTester].cBack[nCardBackIdx+1], currPlayers[nPlyrIdx].theDeck.tankPile[nDeckTester].cBack[nCardBackIdx+2], currPlayers[nPlyrIdx].theDeck.tankPile[nDeckTester].nPointVal);
                nDeckTester++;
            }
            // ==========================================
        }


    }

    // Remove the drawn card from the game deck.

    theGame.deck[nDeckIdx].cFront = '\0';
    theGame.deck[nDeckIdx].cBack[nCardBackIdx] = '\0';
    theGame.deck[nDeckIdx].cBack[nCardBackIdx+1] = '\0';
    theGame.deck[nDeckIdx].cBack[nCardBackIdx+2] = '\0';
    theGame.deck[nDeckIdx].nPointVal = 0;

    // ==========================================
    // DEBUGGING PRINTS 7 (TO BE REMOVED)

    nDeckIdx = 0;
    printf("\n\nGame Deck after score flow\n");
    while (nDeckIdx != MAX_CARDS)
    {
        nCardBackIdx = 0;
        printf("CARD IDX %d: Front: %c, Back: %c, %c, %c, Point Value: %d\n", nDeckIdx, theGame.deck[nDeckIdx].cFront, theGame.deck[nDeckIdx].cBack[nCardBackIdx], theGame.deck[nDeckIdx].cBack[nCardBackIdx+1], theGame.deck[nDeckIdx].cBack[nCardBackIdx+2], theGame.deck[nDeckIdx].nPointVal);
        nDeckIdx++;
    }
    // ==========================================

}

/*
    The function stealFlow()...
*/
void stealFlow(PlayerData currPlayers[], GameState theGame, int nPlyrIdx, int nDeckIdx)
{


    
}

/*
    The function runGame()...
*/
void runGame()
{   
    
    // Declarations

    FILE* fPlayers;
    FILE* fCards;
    PlayerData currPlayers[PLAYER_MAX];
    GameState theGame;

    int nCardNum = 0; // The index to start at after card dealing.
    int nRoundCtr = 0; // A counter for the number of rounds occurred within the game.
    int nGameSignal = 1; // Can only be '1' or '0'. Signals the game's start or end.
    
    int nPlyrIdx; // Player Index Number
    int nDeckIdx; // Game Deck Index Number
    int nCardBackIdx; // Index of Card's Back Colors
    //int nScoreIdx = 0; // Player's Score Pile Index

    int nChoice; // Can only be '1' or '2'. Choice of the player to score or steal. 1 = Score, 2 = Steal.

    // Winner Declarations
    //Username Winner; // Username of the winner.
    //int nWinScore; // The winner's score.
    //int nWinPNum; // Player number of the winner.

    // Initialization Processes
    initRandom();

    fPlayers = fopen("players.txt", "r");
    theGame.nPlyrCtr = playerInit(currPlayers, fPlayers);
    fclose(fPlayers);

    printf("\nTOTAL PLAYER COUNT: %d\n", theGame.nPlyrCtr); // To be removed.

    fCards = fopen("mantis.txt", "r");
    nCardNum = deckInit(theGame.nPlyrCtr, fCards, currPlayers, &theGame);
    fclose(fCards);

    if (nCardNum > 0)
        nGameSignal = 0;

    printf("\nNEXT CARD STARTS AT IDX: %d\n", nCardNum); // To be removed.

    // ==========================================
    // DEBUGGING PRINTS 3 (TO BE REMOVED)

    nDeckIdx = 0;
    printf("\n\nGame Deck after deckInit()\n");
    while (nDeckIdx != MAX_CARDS)
    {
        nCardBackIdx = 0;
        printf("CARD IDX %d: Front: %c, Back: %c, %c, %c, Point Value: %d\n", nDeckIdx, theGame.deck[nDeckIdx].cFront, theGame.deck[nDeckIdx].cBack[nCardBackIdx], theGame.deck[nDeckIdx].cBack[nCardBackIdx+1], theGame.deck[nDeckIdx].cBack[nCardBackIdx+2], theGame.deck[nDeckIdx].nPointVal);
        nDeckIdx++;
    }
    // ==========================================

    // Game Proper
    printf("\n\n[LET THE GAMES BEGIN!]\n");
    nDeckIdx = nCardNum;
    nRoundCtr = 1;

    while (nGameSignal != 1)
    {
        printf("\n[ ROUND %d ]\n\n", nRoundCtr);  
        
        for (nPlyrIdx = 0; nPlyrIdx < theGame.nPlyrCtr; nPlyrIdx++)
        {
            nCardBackIdx = 0;
            
            displayDeck(currPlayers, theGame);
            printf("Top Deck: %c%c%c (%d cards remaining in deck)\n\n", theGame.deck[nDeckIdx].cBack[nCardBackIdx], theGame.deck[nDeckIdx].cBack[nCardBackIdx+1], theGame.deck[nDeckIdx].cBack[nCardBackIdx+2], MAX_CARDS-nDeckIdx);

            printf("Your move, Player %d (%s)\n", currPlayers[nPlyrIdx].nPNum, currPlayers[nPlyrIdx].playerName);
            printf("    [1] Score\n");
            printf("    [2] Steal\n");

            do
            {
                printf("\n>> ");
                scanf("%d", &nChoice);

                if (nChoice > 2 || nChoice < 1)
                    printf("\nInvalid input! \'1\' or \'2\' only!");

            } while (nChoice > 2 || nChoice < 1);

            if (nChoice == 1)
            {
                // Score Flow
                scoreFlow(currPlayers, theGame, nPlyrIdx, nDeckIdx/*, &nScoreIdx*/);

            }
            else if (nChoice == 2)
            {
                // Steal Flow
                stealFlow(currPlayers, theGame, nPlyrIdx, nDeckIdx);
            }

            nDeckIdx++;

        }

        nRoundCtr++;
    }

    // Present the Winner (INCOMPLETE)

    //printf("\n\n[ VICTORY ACHIEVED! ]\n\n");
    //printf("With a score of %d, Player %d - (%s) has conquered the match!\n", nWinScore, nWinPNum, Winner);
}