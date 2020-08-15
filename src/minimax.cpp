#include "functions.h"
#include <limits>
#include <cstdlib>

using namespace std;

int negamax(Board board, TranspositionTable* transposition_table, bool* stop, int size, int alpha, int beta, int color, bool max_pruning, bool ab_pruning, int eval, bool tt)
{
    if (*stop)
        return 3;
    
    int val;
    if (tt && (val = transposition_table->get(board) != 0))
    {
        return val;
    }
    
    int game_state = board.game_state(eval);
    if (game_state != -2)
        return color * game_state;

    int value = -2;
    vector<Board> potential_moves = board.generate_moves();

    for (Board b : potential_moves)
    {
        value = max(value, -negamax(b, transposition_table, stop, size + 1, -beta, -alpha, -color, max_pruning, ab_pruning, tt, eval));
        if (ab_pruning)
        {
            alpha = max(alpha, value);
            if (alpha >= beta)
            break;
        }
        if (max_pruning && value >= 1)
            break;
    }
    
    if (tt && !val && value != 3 && value != -3)
    {
        transposition_table->set(board, value, size);
    }

    if (*stop)
        return 3;

    return value;
}

Board generate_random_board(int depth, int recursion_level)
{
    Board board = Board();
    int counter = 0;

    for(int i = 0; i < depth; i++)
    {
        vector<pair<Board*, pair<int, int> > > potential_moves = board.generate_integer_moves();

        if (potential_moves.size() == 0)
        {
            return generate_random_board(depth, recursion_level + 1);
        }

        pair<int, int> random_move = potential_moves[rand() % potential_moves.size()].second;
        board.move(random_move.first, random_move.second);
        counter++;

        if (board.game_state() != -2)
        {
            return generate_random_board(depth, recursion_level + 1);
        }
    }

    return board;
}

vector<Board> generate_boards(int depth, int number_of_boards)
{
    Board board = Board();
    vector<Board> boards;
    for(int i = 0; i < number_of_boards; i++)
    {
        bool new_board = false;

        while (!new_board)
        {
            Board board = generate_random_board(depth, 0);
            for(int i = 0; i < boards.size(); i++)
            {
                if (board.same(boards[i]))
                {
                    new_board = !new_board;
                    break;
                }
            }

            new_board = !new_board;
            if (new_board)
            {
                boards.push_back(board);
            }
        }
    }

    return boards;
}
/*
void add_to_result_database(mongocxx::collection collection, int board_size, int value, int microseconds, string code_version, int test_size, double break_percentage, int seed, int time_limit, bool ab_pruning, bool max_pruning, int evaluation, int tt_type, int ordering_type, int tt_size, string test_id)
{
    bsoncxx::builder::stream::document document{};
    document << "board_size" << board_size
    << "value" << value
    << "time_in_microseconds" << microseconds
    << "version" << code_version
    << "test_size" << test_size
    << "break_percentage" << break_percentage
    << "seed" << seed
    << "time_limit" << time_limit
    << "ab_pruning" << ab_pruning
    << "max_pruning" << max_pruning
    << "evaluation" << evaluation
    << "tt_type" << tt_type
    << "ordering_type" << ordering_type
    << "tt_size" << tt_size
    << "test_id" << test_id;
    
    collection.insert_one(document.view());
}

void add_hit_ratio_to_database(mongocxx::collection collection, int board_size, double ratio, string code_version, int test_size, double break_percentage, int seed, int time_limit, bool ab_pruning, bool max_pruning, int evaluation, int tt_type, int ordering_type, int tt_size, string test_id)
{
    bsoncxx::builder::stream::document document{};
    document << "board_size" << board_size
    << "ratio" << ratio
    << "version" << code_version
    << "test_size" << test_size
    << "break_percentage" << break_percentage
    << "seed" << seed
    << "time_limit" << time_limit
    << "ab_pruning" << ab_pruning
    << "max_pruning" << max_pruning
    << "evaluation" << evaluation
    << "tt_type" << tt_type
    << "ordering_type" << ordering_type
    << "tt_size" << tt_size
    << "test_id" << test_id;
    
    collection.insert_one(document.view());
}           
*/