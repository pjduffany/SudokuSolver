#include <stdio.h>
#include "puzzle.h"
#include "sudoku.h"

int UNSOLVED = 81;
int SIZE_ROWS = 9;
int SIZE_COLS = 9;

int main() {
    int** puzzle = createPuzzle();


    Square *** sudoku = setPuzzle(puzzle);
    printPuzzle(sudoku);

    checkPuzzle(sudoku);
    printf("\n");
    printPuzzle(sudoku);

    return 0;
}
