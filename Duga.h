#pragma once

class Duga {
private:
	int actions;
	char name;
	std::function<std::string()> act;
public:
	Duga(char name, int actions, std::function<std::string()> act);
};