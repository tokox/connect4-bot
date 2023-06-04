#include <iostream>
#include <fstream>
#include <string>
#include "eval.hpp"
#include "board.hpp"
#include "minimax.hpp"
using namespace std;
void print_help() {
	ifstream file("README.md");
	if(!file.good()) {
		cout << "See at https://github.com/tokox/connect4-bot#readme" << endl;
	} else {
		string line;
		getline(file, line);
		while(!file.eof()) {
			cout << line << endl;
			getline(file, line);
		}
	}
};
int main(int argc, char* argv[])
{
	bool move = false;
	bool print_moves = false;
	int depth = 8;
	for(int i = 1; i < argc; i++) {
		string arg = argv[i];
		if(arg == "start")
			move = true;
		else if(arg == "print_moves")
			print_moves = true;
		else if(arg == "help")
			{
				print_help();
				return 0;
			}
		else if(!arg.empty() && arg.find_first_not_of("0123456789") == std::string::npos)
			depth = stoi(arg);
		else
			cout << "Wrong argument!" << endl;
	}
	Board board;
	int result = 0;
	while(board.moves_hist.size() < board.HEIGHT * board.WIDTH && (result == 0 || result == 2)) {
		if(result == 2)
			cout << "You will lose!" << endl;
		board.print();
		if(move) {
			auto[ev, move] = minimax(board, depth);
			board.move(move, 'O');
			if(print_moves)
				cerr << move+1 << endl;
			if(eval(board) == 1) {
				result = 1;
			} else if(ev == 1) {
				if(result != 2)
					cout << endl;
				result = 2;
			}
		} else {
			int pm;
			do {
				cin >> pm;
				cout << "\033[A\r   \r";
			} while(!board.move(pm-1, 'X'));
			if(eval(board) == 1)
				result = -1;
		}
		for(int i = 0; i < board.HEIGHT+1+(result==2); i++)
			cout << "\033[A";
		move = !move;
	}
	board.print();
	switch(result) {
		case -1:
			cout << "You won!" << endl;
			break;
		case 0:
			cout << "Draw!" << endl;
			break;
		case 1:
			cout << "You lost!" << endl;
	}
}
