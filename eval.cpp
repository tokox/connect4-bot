#include "eval.hpp"

int eval(const Board& board, int lastMove) {
	int c = lastMove, r = board.empty[lastMove];
	char p = board.board[r][c];
	bool down = false;
	if(r < 3) {
		down = true;
		for(int i = r; i < board.HEIGHT && i-r < 4; i++) {
			if(board.board[i][c] != p)
				down = false;
		}
		if(down)
			return 1;
	}
	int hor = -1;
	for(int i = c; i >= 0 && board.board[r][i] == p; i--) {
		hor++;
		if(hor == 4)
			return 1;
	}
	for(int i = c; i < board.WIDTH && board.board[r][i] == p; i++) {
		hor++;
		if(hor == 4)
			return 1;
	}
	int backslash = -1;
	for(int i = 0; c-i >= 0 && r-i >= 0 && board.board[r-i][c-i] == p; i++) {
		backslash++;
		if(backslash == 4)
			return 1;
	}
	for(int i = 0; c+i < board.WIDTH && r+i < board.HEIGHT && board.board[r+i][c+i] == p; i++) {
		backslash++;
		if(backslash == 4)
			return 1;
	}
	int slash = -1;
	for(int i = 0; c-i >= 0 && r+i < board.HEIGHT && board.board[r+i][c-i] == p; i++) {
		slash++;
		if(slash == 4)
			return 1;
	}
	for(int i = 0; c+i < board.WIDTH && r-i >= 0 && board.board[r-i][c+i] == p; i++) {
		slash++;
		if(slash == 4)
			return 1;
	}
	return 0;
}
