#include <iostream>
#include <vector>

using namespace std;

class Board 
{
    //column1|column2|column3|row1|row2|row3|diag1|diag2
    private:
        int current_player;
        int number_of_moves;
        pair<int, int> previous_move;
        vector<int> board[2];
        int input_bitmasks[9] = {
            0b00000000100000000100000000100000,
            0b00000000000100000010000000000000,
            0b00000000000000100001000000000100,
            0b00000000010000000000100000000000,
            0b00000000000010000000010000010010,
            0b00000000000000010000001000000000,
            0b00000000001000000000000100000001,
            0b00000000000001000000000010000000,
            0b00000000000000001000000001001000
        };
        bool board_full(int board_number);
        bool boards_full();
    
    public:
        Board();
        Board(int current_player, int number_of_moves, pair<int, int> previous_move, vector<int> board0, vector<int> board1);
        bool move(int board_number, int position);
        bool board_won(int board);
        int game_state();
        int occupied_spaces(int board_number);
        int get_board(int i, int j);
        int get_current_player();
        int get_previous_move_second();
        int get_number_of_moves();
        Board copy();
        bool same(Board board);
        vector<pair<int, int> > generate_integer_moves();
        vector<Board> generate_moves();
        string to_string();
};