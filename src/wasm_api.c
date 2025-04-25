// wasm_api.c
//
// Attribution:
//   Primary Author: Patrick Duffany
//   Contributor: Zack Ahmed (Verification)

#include <stdlib.h>
#include "sudoku.h"

int SIZE_ROWS = 9;
int SIZE_COLS = 9;
// global variable to store the puzzle for later use
static Square *** puzzle = NULL;

/**
 * Author: Patrick Duffany
 * Description:  wrapper function to validity check of the value entered by user
 * Param: sudoku  grid to fill
 * Param: row     box-start row
 * Param: col     box-start column
 * Param: val     number 1-9
 */
int is_valid_buffer(int *buffer, int row, int col, int val) {
    return checkPuzzle(puzzle, row, col, val);
}

/**
 * Author: Patrick Duffany
 * Description: generate a new puzzle and copy it into a flat buffer for JS
 * Param: buffer  a pointer to 81 ints in WASM memory
 * Param: difficulty  number of cells to remove
 * Side-effects: frees all malloced memory
 * Vulnerability: Buffer Overrun [1-4] nested loop doesn't write past 81-element buffer
 */
void generate_puzzle(int *buffer, int difficulty) {
    puzzle = setPuzzle();

    // fill the puzzle using backtracking
    fillPuzzle(puzzle, 0, 0);

    // remove random values from the puzzle
    removeValues(puzzle, difficulty);

    // now copy into buffer:
    for (int row = 0; row < 9; row++)
        for (int col = 0; col < 9; col++)
            buffer[row * 9 + col] = puzzle[row][col] -> number;

    printf("Empty puzzle: \n");
    printPuzzle(puzzle);
}


/**
 * Author: Patrick Duffany
 * Description: Solve the previously generated puzzle, copy back to JS buffer.
 * Param: buffer  a pointer to 81 ints in WASM memory
 * Side-effects: prints debug info, then frees puzzle
 * Vulnerability: Format String [2-2] fixed string literals prevent format-string attacks
 */
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

