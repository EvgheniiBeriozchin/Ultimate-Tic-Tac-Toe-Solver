cmake_minimum_required(VERSION 2.8.9)
project(ultimate_tic_tac_toe_soler)

include_directories(include)

add_executable(solver "src/Board.cpp" "src/minimax.cpp" "src/main.cpp")

