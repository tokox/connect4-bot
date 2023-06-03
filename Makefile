.PHONY: default
default: gtest connect4-bot
gtest: board.o eval.o minimax.o
gtest: LDLIBS += $(shell pkg-config --libs gtest gtest_main)
gtest: CXXFLAGS += $(shell pkg-config --cflags gtest gtest_main) -O3 -std=c++23
connect4-bot: board.o eval.o minimax.o
connect4-bot: CXXFLAGS += -O3 -std=c++23
