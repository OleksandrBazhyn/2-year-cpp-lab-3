// Utils.cpp
#include "Utils.h"

#include <fstream>

void WriteResultToFile(const std::string& filename, const std::string& data)
{
    std::ofstream outfile(filename);
    if (outfile.is_open()) {
        outfile << data;
        outfile.close();
    }
}
