#include "Board.h"

bool Board::compare_boards(pair<int, int> m1, pair<int, int> m2)
{
    if (ordering == 1)
        return (this->evaluate_move(m1) > this->evaluate_move(m2));
    else 
        return (this->evaluate_move2(m1) > this->evaluate_move2(m2));
}

int Board::win_probability_value(int board_number, int position, bool player)
{
    int value = 0; 
    u_int64_t board, not_board;

    //Get board view of player (board) and of the opponent (not_board)
    if (board_number < 9)
    {
        board = this->board[board_number / 3] >> (9 * (1 + player) + 18 * (3 - (board_number % 3)));
        not_board = this->board[board_number / 3] >> (9 * (1 + !player) + 18 * (3 - (board_number % 3)));
    }
    else 
    {
        board = this->board[player];
        not_board = this->board[!player];
    }

    //place move
    board |= (0b0000000000000000000000000000000000000000000000000000000100000000 >> position);

    //add points for approaching 3-in-a-rows
    for (int index : indexes[position])
    {
        if ((bitmasks[index] & not_board) == 0)
        {
            if ((bitmasks[index] & board) == bitmasks[index])
            {
                value = WIN_VALUE;
                break;
            }
            else 
            {
                value += ((board >> (8 - bit_positions[index][0])) & 1) + ((board >> (8 - bit_positions[index][1])) & 1) + ((board >> (8 - bit_positions[index][2])) & 1); 
            }
        }
    }

    return value;
}

int Board::evaluate_move(pair<int, int> move)
{   
    bool player = ((0b1000000000000000000000000000000000000000000000000000000000000000 & this->board[2]) != 0);
    return this->win_probability_value(move.first, move.second, player) * this->win_probability_value(9, move.first, player);  
}

int Board::evaluate_move2(pair<int, int> move)
{   
    return (this->win_probability_value(move.first, move.second, 0) + this->win_probability_value(move.first, move.second, 1)) * (this->win_probability_value(9, move.first, 0) + this->win_probability_value(9, move.first, 1));  
}