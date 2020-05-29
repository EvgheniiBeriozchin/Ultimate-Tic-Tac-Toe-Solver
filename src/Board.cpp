#include "Board.h"

using namespace std;


inline void binary_print(uint64_t n)
{
    for (int i = 63; i >= 0; i--)
        cout << ((n >> i) & 1);
    cout << endl;
}

Board::Board()
{
    this->number_of_moves = 0;
    for (int i = 0; i < 3; i++)
    {
        this->board.push_back(0);
    }
}

Board::Board(vector<uint64_t> board, int number_of_moves)
{
    this->number_of_moves = number_of_moves;
    this->board = board;
}

bool Board::move(int board_number, int position)
{
    bool player = ((0b1000000000000000000000000000000000000000000000000000000000000000 & this->board[2]) != 0);
    if (board_number < 9)
    {
        this->board[2] = (this->board[2] & 0b1111111111111111111111111111111111111111111111111111111000000000) ^ 
                    (0b1000000000000000000000000000000000000000000000000000000000000000 | (0b0000000000000000000000000000000000000000000000100000000 >> position));
        this->board[board_number / 3] |= (0b0100000000000000000000000000000000000000000000000000000000000000 >> (position + 9 * player + 18 * (board_number % 3)));
    }
    else 
    {
        this->board[!player] |= (0b0000000000000000000000000000000000000000000000000000000100000000 >> position);
    }

    if (this->board_won(player, board_number))
    {
        if (board_number == 9)
            return true;
        return this->move(9, board_number);
    }
    this->number_of_moves++;
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

int Board::game_state()
{
    if (this->board_won(0, 9))
        return 1;
    else if (this->board_won(1, 9) || this->boards_full())
        return -1;
    return 0; 
}

bool Board::board_won(bool player, int board_number)
{
    int shift;
    u_int64_t board;
    if (board_number < 9)
    {
        shift = 9 * player + 18 * (board_number % 3);
        board = this->board[board_number / 3];
    }
    else
    {
        shift =  55;
        board = this->board[player];
    }

    return ((board & (this->bitmasks[0] >> shift)) == (this->bitmasks[0] >> shift)) ||
            ((board & (this->bitmasks[1] >> shift)) == (this->bitmasks[1] >> shift)) ||
            ((board & (this->bitmasks[2] >> shift)) == (this->bitmasks[2] >> shift)) ||
            ((board & (this->bitmasks[3] >> shift)) == (this->bitmasks[3] >> shift)) ||
            ((board & (this->bitmasks[4] >> shift)) == (this->bitmasks[4] >> shift)) ||
            ((board & (this->bitmasks[5] >> shift)) == (this->bitmasks[5] >> shift)) ||
            ((board & (this->bitmasks[6] >> shift)) == (this->bitmasks[6] >> shift)) ||
            ((board & (this->bitmasks[7] >> shift)) == (this->bitmasks[7] >> shift));
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

int Board::get_number_of_moves()
{
    return this->number_of_moves;
}

Board Board::copy()
{
    return Board(this->board, this->number_of_moves);
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

vector<pair<int, int> > Board::generate_integer_moves()
{
    vector<pair<int, int> > moves;
    if ((this->board[2] & 0b0000000000000000000000000000000000000000000000000000000111111111) == 0)
    {
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
            {
                moves.push_back(make_pair(i, j));
            }
    }
    else
    {
        if (!this->board_available((this->board[2] & 0b0000000000000000000000000000000000000000000000000000000111111111)))
        {
            for (int i = 0; i < 9; i++)
            {
                if (!this->board_available((0b0000000000000000000000000000000000000000000000000000000100000000 >> i)))
                    continue;
                u_int64_t occupied_spaces = this->occupied_spaces(i);
                for(int j = 0; j < 9; j++)
                {
                    if ((occupied_spaces & (0b0100000000000000000000000000000000000000000000000000000000000000 >> j)) == 0)
                    {
                        moves.push_back(make_pair(i, j));
                    }
                }
            }
        }
        else
        {
            int board_to_move_on = get_previous_move(this->board[2]);
            u_int64_t occupied_spaces = this->occupied_spaces(board_to_move_on);
            for(int i = 0; i < 9; i++)
            {
                if ((occupied_spaces & (0b0100000000000000000000000000000000000000000000000000000000000000 >> i)) == 0)
                {
                    moves.push_back(make_pair(board_to_move_on, i));
                }
            }
        }
    }

    return moves;
}

vector<Board> Board::generate_moves()
{
    vector<pair<int, int> > integer_moves = generate_integer_moves();
    vector<Board> moves;
    for(int i = 0; i < integer_moves.size(); i++)
    {
        Board b = this->copy();
        b.move(integer_moves[i].first, integer_moves[i].second);
        moves.push_back(b);
    }    

    return moves;
}

string Board::to_string()
{
    string key = "";
    /*
    char hex_string[9];

    for (int i = 0; i < 10; i++)
    {
        int b0 = this->get_board(0, i);
        int b1 = this->get_board(1, i);
        sprintf(hex_string, "%08X", b0);
        key.append(hex_string);
        sprintf(hex_string, "%08X", b1);
        key.append(hex_string);

    }

    int previous_move = this->get_previous_move_second();
    sprintf(hex_string, "%08X", previous_move);
    key.append(hex_string);
    */
    return key;
}