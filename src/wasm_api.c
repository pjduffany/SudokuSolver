//
// Created by Patrick Duffany on 4/23/25.
//
#include <stdlib.h>
#include "sudoku.h"

int SIZE_ROWS = 9;
int SIZE_COLS = 9;
// global variable to store the puzzle for later use
static Square *** puzzle = NULL;

void freePuzzle(Square *** sudoku) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            free(sudoku[row][col]); // free each Square
        }
        free(sudoku[row]); // free each row
    }
    free(sudoku); // free top-level pointer
}

// Expose a single flat-board API to JS
// `buffer` is a pointer to 81 ints in WASM memory.
void generate_puzzle(int *buffer) {
    puzzle = setPuzzle();

    // fill the puzzle using backtracking
    fillPuzzle(puzzle, 0, 0);

    // remove random values from the puzzle
    removeValues(puzzle);

    // now copy into buffer:
    for (int row = 0; row < 9; row++)
        for (int col = 0; col < 9; col++)
            buffer[row * 9 + col] = puzzle[row][col] -> number;

    printf("Empty puzzle: \n");
    printPuzzle(puzzle);
}

void fill_puzzle(int * buffer)
{
    if (fillPuzzle( puzzle, 0, 0))
    {
        printf("\n\nSucceeded!\n");
        for (int row = 0; row < 9; row++)
        {
            for (int col = 0; col < 9; col++)
            {
                if (puzzle[row][col] == NULL) {
                    printf("ERROR: puzzle[%d][%d] is NULL\n", row, col);
                } else if (puzzle[row][col]->number > 9 || puzzle[row][col] -> number < 0) {
                    printf("ERROR: puzzle[%d][%d] = %d (invalid)\n", row, col, puzzle[row][col]->number);
                } else {
                    // copy numbers into buffer
                    buffer[row * 9 + col] = puzzle[row][col] -> number;
                }
            }
        }
        printPuzzle(puzzle);
    } else {
        printf("No solution....should not happen!\n");
        printPuzzle(puzzle);
    }
    freePuzzle(puzzle);
}

