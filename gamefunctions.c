/*

GAME PROPER FUNCTIONS FILE.

*/

#include "defs.h"


// SUPLEMENTARY GAME FUNCTIONS

// DEVNOTE-Lance: This is widely experimental and not yet to be implemented.
void displayDeck()
{

}

// PRIMARY GAME FUNCTIONS

/*
    The function playerInit() is the first stage of the game proper. (TBC)

    // DEVNOTE-Lance: Players are hard-coded in this version of the game function, adding new players, usernames and file handling will be added in the future.
*/
int playerInit(int nPlyrCnt)
{
    int nCount = 0;
    int nCtr;

    // Inserted temporary usernames while file handling is not yet set.
    Username plyrUN[6] = {"Antioch", "Constantinople", "Ur", "Northumbria", "Gaul", "Prussia"};
    
    do
    {
        printf("How many players?: ");
        scanf("%d", &nCount);
    } while (nCount > 6 || nCount < 3);

    for (nCtr = 0; nCtr < nCount; nCtr++)
    {
        printf("P%d: %s\n", nCtr+1, plyrUN[nCtr]);
    }

    return nCount;
}

/*
    The function deckInit() // DEVNOTE-Lance: WARNING! LINE 50-142 IS AI GENERATED CODE, PLEASE RE-PROGRAM AS SOON AS POSSIBLE!
*/
void deckinit(GameState *gs, int playercount) {
    gs->playercount = playercount;
    gs->deck_size = 0;
    gs->draw_index = 0;
    // const char colorKeys[] = {'R', 'O', 'Y', 'G', 'B', 'I', 'V'};

    for (int p = 0; p < playercount; p++) {
        gs->scores[p] = 0;
        for (int c = 0; c < COLORS; c++) {
            gs->tanks[p][c] = 0;
        }
    }

    // 1. Load deck from mantis.txt //
    FILE *fp = fopen("mantis.txt", "r");
    if (fp != NULL) {
        char f_color;
        char b_colors[4];
        int qty;
        
        // Robust parser to handle source tags like //
        while (gs->deck_size < MAX_CARDS && fscanf(fp, " %c", &f_color) == 1) {
            // If we hit a source tag, skip it and read the actual front color
            if (f_color == '[') {
                while (fgetc(fp) != ']'); 
                fscanf(fp, " %c", &f_color);
            }

            // Read the back colors and the quantity //
            if (fscanf(fp, " | %3s %d", b_colors, &qty) == 2) {
                int k = 0;
                while (k < qty && gs->deck_size < MAX_CARDS) {
                    gs->deck[gs->deck_size].front = f_color;
                    strcpy(gs->deck[gs->deck_size].back, b_colors);
                    gs->deck_size++;
                    k++;
                }
            }
        }
        fclose(fp);
    }

    shuffle(gs->deck, (size_t)gs->deck_size, sizeof(Card), 123);

    // deal 4 cards front up to the tank pile of each player
    for (int p = 0; p < gs->playercount; p++) {
        for (int i = 0; i < 4; i++) {
            char cardFront = gs->deck[gs->draw_index].front;
            int colorIdx = -1;

            switch (cardFront) {
                case 'R': 
                colorIdx = 0; 
                break;
                case 'O': 
                colorIdx = 1; 
                break;
                case 'Y': 
                colorIdx = 2; 
                break;
                case 'G': 
                colorIdx = 3; 
                break;
                case 'B': 
                colorIdx = 4; 
                break;
                case 'I': 
                colorIdx = 5; 
                break;
                case 'V': 
                colorIdx = 6;
            }

            if (colorIdx != -1) {
                gs->tanks[p][colorIdx]++;
            }
            gs->draw_index++; // increment draw pile
        }
    }
}

void displayState(GameState *gs) {
    const char colorKeys[] = {'R', 'O', 'Y', 'G', 'B', 'I', 'V'};
    for (int i = 0; i < gs->playercount; i++) {
        printf("P%d => [ ", i + 1);
        for (int j = 0; j < COLORS; j++) {
            printf("%c:%d", colorKeys[j], gs->tanks[i][j]);
            if (j < COLORS - 1) printf(" | ");
        }
        // Shows Score Pile after the //
        printf(" ] // %d\n", gs->scores[i]);
    }
}

/*
    The function scoreFlow()...
*/
int scoreFlow()
{

    return 999;
}

/*
    The function stealFlow()...
*/
int stealFlow()
{


    return 999;
}

/*
    The function runGame()...
*/
void runGame()
{

}


int main()
{
    
    // Player Count Variable
    int nPlyrCnt = 4;
    GameState game;

    deckinit(&game, nPlyrCnt);
    displayState(&game);

    // Actual Game Run


    return 0;
}