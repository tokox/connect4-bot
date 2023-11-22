CXXFLAGS = -Ofast -march=native -std=gnu++23 -DNDEBUG -flto=auto -fno-exceptions -static
.PHONY: default
default: connect4-bot gtest
connect4-bot: board.o eval.o minimax.o
gtest: board.o eval.o minimax.o
gtest: LDLIBS += $(shell pkg-config --libs gtest gtest_main)
gtest: CXXFLAGS += $(shell pkg-config --cflags gtest gtest_main)
