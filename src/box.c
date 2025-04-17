//
// Created by Patrick Duffany on 4/10/25.
//

#include "box.h"
#include "sudoku.h"
#include <stdlib.h>

Box ** createBoxes()
{
    Box ** box = malloc(sizeof(Box*)*9);

    for (int x = 0; x < SIZE_ROWS; x++) {
        box[x] = malloc(sizeof(Box));
        box[x] -> squares = malloc(sizeof(Square*)*9);
        box[x] -> solvable = 9;
        box[x] -> numbers = 0;

        for (int y = 0; y < SIZE_COLS; y++) {
            box[x] -> possible[y] = 0;
        }
    }
    return box;
}

int updateBoxes(Square *** sudoku, int row, int col)
{
    Box * box = sudoku[row][col] -> box;
    int num = sudoku[row][col] -> number;
    for (int x = 0; x < SIZE_ROWS; x++)
    {
        if (box -> squares[x] -> possible[num - 1] == 0)
        {
            box -> squares[x] -> solvable--;
            box -> squares[x] -> possible[num - 1] = 1;
        }
    }
}

