#include <iostream>
#include <vector>
#include "TranspositionTable.h"

int negamax(Board board, TranspositionTable* transposition_table, bool* stop, int depth, int alpha, int beta, int color);
Board generate_random_board(int depth);
vector<Board> generate_boards(int depth, int number_of_boards);
void playable_version();
void print_board(Board b);
void run_sequential_testing();
void run_parallel_testing();
void add_to_result_database(mongocxx::collection collection, int board_size, string board, int value, int microseconds, string tt_version, string sorting_version, string parallelization);