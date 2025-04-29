
#include <stdio.h>
#include <stdlib.h>


#ifndef SUDOKU_SOLVER_SUDOKU_H
#define SUDOKU_SOLVER_SUDOKU_H
extern int UNSOLVED;
extern int SIZE_ROWS;
extern int SIZE_COLS;

// Holds the entire Sudoku gri
typedef struct Sudoku
{
  struct Square *** puzzle;
} Sudoku;

// Represents one cell in the Sudoku gri
typedef struct Square
{
    int number;
    int row;
    int column;
} Square;


// Function prototypes:
void freePuzzle(Square *** sudoku);
int checkBox(Square *** sudoku, int row, int col, int val);
int checkRow(Square *** sudoku, int row, int val);
int checkColumn(Square *** sudoku,int col, int val);
void fillBox(int row, int col, Square *** sudoku);
int checkPuzzle(Square *** sudoku, int row, int col, int val);
int fillPuzzle(Square *** sudoku, int row, int col);
int insertValues(Square *** sudoku, int row, int col);
void removeValues(Square *** sudoku, int difficulty);
void printPuzzle(Square *** puzzle);
Square *** setPuzzle();

#endif //SUDOKU_SOLVER_SUDOKU_H
