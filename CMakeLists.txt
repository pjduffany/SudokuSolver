cmake_minimum_required(VERSION 3.30)
project(sudokuSolver C)

set(CMAKE_C_STANDARD 11)

add_executable(sudokuSolver src/main.c
        src/sudoku.h
        src/sudoku.c
        src/wasm_api.c
)
