#ifndef CONN4_BOT_MINIMAX
#define CONN4_BOT_MINIMAX

#include <utility>
#include "board.hpp"
#include "eval.hpp"

std::pair<int, int> minimax(Board& board, int depth = Board::WIDTH*Board::HEIGHT, char comp = 'O', bool Max = true, int d = 0, int alpha = -Board::WIDTH*Board::HEIGHT, int beta = Board::WIDTH*Board::HEIGHT);

#endif
