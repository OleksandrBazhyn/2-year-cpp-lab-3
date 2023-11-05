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

#include "actionsSets.cpp"
#include "Duga.h"

const int nt = 5;

std::string f(char x, int i)
{
	std::cout << "From set " << x << " has been done act " << i << "\n";
	return "f";
}

int main()
{
	Duga J('j', 8, []()
		{
			Duga
		});
}