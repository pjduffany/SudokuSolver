#include <stdio.h>
#include "sudoku.h"

int main() {
    Sudoku * sudoku = malloc(sizeof(Sudoku));
    sudoku -> puzzle = setPuzzle();

    // fill the puzzle using backtracking
    fillPuzzle(sudoku -> puzzle, 0, 0);

    // remove random values from the puzzle
    removeValues(sudoku -> puzzle, 55);
    printf("Empty puzzle: \n");
    printPuzzle(sudoku -> puzzle);

    if ( fillPuzzle(sudoku -> puzzle, 0, 0) ) {
        printf("\n\nSucceeded!\n");
        printPuzzle(sudoku -> puzzle);
    } else {
        printf("No solution....should not happen!\n");
        printPuzzle(sudoku -> puzzle);
    }

    free(sudoku);

    return 0;
}
