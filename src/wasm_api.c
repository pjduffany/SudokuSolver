//
// Created by Patrick Duffany on 4/23/25.
//
#include <stdlib.h>
#include "sudoku.h"

int SIZE_ROWS = 9;
int SIZE_COLS = 9;
// global variable to store the puzzle for later use
static Square *** puzzle = NULL;

int is_valid_buffer(int *buffer, int row, int col, int val) {
    return checkPuzzle(puzzle, row, col, val);
}

void generate_puzzle(int *buffer, int difficulty) {
    puzzle = setPuzzle();

    // fill the puzzle using backtracking
    fillPuzzle(puzzle, 0, 0);

    // remove random values from the puzzle
    removeValues(puzzle, difficulty);

    // copy into buffer
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

