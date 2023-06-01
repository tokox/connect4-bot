#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "board.hpp"
#include "eval.hpp"
#include "minimax.hpp"

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

TEST(board, unmoves_print)
{
	Board board;
	EXPECT_EQ(board.unmove(), false);
	board.move(3, 'P');
	board.move(5, 'C');
	board.move(3, 'P');
	board.move(3, 'z');
	board.move(3, 'w');
	EXPECT_EQ(board.unmove(), true);
	board.move(3, 'P');
	board.move(3, 'z');
	std::stringstream ss;
	board.print(ss);
	std::string r = "1 2 3 4 5 6 7 \n"
			"              \n"
			"      z       \n"
			"      P       \n"
			"      z       \n"
			"      P       \n"
			"      P   C   \n";
	EXPECT_EQ(r, ss.str());
}

TEST(eval, down)
{
	Board board;
	board.move(3, 'P');
	EXPECT_EQ(eval(board), 0);
	board.move(3, 'P');
	EXPECT_EQ(eval(board), 0);
	board.move(3, 'P');
	EXPECT_EQ(eval(board), 0);
	board.move(3, 'P');
	EXPECT_EQ(eval(board), 1);
	board.move(3, 'P');
	EXPECT_EQ(eval(board), 1);
	board.move(3, 'P');
	EXPECT_EQ(eval(board), 1);
}

TEST(eval, hor)
{
	Board board;
	board.move(0, 'P');
	EXPECT_EQ(eval(board), 0);
	board.move(1, 'P');
	EXPECT_EQ(eval(board), 0);
	board.move(2, 'P');
	EXPECT_EQ(eval(board), 0);
	board.move(3, 'P');
	EXPECT_EQ(eval(board), 1);
	board.move(4, 'P');
	EXPECT_EQ(eval(board), 1);
	board.move(5, 'P');
	EXPECT_EQ(eval(board), 1);
}

TEST(eval, backslash)
{
	Board board;
	board.move(0, 'C');
	board.move(0, 'C');
	board.move(0, 'C');
	board.move(0, 'P');
	EXPECT_EQ(eval(board), 0);
	board.move(1, 'C');
	board.move(1, 'C');
	board.move(1, 'P');
	EXPECT_EQ(eval(board), 0);
	board.move(2, 'C');
	board.move(2, 'P');
	EXPECT_EQ(eval(board), 0);
	board.move(3, 'P');
	EXPECT_EQ(eval(board), 1);
	board.move(4, 'P');
	EXPECT_EQ(eval(board), 0);
	board.move(5, 'P');
	EXPECT_EQ(eval(board), 0);
}

TEST(eval, slash)
{
	Board board;
	board.move(0, 'P');
	EXPECT_EQ(eval(board), 0);
	board.move(1, 'C');
	board.move(1, 'P');
	EXPECT_EQ(eval(board), 0);
	board.move(2, 'C');
	board.move(2, 'C');
	board.move(2, 'P');
	EXPECT_EQ(eval(board), 0);
	board.move(3, 'C');
	board.move(3, 'C');
	board.move(3, 'C');
	board.move(3, 'P');
	EXPECT_EQ(eval(board), 1);
	board.move(4, 'P');
	EXPECT_EQ(eval(board), 0);
	board.move(5, 'P');
	EXPECT_EQ(eval(board), 0);
}

TEST(minimax, 1)
{
	Board board;
	EXPECT_EQ(minimax(board), std::make_pair(1, 3));
}
