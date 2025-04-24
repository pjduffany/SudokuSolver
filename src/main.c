#include <stdio.h>
#include <time.h>
#include "sudoku.h"

int UNSOLVED = 81;
int SIZE_ROWS = 9;
int SIZE_COLS = 9;

int main() {
    Sudoku * sudoku = malloc(sizeof(Sudoku));
    sudoku -> puzzle = setPuzzle();

    // fill the puzzle using backtracking
    fillPuzzle(sudoku -> puzzle, 0, 0);

    // remove random values from the puzzle
    removeValues(sudoku -> puzzle);
    printf("Empty puzzle: \n");

    printPuzzle(sudoku -> puzzle);

    if ( fillPuzzle(sudoku -> puzzle, 0, 0) ) {
        printf("\n\nSucceeded!\n");
        printPuzzle(sudoku -> puzzle);
    } else {
        printf("No solution (should not happen!)\n");
    }

    free(sudoku);

    return 0;
}
