#include "functions.h"
#include <iostream>
#include <time.h>
#include <chrono>
#include <typeinfo>
#include <future>

using namespace std;

#define MONGODB_NAME "tictactoedb"
#define MONGODB_CACHE_COLLECTION "cache"
#define MONGODB_RESULTS_COLLECTION "results"

#define NUMBER_OF_BOARDS 500
#define BREAK_PERCENTAGE 0.05

int main(int argc, char *argv[])
{
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
    //srand(2);

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
        if (count_unfinished_boards > BREAK_PERCENTAGE * NUMBER_OF_BOARDS)
            break;

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
                }
            }

            if (!stop_thread)
                add_to_result_database(results_collection, i, board.to_string(), value, chrono::duration_cast<chrono::microseconds>(stop - start).count(), "with tt_v1.1", "with sorting_v1", "");
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

void playable_version()
{
    Board b = Board();
    bool game_finished = false;
    while (!game_finished)
    {
        cout << "It's player's " << b.get_current_player() << " move!" << endl << endl;
        print_board(b);
       
        int board_number, field_number;
        cin >> board_number >> field_number;
        game_finished = b.move(board_number, field_number);
    }

    cout << endl << "Game is finished! Player " << (b.get_current_player() == 0) << " won!" << endl;
}

void print_board(Board b)
{
    //Print board
    //1st level board
    cout << "- - - - -" << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << "| ";
        for (int j = 0; j < 3; j++)
        {
            if ((b.get_board(0, 9) & (0b00000000000000000100000000000000 >> (j + 3*i))) > 0)
            {
                cout << "x ";
            }
            else if ((b.get_board(1, 9) & (0b00000000000000000100000000000000 >> (j + 3*i))) > 0)
            {
                cout << "o ";
            }
            else 
            {
                cout << "  ";
            }
        }
        cout << "|" << endl;
    }
    cout << "- - - - -" << endl << endl;

    //2nd level boards
    for (int l = 0; l < 3; l++)
    {
        cout << "- - - - - - - - - - - - -" << endl;
        for (int k = 0; k < 3; k++)
        {
            for (int i = 0; i < 3; i++)
            {
                cout << "| ";
                for (int j = 0; j < 3; j++)
                {
                    if ((b.get_board(0, i + 3*l) & (0b00000000000000000100000000000000 >> (j + 3*k))) > 0)
                    {
                        cout << "x ";
                    }
                    else if ((b.get_board(1, i + 3*l) & (0b00000000000000000100000000000000 >> (j + 3*k))) > 0)
                    {
                        cout << "o ";
                    }
                    else 
                    {
                        cout << "  ";
                    }
                }
            }
            cout << "|" << endl;
        }
    }
    cout << "- - - - - - - - - - - - -" << endl << endl;
}

/*
    vector<int> board0 = {
        0b00000000100000000100000000100000,
        0b00000000000101000010000010000000,
        0b00000000000000101001000001001100,
        0b00000000010000000000100000000000,
        0b00000000000010000000010000010010,
        0b00000000010000010000101000000000,
        0b00000000001000000000000100000001,
        0b00000000000001000000000010000000,
        0b00000000000000001000000001001000,
        0b00000000000000000000000000000000
    };
    vector<int> board1 = {
        0b00000000000100000010000000000000,
        0b00000000000000010000001000000000,
        0b00000000001000000000000100000000,
        0b00000000000100100011000000000100,
        0b00000000000000001000000001001000,
        0b00000000000001000000000010000000,
        0b00000000100000000100000000100000,
        0b00000000010000010000101000000000,
        0b00000000100000100101000000100100,
        0b00000000000000000000000000000000
    };
    
    vector<int> board0 = {
        0b00000000000000000000000000000000,
        0b00000000000000111001001001001100,
        0b00000000000000100001000000000100,
        0b00000000001001100001000110000101,
        0b00000000000011011000011011011010,
        0b00000000000000000000000000000000,
        0b00000000000000100001000000000100,
        0b00000000101010010100011100110011,
        0b00000000000000000000000000000000,
        0b00000000000100000010000000000000
    };
    vector<int> board1 = {
        0b00000000000001000000000010000000,
        0b00000000000000000000000000000000,
        0b00000000000111000010010010010010,
        0b00000000000000000000000000000000,
        0b00000000010000100001100000000100,
        0b00000000000111000010010010010010,
        0b00000000001001000000000110000001,
        0b00000000010101000010100010000000,
        0b00000000000110000010010000010010,
        0b00000000000000110001001000000100
    };
    */
    //Board board = Board(0, make_pair(6, 7), board0, board1);
    //Board board = Board();
    //print_board(board);
    //cout << negamax(board, &transposition_table, 81, -2, 2, 1) << endl;

     /*
        - - - - -
        | x o x |
        | x o x |
        | x o x |
        - - - - -

        - - - - - - - - - - - - -
        | x o x | x o x | x o x |
        | o x o | x o x | x o x |
        | x o x | x o x | x o x |
        - - - - - - - - - - - - -
        | x o x | x o x | x o x |
        | o x o | x o x | x o x |
        | x o x | x o x | x o x |
        - - - - - - - - - - - - -
        | x o x | x o x | x o x |
        | o x o | x o x | x o x |
        | x o x | x o x | x o x |
        - - - - - - - - - - - - -  
    */