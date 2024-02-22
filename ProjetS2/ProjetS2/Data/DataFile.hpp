#pragma once

#include "IData.hpp"

class DataFile : public IData
{
public:
    DataFile();
    ~DataFile();

    std::vector<int> getScores() override;
    Watershed getWatershed(int watershedId) override;
    Map getMap(int mapId) override;
    void addScore(int score) override;
    int getHighScore() override;
private:
    const std::string FISH_PATH = "../../GameData/Fish/Fish.csv";
    const std::string FISH_POOL_PATH = "../../GameData/Fish/FishPool.csv";
    const std::string MAP_PATH = "../../GameData/Map/Map.csv";
    const std::string SCORE_PATH = "../../GameData/Scores/Scores.csv";
};