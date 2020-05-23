#include "Board.h"
#include <unordered_map>
#include <stack>
#include <queue> 

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

#define STACK_SIZE  200000//2000000 - around 12.1% of RAM

class Compare
{
public:
    bool operator() (pair<string, int> p1, pair<string, int> p2)
    {
        return (p1.second <= p2.second);
    }
};

class TranspositionTable
{
    private:
        unordered_map<string, int> transposition_table;
        stack<string> latest_boards;
        priority_queue<pair<string, int>, vector<pair<string, int> >, Compare> biggest_boards; 
        int hit_counter;

    public:
        TranspositionTable();
        TranspositionTable(mongocxx::collection collection);
        void set(Board board, int value);
        int get(Board board);
        int get_hit_counter();
        int get_size();
        int dump_to_db(mongocxx::collection collection);
};