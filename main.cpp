// Bazhyn Oleksandr K-24 variant 1
// scheme 1, nt = 5, a = 6, b = 5, c = 8, d = 5, e = 8, f = 9, g = 4, h = 5, i = 6, j = 8
// scheme 1:  a->c->g->j, a->d->h->j, b->e->h->j, b->f->i->j

#include "actionsSets.cpp"
#include "Duga.h"
#include "Orgraph.h"

#include <iostream>

const int nt = 5;

int main()
{
	int usednt = 0;
	std::string start1 = "1";
	std::string start2 = "2";

	Orgraph orgraph(start1, start2);

	std::string result = orgraph.GetResult();

	std::cout << orgraph.orgraph['j'].size() << " with value " << result << std::endl;
}