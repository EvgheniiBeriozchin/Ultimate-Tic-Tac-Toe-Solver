#include "Board.h"
#include <unordered_map>
#include <stack>
//#include <queue> 

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

//compare function for priority_queue
class Compare
{
public:
    bool operator() (pair<Board, int> p1, pair<Board, int> p2)
    {
        return (p1.second <= p2.second);
    }
};

class TranspositionTable
{
    private:
        unordered_map<u_int64_t, unordered_map<u_int64_t, unordered_map<u_int64_t, int>> > transposition_table; //hash table
        stack<Board> latest_boards; 
        priority_queue<pair<Board, int>, vector<pair<Board, int> >, Compare> biggest_boards; //most complex boards
        int hit_counter;
        int query_counter;
        int type;
        int size;

    public:
        TranspositionTable(int tt_type=3, int size=2000000);
        TranspositionTable(mongocxx::collection collection, int tt_type=3, int size=2000000);
        void insert_latest_board(Board board, int value); //insert to latest_boards
        void erase_board(Board board_to_erase); //erase board from hash table
        void set(Board board, int value, int size);
        int get(Board board);
        double get_hit_ratio();
        int get_size();
        int dump_to_db(mongocxx::collection collection); //Since the new bitboard, this option was not implemented and used (was not really useful with the previous bitboard)
};