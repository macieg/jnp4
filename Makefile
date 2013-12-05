all: holding.hh test.cc
	g++ -Wall holding.hh -std=c++11 test.cc -o test
