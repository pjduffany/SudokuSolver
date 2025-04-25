// main.c
//
// Attribution:
//   Primary Author: Patrick Duffany
//   Contributor: Zack Ahmed

#include <stdio.h>
#include "sudoku.h"


/**
 * Author: Patrick Duffany
 * Description:  Console entry point: generate, display, solve, and display Sudoku puzzles
 * Return: int  0 on success; nonzero if memory allocation fails
 * Side-effects: prints to stdout; allocates and frees a Sudoku instance
 * Vulnerability: Format String [2-1] literal string format, hard-coded format strings
 * Vulnerability: Failure to Handle Errors [4-3] prevents undefined behavior if sudoku returns NULL
 */
int main() {
    Sudoku * sudoku = malloc(sizeof(Sudoku));

    if (!sudoku) {
        perror("malloc");            
        return 1;
    }

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

    free(sudoku); // free top-level struct

    return 0;
}
