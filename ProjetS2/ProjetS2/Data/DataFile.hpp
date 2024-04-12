#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

#include "IData.hpp"
#include "FishDTO.hpp"
#include "../Rng/RngClassic.hpp"

#define DIFFICULTY_VERY_EASY 1
#define DIFFICULTY_EASY 2
#define DIFFICULTY_MEDIUM 3
#define DIFFICULTY_HARD 4
#define DIFFICULTY_VERY_HARD 5
#define DIFFICULTY_EXTREME 6

#define MARGIN_EASY 1
#define MARGIN_HARD 2

class DataFile : public IData
{
public:
    DataFile();
    ~DataFile();

    std::vector<int> getScores();
    Watershed getWatershed(int watershedId);
    Map getMap(int mapId);
    void addScore(int score);
    std::vector<int> get5HighScores();
    std::vector<Fish> getRandomFish(int quantity);
    std::vector<FishDTO> getAllFish();

private:
    const std::string FISH_PATH = "../../GameData/Fish/Fish.csv";
    const std::string FISH_POOL_PATH = "../../GameData/Fish/FishPool.csv";
    const std::string MAP_PATH = "../../GameData/Map/Map.csv";
    const std::string SCORE_PATH = "../../GameData/Scores/Scores.csv";

    std::vector<CaptureStep> getCaptureSteps(int difficulty);
    std::vector<CaptureStep> getCaptureSteps_veryEasy(int margin);
    std::vector<CaptureStep> getCaptureSteps_easy(int margin);
    std::vector<CaptureStep> getCaptureSteps_medium(int margin);
    std::vector<CaptureStep> getCaptureSteps_hard(int margin);
    std::vector<CaptureStep> getCaptureSteps_veryHard(int margin);
    std::vector<CaptureStep> getCaptureSteps_extreme(int margin);
};