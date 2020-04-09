#include "Board.h"
#include <limits>

using namespace std;

int counter = 0;

int negamax(Board board, int depth, int alpha, int beta, int color)
{
    cout << counter++ << endl;

    int game_state = board.game_state();
    if (depth == 0 || game_state != 0)
        return color * game_state;

    int value = numeric_limits<int>::min();
    vector<Board> potential_moves = board.generate_moves();
    for (Board b : potential_moves)
    {
        value = max(value, -negamax(b, depth - 1, -beta, -alpha, -color));
        alpha = max(alpha, value);
        if (alpha >= beta || value * color == 1)
            break;
    }

    return value;
}