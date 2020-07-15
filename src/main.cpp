#include "functions.h"
#include <iostream>
#include <time.h>
#include <chrono>
#include <typeinfo>
#include <future>

using namespace std;

#define MONGODB_NAME "tictactoedb"
#define MONGODB_CACHE_COLLECTION "cache"
#define MONGODB_RESULTS_COLLECTION "final_results"
#define MONGODB_HIT_RATIO_COLLECTION "hit_ratios"

#define NUMBER_OF_BOARDS 500
#define BREAK_PERCENTAGE 0.05
#define SEED 958654//748085

int ordering;

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
    int input_board = 0; 
    int test_size = 500;
    double break_percentage = 0.05;
    bool max_pruning = false, ab_pruning = false;
    int seed = 958654;
    int evaluation = 0;
    int tt_type = 0; //0 - none, 1 - latest, 2 - complex, 3 - both
    int ordering_type = 0;
    int time_limit = 5;
    int tt_size = 2000000;
    string test_id;

    for(int i = 1; i < argc; i++)
        if (strcmp(argv[i], "--size") == 0)
            test_size = atoi(argv[i + 1]);
        else if (strcmp(argv[i], "--percentage") == 0)
            break_percentage = stod(argv[i + 1]);
        else if (strcmp(argv[i], "--seed") == 0) 
            seed = atoi(argv[i + 1]);
        else if (strcmp(argv[i], "--maxp") == 0) 
            max_pruning = true;
        else if (strcmp(argv[i], "--abp") == 0) 
            ab_pruning = true;
        else if (strcmp(argv[i], "--evaluation") == 0) 
            evaluation = atoi(argv[i + 1]);
        else if (strcmp(argv[i], "--tttype") == 0)
            tt_type = atoi(argv[i + 1]);
        else if (strcmp(argv[i], "--ordering") == 0)
            ordering_type = atoi(argv[i + 1]);
        else if (strcmp(argv[i], "--time") == 0)
            time_limit = atoi(argv[i + 1]);
        else if (strcmp(argv[i], "--testid") == 0)
            test_id = argv[i + 1];
        else if (strcmp(argv[i], "--ttsize") == 0)
            tt_size = atoi(argv[i + 1]);
        else if (strcmp(argv[i], "--input") == 0)
            input_board = atoi(argv[i + 1]);

    if (input_board)
    {
        cout << "Running the algorithm for an input board. " << "Max_pruning: " << max_pruning << ", ab_pruning: " << ab_pruning
            << ", evaluation: " << evaluation  << ", tt_type: " << tt_type << ", ordering_type: " << ordering_type << ", tt_size: " << tt_size << "." << endl;
        run_input_board(input_board, max_pruning, ab_pruning, evaluation, tt_type, ordering_type, tt_size, time_limit);
    }
    else 
    {
        cout << "Running test: " << test_size << " samples, " << break_percentage << " break percentage;\n"
            << "Seed: " << seed << ", max_pruning: " << max_pruning << ", ab_pruning: " << ab_pruning
            << ", evaluation: " << evaluation << ", tt_type: " << tt_type << ", ordering_type: " << ordering_type << ", tt_size: " << tt_size << "." << endl;
        
        run_final_testing(test_size, break_percentage, seed, max_pruning, ab_pruning, evaluation, tt_type, ordering_type, time_limit, tt_size, test_id);
    }
}

void run_input_board(int type, bool max_pruning, bool ab_pruning, int evaluation, int tt_type, int ordering_type, int tt_size, int time_limit)
{
    vector<u_int64_t> board = {0, 0, 0};

    int value, board_size, subboard;
    long input_board;

    if (type == 1)
        cout << "Input the board subboard by subboard" << endl;
    else 
        cout << "Input all data at the same type with spacing" << endl;

    for (int i = 0; i < 9; i++)
    {
        u_int64_t bitboard = 0;
        if (type == 1)
            cout << "Input value of board " << i << endl;
        cin >> value;
        if (value)
        {
            if (value == 2)
            {
                board[1] |= (1 << (8 - i));
            }
            else
            {
                board[0] |= (1 << (8 - i));
            }
            board[i/3] |= (0b0111111111111111111000000000000000000000000000000000000000000000 >> (18 * (i % 3)));
        }
        else
        {
            if (type == 1)
                cout << "Input board" << endl;
            cin >> input_board;
            for (int j = 0; j < 9; j++)
            {
                int field = input_board % 10;
                input_board /= 10;
            
                if (field == 1)
                    bitboard |= (1 << (j + 9));
                else if (field == 2)
                    bitboard |= (1 << j);
            }

            board[i/3] |= (bitboard << (9 + 18 * (2 - i % 3)));
        }
    }

    u_int64_t player;
    if (type == 1)
        cout << "Input the subboard the next player has to place their token in and the total number of tokens placed until now" << endl;
    cin >> subboard >> board_size;
    player = board_size % 2;

    board[2] |= ((player - 1) << 63);
    board[2] |= (1 << (8 - subboard));
    Board b = Board(board);

    cout << "The bitboard was created:" << endl;
    print_board(b);
    cout << "Starting the algorithm. It will run for at most " << time_limit << " minutes." << endl;


    TranspositionTable transposition_table = TranspositionTable(tt_type, tt_size);
    bool stop_thread = false;
    chrono::milliseconds span (time_limit * 60000);
    chrono::high_resolution_clock::time_point start, stop;

    start = chrono::high_resolution_clock::now(); 
    std::future<int> fut = std::async (negamax, b, &transposition_table, &stop_thread, board_size, -2, 2, 1, max_pruning, ab_pruning, evaluation, (tt_type != 0)); 
    future_status f = fut.wait_for(span);
    stop = chrono::high_resolution_clock::now(); 
    
    if (f == future_status::ready)
    {
        value = fut.get(); 
        cout << "Board finished with value " << value << "." << endl;
    }
    else
    {
        stop_thread = true;
        cout << "Board didn't finish in time. Leaving program." << endl;
    }
}

void run_final_testing(int test_size, double break_percentage, int seed, bool max_pruning, bool ab_pruning, int evaluation, int tt_type, int ordering_type, int time_limit, int tt_size, string test_id)
{
    if (seed == -1)
        srand(time(NULL));
    else
        srand(seed);

    ordering = ordering_type;

    mongocxx::instance inst{};
    mongocxx::client conn{mongocxx::uri{}};
    auto cache_collection = conn[MONGODB_NAME][MONGODB_CACHE_COLLECTION];
    auto results_collection = conn[MONGODB_NAME][MONGODB_RESULTS_COLLECTION];
    auto hit_ratio_collection = conn[MONGODB_NAME][MONGODB_HIT_RATIO_COLLECTION];
    TranspositionTable transposition_table = TranspositionTable(cache_collection, tt_type, tt_size);

    bool stop_thread;
    int value,  count_unfinished_boards = 0, j;
    chrono::milliseconds span (time_limit * 60000);
    chrono::high_resolution_clock::time_point start, stop;
    vector<Board> boards;

    for (int i = 74; i > -1; i-=2)
    {
        if (++count_unfinished_boards > break_percentage * test_size)
            break;
        cout << "Executing for boards with " << i << " tokens." << endl;
        
        if (i == 0)
            boards = generate_boards(i, 1);
        else
            boards = generate_boards(i, test_size);
        cout << "Boards generated" << endl;
        
        j = 0;
        count_unfinished_boards = 0;

        for(Board board : boards)
        {
            stop_thread = false;
            start = chrono::high_resolution_clock::now(); 
            std::future<int> fut = std::async (negamax, board, &transposition_table, &stop_thread, i, -2, 2, 1, max_pruning, ab_pruning, evaluation, (tt_type != 0)); 
            
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
                if (++count_unfinished_boards > break_percentage * test_size)
                {
                    cout << "Board timeout percentage exceeded. Leaving program at " << i << " moves in." << endl;
                    break;
                }
            }

            if (!stop_thread)
                add_to_result_database(results_collection, i, value, chrono::duration_cast<chrono::microseconds>(stop - start).count(), "f0.0", test_size, break_percentage, seed, time_limit,
                max_pruning, ab_pruning, evaluation, tt_type, ordering_type, tt_size, test_id);
                j++;
        }
        if (++count_unfinished_boards <= break_percentage * test_size)
            add_hit_ratio_to_database(hit_ratio_collection, i, transposition_table.get_hit_ratio(), "f0.0", test_size, break_percentage, seed, time_limit,
                                        max_pruning, ab_pruning, evaluation, tt_type, ordering_type, tt_size, test_id);      
    }

    add_hit_ratio_to_database(hit_ratio_collection, -1, transposition_table.get_hit_ratio(), "f0.0", test_size, break_percentage, seed, time_limit,
                            max_pruning, ab_pruning, evaluation, tt_type, ordering_type, tt_size, test_id);

    int items_added = transposition_table.dump_to_db(cache_collection);
    cout << items_added << " items were added to the transposition table cache." << endl;  
}