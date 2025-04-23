//
// Created by Patrick Duffany on 4/18/25.
//

#include "row.h"
#include "sudoku.h"
#include "box.h"

int checkRows(Square *** sudoku, Box ** boxes)
{
    int sum[9];
    int temp[9];

    // loop through rows
    for (int x = 0; x < 9; x++)
    {
        // loop through squares in row
        for (int y = 0; y < 9; y++)
        {
            sum[y] = 0;
            temp[y] = 0;
            if (sudoku[x][y] -> number != 0)
            {
                continue;
            }
            // loop through possible values
            for (int z = 0; z < 9; z++)
            {
                if (sudoku[x][y] -> possible[z] == 0)
                {
                    temp[z] = y;
                    sum[z]++;

                }
            }
        }
        for (int y = 0; y < 9; y++)
        {
            if (sum[y] == 1)
            {
                sudoku[x][temp[y]] -> number = y + 1;
                sudoku[x][temp[y]] -> solvable = 0;
                UNSOLVED--;

                updateSudoku(sudoku, x, temp[y]);
                updateBoxes(sudoku, x, temp[y]);

                return 1;
            }
        }
    }
    return 0;
}
