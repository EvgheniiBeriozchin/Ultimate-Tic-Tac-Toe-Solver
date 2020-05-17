#include "functions.h"
#include <limits>
#include <cstdlib>
#include<bits/stdc++.h>

using namespace std;

int counter = 0;

bool compare_boards(Board b1, Board b2) 
{
    int value = -1;
    bool smaller;
    for (Board b : {b1, b2})
    {
        int tmp;
        if (b.board_won(b.get_previous_move_second()))
        {
            tmp = 0;
            for (int i = 0; i < 9; i++)
            {
                if (!b.board_won(i))
                    tmp += 9 - b.occupied_spaces(i);
            }
        }
        else 
        {
            tmp = 9 - b.occupied_spaces(b.get_previous_move_second());
        }
        
        smaller = (value < tmp);
        value = tmp;
    }
    
    return smaller; 
} 

int negamax(Board board, TranspositionTable* transposition_table, bool* stop, int depth, int alpha, int beta, int color)
{
    /*
    if (++counter % 10000 == 0)
        cout << counter << endl;
    */

    if (*stop)
        return -3;
    
    int val;
    if (val = transposition_table->get(board) != 0)
    {
        return val;
    }
    
    int game_state = board.game_state();
    if (depth == 0 || game_state != 0)
        return color * game_state;

    int value = -2;
    vector<Board> potential_moves = board.generate_moves();
    sort(potential_moves.begin(), potential_moves.end(), compare_boards);

    for (Board b : potential_moves)
    {
        value = max(value, -negamax(b, transposition_table, stop, depth - 1, -beta, -alpha, -color));
        alpha = max(alpha, value);
        if (alpha >= beta || value == 1)
            break;
    }
    
    if (!val && value != 3 && value != -3)
    {
        transposition_table->set(board, value);
    }
    
    return value;
}

Board generate_random_board(int depth, int recursion_level)
{
    Board board = Board();
    int counter = 0;

    for(int i = 0; i < depth; i++)
    {
        //print_board(board);
        vector<pair<int, int> > potential_moves = board.generate_integer_moves();
        if (potential_moves.size() == 0)
        {
            return generate_random_board(depth, recursion_level + 1);
        }

        pair<int, int> random_move = potential_moves[rand() % potential_moves.size()];
        board.move(random_move.first, random_move.second);
        counter++;

        if (board.game_state() != 0)
        {
            return generate_random_board(depth, recursion_level + 1);
        }
    }

    //cout << "Counter: " << counter << endl;
    //cout << "Recursion level: " << recursion_level << endl;
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

void add_to_result_database(mongocxx::collection collection, int board_size, string board, int value, int microseconds, string tt_version, string sorting_version, string parallelization)
{
    bsoncxx::builder::stream::document document{};
    document << "board_size" << board_size
    << "board" << board
    << "value" << value
    << "time_in_microseconds" << microseconds
    << "transposition_table" << tt_version
    << "sorting" << sorting_version
    << "parallelization" << parallelization;
    
    collection.insert_one(document.view());
}
            
