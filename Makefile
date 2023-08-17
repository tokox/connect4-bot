CXXFLAGS = -O3 -std=c++23 -DNDEBUG
DEBUGFLAGS = -Wall -Wextra -pedantic -std=c++23 -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -fsanitize=address -fsanitize=undefined -fno-sanitize-recover -fstack-protector -ggdb
.PHONY: default
default: connect4-bot gtest
.PHONY: debug
debug: default
debug: CXXFLAGS = $(DEBUGFLAGS)
connect4-bot: board.o eval.o minimax.o
gtest: board.o eval.o minimax.o
gtest: LDLIBS += $(shell pkg-config --libs gtest gtest_main)
gtest: CXXFLAGS += $(shell pkg-config --cflags gtest gtest_main)
