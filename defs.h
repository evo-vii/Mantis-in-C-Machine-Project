/*

MANTIS - DEFS Header File

* Author/s : Kabigting, Derrell Maiko V.
*            Sanico, Lance Matthew G.
* Section : S12A
* Last Modified : 2/15/26

*/

// PRE-PROCESSOR DIRECTIVES

#include <stdio.h>
#include <string.h>
#include "helpers_1.c"
#include "helpers_2.c"

// DEFINITIONS

// Constants
#define USERCHAR_MAX 37;

// Type Definitions
typedef char Username[37];

typedef struct plyrDT
{
    Username playerName;
    int nScoreMax;
    int nGameWins;
} playerData;

