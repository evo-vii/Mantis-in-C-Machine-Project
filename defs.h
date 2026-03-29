/******************************************************************************
 *  Description     : This is the defs.h file of the Machine Project, including all necessary
                      type definitions and constant declarations to be used in the program.
 *  Author/s        : Kabigting, Derrell Maiko V.
 *                    Sanico, Lance Matthew G.
 *  Section         : S12A
 *  Last Modified   : 03/19/2026
******************************************************************************/

// PRE-PROCESSOR DIRECTIVES

#include <stdio.h>
#include <string.h>
// #include "helpers_1.c"
#include "helpers_2.c"

// DEFINITIONS

// Constants
#define USERCHAR_MAX 37
#define MAX_CARDS 84
#define COLORS 7
#define PLAYER_MAX 6
#define CARD_DEAL 4
#define MAX_PLAYER_LOAD 50

// Type Definitions
typedef char Username[USERCHAR_MAX]; // Type Definition for storing player names

/**
    Holds all details regarding a single card in Mantis.
*/
typedef struct CardDetails
{
    char cFront;   // Front face of card
    char cBack[3]; // Back colors of a card
    int nPointVal; // Attributed point value of card
} Card;

/**
    Central structure holding all primary details to be tracked in the game.
*/
typedef struct GameBase
{
    int nPlyrCtr;         // Total number of game players
    Card deck[MAX_CARDS]; // The game deck
} GameState;

/**
    The player's deck, and relevant deck information.
*/
typedef struct PDeck
{
    int nTankAmt;              // Max used index of tank pile
    int nTankCtr;              // Actual Number of Tank Cards
    int nColorCards[COLORS];   // Tracker for tank pile colors
    Card tankPile[MAX_CARDS];  // Tank pile

    int nScoreAmt;             // Max used index of score pile
    int nCurrScore;            // Current Score of player
    Card scorePile[MAX_CARDS]; // Score pile
} PlayerDeck;

/**
    All relevant variables regarding the player. Includes data imported from players.txt
*/
typedef struct PDT
{
    Username playerName; // Player username
    int nPNum;           // Player number during gameplay
    int nScoreMax;       // Player's all-time high score
    int nGameWins;       // Player's all time game wins
    PlayerDeck theDeck;  // Player's deck structure

} PlayerData;


