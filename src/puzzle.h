#include "sudoku.h"
//
// Created by Patrick Duffany on 4/6/25.
//

#ifndef SUDOKU_SOLVER_PUZZLE_H
#define SUDOKU_SOLVER_PUZZLE_H
int ** createPuzzle();
int updateSudoku(Square *** sudoku, int row, int col);
void printPuzzle(Square *** puzzle);
void printPuzzleTest(int ** puzzle);
Square *** setPuzzle(int ** puzzle);
int checkPuzzle(Square *** sudoku);
#endif //SUDOKU_SOLVER_PUZZLE_H
