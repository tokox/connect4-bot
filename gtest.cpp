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
	board.move(3, 'P');
	std::stringstream ss;
	board.print(ss);
	std::string r = "1 2 3 4 5 6 7 \n"
			". . . . . . . \n"
			". . . . . . . \n"
			". . . . . . . \n"
			". . . . . . . \n"
			". . . . . . . \n"
			". . . P . . . \n";
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
			". . . z . . . \n"
			". . . P . . . \n"
			". . . w . . . \n"
			". . . z . . . \n"
			". . . P . . . \n"
			". . . P . C . \n";
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
			". . . . . . . \n"
			". . . z . . . \n"
			". . . P . . . \n"
			". . . z . . . \n"
			". . . P . . . \n"
			". . . P . C . \n";
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

TEST(eval, error)
{
	Board board("...OO../klfneod/vienvoa/odjeivn/maneoaa/obnemtn");
	for(int i = 0; i < board.WIDTH; i++) {
		if(board.empty[i]) {
			board.move(i, 'O');
			EXPECT_EQ(eval(board), 0);
			board.unmove();
		}
	}
}

TEST(load, all)
{
	Board board("......./......./......./P.C.AD./P.ADCA./PAPDCD.");
	std::stringstream ss;
	board.print(ss);
	std::string r = "1 2 3 4 5 6 7 \n"
			". . . . . . . \n"
			". . . . . . . \n"
			". . . . . . . \n"
			"P . C . A D . \n"
			"P . A D C A . \n"
			"P A P D C D . \n";
	EXPECT_EQ(r, ss.str());
}

TEST(left, easy1)
{
	Board board("...OO../klfneod/vienvoa/odjeivn/maneoaa/obnemtn");
	EXPECT_EQ(board.left(), 5);
}

TEST(minimax, easy_max)
{
	Board board("...OO../klfneod/vienvoa/odjeivn/maneoaa/obnemtn");
	EXPECT_EQ(minimax(board).first, board.WIDTH*board.HEIGHT-2);
}

TEST(minimax, easy2_7)
{
	Board board("......./......./......./P.C.OD./P.ODCO./POPDCDO");
	EXPECT_EQ(minimax(board, 7).first, board.WIDTH*board.HEIGHT-2);
}

TEST(minimax, draw_9)
{
	Board board("......./......O/......X/......O/.X.X..O/XXXO..O");
	EXPECT_EQ(minimax(board, 9), std::make_pair(0, 5));
}

TEST(minimax, win_8)
{
	Board board("......O/......O/......X/......O/.X.X..O/XXXO..O");
	EXPECT_EQ(minimax(board, 8, false).first, -board.WIDTH*board.HEIGHT+8);
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

TEST(minimax, startpos_14)
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
