#pragma once

#include <vector>
#include "../GameDomain/Entities/Fish.hpp"
#include "../GameDomain/Map/Map.hpp"
#include "../GameDomain/Watershed.hpp"

class IData
{
public:
    virtual std::vector<int> getScores() = 0;
    virtual Watershed getWatershed(int watershedId) = 0;
    virtual Map getMap(int mapId) = 0;
    virtual void addScore(int score) = 0;
    virtual int getHighScore() = 0;
};