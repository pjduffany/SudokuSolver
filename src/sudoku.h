#include <stdio.h>
#include <stdlib.h>
//
// Created by Patrick Duffany on 4/3/25.
//

#ifndef SUDOKU_SOLVER_SUDOKU_H
#define SUDOKU_SOLVER_SUDOKU_H
extern int UNSOLVED;
extern int SIZE_ROWS;
extern int SIZE_COLS;

typedef struct Box
{
    struct Square ** squares;
    int numbers;
    int possible[9];
    int solvable;
    struct Box * next;
} Box;

typedef struct Square
{
    int number;
    int possible[9];
    int solvable;
    Box * box;
    int row, column;
} Square;

int** createPuzzle();
#endif //SUDOKU_SOLVER_SUDOKU_H
