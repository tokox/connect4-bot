gtest: board.o eval.o
gtest: LDLIBS += $(shell pkg-config --libs gtest gtest_main)
gtest: CXXFLAGS += $(shell pkg-config --cflags gtest gtest_main)
