#pragma once

#include <vector>
#include "../GameDomain/Entities/Fish.hpp"

class IData
{
public:
    virtual std::vector<int> getScores() = 0;
    virtual std::vector<Fish> getFishPool(int watershedId) = 0;
};