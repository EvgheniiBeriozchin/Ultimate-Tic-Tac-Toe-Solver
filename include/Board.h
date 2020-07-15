#include <iostream>
#include <vector>
#include <cmath>
#include<bits/stdc++.h>

using namespace std;

#define WIN_VALUE 12
//win bitmasks
const u_int64_t bitmasks[9] = {0b0000000000000000000000000000000000000000000000000000000111000000,
                            0b0000000000000000000000000000000000000000000000000000000000111000,
                            0b0000000000000000000000000000000000000000000000000000000000000111,
                            0b0000000000000000000000000000000000000000000000000000000100100100,
                            0b0000000000000000000000000000000000000000000000000000000010010010,
                            0b0000000000000000000000000000000000000000000000000000000001001001,
                            0b0000000000000000000000000000000000000000000000000000000100010001,
                            0b0000000000000000000000000000000000000000000000000000000001010100};
//3-in-a-rows
const int bit_positions[9][3] = { {0, 1, 2},
                                    {3, 4, 5},
                                    {6, 7, 8},
                                    {0, 3, 6},
                                    {1, 4, 7},
                                    {2, 5, 8},
                                    {0, 4, 8},
                                    {2, 4, 6}};
//indexes of possible 3-in-a-rows that include a field     
const vector<int> indexes[9] = { {0, 3, 6},
                            {0, 4},
                            {0, 5, 7},
                            {1, 3},
                            {1, 4, 6, 7},
                            {1, 5},
                            {2, 3, 7},
                            {2, 4},
                            {2, 5, 6} };

extern int ordering;

class Board 
{
    private:
        vector<uint64_t> board;
        bool board_available(u_int64_t bitmask); //check if a (sub-, super-) board is available, instead of an index, the board is marked by a bit placed in the last 9 bits of the u_int64_t 
        bool boards_full(); //check if all (sub-, super-) boards are full
        bool board_full(int board_number); //check if a (sub-, super-) board is full
    
    public:
        Board(); //create empty board
        Board(vector<uint64_t> board); //create board from input
        bool move(int board_number, int position); //execute a move
        bool get(bool player, int board_number, int position); //get value of a bitboard field
        bool board_won(bool player, int board_number); //check if a subboard was won by a player
        int game_state(int eval=0); //evaluate game state
        uint64_t occupied_spaces(int board_number); //return what spaces are occupied in a specific board
        uint64_t get_board(int i); 
        Board copy(); //clone a board for board generation
        bool same(Board board);
        vector<pair<Board*, pair<int, int> > > generate_integer_moves(); //generate moves and return them as int pairs, the format is so for sorting
        vector<Board> generate_moves(); //generate all possible valid boards from the current board (i.e. generate moves and place them)
        int win_probability_value(int board_number, int position, bool player); //reward function for a (sub-, super-) board 
        int evaluate_move(pair<int, int> move); //Evaluation for move ordering 2
        int evaluate_move2(pair<int, int> move); //Evaluation for move ordering 3 with w = 0.5
        bool compare_boards(pair<int, int> m1, pair<int, int> m2); //compare move evaluations
};