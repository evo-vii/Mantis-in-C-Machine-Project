/******************************************************************************
 *  Description     : This is the defs.h file of the Machine Project, including all necessary
                      type definitions and constant declarations to be used in the program.
 *  Author/s        : Kabigting, Derrell Maiko V.
 *                    Sanico, Lance Matthew G.
 *  Section         : S12A
 *  Last Modified   : 03/11/2026
******************************************************************************/

// PRE-PROCESSOR DIRECTIVES

#include <stdio.h>
#include <string.h>
// #include "helpers_1.c"
#include "helpers_2.c"

// DEFINITIONS

// Constants
#define USERCHAR_MAX 37
#define MAX_CARDS 100
#define COLORS 7
#define PLAYER_TAG 3
#define PLAYER_MAX 6

// Type Definitions
typedef char Username[37];
typedef char playerTag[PLAYER_TAG];

typedef struct Players
{
    Username playerName;
    playerTag PT;
    int nScoreMax;
    int nGameWins;
} PlayerData;

typedef struct CardDetails
{
    char front;
    char back[4];
} Card;

typedef struct GameStatus
{
    Card deck[MAX_CARDS];
    int deck_size;
    int draw_index; //next card in the draw pile
    int tanks[6][COLORS];
    int scores[6];
    int playercount;
} GameState;


