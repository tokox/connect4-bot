#ifndef CONN4_BOT_BOARD
#define CONN4_BOT_BOARD

#include <ostream>
#include <iostream>

class Board {
	public:
		static const int HEIGHT = 6, WIDTH = 7;
		Board() {
			for(auto& r: board) {
				for(auto& c: r)
					c = ' ';
			}
			for(auto& e: empty)
				e = HEIGHT;
		}
		void print(std::ostream& os = std::cout);
		bool move(int c, char p);
		char board[HEIGHT][WIDTH];
		int empty[WIDTH];
};

#endif
