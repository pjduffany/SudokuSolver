#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "helper.h"
#include "sudoku.h"

int UNSOLVED = 81;
int SIZE_ROWS = 9;
int SIZE_COLS = 9;

int main() {
    int ** puzzle = (int**) malloc(sizeof (int*)*9);
    srand(time(0));

    for (int i = 0; i < 9; i++)
    {
        puzzle[i] = (int*) malloc(sizeof(int)*9);

        for (int j = 0; j < 9; j++)
        {
            puzzle[i][j] = 0;
        }
    }
    for (int i = 0; i < 9; i += 3) {
        fillBox(i, i, puzzle);
    }

    fillPuzzle(puzzle, 0, 0);
    printf("Solution to puzzle: \\n\\n");
    printPuzzleTest(puzzle);
    printf("\n\n");
    removeValues(puzzle);
    Sudoku * sudoku = setPuzzle(puzzle);
    printf("Empty puzzle: \n\n");

    printPuzzle(sudoku -> squares);

    int progress;
    while (UNSOLVED > 0)
    {
        progress = checkPuzzle(sudoku->squares, sudoku->boxes);

        if (progress == 0)
        {
            printf("\nFailed to solve the puzzle!");
            break;
        }
    }
    printf("\n\n");
    printPuzzle(sudoku -> squares);
    free(puzzle);
    free(sudoku);

    return 0;
}

