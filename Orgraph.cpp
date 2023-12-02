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

std::string Orgraph::f(char x, int i = 1)
{
	std::string result;
	for (int j = 0; j < i; j++)
	{
		result += this->orgraph[x][i - 1]();
	}
	return result;
}

std::string Orgraph::CalculateDuga(char duga)
{
	return std::string();
}

std::string Orgraph::GetResult()
{
	std::string result = "";
	std::latch work_done(2);

	std::string Node1 = "";
	std::string Node2 = "";

	std::thread t1([&] {Node1 = f('a', 6); work_done.count_down(); });
	std::thread t2([&] {Node2 = f('b', 5); work_done.count_down(); });

	this->nt -= 2;

	work_done.wait();
	t1.join();
	t2.join();
	this->nt += 2;

	std::latch work_done2(4);

	std::string Node3 = "";
	std::string Node4 = "";

	std::thread t1([&] {Node1 = f('a', 6); work_done.count_down(); });
	std::thread t2([&] {Node2 = f('b', 5); work_done.count_down(); });


	return result;
}