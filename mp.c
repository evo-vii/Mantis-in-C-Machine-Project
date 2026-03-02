
// INTRODUCTION

/**

* Description : This is a modified version of the Mantis Card game in text form, written in C99 and is
                capable to be ran on a command line interpreter.
* Author/s : Kabigting, Derrell Maiko V.
*            Sanico, Lance Matthew G.
* Section : S12A
* Last Modified : 2/15/26
* Version : In-dev 0.0.2
* Acknowledgments : <list of references used in the making of this project>

*/

#include "defs.h"

// FUNCTION DECLARATIONS

// Game Proper

void startGame()
{
    printf("You are Starting the Game.");
}

// Game Control

void settings()
{
    printf("You are in the Settings Menu.");
}

void topPlayers()
{
    printf("You are in the Top Players Menu.");
}

void mainMenu()
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