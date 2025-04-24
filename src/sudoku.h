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
  struct Square *** puzzle;
} Sudoku;

typedef struct Square
{
    int number;
    int row;
    int column;
} Square;

int checkBox(Square *** sudoku, int row, int col, int val);
int checkRow(Square *** sudoku, int row, int val);
int checkColumn(Square *** sudoku,int col, int val);
void fillBox(int row, int col, Square *** sudoku);
int isValid(Square *** sudoku, int row, int col, int val);
int fillPuzzle(Square *** sudoku, int row, int col);
int insertValues(Square *** sudoku, int row, int col);
void removeValues(Square *** sudoku, int difficulty);
void printPuzzle(Square *** puzzle);
Square *** setPuzzle();
#endif //SUDOKU_SOLVER_SUDOKU_H
