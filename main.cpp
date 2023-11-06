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

const int nt = 5;

//static std::string f(char x, int i)
//{
//	switch (x)
//	{
//		case 'a':
//			return ;
//		break;
//		case 'b':
//			return ;
//		break;
//	default:
//		break;
//	}
//	return;
//}

//std::string GetResult()
//{
//	std::vector<Duga> duga;
//	duga.push_back(A());
//	duga.push_back(B());
//	duga.push_back(C());
//	duga.push_back(D());
//	duga.push_back(E());
//	duga.push_back(F());
//	duga.push_back(G());
//	duga.push_back(H());
//	duga.push_back(I());
//	duga.push_back(J());
//
//	std::vector<std::thread> threads;
//	std::vector<std::string> results;
//
//	std::latch latch(nt);
//	std::barrier barrier(nt);
//
//	for (int i = 0; i < nt; i++)
//	{
//		threads.push_back(std::thread([&duga, &results, &latch, &barrier, i]()
//			{
//				std::string result = duga[i].GetResult();
//				results.push_back(result);
//				latch.count_down();
//				barrier.arrive_and_wait();
//			}));
//	}
//
//	latch.wait();
//
//	std::string result = "";
//	for (int i = 0; i < nt; i++)
//	{
//		result += results[i];
//	}
//
//	return result;
//
//}

int main()
{
	int usednt = 0;
	std::string start1 = " ";
	std::string start2 = " ";

	auto A = [&]() {
		return start1 + "A";
		};
	auto B = [&]() {
		return start1 + "B";
		};
	auto C = [&]() {
		return A() + "C";
		};
	auto D = [&]() {
		return A() + "D";
		};
	auto E = [&]() {
		return B() + "E";
		};
	auto F = [&]() {
		return B() + "F";
		};
	auto G = [&]() {
		return C() + "G";
		};
	auto H = [&]() {
		return D() + E() + "H";
		};
	auto I = [&]() {
		return F() + "I";
		};
	auto J = [&]() {
		return G() + H() + I() + "J";
		};

	std::cout << J();
}