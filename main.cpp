// Bazhyn Oleksandr K-24 variant 1
// scheme 1, nt = 5, a = 6, b = 5, c = 8, d = 5, e = 8, f = 9, g = 4, h = 5, i = 6, j = 8
// scheme 1:  a->c->g->j, a->d->h->j, b->e->h->j, b->f->i->j

// main.cpp
#include "Orgraph.h"
#include "Utils.h"

#include <iostream>

int main()
{
    std::string start1 = "1";
    std::string start2 = "2";

    Orgraph orgraph(start1, start2);

    std::string result = orgraph.GetResult();

    WriteResultToFile("result.txt", result);

    std::cout << result << std::endl;

    return 0;
}
