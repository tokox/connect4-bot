#include "minimax.hpp"
#include "eval.hpp"
#include "board.hpp"

std::pair<int, int> minimax(Board& board, int depth, bool Max, int d) {
	int best = -1, bestev = Max?-1:1;
	for(int i = 0; i < board.WIDTH; i++) {
		if(board.empty[i]) {
			board.move(i, Max?'O':'X');
			int ev = eval(board);
			if(ev == 1) {
				board.unmove();
				if(Max)
					return {1, i};
				else
					return {-1, i};
			}
			if(d < depth) {
				ev = minimax(board, depth, !Max, d+1).first;
				if(Max) {
					if(ev == 1) {
						board.unmove();
						return {1, i};
					}
				} else {
					if(ev == -1) {
						board.unmove();
						return {-1, i};
					}
				}
				if(Max) {
					if(ev > bestev) {
						bestev = ev;
						best = i;
					}
				} else {
					if(ev < bestev) {
						bestev = ev;
						best = i;
					}
				}
			}
			board.unmove();
		}
	}
	return {best==-1?0:bestev, best};
}
