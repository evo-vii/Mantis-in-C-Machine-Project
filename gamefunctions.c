/******************************************************************************
 *  Description     : This is the primary file housing the game flow functions and is normally accessed via
                      playing the actual game. Cannot be accessed otherwise in other main menu options.
 *  Author/s        : Kabigting, Derrell Maiko V.
 *                    Sanico, Lance Matthew G.
 *  Section         : S12A
 *  Last Modified   : 03/11/2026
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

    @return nCount - The total number of players that will participate in a match.
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
    @param nGameSeed - The seed for the number randomizer used in shuffling the card deck.

    @return nCardNum - The index of the game's deck to continue incrementing after removing the dealt cards at initialization.

*/
int deckInit(int nCount, FILE* fPtr, PlayerData currPlayers[], GameState *theGame, int nGameSeed) // Check for seed settings
{

    int nDeckIdx = 0; // Index of card deck
    int nCardBackIdx; // Index of the card's back colors
    char cTemp; // Placeholder for reading newlines.
    int nPlyrIdx = 0; // Index of player roster.

    int nSeed = nGameSeed; // Seed set by default or by the player.
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


/**
    The function scoreFlow() is the first branch of a player move in this program. It utilizes many factors such
    as variables and structure members. Several of its functionality includes the removal or addition to the player's
    tank pile & score pile, as well as tracking the necessary values such as card amounts, indexes, and points. This is the
    only function in the program that directly focuses on the score aspect (points and score pile) of the player.

    @param currPlayers - The player list containing all players for a running match.
    @param theGame - This is the main control structure of the game, containing relevant information such as the game's deck and player count.
    @param nPlyrIdx - This is the index pertaining to the current player making the move.
    @param nDeckIdx - The index of the current drawn card being handled.

*/
void scoreFlow(PlayerData currPlayers[], GameState theGame, int nPlyrIdx, int nDeckIdx) // DEVNOTE-LANCE: Make sure to make print debug statements to check the status of array members.
{
    int nCardBackIdx = 0;
    int nCtr;
    int nTankCardCtr = 0;
    int nTankPtsSum = 0;

    int nChecker = currPlayers[nPlyrIdx].theDeck.nScoreAmt; // Compares against current nScoreAmt after STAGE I is complete.
    int nFlag = 0; // Stays 0 at STAGE II if the tank card was not slotted into a nulled slot. This means, the next empty tank index slot is to be utilized. If non-zero, card was successfully slotted at a null slot.

    //int nDeckTester; // FOR DEBUGGING PURPOSES

    printf("\nResolving turn for Player %d...\n", currPlayers[nPlyrIdx].nPNum);
    printf("- %s draws a card and it is: %c (%d pt/s)\n", currPlayers[nPlyrIdx].playerName, theGame.deck[nDeckIdx].cFront, theGame.deck[nDeckIdx].nPointVal);

    // STAGE I: Checks if drawn card is present in any of the player's tank pile.

    for (nCtr = 0; nCtr < currPlayers[nPlyrIdx].theDeck.nTankAmt; nCtr++)
    {
        if (currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cFront == theGame.deck[nDeckIdx].cFront) // If a tank card is similar to the drawn card.
        {   
            // Slots the tank card into the score pile.
            currPlayers[nPlyrIdx].theDeck.scorePile[currPlayers[nPlyrIdx].theDeck.nScoreAmt].cFront = currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cFront;
            currPlayers[nPlyrIdx].theDeck.scorePile[currPlayers[nPlyrIdx].theDeck.nScoreAmt].cBack[nCardBackIdx] = currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx];
            currPlayers[nPlyrIdx].theDeck.scorePile[currPlayers[nPlyrIdx].theDeck.nScoreAmt].cBack[nCardBackIdx+1] = currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx+1];
            currPlayers[nPlyrIdx].theDeck.scorePile[currPlayers[nPlyrIdx].theDeck.nScoreAmt].cBack[nCardBackIdx+2] = currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx+2];
            currPlayers[nPlyrIdx].theDeck.scorePile[currPlayers[nPlyrIdx].theDeck.nScoreAmt].nPointVal = currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].nPointVal;

            // Adds the point value of the eligible tank card in the player's score.
            currPlayers[nPlyrIdx].theDeck.nCurrScore += currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].nPointVal;

            currPlayers[nPlyrIdx].theDeck.nScoreAmt++; // Increments the amount of cards in the score pile.

            // Manages data to be presented at the print statements (Number of eligible tank cards and points earned from tanks).
            nTankCardCtr++;
            nTankPtsSum += currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].nPointVal;

            // "Nulls" the eligible tank card from the player.
            currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cFront = '\0';
            currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx] = '\0';
            currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx+1] = '\0';
            currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx+2] = '\0';
            currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].nPointVal = 0;
        }    
    }
    
    // STAGE II: Check if eligible tank card was present, if yes, add drawn card to score pile, otherwise, add to tank pile.

    if (nChecker < currPlayers[nPlyrIdx].theDeck.nScoreAmt) // If the score changes, it means there was an increase in the score pile.
    {
        // Slots the drawn card to the score pile.

        currPlayers[nPlyrIdx].theDeck.scorePile[currPlayers[nPlyrIdx].theDeck.nScoreAmt].cFront = theGame.deck[nDeckIdx].cFront;
        currPlayers[nPlyrIdx].theDeck.scorePile[currPlayers[nPlyrIdx].theDeck.nScoreAmt].cBack[nCardBackIdx] = theGame.deck[nDeckIdx].cBack[nCardBackIdx];
        currPlayers[nPlyrIdx].theDeck.scorePile[currPlayers[nPlyrIdx].theDeck.nScoreAmt].cBack[nCardBackIdx+1] = theGame.deck[nDeckIdx].cBack[nCardBackIdx+1];
        currPlayers[nPlyrIdx].theDeck.scorePile[currPlayers[nPlyrIdx].theDeck.nScoreAmt].cBack[nCardBackIdx+2] = theGame.deck[nDeckIdx].cBack[nCardBackIdx+2];
        currPlayers[nPlyrIdx].theDeck.scorePile[currPlayers[nPlyrIdx].theDeck.nScoreAmt].nPointVal = theGame.deck[nDeckIdx].nPointVal;
        
        currPlayers[nPlyrIdx].theDeck.nCurrScore += theGame.deck[nDeckIdx].nPointVal; // Adds the point value of the drawn card.

        currPlayers[nPlyrIdx].theDeck.nScoreAmt++; // Increments the amount of cards in the score pile.

        printf("- Player %d has (%d) %c card/s worth a total of %d points!\n", currPlayers[nPlyrIdx].nPNum, nTankCardCtr, theGame.deck[nDeckIdx].cFront, nTankPtsSum);
        printf("- %s scores %d points in the Score pile\n", currPlayers[nPlyrIdx].playerName, nTankPtsSum+theGame.deck[nDeckIdx].nPointVal);
    }
    else // If score doesn't change, it means that the drawn card is to be added to the tank cards.
    {
        
        // Checks null spaces to occupy first before incrementing to the next empty tank index.
        for (nCtr = 0; nCtr < currPlayers[nPlyrIdx].theDeck.nTankAmt && nFlag == 0; nCtr++)
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

        // Otherwise, add the drawn card to the next empty tank index slot.

        if (nFlag == 0)
        {
            currPlayers[nPlyrIdx].theDeck.nTankAmt++; // Increments amount of tank cards in the pile.

            currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cFront = theGame.deck[nDeckIdx].cFront;
            currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx] = theGame.deck[nDeckIdx].cBack[nCardBackIdx];
            currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx+1] = theGame.deck[nDeckIdx].cBack[nCardBackIdx+1];
            currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx+2] = theGame.deck[nDeckIdx].cBack[nCardBackIdx+2];
            currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].nPointVal = theGame.deck[nDeckIdx].nPointVal;
        }

        printf("- Player %d has no %c card...\n", currPlayers[nPlyrIdx].nPNum, theGame.deck[nDeckIdx].cFront);
        printf("- Adding drawn card to tank pile of %s\n", currPlayers[nPlyrIdx].playerName);
    }

    // Remove the drawn card from the game deck.
    theGame.deck[nDeckIdx].cFront = '\0';
    theGame.deck[nDeckIdx].cBack[nCardBackIdx] = '\0';
    theGame.deck[nDeckIdx].cBack[nCardBackIdx+1] = '\0';
    theGame.deck[nDeckIdx].cBack[nCardBackIdx+2] = '\0';
    theGame.deck[nDeckIdx].nPointVal = 0;

}

/**
    The function stealFlow() utilizes the various game factors in a similar way as scoreFlow().
    However in this function, the interactions are mostly between members of currPlayers[] which
    are the player stealing, and the player being stolen from. The first stage checks in the victim
    player's array for any available cards. Whatever the result is signalled and retrieved into the
    second stage to deal the necessary actions accordingly, such as which player to give the drawn
    card to.

    @param currPlayers - The player list containing all players for a running match.
    @param theGame - This is the main control structure of the game, containing relevant information such as the game's deck and player count.
    @param nPlyrIdx - This is the index pertaining to the current player making the move.
    @param nDeckIdx - The index of the current drawn card being handled.
*/
void stealFlow(PlayerData currPlayers[], GameState theGame, int nPlyrIdx, int nDeckIdx)
{

    PlayerData BufferList[PLAYER_MAX];
    int nBuffIdx = 0; // Index number of buffer array member

    int nCtr; // General counter
    int nCtr2;
    int nCardBackIdx = 0;

    int nVicIdx;
    int nDispCtr = 1; // A display counter for player selection.
    int nTankCtr = 0; // Counter for number of tank cards.
    int nChoice; // Choice tracker for victim player.
    int nStolen = 0; // Number of eligible cards in the victim player's tank pile.

    int nFlag; // A checker for null slots in tank pile.

    // Initial Messages
    printf("\nChoose the adversary you wish to steal from.\n");

    // Cycles through player selection of whom to steal from.

    for (nCtr = 0; nCtr < theGame.nPlyrCtr; nCtr++)
    {
        if (nCtr != nPlyrIdx)
        {
            printf("    [%d] Player %d (%s)\n", nDispCtr, currPlayers[nCtr].nPNum, currPlayers[nCtr].playerName);
            BufferList[nBuffIdx] = currPlayers[nCtr];

            nBuffIdx++;
            nDispCtr++;
        }
    }

    do
    {
        printf("\n\n>> ");
        scanf("%d", &nChoice);

        if (nChoice > theGame.nPlyrCtr || nChoice < 1)
            printf("\nInvalid Input! \'1\' - \'%d\' only!\n", theGame.nPlyrCtr);

    } while (nChoice > theGame.nPlyrCtr || nChoice < 1);

    nBuffIdx = nChoice - 1;

    // Retrieves the player of the respective index;
    for (nCtr = 0; nCtr < theGame.nPlyrCtr; nCtr++)
    {
        if (BufferList[nBuffIdx].nPNum == currPlayers[nCtr].nPNum)
            nVicIdx = nCtr;
    }

    // STAGE I: Checks if drawn card is present in victim player's tank pile.

    for (nCtr = 0; nCtr < currPlayers[nVicIdx].theDeck.nTankAmt; nCtr++)
    {
        if (currPlayers[nVicIdx].theDeck.tankPile[nCtr].cFront == theGame.deck[nDeckIdx].cFront) // If a tank card is similar to the drawn card.
        {   
            nTankCtr++;
            nStolen++;
            nFlag = 0;

            // Checks null spaces to occupy first before incrementing to the next empty tank index.
            for (nCtr2 = 0; nCtr2 < currPlayers[nPlyrIdx].theDeck.nTankAmt && nFlag == 0; nCtr2++)
            {
                if (currPlayers[nPlyrIdx].theDeck.tankPile[nCtr2].cFront == '\0' && currPlayers[nPlyrIdx].theDeck.tankPile[nCtr2].cBack[nCardBackIdx] == '\0' && currPlayers[nPlyrIdx].theDeck.tankPile[nCtr2].cBack[nCardBackIdx+1] == '\0' && currPlayers[nPlyrIdx].theDeck.tankPile[nCtr2].cBack[nCardBackIdx+2] == '\0' && currPlayers[nPlyrIdx].theDeck.tankPile[nCtr2].nPointVal == 0)
                {                  
                    currPlayers[nPlyrIdx].theDeck.tankPile[nCtr2].cFront = currPlayers[nVicIdx].theDeck.tankPile[nCtr].cFront;
                    currPlayers[nPlyrIdx].theDeck.tankPile[nCtr2].cBack[nCardBackIdx] = currPlayers[nVicIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx];
                    currPlayers[nPlyrIdx].theDeck.tankPile[nCtr2].cBack[nCardBackIdx+1] = currPlayers[nVicIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx+1];
                    currPlayers[nPlyrIdx].theDeck.tankPile[nCtr2].cBack[nCardBackIdx+2] = currPlayers[nVicIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx+2];
                    currPlayers[nPlyrIdx].theDeck.tankPile[nCtr2].nPointVal = currPlayers[nVicIdx].theDeck.tankPile[nCtr].nPointVal;

                    // "Nulls" the respective tank card on the victim's pile.
                    currPlayers[nVicIdx].theDeck.tankPile[nCtr].cFront = '\0';
                    currPlayers[nVicIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx] = '\0';
                    currPlayers[nVicIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx+1] = '\0';
                    currPlayers[nVicIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx+2] = '\0';
                    currPlayers[nVicIdx].theDeck.tankPile[nCtr].nPointVal = 0;

                    nFlag++;
                }
            }

            // Increments the tank amount of the stealing player otherwise.
            if (nFlag == 0)
            {
                currPlayers[nPlyrIdx].theDeck.nTankAmt++; // Increments amount of tank cards in the pile.

                currPlayers[nPlyrIdx].theDeck.tankPile[nCtr2].cFront = currPlayers[nVicIdx].theDeck.tankPile[nCtr].cFront;
                currPlayers[nPlyrIdx].theDeck.tankPile[nCtr2].cBack[nCardBackIdx] = currPlayers[nVicIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx];
                currPlayers[nPlyrIdx].theDeck.tankPile[nCtr2].cBack[nCardBackIdx+1] = currPlayers[nVicIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx+1];
                currPlayers[nPlyrIdx].theDeck.tankPile[nCtr2].cBack[nCardBackIdx+2] = currPlayers[nVicIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx+2];
                currPlayers[nPlyrIdx].theDeck.tankPile[nCtr2].nPointVal = currPlayers[nVicIdx].theDeck.tankPile[nCtr].nPointVal;

                // "Nulls" the respective tank card on the victim's pile.
                currPlayers[nVicIdx].theDeck.tankPile[nCtr].cFront = '\0';
                currPlayers[nVicIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx] = '\0';
                currPlayers[nVicIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx+1] = '\0';
                currPlayers[nVicIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx+2] = '\0';
                currPlayers[nVicIdx].theDeck.tankPile[nCtr].nPointVal = 0;
            }

        }    
    }

    // STAGE II: Check which player gets the drawn card.

    if (nTankCtr == 0) // If steal was unsuccessful
    {
        nFlag = 0;

        // Checks null spaces to occupy first before incrementing to the next empty tank index.
        for (nCtr = 0; nCtr < currPlayers[nVicIdx].theDeck.nTankAmt && nFlag == 0; nCtr++)
        {
            if (currPlayers[nVicIdx].theDeck.tankPile[nCtr].cFront == '\0' && currPlayers[nVicIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx] == '\0' && currPlayers[nVicIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx+1] == '\0' && currPlayers[nVicIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx+2] == '\0' && currPlayers[nVicIdx].theDeck.tankPile[nCtr].nPointVal == 0)
            {    
                currPlayers[nVicIdx].theDeck.tankPile[nCtr].cFront = theGame.deck[nDeckIdx].cFront;
                currPlayers[nVicIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx] = theGame.deck[nDeckIdx].cBack[nCardBackIdx];
                currPlayers[nVicIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx+1] = theGame.deck[nDeckIdx].cBack[nCardBackIdx+1];
                currPlayers[nVicIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx+2] = theGame.deck[nDeckIdx].cBack[nCardBackIdx+2];
                currPlayers[nVicIdx].theDeck.tankPile[nCtr].nPointVal = theGame.deck[nDeckIdx].nPointVal;

                nFlag++;
            }
        }

        // Increments the tank amount of the stealing player otherwise.
        if (nFlag == 0)
        {
            currPlayers[nVicIdx].theDeck.nTankAmt++; // Increments amount of tank cards in the pile.

            currPlayers[nVicIdx].theDeck.tankPile[nCtr].cFront = theGame.deck[nDeckIdx].cFront;
            currPlayers[nVicIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx] = theGame.deck[nDeckIdx].cBack[nCardBackIdx];
            currPlayers[nVicIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx+1] = theGame.deck[nDeckIdx].cBack[nCardBackIdx+1];
            currPlayers[nVicIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx+2] = theGame.deck[nDeckIdx].cBack[nCardBackIdx+2];
            currPlayers[nVicIdx].theDeck.tankPile[nCtr].nPointVal = theGame.deck[nDeckIdx].nPointVal;
        }

        printf("\nResolving turn for Player %d...\n", currPlayers[nPlyrIdx].nPNum);
        printf("- %s draws a card and it is: %c (%d pt/s)\n", currPlayers[nPlyrIdx].playerName, theGame.deck[nDeckIdx].cFront, theGame.deck[nDeckIdx].nPointVal);
        printf("- Player %d (%s) has no %c card/s!\n", currPlayers[nVicIdx].nPNum, currPlayers[nVicIdx].playerName, theGame.deck[nDeckIdx].cFront);
        printf("- Player %d fails in stealing from Player %d!\n", currPlayers[nPlyrIdx].nPNum, currPlayers[nVicIdx].nPNum);
        printf("- Adding drawn card to the tank pile of %s!\n", currPlayers[nVicIdx].playerName);
    }
    else // If player has successfully stolen
    {
        nFlag = 0;

        // Checks null spaces to occupy first before incrementing to the next empty tank index.
        for (nCtr = 0; nCtr < currPlayers[nPlyrIdx].theDeck.nTankAmt && nFlag == 0; nCtr++)
        {
            if (currPlayers[nPlyrIdx].theDeck.tankPile[nCtr2].cFront == '\0' && currPlayers[nPlyrIdx].theDeck.tankPile[nCtr2].cBack[nCardBackIdx] == '\0' && currPlayers[nPlyrIdx].theDeck.tankPile[nCtr2].cBack[nCardBackIdx+1] == '\0' && currPlayers[nPlyrIdx].theDeck.tankPile[nCtr2].cBack[nCardBackIdx+2] == '\0' && currPlayers[nPlyrIdx].theDeck.tankPile[nCtr2].nPointVal == 0)
            {
                currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cFront = theGame.deck[nDeckIdx].cFront;
                currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx] = theGame.deck[nDeckIdx].cBack[nCardBackIdx];
                currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx+1] = theGame.deck[nDeckIdx].cBack[nCardBackIdx+1];
                currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx+2] = theGame.deck[nDeckIdx].cBack[nCardBackIdx+2];
                currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].nPointVal = theGame.deck[nDeckIdx].nPointVal;

                nFlag++;
                nTankCtr++;
            }
        }

        // Increments the tank amount of the stealing player otherwise.
        if (nFlag == 0)
        {
            currPlayers[nPlyrIdx].theDeck.nTankAmt++; // Increments amount of tank cards in the pile.
            
            currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cFront = theGame.deck[nDeckIdx].cFront;
            currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx] = theGame.deck[nDeckIdx].cBack[nCardBackIdx];
            currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx+1] = theGame.deck[nDeckIdx].cBack[nCardBackIdx+1];
            currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].cBack[nCardBackIdx+2] = theGame.deck[nDeckIdx].cBack[nCardBackIdx+2];
            currPlayers[nPlyrIdx].theDeck.tankPile[nCtr].nPointVal = theGame.deck[nDeckIdx].nPointVal;

            nTankCtr++;
        }

        printf("\nResolving turn for Player %d...\n", currPlayers[nPlyrIdx].nPNum);
        printf("- %s draws a card and it is: %c (%d pt/s)\n", currPlayers[nPlyrIdx].playerName, theGame.deck[nDeckIdx].cFront, theGame.deck[nDeckIdx].nPointVal);
        printf("- Player %d (%s) has %d %c card/s!\n", currPlayers[nVicIdx].nPNum, currPlayers[nVicIdx].playerName, nStolen, theGame.deck[nDeckIdx].cFront);
        printf("- Player %d successfully steals from Player %d!\n", currPlayers[nPlyrIdx].nPNum, currPlayers[nVicIdx].nPNum);
        printf("- +%d (%c) cards to the tank pile of %s!\n", nTankCtr, theGame.deck[nDeckIdx].cFront, currPlayers[nPlyrIdx].playerName);       
    }

    // Remove the drawn card from the game deck.

    theGame.deck[nDeckIdx].cFront = '\0';
    theGame.deck[nDeckIdx].cBack[nCardBackIdx] = '\0';
    theGame.deck[nDeckIdx].cBack[nCardBackIdx+1] = '\0';
    theGame.deck[nDeckIdx].cBack[nCardBackIdx+2] = '\0';
    theGame.deck[nDeckIdx].nPointVal = 0;
    
}

/**
    The function runGame() utilizes all of the functions beforehand and arranges
    everything to properly run the Mantis game flow. Various variables are declared
    int his function for control purposes. Similarly, the win condition and player turn
    loops are all declared here. This is also the primary function in which the player
    and card files are to be initialized.

    @param nWinScore - The score that determines the winning mark and the game's end.
    @param nGameSeed - The seed for the number randomizer used in shuffling the card deck.

*/
void runGame(int nWinScore, int nGameSeed)
{   
    
    // Declarations

    // Essentials
    FILE* fPlayers;
    FILE* fCards;
    PlayerData currPlayers[PLAYER_MAX];
    GameState theGame;

    // Game Controls
    int nCardNum = 0; // The index to start at after card dealing.
    int nRoundCtr = 0; // A counter for the number of rounds occurred within the game.
    int nGameSignal = 1; // Can only be '1' or '0'. Signals the game's start or end.
    
    // Essential Indexes
    int nPlyrIdx; // Player Index Number
    int nDeckIdx; // Game Deck Index Number
    int nCardBackIdx; // Index of Card's Back Colors

    // Miscellaneous
    int nChoice; // Can only be '1' or '2'. Choice of the player to score or steal. 1 = Score, 2 = Steal.
    int nGenCtr; // General Counter

    // Winner Variables
    int nWinTag;
    PlayerData Winners[PLAYER_MAX];
    int nWindex = 0;
    
    // Sorting Algorithim Variables
    int nI;
    int nJ;
    int nMin;
    PlayerData Temp;
    
    // Null Player (For Placeholding Use)
    PlayerData NullPlayer;

    // Null Player Initializations
    strcpy(NullPlayer.playerName, "NULL");
    NullPlayer.nPNum = -999;
    NullPlayer.nScoreMax = -999;
    NullPlayer.nGameWins = -999;
    NullPlayer.theDeck.nCurrScore = -999;
    NullPlayer.theDeck.nTankAmt = -999;

    // Initialization Processes

    fPlayers = fopen("players.txt", "r");
    theGame.nPlyrCtr = playerInit(currPlayers, fPlayers);
    fclose(fPlayers);

    fCards = fopen("mantis.txt", "r");
    nCardNum = deckInit(theGame.nPlyrCtr, fCards, currPlayers, &theGame, nGameSeed);
    fclose(fCards);

    if (nCardNum > 0)
        nGameSignal = 0;

    // GAME PROPER
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
                scoreFlow(currPlayers, theGame, nPlyrIdx, nDeckIdx);

            }
            else if (nChoice == 2)
            {
                // Steal Flow
                stealFlow(currPlayers, theGame, nPlyrIdx, nDeckIdx);
            }

            nDeckIdx++;

        }

        nRoundCtr++;

        // Setting the win conditions to flag nGameSignal to 1. Ceases the game regardless of potential tie.
        for (nPlyrIdx = 0; nPlyrIdx < theGame.nPlyrCtr; nPlyrIdx++)
        {
            if (currPlayers[nPlyrIdx].theDeck.nCurrScore >= nWinScore || nDeckIdx >= MAX_CARDS - 1)
            {
                nGameSignal = 1; // Signals the game's end.
                nWinTag++;

                Winners[nWindex] = currPlayers[nPlyrIdx]; // Assigns eligible players to the winners' array.
                nWindex++;
                
            }
        }

    }

    // Nullifying Empty Spaces within the Winners' Index
    for (nGenCtr = nWindex; nGenCtr < PLAYER_MAX; nGenCtr++)
    {
        Winners[nGenCtr] = NullPlayer;
    }

    // Sorting Algo BASED ON SCORE
    for (nI = 0; nI < PLAYER_MAX; nI++)
    {
        nMin = nI;
        for (nJ = nI+1; nJ < PLAYER_MAX; nJ++)
        {
            if (Winners[nMin].theDeck.nCurrScore > Winners[nJ].theDeck.nCurrScore)
                nMin = nJ;
        }

        if (nI != nMin)
        {
            Temp = Winners[nI];
            Winners[nI] = Winners[nMin];
            Winners[nMin] = Temp;
        }
    }

    // Game Messages:

    printf("\n\nTHE GAME HAS CEASED! THE RESULTS WILL BE DISPLAYED...\n");
    printf("This can either end ALONE...or a TIE! But it will be difficult!\n\n");

    nChoice = 0;

    do
    {
        printf("    [1] Confirm End Game\n");
        printf("\n>> ");

        scanf("%d", &nChoice);

        if (nChoice != 1)
        {
            printf("\nInvalid input! Type \'1\' only!\n\n");
        }
    } while (nChoice != 1);

    if (nWinTag > 1) // Second layer of winners' comparison, if there are more than 1 players that achieved the Winning Score.
    {
        nWinTag = 0;

        // COMPARING BY SCORE FIRST
        for (nGenCtr = 0; nGenCtr < PLAYER_MAX; nGenCtr++)
        {
            if (Winners[nGenCtr].theDeck.nCurrScore < Winners[nGenCtr + 1].theDeck.nCurrScore)
            {                     
                Winners[nGenCtr] = NullPlayer;
                nWinTag++;
            }
        }

        // COMPARISON BY TANKS
        if (nWinTag > 1)
        {
            for (nGenCtr = 0; nGenCtr < PLAYER_MAX; nGenCtr++)
            {
                if (Winners[nGenCtr].theDeck.nTankAmt < Winners[nGenCtr + 1].theDeck.nTankAmt)
                {
                    Winners[nGenCtr] = NullPlayer;
                    nWinTag++;
                }
            }
        }

    }

    // FINAL VERDICT
    printf("\n\n[ VICTORY ACHIEVED! ]\n\n");

    printf("\nPresenting the Final Results:\n");

    displayDeck(currPlayers, theGame);

    printf("\nHere are the Victor/s: \n");

    for (nGenCtr = PLAYER_MAX-1; Winners[nGenCtr].nPNum != -999; nGenCtr--)
    {
        printf("Player %d (%s), wins!\n",  Winners[nGenCtr].nPNum, Winners[nGenCtr].playerName);
    }

    // Return to Main Menu

    // Return to Previous Menus
    printf("\nType \'1\' to return to the main menu and save player data.\n");
    nChoice = 0;

    do
    {
        printf("\n>> ");
        scanf("%d", &nChoice);

        if (nChoice != 1)
            printf("\nInvalid input! Type \'1\' only!");
    } while (nChoice != 1);
}

/**

    The function updatePlayerStats() 

*/
void updatePlayerStats(FILE* fPtr, PlayerData currPlayers[])
{

}