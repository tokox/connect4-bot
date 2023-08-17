#include "board.hpp"
#include <algorithm>

Board::Board() {
	this->load(startpos);
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
			if(pos[idx]=='.' || i==0)
				empty_column[j] = i+1-(i==0)+((pos[idx]=='.')&&i==0);
			board[i][j] = pos[idx];
		}
		if(idx != pos.size() && pos[idx] != '/')
			return false;
	}
	return true;
}

bool Board::validate(std::string pl, std::string* tp) const {
	if(full())
		return false;
	if(tp != nullptr)
		tp->clear();
	int cnt[pl.size()];
	for(auto& c: cnt)
		c = 0;
	for(int r = 0; r < HEIGHT; r++) {
		for(int c = 0; c < WIDTH; c++) {
			char p = board[r][c];
			if(r > 0 && p == '.' && board[r-1][c] != '.')
				return false;
			if(p != '.') {
				if(pl.find(p) == std::string::npos)
					return false;
				cnt[pl.find(p)]++;
				if(r < 3) {
					bool down = true;
					for(int i = r; i < HEIGHT && i-r < 4; i++) {
						if(board[i][c] != p)
							down = false;
					}
					if(down)
						return false;
				}
				int hor = -1;
				for(int i = c; i >= 0 && board[r][i] == p; i--) {
					hor++;
					if(hor == 4)
						return false;
				}
				for(int i = c; i < WIDTH && board[r][i] == p; i++) {
					hor++;
					if(hor == 4)
						return false;
				}
				int backslash = -1;
				for(int i = 0; c-i >= 0 && r-i >= 0 && board[r-i][c-i] == p; i++) {
					backslash++;
					if(backslash == 4)
						return false;
				}
				for(int i = 0; c+i < WIDTH && r+i < HEIGHT && board[r+i][c+i] == p; i++) {
					backslash++;
					if(backslash == 4)
						return false;
				}
				int slash = -1;
				for(int i = 0; c-i >= 0 && r+i < HEIGHT && board[r+i][c-i] == p; i++) {
					slash++;
					if(slash == 4)
						return false;
				}
				for(int i = 0; c+i < WIDTH && r-i >= 0 && board[r-i][c+i] == p; i++) {
					slash++;
					if(slash == 4)
						return false;
				}
			}
		}
	}
	int c = cnt[0];
	if(tp != nullptr)
		tp->push_back(pl[0]);
	for(int i = 1; i < pl.size(); i++) {
		if(cnt[i] < c) {
			c = cnt[i];
			if(tp != nullptr) {
				tp->clear();
				tp->push_back(pl[i]);
			}
		} else if(cnt[i] == c) {
			if(tp != nullptr)
				tp->push_back(pl[i]);
		}
	}
	for(auto& cn: cnt) {
		if(cn-1 > c) {
			if(tp != nullptr)
				tp->clear();
			return false;
		}
	}
	return true;
}

void Board::print(std::ostream& os) const {
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

void Board::print_out() const {
	print(std::cout);
}

bool Board::move(int c, char p) {
	if(c < 0 || c >= WIDTH || empty_column[c] == 0)
		return false;
	board[empty_column[c]-1][c] = p;
	empty_column[c]--;
	moves_hist.push_back(c);
	return true;
}

bool Board::unmove() {
	if(moves_hist.empty())
		return false;
	int m = moves_hist.back();
	moves_hist.pop_back();
	board[empty_column[m]][m] = '.';
	empty_column[m]++;
	return true;
}

bool Board::full() const {
	return std::all_of(empty_column, empty_column+WIDTH, [](const auto& e){return e == 0;});
}

bool Board::empty() const {
	return std::all_of(empty_column, empty_column+WIDTH, [](const auto& e){return e == HEIGHT;});
}

int Board::left() const {
	int sum = 0;
	for(auto& e: empty_column) {
		sum += e;
	}
	return sum;
}
