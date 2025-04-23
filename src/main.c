#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sudoku.h"

int UNSOLVED = 81;
int SIZE_ROWS = 9;
int SIZE_COLS = 9;

int main() {
    // allocate mem for sudoku
    Square *** sudoku = (Square***)malloc(sizeof(Square**)*9);
    srand(time(0));

    for (int i = 0; i < 9; i++)
    {
        // allocate mem for rows
        sudoku[i] = (Square**)malloc(sizeof(Square*)*9);

        for (int j = 0; j < 9; j++)
        {
            // allocate mem for cols
            sudoku[i][j] = (Square*)malloc(sizeof(Square));

            // initialize numbers to 0
            sudoku[i][j] -> number = 0;
        }
    }

    for (int i = 0; i < 9; i += 3) {
        // fill boxes diagonally
        fillBox(i, i, sudoku);
    }

    // fill the puzzle using backtracking
    fillPuzzle(sudoku, 0, 0);

    // remove random values from the puzzle
    removeValues(sudoku);
    printf("Empty puzzle: \n");

    printPuzzle(sudoku);

    if ( fillPuzzle(sudoku, 0, 0) ) {
        printf("\nSolution Found!\n");
        printPuzzle(sudoku);
    } else {
        printf("No solution found...This shouldn't happen.\n");
    }

    free(sudoku);

    return 0;
}

