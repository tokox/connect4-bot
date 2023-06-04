#include <algorithm>
#include "minimax.hpp"
#include "eval.hpp"
#include "board.hpp"

std::pair<int, int> minimax(Board& board, int depth, bool Max, int d, int alpha, int beta) {
	int best = -1, bestev = Max?-board.WIDTH*board.HEIGHT:board.WIDTH*board.HEIGHT;
	for(int i = 0; i < board.WIDTH && beta > alpha; i++) {
		if(board.empty[i]) {
			board.move(i, Max?'O':'X');
			int ev = eval(board);
			if(ev != 0) {
				ev = (Max?1:-1)*board.WIDTH*board.HEIGHT;
			} else if(d < depth) {
				ev = minimax(board, depth, !Max, d+1, alpha, beta).first;
				if(ev != 0)
					ev += (ev>0?-1:1);
			}
			if(Max) {
				if(ev >= bestev) {
					bestev = ev;
					best = i;
					if(d > 0)
						alpha = std::max(alpha, bestev);
				}
			} else {
				if(ev <= bestev) {
					bestev = ev;
					best = i;
					if(d > 0)
						beta = std::min(beta, bestev);
				}
			}
			board.unmove();
		}
	}
	return {best==-1?0:bestev, best};
}
