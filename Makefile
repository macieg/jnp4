all: holding.hh test.cc
	g++ -Wall holding.hh test.cc -o test
