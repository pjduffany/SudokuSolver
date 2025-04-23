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

typedef struct Sudoku
{
  struct Square *** squares;
  struct Box ** boxes;
} Sudoku;


typedef struct Box
{
    struct Square ** squares;
    int numbers;
    int possible[9];
    int solvable;
} Box;

typedef struct Square
{
    int number;
    int possible[9];
    int solvable;
    Box * box;
    int row, column;
} Square;

int checkBox(Square *** sudoku, int row, int col, int val);
int checkRow(Square *** sudoku, int row, int val);
int checkColumn(Square *** sudoku,int col, int val);
void fillBox(int row, int col, Square *** sudoku);
int isValid(Square *** sudoku, int row, int col, int val);
int fillPuzzle(Square *** sudoku, int row, int col);
void removeValues(Square *** sudoku);
void printPuzzle(Square *** puzzle);
#endif //SUDOKU_SOLVER_SUDOKU_H
