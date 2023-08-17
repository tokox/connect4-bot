#ifndef CONN4_BOT_BOARD
#define CONN4_BOT_BOARD

#include <ostream>
#include <iostream>
#include <vector>
#include <string>

class Board {
	public:
		static const int HEIGHT = 6, WIDTH = 7;
		static constexpr const char* startpos = "......./......./......./......./......./.......";
		Board();
		Board(std::string pos);
		bool load(std::string pos);
		bool validate(std::string pl = "XO", std::string* tp = nullptr) const;
		void print(std::ostream& os = std::cout) const;
		void print_out() const;
		bool move(int c, char p);
		bool unmove();
		bool full() const;
		bool empty() const;
		int left() const;
		char board[HEIGHT][WIDTH];
		int empty_column[WIDTH];
		std::vector<int> moves_hist;
};

#endif
