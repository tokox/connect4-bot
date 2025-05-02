FLAGS = -std=gnu++26
FLAGS += -Wall -Wextra -Wpedantic -Werror -Wno-error=conversion -Wno-error=implicit-fallthrough -Wshadow -Wformat=2 -Wconversion -Wlogical-op -Wduplicated-cond -Wcast-qual -Wcast-align
.PHONY: default
default: gtest
.PHONY: debug
debug: FLAGS += -fsanitize=undefined -fsanitize=address -fno-sanitize-recover -fstack-protector
debug: FLAGS += -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -O1 -ggdb3
debug:  gtest connect4-bot
.PHONY: release
release: FLAGS += -Ofast -march=native -flto -DNDEBUG
release: gtest connect4-bot
connect4-bot: always
	g++ -o connect4-bot connect4-bot.cpp $(FLAGS)
gtest: always
	g++ -o gtest gtest.cpp -lgtest -lgtest_main $(FLAGS)
	./gtest | tee gtest_result.txt
cleanup:
	rm -f gtest connect4-bot
always:
