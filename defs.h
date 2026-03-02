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

// DEFINITIONS

// Constants
#define USERCHAR_MAX 37;

// Type Definitions
typedef char[37] Username;


// Structures
struct playerData
{
    Username playerName;
    int nScoreMax;
    int nGameWins;
};
