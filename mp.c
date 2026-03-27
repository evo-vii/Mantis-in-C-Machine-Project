/******************************************************************************
 *  Description     : This is a modified version of the Mantis Card game in text form, written in C99 and is
                      capable to be ran on a command line interpreter. This is a local turn based game with settings
                      such as the winning score and the number randomizer's seed to be set as configurable by the
                      player user.
 *  Author/s        : Kabigting, Derrell Maiko V.
 *                    Sanico, Lance Matthew G.
 *  Section         : S12A
 *  Last Modified   : 03/27/2026
 *  Acknowledgments : 1. w3schools.com 
                      2. Search and Sorting Algoritms (by Ms. Kalaw)
                      3. What's a seed in a random number generator? Retrieved from: https://yourbasic.org/algorithms/random-number-generator-seed/
******************************************************************************/

/*
    PATCH NOTES Beta 0.1.1 (To be UPDATED AND REPLACED at EVERY FILE MODIFICATION)
    
    Primary
    - Primary game flow has been established.
    - Modified the description of the program.
    
    In mp.c
    - Began building settings() and topPlayers().
    - Established Settings to Change Winning Score.
    - 

    In gamefunctions.c
    - Established runGame().
    - Removed Debugging Tools.
    - Updated function comments for proper format.

    In defs.h
    - Removed original GameState structure.

    
*/


#include "gamefunctions.c"

// FUNCTION DECLARATIONS

// Game Proper
/**
    The function startGame() calls the helper functions from the file "gamefunctions.c",
    to begin processing the game flow including player initialization, deck preparation,
    game proper, and summarization of the game.

    @param nWinScore - The winning score needed to end the game and decide a winner. Modifiable via these settings.
    @param nGameSeed - The seed for the number randomizer used in shuffling the card deck.
*/
void startGame(int nWinScore, int nGameSeed)
{
 
    runGame(nWinScore, nGameSeed);
    
}

// Game Control

/**
    The function settings() brings the user to access the program's settings wherein various
    game preferences such as winning score, and randomizer seed can be configured.

    @param nWinScore - The winning score needed to end the game and decide a winner. Modifiable via these settings.
    @param nGameSeed - The seed for the number randomizer used in shuffling the card deck.

    @pre - Any modified settings will be reverted to default when the program terminates. The player must configure them once again upon another execution.
*/
void settings(int *nWinScore, int *nGameSeed)
{
    int nChoice; // Choice Tracker
    int nSetting; // Choice of Winning Score
    
    do // Main Menu for Settings
    {
        printf("\n[GAME SETTINGS]\n\n");
        printf("    [1] Set Win Score\n");
        printf("    [2] Set Randomizer Seed\n");
        printf("    [3] Return to Main Menu\n");


        printf("\n>> ");
        scanf("%d", &nChoice);

        if (nChoice > 3 || nChoice < 1)
            printf("\nInvalid input! \'1\' or \'2\' only!");
    } while (nChoice > 3 || nChoice < 1);

    if (nChoice == 1) // If player chooses to configure winning score.
    {
        printf("\n[Configure Winning Score]\n");
        printf("Current Winning Score: %d\n", *nWinScore);

        do
        {
            printf("\nSet Winning Score (Minimum: 10, Maximum: 100)\n");
            printf(">> ");
            scanf("%d", &nSetting);

            if (nSetting > 100 || nSetting < 10)
                printf("\nInvalid input! Follow the minimum and maximum allowed values!\n");

        } while (nSetting > 100 || nSetting < 10);

        printf("\nYou set the Winning Score to: %d\n", nSetting);

        *nWinScore = nSetting;

        printf("\nDo you wish to return to the Settings (Type \'1\') or the Main Menu? (Type \'0\')\n");

        nChoice = 0;

        do
        {
            printf("\n>> ");
            scanf("%d", &nChoice);

            if (nChoice > 1 || nChoice < 0)
                printf("\nInvalid input! \'1\' or \'2\' only!");
        } while (nChoice > 1 || nChoice < 0);

        if (nChoice == 1)
            settings(nWinScore, nGameSeed);

    }
    else if (nChoice == 2) // If the player chooses to configure the randomizer's seed.
    {

    }

}

/*
    The function topPlayers() brings the user to access the Mantis leaderboard.
    This is simply a display function, utilizing file access to retrieve the
    relevant data.
*/
void topPlayers()
{
    //FILE* fPlayers;
    
    printf("\n[MANTIS TOP PLAYERS]\n");
    printf("(Based on Most Wins)\n");

    // Start commands here.


}

void mainMenu(int nWinScore, int nGameSeed)
{

    int nSelection;
    // int nWinScore = 20; // Default Winning Score

    printf("\nWelcome to MANTIS\n");
    printf("Version Beta 0.1.1\n\n");

    printf("Main Menu\n");
    printf("    [1] New Game\n");
    printf("    [2] Top Players\n");
    printf("    [3] Settings\n");
    printf("    [0] Exit\n\n");
    
    do
    {
        printf(">> ");
        scanf("%d", &nSelection);

        if (nSelection == 1)
        {
            startGame(nWinScore, nGameSeed);
            mainMenu(nWinScore, nGameSeed); // Recursive Call
        }
        else if (nSelection == 2)
        {
            topPlayers();
            mainMenu(nWinScore, nGameSeed); // Recursive Call
        }
        else if (nSelection == 3)
        {
            settings(&nWinScore, &nGameSeed);
            mainMenu(nWinScore, nGameSeed); // Recursive Call
        }
        else if (nSelection == 0)
            printf("\nThank you for Playing Mantis!\n");
        else
            printf("Invalid Input! Input Again!\n\n");
    }
    while (nSelection > 3 || nSelection < 0);

}

// MAIN FUNCTION

int main()
{
    // Declaration of Player-set Variables.
    int nWinScore = 20;
    int nGameSeed;

    // Seed Initialization
    initRandom();
    nGameSeed = randomInt();

    // Calling the main menu of the game.
    mainMenu(nWinScore, nGameSeed);

    return 0;
}

/**
 * This is to certify that this project is my/our own work, based on my/our personal
 * efforts in studying and applying the concepts learned. I/We have constructed the
 * functions and their respective algorithms and corresponding code by myself/ourselves.
 * The program was run, tested, and debugged by my/our own efforts. I/We further certify
 * that I/we have not copied in part or whole or otherwise plagiarized the work of other
 * students and/or persons, nor did I employ the use of AI in any part of the deliverable.
 *
 * Kabigting, Derrell Maiko V. (ID NO.)
 * Sanico, Lance Matthew G.    12506311
 */