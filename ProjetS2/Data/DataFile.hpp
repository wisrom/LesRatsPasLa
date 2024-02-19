#pragma once

#include "IData.hpp"

class DataFile : public IData
{
public:
    DataFile();
    ~DataFile();
    std::vector<int> getScores();
    std::vector<Fish> getFishPool(int watershedId);
};