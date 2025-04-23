//
// Created by Patrick Duffany on 4/22/25.
//

#ifndef SUDOKUSOLVER_HELPER_H
#define SUDOKUSOLVER_HELPER_H

int checkBox(int ** sudoku, int row, int col, int val);
int checkRow(int ** sudoku, int row, int val);
int checkColumn(int ** sudoku,int col, int val);
void fillBox(int row, int col, int ** sudoku);
int isValid(int ** sudoku, int row, int col, int val);
int fillPuzzle(int ** sudoku, int row, int col);
void removeValues(int ** sudoku);

#endif //SUDOKUSOLVER_HELPER_H
