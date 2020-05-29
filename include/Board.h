#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Board 
{
    //column1|column2|column3|row1|row2|row3|diag1|diag2
    private:
        int number_of_moves;
        vector<uint64_t> board;
        u_int64_t bitmasks[9] = {0b0111000000000000000000000000000000000000000000000000000000000000,
                                0b0000111000000000000000000000000000000000000000000000000000000000,
                                0b0000000111000000000000000000000000000000000000000000000000000000,
                                0b0100100100000000000000000000000000000000000000000000000000000000,
                                0b0010010010000000000000000000000000000000000000000000000000000000,
                                0b0001001001000000000000000000000000000000000000000000000000000000,
                                0b0100010001000000000000000000000000000000000000000000000000000000,
                                0b0001010100000000000000000000000000000000000000000000000000000000};
        
        bool board_available(u_int64_t bitmask);
        bool boards_full();
        bool board_full(int board_number);
    
    public:
        Board();
        Board(vector<uint64_t> board, int number_of_moves);
        bool move(int board_number, int position);
        bool get(bool player, int board_number, int position);
        bool board_won(bool player, int board_number);
        int game_state();
        uint64_t occupied_spaces(int board_number);
        uint64_t get_board(int i);
        int get_number_of_moves();
        Board copy();
        bool same(Board board);
        vector<pair<int, int> > generate_integer_moves();
        vector<Board> generate_moves();
        string to_string();
};