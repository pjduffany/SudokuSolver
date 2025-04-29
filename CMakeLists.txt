cmake_minimum_required(VERSION 3.30)
project(sudokuSolver C)

set(CMAKE_C_STANDARD 11)

find_package(Curses REQUIRED)

add_executable(sudokuSolver src/main.c
        src/sudoku.h
        src/sudoku.c
        src/wasm_api.c
)

# Include the ncurses headers
target_include_directories(sudokuSolver PRIVATE ${CURSES_INCLUDE_DIR})

# Link against the ncurses library
target_link_libraries(sudokuSolver PRIVATE ${CURSES_LIBRARIES})
