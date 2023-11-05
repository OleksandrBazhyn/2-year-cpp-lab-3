#include "Duga.h"

#include <thread>
#include <semaphore>
#include <latch>
#include <barrier>

#include <vector>
#include <string>
#include <iostream>
#include <syncstream>
#include <functional>

Duga::Duga(char name, int actions, std::function<std::string()> act)
{
	this->name = name;
	this->actions = actions;
	this->act = act;
}
