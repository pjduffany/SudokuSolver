#include "sudoku.h"
//
// Created by Patrick Duffany on 4/6/25.
//

#ifndef SUDOKU_SOLVER_PUZZLE_H
#define SUDOKU_SOLVER_PUZZLE_H
int ** createPuzzle();
Sudoku * createSudoku(Square *** squares, Box ** boxes);
int updateSudoku(Square *** sudoku, int row, int col);
void printPuzzle(Square *** puzzle);
void printPuzzleTest(int ** puzzle);
Sudoku * setPuzzle(int ** puzzle);
int checkPuzzle(Square *** squares, Box **  boxes);
#endif //SUDOKU_SOLVER_PUZZLE_H
