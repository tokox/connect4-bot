#include "minimax.hpp"
#include "eval.hpp"
#include "board.hpp"

std::pair<int, int> minimax(Board& board, int depth, bool Max, int d) {
	int best = -1, bestev = Max?-42:42;
	for(int i = 0; i < board.WIDTH; i++) {
		if(board.empty[i]) {
			board.move(i, Max?'O':'X');
			int ev = eval(board);
			if(ev != 0) {
				ev = (Max?1:-1)*board.WIDTH*board.HEIGHT;
			} else if(d < depth) {
				ev = minimax(board, depth, !Max, d+1).first;
				if(ev != 0)
					ev += (ev>0?-1:1);
			}
			if(Max) {
				if(ev >= bestev) {
					bestev = ev;
					best = i;
				}
			} else {
				if(ev <= bestev) {
					bestev = ev;
					best = i;
				}
			}
			board.unmove();
		}
	}
	return {best==-1?0:bestev, best};
}
