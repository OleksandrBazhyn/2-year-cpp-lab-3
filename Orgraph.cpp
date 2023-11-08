#include "Orgraph.h"

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

Orgraph::Orgraph(std::string value1, std::string value2)
{
	startValues[0] = value1;
	startValues[1] = value2;

	orgraph['a'] = fillDuga(6, [&]() {
		return this->startValues[0] + "A";
		});

	orgraph['b'] = fillDuga(5, [&]() {
		return this->startValues[1] + "B";
		});
	orgraph['c'] = fillDuga(8, [&]() {
		return this->f('a', 6) + "C";
		});
	orgraph['d'] = fillDuga(5, [&]() {
		return this->f('a', 6) + "D";
		});
	orgraph['e'] = fillDuga(8, [&]() {
		return this->f('b', 5) + "E";
		});
	orgraph['f'] = fillDuga(9, [&]() {
		return this->f('b', 5) + "F";
		});
	orgraph['g'] = fillDuga(4, [&]() {
		return this->f('c', 8) + "G";
		});
	orgraph['h'] = fillDuga(5, [&]() {
		return this->f('d', 5) + this->f('e', 8) + "H";
		});
	orgraph['i'] = fillDuga(6, [&]() {
		return this->f('f', 9) + "I";
		});
	orgraph['j'] = fillDuga(8, [&]() {
		return this->f('g', 4) + this->f('h', 5) + this->f('i', 6) + "J";
		});
}

int Orgraph::usednt = 0;

std::vector<std::function<std::string()>> Orgraph::fillDuga(int countOfActs, std::function<std::string()>  func)
{
	std::vector<std::function<std::string()>> duga;

	for (int i = 0; i < countOfActs; i++)
	{
		duga.push_back(func);
	}

	return duga;
}

std::string Orgraph::f(char x, int i)
{
	std::string result = this->orgraph[x][i - 1]();
	return result;
}

std::string Orgraph::GetResult()
{
	std::string result = this->orgraph['j'][7]();
	return result;
}