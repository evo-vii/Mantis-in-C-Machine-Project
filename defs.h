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
#include "helpers_1.c"
#include "helpers_2.c"

// DEFINITIONS

// Constants
#define USERCHAR_MAX 37
#define MAX_CARDS 100
#define COLORS 7

// Type Definitions
typedef char Username[37];

typedef struct plyrDT
{
    Username playerName;
    int nScoreMax;
    int nGameWins;
} playerData;

typedef struct
{
    char front;
    char back[4];
} Card;

typedef struct 
{
    Card deck[MAX_CARDS];
    int deck_size;
    int draw_index; //next card in the draw pile
    int tanks[6][COLORS];
    int scores[6];
    int playercount;
} GameState;


