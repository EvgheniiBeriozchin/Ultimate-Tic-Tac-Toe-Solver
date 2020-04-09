#include "Board.h"

using namespace std;


inline void binary_print(int n)
{
    for (int i = 31; i >= 0; i--)
        cout << ((n >> i) & 1);
    cout << endl;
}

Board::Board()
{
    this->previous_move = make_pair(1, 1);
    this->current_player = 0;
    for (int i = 0; i < 10; i++)
    {
        this->board[0].push_back(0);
        this->board[1].push_back(0);
    }
}

Board::Board(int current_player, pair<int, int> previous_move, vector<int> board0, vector<int> board1)
{
    this->current_player = current_player;
    this->previous_move = make_pair(previous_move.first, previous_move.second);
    this->board[0] = board0;
    this->board[1] = board1;
}

bool Board::move(int board_number, int position)
{
    this->previous_move = make_pair(board_number, position);
    this->board[this->current_player][board_number] |= this->input_bitmasks[position];
    if (this->board_won(this->board[this->current_player][board_number]))
    {
        if (board_number == 9)
        {
            this->current_player = (int)(this->current_player == 0);
            return true;
        }
        return this->move(9, board_number);
    }
    this->current_player = (int)(this->current_player == 0);
    return false;
}

int Board::game_state()
{
    if (this->board_won(board[0][9]))
        return 1;
    else if (this->board_won(board[1][9]) || this->boards_full())
        return -1;
    return 0; 
}

bool Board::board_won(int board)
{
    return ((board & (board >> 1) & (board >> 2) & (0b00000000001001001001001001001001)) > 0);   
}

bool Board::board_full(int board_number)
{
    return ((occupied_spaces(board_number)) ^ (0b00000000111111111111111111111111)) == 0;
}

bool Board::boards_full()
{
    bool board_not_full = false;
    for(int i = 0; i < 9; i++)
    {
        board_not_full = !this->board_full(i);
        if (board_not_full)
            return false;
    }
    return true;
}

int Board::occupied_spaces(int board_number)
{
    return (this->board[0][board_number] | this->board[1][board_number]);
}

int Board::get_board(int i, int j)
{
    return this->board[i][j];
}

int Board::get_current_player()
{
    return this->current_player;
}

Board Board::copy()
{
    return Board(this->current_player, this->previous_move, this->board[0], this->board[1]);
}

vector<Board> Board::generate_moves()
{
    vector<Board> moves;
    if (this->previous_move.first == -1)
    {
        //cout << "Entered first if statement" << endl;
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; i++)
            {
                Board b = Board(); 
                b.move(i, j);
                moves.push_back(b);
            }
    }
    else
    {
        int board_to_move_on = this->previous_move.second;
        if (this->board_won(this->board[(int)(this->current_player == 0)][board_to_move_on]) || this->board_full(board_to_move_on))
        {
            //cout << "Entered second if statement" << endl;
            for (int j = 0; j < 9; j++)
            {
                if (j == board_to_move_on)
                    continue;
                int occupied_spaces = this->occupied_spaces(j);
                for(int i = 0; i < 9; i++)
                {
                    if ((occupied_spaces & (0b00000000100000000000000000000000 >> i)) == 0)
                    {
                        Board b = this->copy();
                        b.move(j, i);
                        moves.push_back(b);
                    }
                }
            }
        }
        else
        {
            int occupied_spaces = this->occupied_spaces(board_to_move_on);
            for(int i = 0; i < 9; i++)
            {
                if ((occupied_spaces & (0b00000000100000000000000000000000 >> i)) == 0)
                {
                    Board b = this->copy();
                    b.move(board_to_move_on, i);
                    moves.push_back(b);
                }
            }
        }
    }

    return moves;
}