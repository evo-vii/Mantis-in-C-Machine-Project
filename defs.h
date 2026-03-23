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

// Type Definitions
typedef char Username[USERCHAR_MAX];

typedef struct CardDetails
{
    char cFront;
    char cBack[3];
    int nPointVal;
} Card;

typedef struct GameBase
{
    int nPlyrCtr;
    Card deck[MAX_CARDS];
} GameState;

typedef struct PDeck
{
    int nTankAmt;
    int nColorCards[COLORS];
    Card tankPile[MAX_CARDS];

    int nScoreAmt;
    int nCurrScore;
    Card scorePile[MAX_CARDS];
} PlayerDeck;

typedef struct PDT
{
    Username playerName;
    int nPNum;
    int nScoreMax;
    int nGameWins;
    PlayerDeck theDeck;

} PlayerData;

// typedef struct GameStatus
// {
//     Card deck[MAX_CARDS];
//     int deck_size;
//     int draw_index; //next card in the draw pile
//     int tanks[6][COLORS];
//     int scores[6];
//     int playercount;
// } GameState;


