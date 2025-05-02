#include "board.hpp"

#include <iostream>
#include <cassert>
#include <stdexcept>
#include <cstring>
#include <bit>

Board::Board()
{
	this->moves = REPB(111, 42);
	this->board_o = 0;
	this->board_x = 0;
	this->count = 0;
	this->turn = 0;
	this->x_O = 0;
}

Board::Board(const char* pos, const char* mov)
{
	if (!this->loadpos(pos))
		throw std::invalid_argument("Invalid position");
	if (mov != NULL && !this->makemoves(mov))
		throw std::invalid_argument("Invalid moves");
}

bool Board::loadpos(const char* pos)
{
	usz len = strlen(pos);
	if (len != 49)
		return false;
	this->moves = REPB(111, 42);
	this->board_o = 0;
	this->board_x = 0;
	this->count = 0;
	for (u64 i = 0; i < 6; i++, pos++)
	{
		for (u64 j = 0; j < 7; j++, pos++)
		{
			if (*pos == 'O' || *pos == 'o')
				this->board_o ^= 1ull << ((5 - i) * 7 + j);
			else if (*pos == 'X' || *pos == 'x')
				this->board_x ^= 1ull << ((5 - i) * 7 + j);
			else if (*pos != '.')
				return false;

			if (((this->count >> (j * 3)) & 0b111) == 0)
			{
				if (*pos != '.')
					this->count |= (u32) (6 - i) << (j * 3);
			}
			else
			{
				if (*pos == '.')
					return false;
			}
		}
		if (i + 1 < 6 && *pos != '/')
			return false;
		if (i + 1 == 6 && *pos != ':')
			return false;
	}
	int cnto = std::popcount(this->board_o);
	int cntx = std::popcount(this->board_x);
	if (cnto != cntx && cnto != cntx + 1 && cnto != cntx - 1)
		return false;
	this->turn = cnto > cntx;
	if (*pos == 'X' || *pos == 'x')
		this->x_O = !this->turn;
	else if (*pos == 'O' || *pos == 'o')
		this->x_O = this->turn;
	else
		return false;
	return true;
}

bool Board::makemoves(const char* mov)
{
	const char* movcpy = mov;
	while (*mov != '\0')
	{
		if (*mov <= '1' || *mov >= '7')
			return false;
		mov++;
	}
	mov = movcpy;
	while (*mov != '\0')
	{
		if (!this->move(*mov - '1'))
		{
			while (mov >= movcpy)
			{
				this->unmove();
				mov--;
			}
			return false;
		}
		mov++;
	}
	return true;
}

void Board::reset()
{
	this->moves = REPB(111, 42);
	this->board_o = 0;
	this->board_x = 0;
	this->count = 0;
	this->turn = 0;
	this->x_O = 0;
}

u64 Board::made() const
{
	u64 s = 0;
	u64 cnt = this->count;
	for (u64 i = 0; i < 7; i++)
	{
		s += cnt & 0b111;
		cnt >>= 3;
	}
	return s;
}

u64 Board::left() const
{
	return 42 - this->made();
}

inline bool Board::move(u64 c)
{
	assert(c < 7);
	u64 count_c = (this->count >> (c * 3)) & 0b111;
	if (count_c == 6)
		return false;
	if (this->turn)
		this->board_x ^= 1ull << (count_c * 7 + c);
	else
		this->board_o ^= 1ull << (count_c * 7 + c);
	count_c ^= count_c + 1;
	this->count ^= (u32) count_c << (c * 3);
	this->turn ^= 1;
	this->moves <<= 3;
	this->moves |= c;
	return true;
}

inline bool Board::unmove()
{
	u64 c = this->moves & 0b111;
	if (c == 0b111)
		return false;
	this->moves >>= 3;
	this->moves |= (u128) 0b111 << 123;
	this->turn ^= 1;
	u64 count_c = (this->count >> (c * 3)) & 0b111;
	assert(count_c > 0);
	--count_c;
	if (this->turn)
		this->board_x ^= 1ull << (count_c * 7 + c);
	else
		this->board_o ^= 1ull << (count_c * 7 + c);
	count_c ^= count_c + 1;
	this->count ^= (u32) count_c << (c * 3);
	return true;
}

inline bool Board::won() const
{
	u64 board = this->turn ? this->board_o : this->board_x;
	u64 mask = board & (board >> 1);
	if (mask & (mask >> 2))
		return true;
	mask = board & (board >> 7);
	if (mask & (mask >> 14))
		return true;
	mask = board & (board >> 6);
	if (mask & (mask >> 12))
		return true;
	mask = board & (board >> 8);
	if (mask & (mask >> 16))
		return true;
	return false;
}

inline bool Board::full() const
{
	return this->count == REPB(110, 7);
}

inline bool Board::empty() const
{
	return this->count == 0;
}

inline u64 Board::compressed() const
{
	return this->board_x << 21 | this->count;
}

void Board::to_array(char arr[6][7]) const
{
	for (u64 i = 0; i < 6; i++)
	{
		for (u64 j = 0; j < 7; j++)
		{
			if (this->board_o & (1ull << ((5 - i) * 7 + j)))
				arr[i][j] = (this->x_O ? 'X' : 'O');
			else if (this->board_x & (1ull << ((5 - i) * 7 + j)))
				arr[i][j] = (this->x_O ? 'O' : 'X');
			else
				arr[i][j] = '.';
		}
	}
}

void Board::print_os(std::ostream& os) const
{
	for (u64 i = 0; i < 7; i++)
		os << i + 1 << ' ';
	os << '\n';
	for (u64 i = 0; i < 6; i++)
	{
		for (u64 j = 0; j < 7; j++)
		{
			bool e = true;
			if (this->board_o & (1ull << ((5 - i) * 7 + j)))
			{
				os << (this->x_O ? 'X' : 'O');
				e = false;
			}
			if (this->board_x & (1ull << ((5 - i) * 7 + j)))
			{
				os << (this->x_O ? 'O' : 'X');
				e = false;
			}
			if (e)
				os << '.';
			os << ' ';
		}
		os << '\n';
	}
	os << std::flush;
}

void Board::print() const
{
	this->print_os(std::cout);
}
