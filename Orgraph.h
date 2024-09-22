// Orgraph.h
#pragma once

#include <string>
#include <mutex>
#include <latch>

class Orgraph
{
private:
    int nt = 5;
    std::string startValues[2];

public:
    Orgraph(const std::string& startValue1, const std::string& startValue2);

    std::string f(char x, int i = 1);

    std::string GetResult();

private:
    void InitNodesAB(std::string& Node1, std::string& Node2, std::latch& work_done);
    void ProcessNodesCDEF(std::string& Node1, std::string& Node2, std::string& Node3, std::string& Node4, std::string& Node5, std::latch& work_done2, std::mutex& mutex);
    void ProcessNodesGHI(std::string& Node3, std::string& Node4, std::string& Node5, std::string& Node6, std::latch& work_done3, std::mutex& mutex);
    std::string FinalizeResult(const std::string& Node6);
};
