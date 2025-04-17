#include <stdio.h>
#include "sudoku.h"

int UNSOLVED = 81;
int SIZE_ROWS = 9;
int SIZE_COLS = 9;

int main() {
    int** puzzle = createPuzzle();
    int solved = 0;

    Sudoku * sudoku = setPuzzle(puzzle);
    printPuzzle(sudoku -> squares);

    while (UNSOLVED > 0)
    {
        solved = checkPuzzle(sudoku->squares, sudoku -> boxes);

        if (solved == 0)
        {
            printf("Failed to solve puzzle...\n");
            break;
        }
    }

    printf("\n\n");
    printPuzzle(sudoku -> squares);

    return 0;
}
