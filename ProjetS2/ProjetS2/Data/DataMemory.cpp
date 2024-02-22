#include "DataMemory.hpp"

DataMemory::DataMemory()
{
	// Maps
	maps.push_back(Map(1, 80, 20));
	maps.push_back(Map(2, 60, 15));
	maps.push_back(Map(3, 40, 10));
	maps.push_back(Map(4, 100, 25));

	//Watersheds
	Watershed watershed;
	std::vector<Fish> fishPool1;
	std::vector<CaptureStep> captureSteps;
	CaptureStep captureStep;
	captureStep.speed_rotPerSec = 1.0f;
	captureStep.margin = 0.0f;
	captureStep.duration_s = 0.0f;
	captureSteps.push_back(captureStep);

	captureStep.speed_rotPerSec = 2.0f;
	captureStep.margin = 0.0f;
	captureStep.duration_s = 0.0f;
	captureSteps.push_back(captureStep);
	fishPool1.push_back(Fish(1, captureSteps, "Truite", 0.25f, 1.0f, 5));

	captureSteps.clear();

	captureStep.speed_rotPerSec = 3.0f;
	captureStep.margin = 0.0f;
	captureStep.duration_s = 0.0f;
	captureSteps.push_back(captureStep);
	fishPool1.push_back(Fish(2, captureSteps, "Saumon", 0.4f, 3.0f, 10));

	watershed = Watershed(1, fishPool1);
}

DataMemory::~DataMemory()
{

}

std::vector<int> DataMemory::getScores()
{
	return scores;
}

Watershed DataMemory::getWatershed(int watershedId)
{
	for (Watershed watershed : watersheds)
	{
		if (watershed.getId() == watershedId)
		{
			return watershed;
		}
	}
}

Map DataMemory::getMap(int mapId)
{
	for (Map map : maps)
	{
		if (map.getId() == mapId)
		{
			return map;
		}
	}
	return Map();
}

void DataMemory::addScore(int score)
{
	scores.push_back(score);
}

int DataMemory::getHighScore()
{
	int highScore = 0;
	for (int score : scores)
	{
		if (score > highScore)
		{
			highScore = score;
		}
	}
	return highScore;
}