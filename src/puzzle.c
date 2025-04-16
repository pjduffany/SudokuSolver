//
// Created by Patrick Duffany on 4/6/25.
//
#include <stdlib.h>
#include <stdio.h>
#include "sudoku.h"
#include "square.h"

int updateSudoku(Square *** sudoku, int row, int col)
{
    int number = sudoku[row][col] -> number;

    for(int x = 0; x < SIZE_ROWS; x++)
    {
        if (sudoku[row][x] -> possible[number - 1] == 0)
        {
            sudoku[row][x] -> solvable--;
        }
        sudoku[row][x] -> possible[number - 1] = 1;
    }
    return 1;
}

int checkPuzzle(Square *** sudoku)
{
    for (int i = 0; i < SIZE_ROWS; i++)
    {
        for (int j = 0; j < SIZE_COLS; j++)
        {
            if (sudoku[i][j] -> solvable == 1)
            {
                solveSquare(sudoku[i][j]);
                updateSudoku(sudoku, i, j);
            }
        }
    }
    return 1;
}

void checkValues(Square *** sudoku)
{

}

Square *** setPuzzle(int ** puzzle)
{
    // allocate space for the Square struct
    Square *** sudoku = (Square***)malloc(sizeof(Square**)*9);
    // loop rows
    for (int i = 0; i < SIZE_ROWS; i++)
    {
        // allocate space for each row
        sudoku[i] = (Square**)malloc(sizeof(Square*)*9);
        // loop columns
        for (int j = 0; j < SIZE_COLS; j++)
        {
            // allocate space for each square
            sudoku[i][j] = (Square*)malloc(sizeof(Square));

            // assign number to sudoku
            sudoku[i][j] -> number = puzzle[i][j];

            //assign row and columns to each square
            sudoku[i][j] -> row = i;
            sudoku[i][j] -> column = j;
            sudoku[i][j] -> solvable = 9;

            for (int x = 0; x < SIZE_ROWS; x++)
            {
                sudoku[i][j] -> possible[x] = 0;
            }
        }
    }
    //checkValues(sudoku);
    for(int i = 0; i < SIZE_ROWS; i++)
    {
        for (int j = 0; j < SIZE_COLS; j++)
        {
            if (sudoku[i][j] -> number !=  0)
            {
                sudoku[i][j] -> solvable = 0;
                updateSudoku(sudoku, i, j);
                UNSOLVED--;
            }
        }
    }
    return sudoku;
}

int** createPuzzle()
{
    int** puzzle;
    int array[9][9] = {0, 1, 9,  8, 0, 2,  0, 0, 0,
                       4, 7,  0,  6, 9, 0,  0, 0, 1,
                       0, 0, 0,  4, 0, 0,  0, 9, 0,

                       8, 9, 4,  5, 0, 7,  0, 0, 0,
                       0, 0, 0,  0, 0, 0,  0, 0, 0,
                       0, 0, 0,  2, 0, 1,  9, 5, 8,

                       0, 5, 0,  7, 0, 6,  0, 0, 0,
                       6, 0, 0,  3, 2, 8,  0, 7, 9,
                       0, 0, 0,  1, 0, 0,  8, 6, 0};

    puzzle = (int**) malloc(sizeof (int*)*9);

    for (int i = 0; i < SIZE_ROWS; i++)
    {
        puzzle[i] = (int*) malloc(sizeof(int)*9);
        for (int j = 0; j < SIZE_COLS; j++)
        {
            puzzle[i][j] = array[i][j];
        }
    }
    return puzzle;
}

void printPuzzle(Square *** puzzle)
{
    printf("-------------------------------\n");
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (j == 0)
            {
                printf("|");
            }
            printf(" %d ", puzzle[i][j] -> number);
            if ((j + 1) % 3 == 0)
            {
                printf("|");
            }

        }
        printf("\n");
        if ((i + 1) % 3 == 0)
        {
            printf("-------------------------------\n");
        }
    }
}
