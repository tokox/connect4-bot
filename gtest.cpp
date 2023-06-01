#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "board.hpp"

TEST(board, print_empty)
{
	Board board;
	std::stringstream ss;
	board.print(ss);
	std::string r = "1 2 3 4 5 6 7 \n"
			"              \n"
			"              \n"
			"              \n"
			"              \n"
			"              \n"
			"              \n";
	EXPECT_EQ(r, ss.str());
}

TEST(board, move_print)
{
	Board board;
	board.move(3, 'P');
	std::stringstream ss;
	board.print(ss);
	std::string r = "1 2 3 4 5 6 7 \n"
			"              \n"
			"              \n"
			"              \n"
			"              \n"
			"              \n"
			"      P       \n";
	EXPECT_EQ(r, ss.str());
}

TEST(board, moves_print)
{
	Board board;
	board.move(3, 'P');
	board.move(5, 'C');
	board.move(125, 'X');
	board.move(-1, 'A');
	board.move(3, 'P');
	board.move(3, 'z');
	board.move(3, 'w');
	board.move(3, 'P');
	board.move(3, 'z');
	board.move(3, 'w');
	std::stringstream ss;
	board.print(ss);
	std::string r = "1 2 3 4 5 6 7 \n"
			"      z       \n"
			"      P       \n"
			"      w       \n"
			"      z       \n"
			"      P       \n"
			"      P   C   \n";
	EXPECT_EQ(r, ss.str());
}
