#include "minimax.hpp"

#include <algorithm>

std::pair<int, int> minimax(Board& board, int depth, char comp, bool Max, int d, int alpha, int beta)
{
	int best = -1, bestev = Max ? -42 : 42;
	for (int i = 0; i < 7 && beta > alpha; i++)
	{
		if (board.move(i))
		{
			int ev = board.won();
			if (ev != 0)
			{
				ev = (Max ? 1 : -1) * 42;
			}
			else if (d < depth)
			{
				ev = minimax(board, depth, comp, !Max, d + 1, alpha, beta).first;
				if (ev != 0)
					ev += (ev > 0 ? -1 : 1);
			}
			if (Max)
			{
				if (ev >= bestev)
				{
					bestev = ev;
					best = i;
					if (d > 0)
						alpha = std::max(alpha, bestev);
				}
			}
			else
			{
				if (ev <= bestev)
				{
					bestev = ev;
					best = i;
					if (d > 0)
						beta = std::min(beta, bestev);
				}
			}
			board.unmove();
		}
	}
	return { best == -1 ? 0 : bestev, best };
}
