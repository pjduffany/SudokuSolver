//
// Created by Patrick Duffany on 4/10/25.
//

#include "box.h"
#include "sudoku.h"
#include <stdlib.h>

int checkBoxes(Square *** squares, Box ** boxes)
{
    //loop through boxes
    for(int i = 0; i < 9; i++)
    {
        // loop through possible values
        for (int j = 0; j < 9; j++)
        {
            int count = 0;
            int temp = 0;
            // loop through squares
            for (int k = 0; k < 9; k++)
            {
               if (boxes[i] -> squares[k] != 0)
                   continue;
               // found possible solution for val
               if (boxes[i] -> squares[k] -> possible[j] == 0)
               {
                   count++;
                   temp = k;
               }
               // current square is unsolvable
               if (count > 1)
                    break;
            }
            // found solution for square
            if (count == 1)
            {
                boxes[i] -> squares[temp] -> number = j + 1;
                boxes[i] -> squares[temp] -> solvable = 0;
                UNSOLVED--;
                updateSudoku(squares, boxes[i] -> squares[temp] -> row, boxes[i] -> squares[temp] -> column);
                return 1;
            }
        }
    }
    return 0;
}

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

void updateBoxes(Square *** sudoku, int row, int col)
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

