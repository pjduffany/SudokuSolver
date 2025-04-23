//
// Created by Patrick Duffany on 4/22/25.
//

#include "helper.h"
#include <stdlib.h>
int checkBox(int ** sudoku, int row, int col, int val) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (sudoku[row + i][col + j] == val) {
                return 0;
            }
        }
    }
    return 1;
}


int checkRow(int ** sudoku, int row, int val)
{
    for (int col = 0; col < 9; col++) {
        if (sudoku[row][col] == val) {
            return 0;
        }
    }
    return 1;
}

int checkColumn(int ** sudoku,int col, int val)
{
    for (int row = 0; row < 9; row++) {
        if (sudoku[row][col] == val) {
            return 0;
        }
    }
    return 1;
}

void fillBox(int row, int col, int ** sudoku)
{
    int val = rand() % 9 + 1;


    for(int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            while (!checkBox(sudoku, row, col, val))
            {
                val = (rand() % 9) + 1;
            }
            sudoku[row + i][col + j] =  val;
        }
    }
}

int isValid(int ** sudoku, int row, int col, int val)
{
    int boxStartRow = row - row % 3;
    int boxStartCol = col - col % 3;
    return checkRow(sudoku, row, val) &&
           checkColumn(sudoku, col, val) &&
           checkBox(sudoku, boxStartRow, boxStartCol, val);
}

int fillPuzzle(int ** sudoku, int row, int col)
{
    // end of puzzle
    if (row == 9)
        return 1;

    // end of column
    if (col == 9)
        return fillPuzzle(sudoku, row + 1, 0);

    // Skip filled cells
    if (sudoku[row][col] != 0)
        return fillPuzzle(sudoku, row, col + 1);

    // Try valid values 1–9
    for (int val = 1; val < 10; val++) {
        if (isValid(sudoku, row, col, val)) {
            sudoku[row][col] = val;

            if (fillPuzzle(sudoku, row, col + 1))
                return 1;

            sudoku[row][col] = 0; // Backtrack
        }
    }
    return 0; // Trigger backtracking
}


// Remove K digits randomly from the grid
// This will create a Sudoku puzzle by removing digits
void removeValues(int ** sudoku) {
    int count = 51;
    while ( count > 0) {

        // Pick a random cell
        int square = rand() % 81;

        // Get the row index
        int i = square / 9;

        // Get the column index
        int j = square % 9;

        // Remove the digit if the cell is not already empty
        if (sudoku[i][j] != 0) {

            // Empty the cell
            sudoku[i][j] = 0;

            // Decrease the count of digits to remove
            count--;
        }
    }
}

