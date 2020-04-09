#include <Board.h>
#include <TranspositionTable.h>

void TranspositionTable::set(Board board, int value)
{
    this->transposition_table.insert({board, value}); 
}

/*
int TranspositionTable::get(Board board)
{
    if (this->transposition_table)
}
*/