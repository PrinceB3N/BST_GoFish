# Makefile
CXX_FLAG = --std=c++11 -g

all: game tests

game: main.o
	g++ $(CXX_FLAG) main.cpp cards.cpp -o game

tests: tests.o
	g++ $(CXX_FLAG) tests.cpp cards.cpp -o tests

clean:
	rm -f game tests *.o
