#pragma once

//string‚Ævector
#include <string>
#include <vector>

class CSVLoader
{
public:

    static bool LoadCSV(
        const std::string& filePath,
        std::vector<std::vector<std::string>>& outData);

private:

    static std::vector<std::string> Split(
        const std::string& line,
        char delimiter = ',');
};