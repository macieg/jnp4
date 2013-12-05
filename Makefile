all: holding.hh test.cc
	g++ -Wall holding.hh -std=c++0x test.cc -o test
