#ifndef CONN4_BOT_MINIMAX
#define CONN4_BOT_MINIMAX

#include <utility>
#include "board.hpp"

std::pair<int, int> minimax(Board& board, int depth = 42, char comp = 'O', bool Max = true, int d = 0, int alpha = -42, int beta = 42);

#include "minimax.cpp"

#endif
