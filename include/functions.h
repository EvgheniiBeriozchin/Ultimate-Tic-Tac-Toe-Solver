#include <iostream>
#include <vector>
#include "TranspositionTable.h"

int negamax(Board board, TranspositionTable* transposition_table, bool* stop, int size, int alpha, int beta, int color, bool max_pruning, bool ab_pruning, int eval, bool tt);
Board generate_random_board(int depth); //generate one random board
vector<Board> generate_boards(int depth, int number_of_boards); //generate random boards for testing
void print_board(Board b);
void run_input_board(int type, bool max_pruning, bool ab_pruning, int evaluation, int tt_type, int ordering_type, int tt_size, int time_limit);
void run_final_testing(int test_size, double break_percentage, int seed, bool max_pruning, bool ab_pruning, int evaluation, int tt_type, int ordering_type, int time_limit, int tt_size, string test_id);
void add_to_result_database(mongocxx::collection collection, int board_size, int value, int microseconds, string code_version, int test_size, double break_percentage, int seed, int time_limit, bool ab_pruning, bool max_pruning, int evaluation, int tt_type, int ordering_type, int tt_size, string test_id);
void add_hit_ratio_to_database(mongocxx::collection collection, int board_size, double ratio, string code_version, int test_size, double break_percentage, int seed, int time_limit, bool ab_pruning, bool max_pruning, int evaluation, int tt_type, int ordering_type, int tt_size, string test_id);