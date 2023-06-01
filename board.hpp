#ifndef CONN4_BOT_BOARD
#define CONN4_BOT_BOARD

#include <ostream>
#include <iostream>
#include <vector>
#include <string>

class Board {
	public:
		static const int HEIGHT = 6, WIDTH = 7;
		Board();
		Board(std::string pos);
		bool load(std::string pos);
		void print(std::ostream& os = std::cout);
		bool move(int c, char p);
		bool unmove();
		char board[HEIGHT][WIDTH];
		int empty[WIDTH];
		std::vector<int> moves_hist;
};

#endif
