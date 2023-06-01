#include "board.hpp"

void Board::print(std::ostream& os) {
	for(int i = 0; i < WIDTH; i++) {
		os << i+1 << ' ';
	}
	os << '\n';
	for(auto& r: board) {
		for(auto& c: r) {
			os << c << ' ';
		}
		os << '\n';
	}
	os << std::flush;
}

bool Board::move(int c, char p) {
	if(c < 0 || c >= WIDTH || empty[c] == 0)
		return false;
	board[empty[c]-1][c] = p;
	empty[c]--;
	return true;
}