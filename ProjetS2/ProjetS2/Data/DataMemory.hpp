#pragma once

#include "IData.hpp"

class DataMemory : public IData
{
public:
	DataMemory();
	~DataMemory();

    std::vector<int> getScores() override;
    Watershed getWatershed(int watershedId) override;
    Map getMap(int mapId) override;
    void addScore(int score) override;
    int getHighScore();
    std::vector<Fish> getRandomFish(int quantity) override;
private:
    std::vector<Watershed> watersheds;
    std::vector<int> scores;
    std::vector<Map> maps;
};