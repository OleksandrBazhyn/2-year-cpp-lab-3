#pragma once
#ifndef DUGA_H
#define DUGA_H

#include <functional>
#include <string>

class Orgraph {
private:
	std::string f(char x, int i);

	std::string startValues[2];
	const int nt = 5;
	static int usednt;
	//std::unordered_map<char, std::vector<std::function<std::string()>>> orgraph;

	std::vector<std::function<std::string()>> fillDuga(int countOfActs, std::function<std::string()>  func);
public:
	Orgraph(std::string value1, std::string value2);
	std::string GetResult();
	std::unordered_map<char, std::vector<std::function<std::string()>>> orgraph;
};

#endif