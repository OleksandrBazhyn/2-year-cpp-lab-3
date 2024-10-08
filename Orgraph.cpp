// Orgraph.cpp
#include "Orgraph.h"

#include <thread>
#include <iostream>

Orgraph::Orgraph(const std::string& startValue1, const std::string& startValue2)
{
    this->startValues[0] = startValue1;
    this->startValues[1] = startValue2;
}

std::string Orgraph::f(char x, int i)
{
    std::string result;
    for (int j = 0; j < i; j++)
    {
        result += x;
    }
    return result;
}

void Orgraph::InitNodesAB(std::string& Node1, std::string& Node2, std::latch& work_done)
{
    std::thread t1([&] { Node1 += f('a', 6); work_done.count_down(); });
    std::thread t2([&] { Node2 += f('b', 5); work_done.count_down(); });

    this->nt -= 2;
    std::cout << "Duge A and B are working. nt was left = " << this->nt << "." << std::endl;

    work_done.wait();
    t1.join();
    t2.join();

    this->nt += 2;
    std::cout << "Duge A and B have been completed. nt was left = " << this->nt << "." << std::endl;
}

void Orgraph::ProcessNodesCDEF(std::string& Node1, std::string& Node2, std::string& Node3, std::string& Node4, std::string& Node5, std::latch& work_done2, std::mutex& mutex)
{
    std::thread t1([&] { Node3 += Node1 + f('c', 8); work_done2.count_down(); });
    std::thread t2([&] { mutex.lock(); Node4 += Node1 + f('d', 5); mutex.unlock(); work_done2.count_down(); });
    std::thread t3([&] { mutex.lock(); Node4 += Node2 + f('e', 8); mutex.unlock(); work_done2.count_down(); });
    std::thread t4([&] { Node5 += Node2 + f('f', 9); work_done2.count_down(); });

    this->nt -= 4;
    std::cout << "Duge C, D, E and F are working. nt was left = " << this->nt << "." << std::endl;

    work_done2.wait();
    t1.join();
    t2.join();
    t3.join();
    t4.join();

    this->nt += 4;
    std::cout << "Duge C, D, E and F have been completed. nt was left = " << this->nt << "." << std::endl;
}

void Orgraph::ProcessNodesGHI(std::string& Node3, std::string& Node4, std::string& Node5, std::string& Node6, std::latch& work_done3, std::mutex& mutex)
{
    std::thread t1([&] { mutex.lock(); Node6 += Node3 + f('g', 4); mutex.unlock(); work_done3.count_down(); });
    std::thread t2([&] { mutex.lock(); Node6 += Node4 + f('h', 5); mutex.unlock(); work_done3.count_down(); });
    std::thread t3([&] { mutex.lock(); Node6 += Node5 + f('i', 6); mutex.unlock(); work_done3.count_down(); });

    this->nt -= 3;
    std::cout << "Duge G, H and I are working. nt was left = " << this->nt << "." << std::endl;

    work_done3.wait();
    t1.join();
    t2.join();
    t3.join();

    this->nt += 3;
    std::cout << "Duge G, H and I have been completed. nt was left = " << this->nt << "." << std::endl;
}

std::string Orgraph::FinalizeResult(const std::string& Node6)
{
    std::string result;
    std::thread t1([&] { result = Node6 + f('j', 8); });
    t1.join();
    std::cout << "Orgraph has finished work!" << std::endl;
    return result;
}

std::string Orgraph::GetResult()
{
    std::string result = "";
    std::latch work_done(2);
    std::string Node1 = "", Node2 = "";
    InitNodesAB(Node1, Node2, work_done);

    std::latch work_done2(4);
    std::string Node3 = "", Node4 = "", Node5 = "";
    std::mutex mutex;
    ProcessNodesCDEF(Node1, Node2, Node3, Node4, Node5, work_done2, mutex);

    std::latch work_done3(3);
    std::string Node6 = "";
    ProcessNodesGHI(Node3, Node4, Node5, Node6, work_done3, mutex);

    result = FinalizeResult(Node6);
    return result;
}
