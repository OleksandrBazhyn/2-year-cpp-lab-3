#pragma once
#ifndef DUGA_H
#define DUGA_H

#include <functional>
#include <string>

class Orgraph {
private:
	std::string f(char x, int i);

	std::string startValues[2];
	int nt = 5;
public:
	Orgraph(const std::string& startValue1, const std::string& startValue2);
	std::string GetResult();
};

#endif