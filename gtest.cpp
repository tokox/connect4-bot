#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "board.hpp"
#include "minimax.hpp"

TEST(board, print_empty)
{
	Board board;
	std::stringstream ss;
	board.print_os(ss);
	std::string r =
		"1 2 3 4 5 6 7 \n"
		". . . . . . . \n"
		". . . . . . . \n"
		". . . . . . . \n"
		". . . . . . . \n"
		". . . . . . . \n"
		". . . . . . . \n";
	EXPECT_EQ(r, ss.str());
}

TEST(board, move_print)
{
	Board board;
	board.move(3);
	std::stringstream ss;
	board.print_os(ss);
	std::string r =
		"1 2 3 4 5 6 7 \n"
		". . . . . . . \n"
		". . . . . . . \n"
		". . . . . . . \n"
		". . . . . . . \n"
		". . . . . . . \n"
		". . . O . . . \n";
	EXPECT_EQ(r, ss.str());
}

TEST(board, moves_print)
{
	Board board;
	board.move(3);
	board.move(5);
	board.move(3);
	board.move(3);
	board.move(3);
	board.move(3);
	board.move(3);
	std::stringstream ss;
	board.print_os(ss);
	std::string r =
		"1 2 3 4 5 6 7 \n"
		". . . O . . . \n"
		". . . X . . . \n"
		". . . O . . . \n"
		". . . X . . . \n"
		". . . O . . . \n"
		". . . O . X . \n";
	EXPECT_EQ(r, ss.str());
}

TEST(board, unmoves_print)
{
	Board board;
	EXPECT_FALSE(board.unmove());
	EXPECT_TRUE(board.move(3));
	EXPECT_TRUE(board.move(5));
	EXPECT_TRUE(board.move(3));
	EXPECT_TRUE(board.move(3));
	EXPECT_TRUE(board.move(3));
	EXPECT_TRUE(board.unmove());
	EXPECT_TRUE(board.move(3));
	std::string rt =
		"1 2 3 4 5 6 7 \n"
		". . . . . . . \n"
		". . . . . . . \n"
		". . . O . . . \n"
		". . . X . . . \n"
		". . . O . . . \n"
		". . . O . X . \n";
	std::stringstream sst;
	board.print_os(sst);
	EXPECT_EQ(rt, sst.str());
	EXPECT_TRUE(board.move(3));
	std::stringstream ss;
	board.print_os(ss);
	std::string r =
		"1 2 3 4 5 6 7 \n"
		". . . . . . . \n"
		". . . X . . . \n"
		". . . O . . . \n"
		". . . X . . . \n"
		". . . O . . . \n"
		". . . O . X . \n";
	EXPECT_EQ(r, ss.str());
}

TEST(board, unmoves)
{
	Board board;
	for (u8 i = 0; i < 6; i++)
	{
		for (u8 j = 0; j < 7; j++)
			EXPECT_TRUE(board.move(j));
	}
	for (u8 i = 0; i < 6; i++)
	{
		for (u8 j = 0; j < 7; j++)
			EXPECT_TRUE(board.unmove());
	}
	EXPECT_FALSE(board.unmove());
}

TEST(loadpos, all)
{
	Board board("......./......./O....../X.O.OO./X.OXXX./XOXOXO.");
	std::stringstream ss;
	board.print_os(ss);
	std::string r =
		"1 2 3 4 5 6 7 \n"
		". . . . . . . \n"
		". . . . . . . \n"
		"O . . . . . . \n"
		"X . O . O O . \n"
		"X . O X X X . \n"
		"X O X O X O . \n";
	EXPECT_EQ(r, ss.str());
}

TEST(is_full, empty)
{
	Board board;
	EXPECT_FALSE(board.full());
}

TEST(loadpos_is_full, easy2)
{
	Board board;
	EXPECT_TRUE(board.loadpos("X..OO../XXXOXXX/OXOXOXO/XOXOXOX/OOXOOXO/OOXXXOO:O"));
	EXPECT_FALSE(board.full());
}

TEST(eval, down)
{
	Board board;
	board.move(3);
	EXPECT_FALSE(board.won());
	board.move(5);
	board.move(3);
	EXPECT_FALSE(board.won());
	board.move(5);
	board.move(3);
	EXPECT_FALSE(board.won());
	board.move(5);
	board.move(3);
	EXPECT_TRUE(board.won());
	board.move(5);
	board.move(3);
	EXPECT_TRUE(board.won());
	board.move(5);
	board.move(3);
	EXPECT_TRUE(board.won());
}

TEST(eval, hor)
{
	Board board;
	board.move(0);
	board.move(0);
	EXPECT_FALSE(board.won());
	board.move(1);
	board.move(1);
	EXPECT_FALSE(board.won());
	board.move(2);
	board.move(2);
	EXPECT_FALSE(board.won());
	board.move(3);
	board.move(3);
	EXPECT_TRUE(board.won());
	board.move(4);
	board.move(4);
	EXPECT_TRUE(board.won());
	board.move(5);
	board.move(5);
	EXPECT_TRUE(board.won());
}

TEST(eval, slash)
{
	Board board;
	board.move(0);
	board.move(1);
	board.move(1);
	board.move(2);
	EXPECT_FALSE(board.won());
	board.move(3);
	board.move(2);
	board.move(2);
	EXPECT_FALSE(board.won());
	board.move(3);
	board.move(3);
	EXPECT_FALSE(board.won());
	board.move(4);
	EXPECT_FALSE(board.won());
	board.move(3);
	EXPECT_TRUE(board.won());
	board.move(4);
	EXPECT_FALSE(board.won());
}

TEST(eval, slash2)
{
	Board board;
	board.move(1);
	board.move(2);
	board.move(2);
	board.move(3);
	EXPECT_FALSE(board.won());
	board.move(4);
	board.move(3);
	board.move(3);
	EXPECT_FALSE(board.won());
	board.move(4);
	board.move(4);
	EXPECT_FALSE(board.won());
	board.move(5);
	EXPECT_FALSE(board.won());
	board.move(4);
	EXPECT_TRUE(board.won());
	board.move(5);
	EXPECT_FALSE(board.won());
}

TEST(eval, backslash)
{
	Board board;
	board.move(6);
	board.move(5);
	board.move(5);
	board.move(4);
	EXPECT_FALSE(board.won());
	board.move(3);
	board.move(4);
	board.move(4);
	EXPECT_FALSE(board.won());
	board.move(3);
	board.move(3);
	EXPECT_FALSE(board.won());
	board.move(2);
	EXPECT_FALSE(board.won());
	board.move(3);
	EXPECT_TRUE(board.won());
	board.move(2);
	EXPECT_FALSE(board.won());
}

TEST(eval, through_wall)
{
	Board board("......./......./......./......./xx.o.../oo.o.xx:o");
	EXPECT_FALSE(board.won());
}

TEST(minimax, easy_max)
{
	Board board("oo.xx../xoxoxox/xoxoxox/oxoxoxo/oxoxoxo/oxoxoxo");
	EXPECT_EQ(minimax(board).first, 42 - 2);
}

TEST(minimax, easy2_7)
{
	Board board("......./......./......./x.x.ox./o.oxxo./ooxxoxo:o");
	EXPECT_EQ(minimax(board, 7).first, 42 - 2);
}

TEST(minimax, draw_9)
{
	Board board("......./......X/......O/......X/.O.O..X/OOOX..X");
	EXPECT_EQ(minimax(board, 9), std::make_pair(0, 5));
}

TEST(minimax, win_8)
{
	Board board("......X/......X/......O/......X/.O.O..X/OOOX..X:O");
	EXPECT_EQ(minimax(board, 8, 'X').first, 42 - 8);
}

TEST(minimax, startpos_0)
{
	Board board;
	EXPECT_EQ(minimax(board, 0).first, 0);
}

TEST(minimax, startpos_1)
{
	Board board;
	EXPECT_EQ(minimax(board, 1).first, 0);
}

TEST(minimax, startpos_2)
{
	Board board;
	EXPECT_EQ(minimax(board, 2).first, 0);
}

TEST(minimax, startpos_5)
{
	Board board;
	EXPECT_EQ(minimax(board, 5).first, 0);
}

TEST(minimax, startpos_9)
{
	Board board;
	EXPECT_EQ(minimax(board, 9).first, 0);
}

TEST(minimax, startpos_10)
{
	Board board;
	EXPECT_EQ(minimax(board, 10).first, 0);
}

TEST(minimax, startpos_11)
{
	Board board;
	EXPECT_EQ(minimax(board, 11).first, 0);
}

TEST(minimax, startpos_12)
{
	Board board;
	EXPECT_EQ(minimax(board, 12).first, 0);
}

TEST(minimax, startpos_13)
{
	Board board;
	EXPECT_EQ(minimax(board, 13).first, 0);
}

TEST(minimax, DISABLED_startpos_14)
{
	Board board;
	EXPECT_EQ(minimax(board, 14).first, 0);
}

TEST(minimax, DISABLED_startpos_15)
{
	Board board;
	EXPECT_EQ(minimax(board, 15).first, 0);
}

TEST(minimax, DISABLED_startpos_21)
{
	Board board;
	EXPECT_EQ(minimax(board, 21).first, 0);
}

TEST(minimax, DISABLED_startpos_max)
{
	Board board;
	EXPECT_EQ(minimax(board), std::make_pair(1, 3));
}
