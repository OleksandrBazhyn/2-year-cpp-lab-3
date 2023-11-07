// Bazhyn Oleksandr K-24 variant 1
// scheme 1, nt = 5, a = 6, b = 5, c = 8, d = 5, e = 8, f = 9, g = 4, h = 5, i = 6, j = 8
// scheme 1:  a->c->g->j, a->d->h->j, b->e->h->j, b->f->i->j

#include <thread>
#include <semaphore>
#include <latch>
#include <barrier>

#include <vector>
#include <string>
#include <iostream>
#include <syncstream>
#include <functional>
#include <map>

#include "actionsSets.cpp"
#include "Duga.h"

typedef std::unordered_map<char, std::vector<std::function<std::string()>>> Orgraph;

const int nt = 5;

std::vector<std::function<std::string()>> fillDuga(int countOfActs, std::function<std::string()>  func)
{
	std::vector<std::function<std::string()>> duga;

	for (int i = 0; i < countOfActs; i++)
	{
		duga.push_back(func);
	}

	return duga;
}

std::string f(char x, int i)
{
	return "v";
}

int main()
{
	int usednt = 0;
	std::string start1 = " ";
	std::string start2 = " ";

	Orgraph orgraph;

	orgraph['a'] = fillDuga(6, [&]() {
		return start1 + "A";
		});

	orgraph['b'] = fillDuga(5, [&]() {
		return start1 + "B";
		});
	orgraph['c'] = fillDuga(8, [&]() {
		return f('a', 6) + "C";
		});
	orgraph['d'] = fillDuga(5, [&]() {
		return f('a', 6) + "D";
		});
	orgraph['e'] = fillDuga(8, [&]() {
		return f('b', 5) + "E";
		});
	orgraph['f'] = fillDuga(9, [&]() {
		return f('b', 5) + "F";
		});
	orgraph['g'] = fillDuga(4, [&]() {
		return f('c', 8) + "G";
		});
	orgraph['h'] = fillDuga(5, [&]() {
		return f('d', 5) + f('e', 8) + "H";
		});
	orgraph['i'] = fillDuga(6, [&]() {
		return f('f', 9) + "I";
		});
	orgraph['j'] = fillDuga(8, [&]() {
		return f('g', 4) + f('h', 5) + f('i', 6) + "J";
		});

	std::string result = orgraph['j'][7]();

	std::cout << orgraph['a'].size() << " with value " << result << std::endl;
}