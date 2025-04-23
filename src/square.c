//
// Created by Patrick Duffany on 4/9/25.
//

#include "square.h"
#include "sudoku.h"

void solveSquare(Square * square)
{
    for (int x = 0; x < SIZE_ROWS; x++)
    {
        if (square -> possible[x] == 0)
        {
            square -> number = x + 1;
            square -> solvable = 0;
            UNSOLVED--;
        }
    }
}
