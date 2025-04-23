//
// Created by Patrick Duffany on 4/3/25.
//
#include <stdlib.h>
#include <stdio.h>
#include "sudoku.h"

int checkBox(Square *** sudoku, int row, int col, int val) {
    for (int x = 0; x < SIZE_ROWS / 3; x++) {
        for (int y = 0; y < SIZE_COLS / 3; y++) {
            if (sudoku[row + x][col + y] -> number == val) {
                return 0;
            }
        }
    }
    return 1;
}


int checkRow(Square *** sudoku, int row, int val)
{
    for (int col = 0; col < SIZE_COLS; col++) {
        if (sudoku[row][col] -> number == val) {
            return 0;
        }
    }
    return 1;
}

int checkColumn(Square *** sudoku,int col, int val)
{
    for (int row = 0; row < SIZE_ROWS; row++) {
        if (sudoku[row][col] -> number == val) {
            return 0; // return false
        }
    }
    return 1; // return true
}

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
            sudoku[row + x][col + y] -> number =  val;
        }
    }
}

int isValid(Square *** sudoku, int row, int col, int val)
{
    int boxStartRow = row - row % 3;
    int boxStartCol = col - col % 3;
    return checkRow(sudoku, row, val) &&
           checkColumn(sudoku, col, val) &&
           checkBox(sudoku, boxStartRow, boxStartCol, val);
}

int fillPuzzle(Square *** sudoku, int row, int col)
{
    // end of puzzle
    if (row == SIZE_ROWS)
        return 1;

    // end of column
    if (col == SIZE_COLS)
        return fillPuzzle(sudoku, row + 1, 0);

    // Square is already filled
    if (sudoku[row][col] ->number != 0)
        return fillPuzzle(sudoku, row, col + 1);

    // try inserting values
    for (int val = 1; val < 10; val++) {
        if (isValid(sudoku, row, col, val)) {
            sudoku[row][col] -> number = val;

            if (fillPuzzle(sudoku, row, col + 1))
                return 1; // return true

            sudoku[row][col] -> number = 0; // Backtrack
        }
    }
    return 0; // Trigger backtracking
}


// Remove random values from puzzle
void removeValues(Square *** sudoku) {
    int count = 51;
    while ( count > 0) {

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
            count--;
        }
    }
}


void printPuzzle(Square *** puzzle)
{
    printf("-------------------------------\n");
    for (int x = 0; x < SIZE_ROWS; x++)
    {
        for (int y = 0; y < SIZE_COLS; y++)
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




