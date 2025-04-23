//
// Created by Patrick Duffany on 4/3/25.
//
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "sudoku.h"
#include "square.h"
#include "box.h"
#include "row.h"

Sudoku * createSudoku(Square *** squares, Box ** boxes)
{
    Sudoku  * sudoku = malloc(sizeof(Sudoku));
    sudoku -> squares = squares;
    sudoku -> boxes = boxes;

    return sudoku;
}

int updateSudoku(Square *** sudoku, int row, int col)
{
    int number = sudoku[row][col] -> number;

    for (int x = 0; x < SIZE_ROWS; x++)
    {
        if (sudoku[x][col]->possible[number - 1] == 0)
        {
            sudoku[x][col]->solvable--;
        }
        sudoku[x][col]->possible[number -1] = 1;
    }

    for (int y = 0; y < SIZE_COLS; y++)
    {
        if (sudoku[row][y]->possible[number - 1] == 0)
        {
            sudoku[row][y]->solvable--;
        }
        sudoku[row][y]->possible[number -1] = 1;
    }
    return 1;
}

int checkPuzzle(Square *** sudoku, Box ** boxes)
{
    for (int x = 0; x < SIZE_ROWS; x++)
    {
        for (int y = 0; y < SIZE_COLS; y++)
        {
            if (sudoku[x][y] -> solvable == 1)
            {
                solveSquare(sudoku[x][y]);
                updateSudoku(sudoku, x, y);
                updateBoxes(sudoku, x, y);

                return 1;
            }
        }
    }
    if (checkBoxes(sudoku , boxes))
        return 1;

    return checkRows(sudoku, boxes);
}

void updateValues(Square *** sudoku)
{
    for(int x = 0; x < SIZE_ROWS; x++)
    {
        for (int y = 0; y < SIZE_COLS; y++)
        {
            if (sudoku != NULL && sudoku[x][y] -> number !=  0)
            {
                sudoku[x][y] -> solvable = 0;
                updateSudoku(sudoku, x, y);
                updateBoxes(sudoku, x, y);
                UNSOLVED--;
            }
        }
    }
}

Sudoku * setPuzzle(int ** puzzle)
{
    // allocate space for the Square & boxes structs
    Square *** sudoku = (Square***)malloc(sizeof(Square**)*9);
    Box ** boxes = createBoxes();
    int currentBox = 0;
    // loop rows
    for (int x = 0; x < SIZE_ROWS; x++)
    {
        // allocate space for each row
        sudoku[x] = (Square**)malloc(sizeof(Square*)*9);
        // loop columns
        for (int y = 0; y < SIZE_COLS; y++)
        {
            // allocate space for each square
            sudoku[x][y] = (Square*)malloc(sizeof(Square));

            // assign number to sudoku
            sudoku[x][y] -> number = puzzle[x][y];

            //assign row and columns to each square
            sudoku[x][y] -> row = x;
            sudoku[x][y] -> column = y;
            sudoku[x][y] -> solvable = 9;

            boxes[currentBox] -> squares[boxes[currentBox] -> numbers] = sudoku[x][y];
            sudoku[x][y] -> box = boxes[currentBox];
            boxes[currentBox] -> numbers++;
            for (int z = 0; z < SIZE_ROWS; z++)
            {
                sudoku[x][y] -> possible[z] = 0;
            }
            if (y == 2 || y == 5)
            {
                currentBox++;
            }
        }
        currentBox -= 2;
        if (x == 2)
        {
            currentBox = 3;
        }
        if (x == 5)
        {
            currentBox = 6;
        }
    }
    updateValues(sudoku);
    return createSudoku(sudoku, boxes);
}

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

void printPuzzleTest(int ** puzzle)
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
            printf(" %d ", puzzle[x][y]);
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



