#include <Board.h>
#include <map>

class TranspositionTable
{
    private:
        map<Board, int> transposition_table;

    public:
        void set(Board board, int value);
        int get(Board board);
};