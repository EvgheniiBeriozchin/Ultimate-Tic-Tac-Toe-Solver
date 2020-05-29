#include "functions.h"
#include <iostream>
#include <time.h>
#include <chrono>
#include <typeinfo>
#include <future>

using namespace std;

//#define PRIME 36893488147419103363

#define MONGODB_NAME "tictactoedb"
#define MONGODB_CACHE_COLLECTION "cache"
#define MONGODB_RESULTS_COLLECTION "results"

#define NUMBER_OF_BOARDS 500
#define BREAK_PERCENTAGE 0.05

inline void binary_print(uint64_t n)
{
    cout << ((n >> 63) & 1);
    for (int i = 62; i >= 0; i--)
    {
        if ((i + 1) % 9 == 0)
            cout << " " << ((n >> i) & 1);
        else
            cout << ((n >> i) & 1);
    }
    cout << endl;
}

inline void print_board(Board board)
{
    binary_print(board.get_board(0));
    binary_print(board.get_board(1));
    binary_print(board.get_board(2));
}

int main(int argc, char *argv[])
{
    //cout << PRIME << endl;
    
    /*
    vector<u_int64_t> b = {0b0001110000110001100111100000000011110000010100111000000010000101,
                            0b0010100001000011010100011010011100001001011010110100001001000010,
                            0b0001001001000000100110000000000111000111000000000010001000010000}; //56
    
    vector<u_int64_t> b = {0b0001110010110001101111100000000011110000010100111000000010100101,
                            0b0110100101001011010100011110011100001001011010110100101001001010,
                            0b1001001001000000100110000000000111000111000000000010001000000100}; //62
    
    Board bd = Board(b, 64);
    cout << bd.boards_full() << endl;
    for(int i = 0; i < 9; i++)
    {
        //cout << bd.board_full(i) << endl;
        //cout << bd.get(1, 9, i) << endl;
    }
    */
    /*
    int number_of_moves_in = 40;
    if (argc == 2)
        number_of_moves_in = stoi(argv[1]);
    */
    run_sequential_testing();
}

void run_parallel_testing()
{

}

void run_sequential_testing()
{
    srand (time(NULL));

    mongocxx::instance inst{};
    mongocxx::client conn{mongocxx::uri{}};
    auto cache_collection = conn[MONGODB_NAME][MONGODB_CACHE_COLLECTION];
    auto results_collection = conn[MONGODB_NAME][MONGODB_RESULTS_COLLECTION];
    TranspositionTable transposition_table = TranspositionTable(cache_collection);

    bool stop_thread;
    int value,  count_unfinished_boards = 0, j;
    chrono::milliseconds span (300000);
    chrono::high_resolution_clock::time_point start, stop;
    vector<Board> boards;
    
    for (int i = 74; i > -1; i-=2)
    {
        cout << "Executing for boards with " << i << " tokens." << endl;
        
        if (i == 0)
            boards = generate_boards(i, 1);
        else
            boards = generate_boards(i, NUMBER_OF_BOARDS);
        cout << "Boards generated" << endl;
        
        j = 0;
        count_unfinished_boards = 0;

        for(Board board : boards)
        {
            stop_thread = false;
            start = chrono::high_resolution_clock::now(); 
            std::future<int> fut = std::async (negamax, board, &transposition_table, &stop_thread, 81, -2, 2, 1); 
            
            future_status f = fut.wait_for(span);
            stop = chrono::high_resolution_clock::now(); 
            if (f == future_status::ready)
            {
                value = fut.get(); 
                cout << "Board " << j << ", with " << i << " moves in, finished with value " << value << "." << endl;
            }
            else
            {
                stop_thread = true;
                cout << "Board " << j << ", with " << i << " moves in, didn't finish in time." << endl;
                if (++count_unfinished_boards > BREAK_PERCENTAGE * NUMBER_OF_BOARDS)
                {
                    cout << "Board timeout percentage exceeded. Leaving program at " << i << " moves in." << endl;
                    break;
                }
            }

            if (!stop_thread)
                add_to_result_database(results_collection, i, board.to_string(), value, chrono::duration_cast<chrono::microseconds>(stop - start).count(), "v1.3", "no", "no", "");
            j++;
            
            /*
            cout << "The execution took " << chrono::duration_cast<chrono::microseconds>(stop - start).count() << " microseconds." << endl;
            cout << "The transposition table was hit " << transposition_table.get_hit_counter() << " times." << endl;
            cout << items_added << " items were added to the transposition table cache." << endl;
            */
        }      
    }

    int items_added = transposition_table.dump_to_db(cache_collection);
    cout << items_added << " items were added to the transposition table cache." << endl;  
    
}