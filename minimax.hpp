#ifndef CONN4_BOT_MINIMAX
#define CONN4_BOT_MINIMAX

#include <utility>
#include "board.hpp"
#include "eval.hpp"

std::pair<int, int> minimax(Board& board, int depth = Board::WIDTH*Board::HEIGHT, bool Max = true, int d = 0);

#endif
