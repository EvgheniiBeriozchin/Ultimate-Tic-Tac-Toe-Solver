cmake_minimum_required(VERSION 2.8.9)
project(ultimate_tic_tac_toe_solver)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

find_package(libmongocxx REQUIRED)
find_package(libbsoncxx REQUIRED)
include_directories(${LIBMONGOCXX_INCLUDE_DIR})
include_directories(${LIBBSONCXX_INCLUDE_DIR})
include_directories("/usr/local/include/mongocxx/v_noabi")
include_directories("/usr/local/include/bsoncxx/v_noabi")
include_directories("/usr/local/include/libmongoc-1.0")
include_directories("/usr/local/include/libbson-1.0")
include_directories("/usr/local/lib")

include_directories(include)

add_executable(solver "src/Board.cpp" "src/TranspositionTable.cpp" "src/minimax.cpp" "src/main.cpp")

target_link_libraries(solver ${LIBMONGOCXX_LIBRARIES})
target_link_libraries(solver ${LIBBSONCXX_LIBRARIES})