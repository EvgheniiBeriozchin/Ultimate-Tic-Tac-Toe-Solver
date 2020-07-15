#include "Board.h"

using namespace std;

//Non-class function for sorting in generate_moves
bool board_comparison(pair<Board*, pair<int, int> > m1, pair<Board*, pair<int, int> > m2)
{
    return m1.first->compare_boards(m1.second, m2.second);
}

//Printing function for debugging
inline void binary_print(uint64_t n)
{
    for (int i = 63; i >= 0; i--)
        cout << ((n >> i) & 1);
    cout << endl;
}

Board::Board()
{
    for (int i = 0; i < 3; i++)
    {
        this->board.push_back(0);
    }
}

Board::Board(vector<uint64_t> board)
{
    this->board = board;
}

bool Board::move(int board_number, int position)
{
    bool player = ((0b1000000000000000000000000000000000000000000000000000000000000000 & this->board[2]) != 0);
    if (board_number < 9)
    {
        //update player and previous move
        this->board[2] = (this->board[2] & 0b1111111111111111111111111111111111111111111111111111111000000000) ^ 
                    (0b1000000000000000000000000000000000000000000000000000000000000000 | (0b0000000000000000000000000000000000000000000000100000000 >> position));
        //place move
        this->board[board_number / 3] |= (0b0100000000000000000000000000000000000000000000000000000000000000 >> (position + 9 * player + 18 * (board_number % 3)));
    }
    else 
    {
        //place move in superboard
        this->board[!player] |= (0b0000000000000000000000000000000000000000000000000000000100000000 >> position);
    }

    if (this->board_won(player, board_number))
    {
        if (board_number == 9)
            return true;
        //if subboard is won or full (below), put all ones, because the moves inside are now irrelevant
        this->board[board_number / 3] |= (0b0111111111111111111000000000000000000000000000000000000000000000 >>  (18 * (board_number % 3)));
        return this->move(9, board_number);
    }

    if (this->board_full(board_number))
        this->board[board_number / 3] |= (0b0111111111111111111000000000000000000000000000000000000000000000 >>  (18 * (board_number % 3)));
    
    return false;
}

bool Board::get(bool player, int board_number, int position)
{
    if (board_number < 9)
        return ((this->board[board_number / 3] & ((0b0100000000000000000000000000000000000000000000000000000000000000 >> (position + 9 * player + 18 * (board_number % 3))))) != 0);
    else 
    {
        return ((this->board[player] & (0b0000000000000000000000000000000000000000000000000000000100000000 >> position)) != 0);
    }
}

int Board::game_state(int eval)
{
    if (this->board_won(0, 9))
        return 1;
    else if (this->board_won(1, 9))
        return -1;
    else if (this->boards_full())
    {
        return eval;
    }

    return -2; 
}

bool Board::board_won(bool player, int board_number)
{
    int shift;
    u_int64_t board;
    if (board_number < 9)
    {
        shift = 54 - 9 * player - 18 * (board_number % 3);
        board = this->board[board_number / 3];
    }
    else
    {
        shift =  0;
        board = this->board[player];
    }

    return ((board & (bitmasks[0] << shift)) == (bitmasks[0] << shift)) ||
            ((board & (bitmasks[1] << shift)) == (bitmasks[1] << shift)) ||
            ((board & (bitmasks[2] << shift)) == (bitmasks[2] << shift)) ||
            ((board & (bitmasks[3] << shift)) == (bitmasks[3] << shift)) ||
            ((board & (bitmasks[4] << shift)) == (bitmasks[4] << shift)) ||
            ((board & (bitmasks[5] << shift)) == (bitmasks[5] << shift)) ||
            ((board & (bitmasks[6] << shift)) == (bitmasks[6] << shift)) ||
            ((board & (bitmasks[7] << shift)) == (bitmasks[7] << shift));
}

bool Board::board_full(int board_number)
{
    return ((0b0111111111000000000000000000000000000000000000000000000000000000 ^
            (0b0111111111000000000000000000000000000000000000000000000000000000 &
            ((this->board[board_number / 3] << (18 * (board_number % 3))) |
            (this->board[board_number / 3] << (9 + 18 * (board_number % 3)))))) == 0);
}

bool Board::boards_full()
{
    for(int i = 0; i < 9; i++)
    {
        if (!(this->board_full(i) || this->get(0, 9, i) || this->get(1, 9, i)))
            return false;
    }
    return true;
}

uint64_t Board::occupied_spaces(int board_number)
{
    return (this->board[board_number / 3] << (18 * (board_number % 3))) |
    (this->board[board_number / 3] << (9 + 18 * (board_number % 3)));
}

uint64_t Board::get_board(int i)
{
    return this->board[i];
}

Board Board::copy()
{
    return Board(this->board);
}

bool Board::same(Board board)
{
    return  (this->board[0] == board.get_board(0))
             && (this->board[1] == board.get_board(1))
             && (this->board[2] == board.get_board(2));
}

int get_previous_move(u_int64_t bits)
{
    return 8 - int(log2(float(bits & 0b0000000000000000000000000000000000000000000000000000000111111111)));
}

bool Board::board_available(u_int64_t bitmask)
{
    return ((((this->board[0] | this->board[1]) & bitmask) == 0)
            && (!this->board_full(get_previous_move(bitmask))));
    
}

vector<pair<Board*, pair<int, int> > > Board::generate_integer_moves()
{
    vector<pair<Board*, pair<int, int> > > moves;
    //if subboard is not available or the whole board is empty
    if ((this->board[2] & 0b0000000000000000000000000000000000000000000000000000000111111111) == 0 || 
        !this->board_available((this->board[2] & 0b0000000000000000000000000000000000000000000000000000000111111111)))
    {
        for (int i = 0; i < 9; i++)
        {
            //go through all subboards and add possible moves in each of them
            if (!this->board_available((0b0000000000000000000000000000000000000000000000000000000100000000 >> i)))
                continue;
            u_int64_t occupied_spaces = this->occupied_spaces(i);
            for(int j = 0; j < 9; j++)
            {
                if ((occupied_spaces & (0b0100000000000000000000000000000000000000000000000000000000000000 >> j)) == 0)
                {
                    moves.push_back(make_pair(this, make_pair(i, j)));
                }
            }
        }
    }
    else
    {
        //add possible moves in current available subboard
        int board_to_move_on = get_previous_move(this->board[2]);
        u_int64_t occupied_spaces = this->occupied_spaces(board_to_move_on);
        for(int i = 0; i < 9; i++)
        {
            if ((occupied_spaces & (0b0100000000000000000000000000000000000000000000000000000000000000 >> i)) == 0)
            {
                moves.push_back(make_pair(this, make_pair(board_to_move_on, i)));
            }
        }
    }

    return moves;
}

vector<Board> Board::generate_moves()
{
    vector<pair<Board*, pair<int, int> > > integer_moves = generate_integer_moves();
    if(ordering > 0)
    {
        sort(integer_moves.begin(), integer_moves.end(), board_comparison);
    }
    vector<Board> moves;
    
    for(int i = 0; i < integer_moves.size(); i++)
    {
        Board b = this->copy();
        b.move(integer_moves[i].second.first, integer_moves[i].second.second);
        moves.push_back(b);
    }    

    return moves;
}