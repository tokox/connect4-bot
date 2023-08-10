#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <regex>
#include "eval.hpp"
#include "board.hpp"
#include "minimax.hpp"
using namespace std;
void print_help() {
	ifstream file("../connect4-bot/README.md");
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
int csswces(string s) {
	regex reg("\033\\[(A|[\\d]+m)");
	return regex_replace(s, reg, "").size();
}
int prev_cms = 0;
int prev_ums = 0;
void print(string comp_mess, Board board, string user_mess, bool override_prev = false) {
	for(int i = 0; override_prev && i < board.HEIGHT+3; i++) {
		cout << "\033[A";
	}
	int cms = csswces(comp_mess);
	int ums = csswces(user_mess);
	cout << comp_mess;
	for(int i = 0; i < prev_cms-cms && override_prev; i++)
		cout << " ";
	cout << endl;
	board.print_out();
	cout << user_mess;
	for(int i = 0; i < prev_ums-ums && override_prev; i++)
		cout << " ";
	cout << endl;
	prev_cms = cms;
	prev_ums = ums;
}
string double_to_string(double value, string::size_type precision = string::npos) {
	string res = to_string(value);
	auto pos = res.find('.');
	if(pos != string::npos && precision != string::npos)
		res.erase(pos+precision+(precision>0?1:0));
	return res;
}
int main(int argc, char* argv[])
{
	bool move = false;
	bool print_moves = false;
	bool history = false;
	long long time = -1;
	int depth = -1;
	char comp = '\0';
	for(int i = 1; i < argc; i++) {
		string arg = argv[i];
		if(arg == "help") {
			print_help();
			return 0;
		} else if(arg == "start") {
			move = true;
		} else if(arg == "X" || arg == "O") {
			if(comp == '\0') {
				comp = arg[0];
			} else {
				cout << "Unexpected multiple `X|O` arguments" << endl;
				return 1;
			}
		} else if(arg == "print_moves") {
			print_moves = true;
		} else if(arg == "history") {
			history = true;
		} else if(arg == "depth") {
			if(depth < 0) {
				if(i+1 < argc) {
					string next_arg = argv[++i];
					try {
						depth = stoi(next_arg);
					} catch(...) {
						cout << "Expected `[any number]` after `depth`. Got this: " << next_arg << endl;
						return 1;
					}
				} else {
					cout << "Expected `[any number]` after `depth`" << endl;
					return 1;
				}
			} else {
				cout << "Unexpected multiple `depth` arguments" << endl;
				return 1;
			}
		} else if(arg == "time") {
			if(time < 0) {
				if(i+1 < argc) {
					string next_arg = argv[++i];
					try {
						time = stoll(next_arg);
					} catch(...) {
						cout << "Expected `[any number]` after `time`. Got this: " << next_arg << endl;
						return 1;
					}
				} else {
					cout << "Expected `[any number]` after `time`" << endl;
					return 1;
				}
			} else {
				cout << "Unexpected multiple `time` arguments" << endl;
				return 1;
			}
		} else {
			cout << "Unexpected argument: " << arg << endl;
			return 1;
		}
	}
	if(time < 0 && depth < 0) {
		time = 5;
		depth = -1;
	}
	if(comp == '\0')
		comp = 'O';
	system("stty -echo -icanon; tput civis");
	Board board;
	string comp_mess;
	string user_mess;
	if(!history)
		cout << "\n\n\n\n\n\n\n\n\n";
	while(!board.full() && eval(board) != 1) {
		if(history) {
			comp_mess.clear();
			user_mess.clear();
			cout << endl;
		}
		if(move) {
			comp_mess.clear();
		} else {
			user_mess.clear();
		}
		print((string)(move?"\033[42m\033[1m":"")+"["+comp+"]"+(move?"\033[49m\033[22m":"")+": "+comp_mess, board, (string)(!move?"\033[42m\033[1m":"")+"["+(comp=='O'?'X':'O')+"]"+(!move?"\033[49m\033[22m":"")+": "+user_mess, !history);
		if(move) {
			int pev = 0, pmove = -1;
			auto stime = chrono::steady_clock::now();
			auto ptime = stime;
			chrono::microseconds pttime = chrono::microseconds::zero();
			chrono::microseconds pdtime = chrono::microseconds::zero();
			for(int d = 0; (d <= depth || depth < 0) && (pttime.count() * 5 <= time*1000000-pdtime.count() || time < 0) && pev == 0; d++) {
				auto[ev, move] = minimax(board, d);
				pev = ev;
				pmove = move;
				auto etime = chrono::steady_clock::now();
				chrono::microseconds dtime = chrono::duration_cast<chrono::microseconds>(etime-stime);
				pdtime = dtime;
				chrono::microseconds ttime = chrono::duration_cast<chrono::microseconds>(etime-ptime);
				pttime = ttime;
				ptime = etime;
				comp_mess = (string)"depth "+(d<10?" ":"")+to_string(d)+(depth<0?"":"/"+to_string(depth))+" ("+double_to_string((double)ttime.count()/1000000, 2)+"s) time "+double_to_string((double)dtime.count()/1000000, 2)+"s"+(time<0?"":"/"+to_string(time)+"s")+" bestmove "+to_string(move+1)+" result "+(ev==0?"draw":(ev>0?"win":"lose"));
				print((string)"\033[42m\033[1m["+comp+"]\033[49m\033[22m: "+comp_mess, board, (string)"["+(comp=='O'?'X':'O')+"]: "+user_mess, true);
			}
			if(!board.move(pmove, comp)) {
				cout << "Computer error!" << endl;
				return 1;
			}
			if(print_moves)
				cerr << pmove+1 << endl;
			if(eval(board) == 1) {
				user_mess += " \033[41m\033[3mYou lost!\033[23m\033[49m";
			}
		} else {
			char pm = '\0';
			auto stime = chrono::steady_clock::now();
			while(true) {
				cin >> pm;
				if(!board.move((int)(pm-'1'), comp=='O'?'X':'O')) {
					user_mess = (string)"\033[31mIncorrect move `"+pm+"`!\033[39m Try different";
					print((string)"["+comp+"]: "+comp_mess, board, (string)"\033[42m\033[1m["+(comp=='O'?'X':'O')+"]\033[49m\033[22m: "+user_mess, true);
				} else {
					user_mess = (string)"\033[32mCorrect move `"+pm+"`\033[39m";
					break;
				}
			}
			if(eval(board) == 1) {
				user_mess += " \033[42m\033[3mYou won!\033[23m\033[49m";
			}
		}
		if(board.full() && eval(board) == 0) {
			user_mess += " \033[43m\033[3mDraw!\033[23m\033[49m";
		}
		print((string)(move?"\033[42m\033[1m":"")+"["+comp+"]"+(move?"\033[49m\033[22m":"")+": "+comp_mess, board, (string)(!move?"\033[42m\033[1m":"")+"["+(comp=='O'?'X':'O')+"]"+(!move?"\033[49m\033[22m":"")+": "+user_mess, true);
		move = !move;
	}
	system("stty echo icanon; tput cnorm");
}
