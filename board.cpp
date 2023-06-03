#include "board.hpp"

Board::Board() {
	for(auto& r: board) {
		for(auto& c: r)
			c = ' ';
	}
	for(auto& e: empty)
		e = HEIGHT;
}

Board::Board(std::string pos) {
	if(!this->load(pos)) {
		throw std::invalid_argument("Invalid position");
	}
}

bool Board::load(std::string pos) {
	if(pos.size() != WIDTH*HEIGHT+HEIGHT-1)
		return false;
	int idx = 0;
	for(int i = 0; i < HEIGHT; i++, idx++) {
		for(int j = 0; j < WIDTH; j++, idx++) {
			if(pos[idx]=='.' || pos[idx]==' ' || i==0)
				empty[j] = i+1-(i==0)+((pos[idx]=='.'||pos[idx]==' ')&&i==0);
			board[i][j] = pos[idx]=='.'?' ':pos[idx];
		}
		if(idx != pos.size() && pos[idx] != '/')
			return false;
	}
	return true;
}

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

void Board::print_out() {
	print(std::cout);
}

bool Board::move(int c, char p) {
	if(c < 0 || c >= WIDTH || empty[c] == 0)
		return false;
	board[empty[c]-1][c] = p;
	empty[c]--;
	moves_hist.push_back(c);
	return true;
}

bool Board::unmove() {
	if(moves_hist.empty())
		return false;
	int m = moves_hist.back();
	moves_hist.pop_back();
	board[empty[m]][m] = ' ';
	empty[m]++;
	return true;
}
