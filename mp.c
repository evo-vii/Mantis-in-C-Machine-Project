
// INTRODUCTION

/******************************************************************************
 *  Description     : This is a modified version of the Mantis Card game in text form, written in C99 and is
                      capable to be ran on a command line interpreter.
 *  Author/s        : Kabigting, Derrell Maiko V.
 *                    Sanico, Lance Matthew G.
 *  Section         : S12A
 *  Last Modified   : 03/27/2026
 *  Acknowledgments : w3schools.com, Search and Sorting Algoritms (by Ms. Kalaw)
******************************************************************************/

/*
    PATCH NOTES Beta 0.1.1 (To be UPDATED AND REPLACED at EVERY FILE MODIFICATION)
    
    Primary
    - Primary game flow has been established.
    
    In mp.c
    - Began building settings() and topPlayers().

    In gamefunctions.c
    - Established runGame().
    - Removed Debugging Tools.
    - Updated function comments for proper format.

    
*/


#include "gamefunctionsCopy.c"

// FUNCTION DECLARATIONS

// Game Proper
/*
    The function startGame() calls the helper functions from the file "gamefunctions.c",
    to begin processing the game flow including player initialization, deck preparation,
    game proper, and summarization of the game.
*/
void startGame(int nWinScore)
{
 
    runGame(nWinScore);
    
}

// Game Control

/*
    The function settings() brings the user to access the program's settings wherein various
    game preferences such as winning score, and randomizer seed can be configured.
*/
void settings()
{
    int nChoice; // Choice tracker
    
    do
    {
        printf("\n[GAME SETTINGS]\n\n");
        printf("    [1] Set Win Score\n");
        printf("    [2] Set Randomizer Seed\n");

        printf("\n\n>> ");
        scanf("%d", &nChoice);

        if (nChoice > 2 || nChoice < 1)
            printf("\nInvalid input! \'1\' or \'2\' only!");
    } while (nChoice > 2 || nChoice < 1);

    if (nChoice == 1)
    {

    }
    else if (nChoice == 2)
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
    FILE* fPlayers;
    
    printf("\n[MANTIS TOP PLAYERS]\n");
    printf("(Based on Most Wins)\n");

    // Start commands here.


}

void mainMenu()
{

    int nSelection;
    int nWinScore = 20;

    printf("\nWelcome to MANTIS\n");
    printf("Version In-dev 0.1.0\n\n");

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
            startGame(nWinScore);
            mainMenu(); // Recursive Call
        }
        else if (nSelection == 2)
        {
            topPlayers();
            mainMenu(); // Recursive Call
        }
        else if (nSelection == 3)
        {
            settings();
            mainMenu(); // Recursive Call
        }
        else if (nSelection == 0)
            printf("You are exiting the program.\n");
        else
            printf("Invalid Input! Input Again!\n\n");
    }
    while (nSelection > 3 || nSelection < 0);

}

// MAIN FUNCTION

int main()
{
    mainMenu();

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
 * Sanico, Lance Matthew G.    (ID NO.)
 */