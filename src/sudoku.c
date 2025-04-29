#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "sudoku.h"

/**
 * Description:  Deallocate a full Sudoku grid
 * Param: sudoku  9x9 grid previously returned by setPuzzle()
 */
void freePuzzle(Square *** sudoku) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            free(sudoku[row][col]);
        }
        free(sudoku[row]);
    }
    free(sudoku);
}
/**
 * Description:  Check a 3x3 box for the presence of a value.
 * Param: sudoku  9x9 grid of Square pointers
 * Param: row     starting row of the box
 * Param: col     starting column of the box
 * Param: val     value to search for (1–9)
 * Return: int    1 if not found (valid), 0 if found (invalid)
 */
int checkBox(Square *** sudoku, int row, int col, int val)
{
    for (int x = 0; x < SIZE_ROWS / 3; x++) {
        for (int y = 0; y < SIZE_COLS / 3; y++) {
            if (sudoku != NULL)
            {
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
 * Description:  Check a row for the presence of val
 * Param: sudoku  9x9 grid
 * Param: row     row index to search
 * Param: val     value to search for
 * Return: int    1 if not found, 0 if found
 */
int checkRow(Square *** sudoku, int row, int val) 
{
    for (int col = 0; col < SIZE_COLS; col++) {  
        if (sudoku[row][col] -> number == val) {
            return 0;
        }
    }
    return 1;
}


/**
 * Description:  Check a column for val
 * Param: sudoku  9x9 grid
 * Param: col     column index
 * Param: val     value to search
 * Return: int    1 if not found, 0 if found
 */
int checkColumn(Square *** sudoku,int col, int val)
{
    for (int row = 0; row < SIZE_ROWS; row++) {
        if (sudoku[row][col] -> number == val) {
            return 0;
        }
    }
    return 1;
}


/**
 * Description:  Fill one 3x3 box with random valid values
 * Param: row     box-start row
 * Param: col     box-start column
 * Param: sudoku  grid to fill
 * side-effect: mutates sudoku[][]->number
 */
void fillBox(int row, int col, Square *** sudoku)
{
    int val = rand() % 9 + 1;

    for(int x = 0; x < SIZE_ROWS / 3; x++)
    {
        for (int y = 0; y < SIZE_COLS / 3; y++)
        {
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
 * Description:  Recursively fill puzzle via backtracking
 * Param: sudoku  grid to fill
 * Param: row     row index
 * Param: col     column index
 */ 
int fillPuzzle(Square *** sudoku, int row, int col)
{
    if (row == SIZE_ROWS)
        return 1;

    if (col == SIZE_COLS)
        return fillPuzzle(sudoku, row + 1, 0);

    if (sudoku[row][col] -> number != 0)
        return fillPuzzle(sudoku, row, col + 1);

    return insertValues(sudoku, row, col);
}


/**
 * Description:  Tries values 1-9 at cell indicated by row,col
 * Param: sudoku  grid to fill
 * Param: row     row index
 * Param: col     column index
 */
int insertValues(Square *** sudoku, int row, int col)
{
    for (int val = 1; val < 10; val++) {
        if (checkPuzzle(sudoku, row, col, val)) {
            sudoku[row][col] -> number = val;

            if (fillPuzzle(sudoku, row, col + 1))
                return 1;

            sudoku[row][col] -> number = 0;
        }
    }
    return 0;
}

/**
 * Description:  Remove random values from puzzle based off difficulty
 * Param: difficulty  # cells to remove
 */
void removeValues(Square *** sudoku, int difficulty) {
    printf("Selected difficulty is: %d", difficulty);
    while (difficulty > 0) {
        int square = rand() % 81;

        int i = square / 9;

        int j = square % 9;

        if (sudoku[i][j] -> number != 0) {

            sudoku[i][j] -> number = 0;

            difficulty--;
        }
    }
}



/**
 * Description:  Allocate and initialize an empty grid, then fill diagonal boxes.
 * Return: Square***  fresh 9x9 grid
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
        puzzle[row] = malloc(sizeof(*puzzle[row]) * SIZE_COLS);
        if (!puzzle[row]) {
            perror("malloc puzzle[row]");
            for (int i = 0; i < row; i++) {
                free(puzzle[i]);
            }
            free(puzzle);
            exit(1); 
        }

        for (int col = 0; col < SIZE_COLS; col++)
        {
            puzzle[row][col] = malloc(sizeof(*puzzle[row][col]));
            if (!puzzle[row][col]) {
                perror("malloc puzzle[row][col]");
                for (int j = 0; j < col; j++) {
                    free(puzzle[row][j]);
                }
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

            puzzle[row][col]->number = 0;
            puzzle[row][col]->row    = row;
            puzzle[row][col]->column = col;
        }
    }

    for (int i = 0; i < SIZE_ROWS; i += SIZE_ROWS/3) {
        fillBox(i, i, puzzle);
    }

    return puzzle;
}


/**
 * Description:  Print the 9x9 grid with ASCII border
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



