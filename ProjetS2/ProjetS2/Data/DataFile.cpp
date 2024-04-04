#include "DataFile.hpp"

DataFile::DataFile()
{
 
}

DataFile::~DataFile()
{

}

std::vector<int> DataFile::getScores()
{
    std::vector<int> scores;
    return scores;
}

std::vector<Fish> DataFile::getRandomFish(int quantity)
{
  std::vector<FishDTO> fishDTOs = getAllFish();
  std::vector<Fish> randomFishs;
  FishDTO selectedFish;
  Fish randomFish;
  IRng* rng = new RngClassic();
  int randomIndex = 0;

  float randomWeight_g = 0.0f;
  float randomLength_mm = 0.0f;

  int i = 0;

  while (i < quantity)
  {
    randomIndex = (int)(fishDTOs.size() * rng->getRandom());

    // Prevent overflow
    if (randomIndex == fishDTOs.size())
    {
      randomIndex--;
    }

    selectedFish = fishDTOs[randomIndex];

    randomWeight_g = selectedFish.minWeight_g + ((selectedFish.maxWeight_g - selectedFish.minWeight_g) * rng->getRandom());
    randomLength_mm = selectedFish.maxLength_mm + ((selectedFish.maxLength_mm - selectedFish.minLength_mm) * rng->getRandom());

    randomFish = Fish(selectedFish.id, getCaptureSteps(selectedFish.difficulty), selectedFish.name, randomLength_mm, randomWeight_g, selectedFish.score);
    randomFishs.push_back(randomFish);
    i++;
  }

  return randomFishs;
}

std::vector<FishDTO> DataFile::getAllFish()
{
  std::ifstream file("../GameData/Fish/Fish.csv");
  std::string line;
  std::vector<FishDTO> fishs;
  FishDTO fish;
  std::getline(file, line); // skip first line

  while (std::getline(file, line))
  {
    std::string s = line;
    std::string delimiter = ";";

    size_t pos = 0;
    std::vector<std::string> fields;

    while ((pos = s.find(delimiter)) != std::string::npos) {
      fields.push_back(s.substr(0, pos));
      s.erase(0, pos + delimiter.length());
    }
    
    fish.id = std::stoi(fields[0]);
    fish.name = fields[1];
    fish.minLength_mm = std::stoi(fields[2]);
    fish.maxLength_mm = std::stoi(fields[3]);
    fish.minWeight_g = std::stoi(fields[4]);
    fish.maxWeight_g = std::stoi(fields[5]);
    fish.score = std::stoi(fields[6]);
    fish.difficulty = std::stoi(s);

    fishs.push_back(fish);
  }

  return fishs;
}


Watershed DataFile::getWatershed(int watershedId)
{
    Watershed watershed;
    return watershed;
}

Map DataFile::getMap(int mapId)
{
    Map map;
    return map;
}

void DataFile::addScore(int score)
{
    std::ofstream outfile;

    outfile.open("Scores.csv", std::ios_base::app); // append instead of overwrite
    outfile << score;
    outfile.close();
}

int DataFile::getHighScore()
{   
    int score;
    int highScore = 0;
    std::ifstream file("../GameData/Scores/Scores.csv");
    std::string lineText;
    while (getline(file, lineText))
    {   
        score = std::stoi(lineText);
        if (highScore < score)
        {
          highScore = score;
        }
    }
   
    file.close();
    return highScore;
}

std::vector<CaptureStep> DataFile::getCaptureSteps(int difficulty)
{
  std::vector<CaptureStep> captureSteps;
  int fishDifficulty = 0;
  int marginDifficulty = MARGIN_EASY;

  if (difficulty % 2 == 0)
  {
    marginDifficulty = MARGIN_HARD;
  }

  fishDifficulty = (int)((difficulty + 1) / 2); // 1 to make for cast truncate

  switch (fishDifficulty)
  {
    case DIFFICULTY_VERY_EASY:
      captureSteps = getCaptureSteps_veryEasy(marginDifficulty);
      break;
    case DIFFICULTY_EASY:
      captureSteps = getCaptureSteps_easy(marginDifficulty);
      break;
    case DIFFICULTY_MEDIUM:
      captureSteps = getCaptureSteps_medium(marginDifficulty);
      break;
    case DIFFICULTY_HARD:
      captureSteps = getCaptureSteps_hard(marginDifficulty);
      break;
    case DIFFICULTY_VERY_HARD:
      captureSteps = getCaptureSteps_veryHard(marginDifficulty);
      break;
    case DIFFICULTY_EXTREME:
      captureSteps = getCaptureSteps_extreme(marginDifficulty);
      break;
    default:
      break;
  }
  return captureSteps;
}

std::vector<CaptureStep> DataFile::getCaptureSteps_veryEasy(int margin)
{
  std::vector<CaptureStep> captureSteps;
  CaptureStep captureStep;
  int baseMargin_rpm = 40;

  captureStep.duration_s = 2.0f;
  captureStep.margin = (int)(baseMargin_rpm / margin);
  captureStep.speed_rpm = 60.0f;
  captureSteps.push_back(captureStep);

  return captureSteps;
}

std::vector<CaptureStep> DataFile::getCaptureSteps_easy(int margin)
{
  std::vector<CaptureStep> captureSteps;
  CaptureStep captureStep;
  int baseMargin_rpm = 30;

  captureStep.duration_s = 2.0f;
  captureStep.margin = (int)(baseMargin_rpm / margin);
  captureStep.speed_rpm = 100.0f;
  captureSteps.push_back(captureStep);

  captureStep.duration_s = 2.0f;
  captureStep.margin = (int)(baseMargin_rpm / margin);
  captureStep.speed_rpm = 60.0f;
  captureSteps.push_back(captureStep);

  return captureSteps;
}

std::vector<CaptureStep> DataFile::getCaptureSteps_medium(int margin)
{
  std::vector<CaptureStep> captureSteps;
  CaptureStep captureStep;
  int baseMargin_rpm = 25;

  captureStep.duration_s = 2.0f;
  captureStep.margin = (int)(baseMargin_rpm / margin);
  captureStep.speed_rpm = 100.0f;
  captureSteps.push_back(captureStep);

  captureStep.duration_s = 2.0f;
  captureStep.margin = (int)(baseMargin_rpm / margin);
  captureStep.speed_rpm = 60.0f;
  captureSteps.push_back(captureStep);

  captureStep.duration_s = 1.0f;
  captureStep.margin = (int)(baseMargin_rpm / margin);
  captureStep.speed_rpm = 100.0f;
  captureSteps.push_back(captureStep);

  return captureSteps;
}

std::vector<CaptureStep> DataFile::getCaptureSteps_hard(int margin)
{
  std::vector<CaptureStep> captureSteps;
  CaptureStep captureStep;
  int baseMargin_rpm = 20;

  captureStep.duration_s = 2.0f;
  captureStep.margin = (int)(baseMargin_rpm / margin);
  captureStep.speed_rpm = 60.0f;
  captureSteps.push_back(captureStep);

  captureStep.duration_s = 2.0f;
  captureStep.margin = (int)(baseMargin_rpm / margin);
  captureStep.speed_rpm = 100.0f;
  captureSteps.push_back(captureStep);

  captureStep.duration_s = 1.0f;
  captureStep.margin = (int)(baseMargin_rpm / margin);
  captureStep.speed_rpm = 140.0f;
  captureSteps.push_back(captureStep);

  return captureSteps;
}

std::vector<CaptureStep> DataFile::getCaptureSteps_veryHard(int margin)
{
  std::vector<CaptureStep> captureSteps;
  CaptureStep captureStep;
  int baseMargin_rpm = 20;

  captureStep.duration_s = 1.0f;
  captureStep.margin = (int)(baseMargin_rpm / margin);
  captureStep.speed_rpm = 140.0f;
  captureSteps.push_back(captureStep);

  captureStep.duration_s = 2.0f;
  captureStep.margin = (int)(baseMargin_rpm / margin);
  captureStep.speed_rpm = 100.0f;
  captureSteps.push_back(captureStep);

  captureStep.duration_s = 1.0f;
  captureStep.margin = (int)(baseMargin_rpm / margin);
  captureStep.speed_rpm = 140.0f;
  captureSteps.push_back(captureStep);

  captureStep.duration_s = 1.0f;
  captureStep.margin = (int)(baseMargin_rpm / margin);
  captureStep.speed_rpm = 100.0f;
  captureSteps.push_back(captureStep);

  return captureSteps;
}

std::vector<CaptureStep> DataFile::getCaptureSteps_extreme(int margin)
{
  std::vector<CaptureStep> captureSteps;
  CaptureStep captureStep;
  int baseMargin_rpm = 10;

  captureStep.duration_s = 3.0f;
  captureStep.margin = (int)(baseMargin_rpm / margin);
  captureStep.speed_rpm = 180.0f;
  captureSteps.push_back(captureStep);

  captureStep.duration_s = 2.0f;
  captureStep.margin = (int)(baseMargin_rpm / margin);
  captureStep.speed_rpm = 140.0f;
  captureSteps.push_back(captureStep);

  captureStep.duration_s = 3.0f;
  captureStep.margin = (int)(baseMargin_rpm / margin);
  captureStep.speed_rpm = 180.0f;
  captureSteps.push_back(captureStep);

  captureStep.duration_s = 1.0f;
  captureStep.margin = (int)(baseMargin_rpm / margin);
  captureStep.speed_rpm = 100.0f;
  captureSteps.push_back(captureStep);

  captureStep.duration_s = 1.0f;
  captureStep.margin = (int)(baseMargin_rpm / margin);
  captureStep.speed_rpm = 30.0f;
  captureSteps.push_back(captureStep);

  return captureSteps;
}
