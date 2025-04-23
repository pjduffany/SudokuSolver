//
// Created by Patrick Duffany on 4/10/25.
//

#ifndef SUDOKU_SOLVER_BOX_H
#define SUDOKU_SOLVER_BOX_H
#include "sudoku.h"

Box ** createBoxes();
int checkBoxes(Square *** squares, Box ** boxes);
void updateBoxes(Square *** sudoku, int row, int col);

#endif //SUDOKU_SOLVER_BOX_H
