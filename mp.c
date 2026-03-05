
// INTRODUCTION

/**

* Description : This is a modified version of the Mantis Card game in text form, written in C99 and is
                capable to be ran on a command line interpreter.
* Author/s : Kabigting, Derrell Maiko V.
*            Sanico, Lance Matthew G.
* Section : S12A
* Last Modified : 03/05/2026
* Version : In-dev 0.0.6
* Acknowledgments : <list of references used in the making of this project>

*/

/*
    PATCH NOTES In-dev 0.0.6 (To be UPDATED AND REPLACED at EVERY FILE MODIFICATION)

    In gamefunctions.c
    - Commented a warning for AI-generated lines of code (lines 50-142).
    - Note: As of 03/05/2026, gamefunctions.c has not undergone any form of formal debugging.

*/


#include "defs.h"

// FUNCTION DECLARATIONS

// Game Proper
/*
    The function startGame() calls the helper functions from the fil "gamefunctions.c",
    to begin processing the game flow including player initialization, deck preparation,
    game proper, and summarization of the game.
*/
void startGame()
{
    printf("You are Starting the Game.");
}

// Game Control

/*
    The function settings() brings the user to access the program's settings wherein various
    game preferences can be toggled and modified.
*/
void settings()
{
    printf("You are in the Settings Menu.");
}

/*
    The function topPlayers() brings the user to access the leaderboard from the last few
    games of MANTIS.
*/
void topPlayers()
{
    printf("You are in the Top Players Menu.");
}

void mainMenu() // TO BE TRANSFERRED TO MAIN IN THE FUTURE
{

    int nSelection;

    printf("\nWelcome to MANTIS\n");
    printf("Version In-dev 0.0.1\n\n");

    printf("Main Menu\n");
    printf("    [1] New Game\n");
    printf("    [2] Top Players\n");
    printf("    [3] Settings\n");
    printf("    [0] Exit\n\n");
    printf(">> ");

 
    scanf("%d", &nSelection);

    if (nSelection == 1)
        startGame();
    else if (nSelection == 2)
        topPlayers();
    else if (nSelection == 3)
        settings();
    else if (nSelection == 0)
        printf("You are exiting the program.\n");
    else
        printf("Invalid Input! Input Again!\n\n");

    if (nSelection > 3 || nSelection < 0)
    {
        while (nSelection > 3 || nSelection < 0)
        {
            printf(">> ");
            scanf("%d", &nSelection);

            if (nSelection == 1)
                startGame();
            else if (nSelection == 2)
                topPlayers();
            else if (nSelection == 3)
                settings();
            else if (nSelection == 0)
                printf("You are exiting the program.\n");
            else
                printf("Invalid Input! Input Again!\n\n");
        }
    }

}

// MAIN FUNCTION

int main()
{

    mainMenu();

    
    return 0;
}