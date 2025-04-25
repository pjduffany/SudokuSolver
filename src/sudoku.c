// sudoku.c
//
// Attribution:
//   Primary Author: Patrick Duffany
//   Contributor: Zack Ahmed (Verification)

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "sudoku.h"

/**
 * Author: Patrick Duffany
 * Description:  Deallocate a full Sudoku grid
 * Param: sudoku  9x9 grid previously returned by setPuzzle()
 * Side-effects: frees all malloc’d memory
 */
void freePuzzle(Square *** sudoku) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            free(sudoku[row][col]); // free each Square
        }
        free(sudoku[row]); // free each row
    }
    free(sudoku); // free top-level pointer
}
/**
 * Author: Patrick Duffany
 * Description:  Check a 3x3 box for the presence of a value.
 * Param: sudoku  9x9 grid of Square pointers
 * Param: row     starting row of the box
 * Param: col     starting column of the box
 * Param: val     value to search for (1–9)
 * Return: int    1 if not found (valid), 0 if found (invalid)
 * Vulnerability: Failure to Handle Errors [4-1] calls perror() if sudoku is NULL and handles mis-init
 */
int checkBox(Square *** sudoku, int row, int col, int val)
{
    for (int x = 0; x < SIZE_ROWS / 3; x++) {
        for (int y = 0; y < SIZE_COLS / 3; y++) {
            if (sudoku != NULL)
            {
                // check if the value is present in the box
                if (sudoku[row + x][col + y] -> number == val) {
                    return 0;
                }
            } else {
                perror("Failed to initialize puzzle...\n");
            }
        }
    }
    return 1;
}

/**
 * Author: Patrick Duffany
 * Description:  Check a row for the presence of val
 * Param: sudoku  9x9 grid
 * Param: row     row index to search
 * Param: val     value to search for
 * Return: int    1 if not found, 0 if found
 * Vulnerability: Buffer Overrun [1-1] loop ensure grid's width is never exceeded before indexing into fixed-sized array
 */
int checkRow(Square *** sudoku, int row, int val) 
{
    for (int col = 0; col < SIZE_COLS; col++) {  
        // check if the value is present in the row
        if (sudoku[row][col] -> number == val) {
            return 0;
        }
    }
    return 1;
}


/**
 * Author: Patrick Duffany
 * Description:  Check a column for val
 * Param: sudoku  9x9 grid
 * Param: col     column index
 * Param: val     value to search
 * Return: int    1 if not found, 0 if found
 * Vulnerability: Buffer Overrun [1-2] loop ensure grid's width is never exceeded before indexing into fixed-sized array
 */
int checkColumn(Square *** sudoku,int col, int val)
{
    for (int row = 0; row < SIZE_ROWS; row++) {
        // check if the value is present in the column
        if (sudoku[row][col] -> number == val) {
            return 0; // return false
        }
    }
    return 1; // return true
}


/**
 * Author: Patrick Duffany
 * Description:  Fill one 3x3 box with random valid values
 * Param: row     box-start row
 * Param: col     box-start column
 * Param: sudoku  grid to fill
 * side-effect: mutates sudoku[][]->number
 * Vulnerability: Failure to Handle Errors [4-2] calls perror() and avoid bad state/undefined behavior
 */
void fillBox(int row, int col, Square *** sudoku)
{
    int val = rand() % 9 + 1;

    for(int x = 0; x < SIZE_ROWS / 3; x++)
    {
        for (int y = 0; y < SIZE_COLS / 3; y++)
        {
            // check if the value is already in the box
            while (!checkBox(sudoku, row, col, val))
            {
                val = (rand() % 9) + 1;
            }
            if (sudoku != NULL)
            {
                sudoku[row + x][col + y] -> number =  val;

            } else {
                perror("Failed to initialize sudoku puzzle...\n"); 
                EXIT_FAILURE;
            }
        }
    }
}


/**
 * Author: Patrick Duffany
 * Description:  validity check of puzzle
 * Param: sudoku  grid to fill
 * Param: row     box-start row
 * Param: col     box-start column
 * Param: val     number 1-9
 */
int checkPuzzle(Square *** sudoku, int row, int col, int val)
{
    // offset rows and columns for boxes
    int boxStartRow = row - row % 3;
    int boxStartCol = col - col % 3;

    return checkRow(sudoku, row, val) &&
           checkColumn(sudoku, col, val) &&
           checkBox(sudoku, boxStartRow, boxStartCol, val);
}


/**
 * Author: Patrick Duffany
 * Description:  Recursively fill puzzle via backtracking
 * Param: sudoku  grid to fill
 * Param: row     row index
 * Param: col     column index
 */ 
int fillPuzzle(Square *** sudoku, int row, int col)
{
    // end of puzzle
    if (row == SIZE_ROWS)
        return 1;

    // end of column
    if (col == SIZE_COLS)
        return fillPuzzle(sudoku, row + 1, 0);

    // Square is already filled
    if (sudoku[row][col] -> number != 0)
        return fillPuzzle(sudoku, row, col + 1);

    return insertValues(sudoku, row, col);
}


/**
 * Author: Patrick Duffany
 * Description:  Tries values 1-9 at cell indicated by row,col
 * Param: sudoku  grid to fill
 * Param: row     row index
 * Param: col     column index
 */
int insertValues(Square *** sudoku, int row, int col)
{
    // try inserting values
    for (int val = 1; val < 10; val++) {
        if (checkPuzzle(sudoku, row, col, val)) {
            sudoku[row][col] -> number = val;

            if (fillPuzzle(sudoku, row, col + 1))
                return 1; // return true

            sudoku[row][col] -> number = 0; // Backtrack
        }
    }
    return 0; // triggers backtracking
}

/**
 * Author: Patrick Duffany
 * Description:  Remove random values from puzzle based off difficulty
 * Param: difficulty  # cells to remove
 * Vulnerability: Integer Overflow [6-1] rand() is bound to 81 squares so it doesn't overflow with fixed grid
 */
void removeValues(Square *** sudoku, int difficulty) {
    printf("Selected difficulty is: %d", difficulty);
    while (difficulty > 0) {
        int square = rand() % 81;

        // get the row
        int i = square / 9;

        // get column index
        int j = square % 9;

        // Remove the digit if the cell is not already empty
        if (sudoku[i][j] -> number != 0) {

            // Empty the cell
            sudoku[i][j] -> number = 0;

            // Decrease the count
            difficulty--;
        }
    }
}



/**
 * Author: Patrick Duffany
 * Description:  Allocate and initialize an empty grid, then fill diagonal boxes.
 * Return: Square***  fresh 9x9 grid
 * Vulnerability: Failure to Handle Errors [4-4],[4-5],[4-6] prevents undefined behavior if malloc fails and exits
 */
Square *** setPuzzle()
{
    Square ***puzzle = malloc(sizeof(*puzzle) * SIZE_ROWS);
    if (!puzzle) {
        perror("malloc puzzle");
        exit(1);  
    }

    srand((unsigned)time(NULL));

    for (int row = 0; row < SIZE_ROWS; row++)
    {
        // allocate row
        puzzle[row] = malloc(sizeof(*puzzle[row]) * SIZE_COLS);
        if (!puzzle[row]) {
            perror("malloc puzzle[row]");
            // clean up any previously allocated rows
            for (int i = 0; i < row; i++) {
                free(puzzle[i]);
            }
            free(puzzle);
            exit(1); 
        }

        for (int col = 0; col < SIZE_COLS; col++)
        {
            // allocate the individual cell
            puzzle[row][col] = malloc(sizeof(*puzzle[row][col]));
            if (!puzzle[row][col]) {
                perror("malloc puzzle[row][col]");
                // clean up this rows cells
                for (int j = 0; j < col; j++) {
                    free(puzzle[row][j]);
                }
                // clean up prior rows
                for (int i = 0; i < row; i++) {
                    for (int j = 0; j < SIZE_COLS; j++) {
                        free(puzzle[i][j]);
                    }
                    free(puzzle[i]);
                }
                free(puzzle[row]);
                free(puzzle);
                exit(1); 
            }

            // initialize members
            puzzle[row][col]->number = 0;
            puzzle[row][col]->row    = row;
            puzzle[row][col]->column = col;
        }
    }

    // Fill diagonal boxes (uses symbolic SIZE_ROWS)
    for (int i = 0; i < SIZE_ROWS; i += SIZE_ROWS/3) {
        fillBox(i, i, puzzle);
    }

    return puzzle;
}


/**
 * Author: Patrick Duffany
 * Description:  Print the 9x9 grid with ASCII border
 * Vulnerability: Buffer Overrun [1-3] nested loop ensures we remain in the 9x9 grid
 */
void printPuzzle(Square *** puzzle)
{
    printf("-------------------------------\n");
    for (int x = 0; x < 9; x++)
    {
        for (int y = 0; y < 9; y++)
        {
            if (y == 0)
            {
                printf("|");
            }
            printf(" %d ", puzzle[x][y] -> number);
            if ((y + 1) % 3 == 0)
            {
                printf("|");
            }

        }
        printf("\n");
        if ((x + 1) % 3 == 0)
        {
            printf("-------------------------------\n");
        }
    }
}



