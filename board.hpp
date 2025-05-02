#ifndef CONN4_BOT_BOARD
#define CONN4_BOT_BOARD

#include <ostream>

#include "types.hpp"

class Board
{
public:
	Board();
	Board(const char* pos, const char* mov = NULL);
	bool loadpos(const char* pos);
	bool makemoves(const char* mov);
	void reset();
	inline bool move(u64 c);
	inline bool unmove();
	inline bool won() const;
	inline bool full() const;
	inline bool empty() const;
	u64 made() const;
	u64 left() const;
	inline u128 compressed() const;
	void to_array(char array[6][7]) const;
	void print_os(std::ostream& os) const;
	void print() const;
	void to_notation(char buf[50]) const;

	u128 moves;
	u64 board_o;
	u64 board_x;
	u32 count;
	u8 turn;
};

#include "board.cpp"

#endif
