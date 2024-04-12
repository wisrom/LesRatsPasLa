#pragma once

#include "Entities/Player.hpp"
#include "Entities/Fish.hpp"
#include "../Types/InputGame.hpp"
#include "Map/Map.hpp"
#include "Watershed.hpp"
#include "../Data/IData.hpp"
#include "../Data/DataMemory.hpp"
#include "../Data/DataFile.hpp"

#define SESSION_DIFFICULTY_EASY 1
#define SESSION_DIFFICULTY_MEDIUM 2
#define SESSION_DIFFICULTY_HARD 3
#define SESSION_DIFFICULTY_DOOM 4

// 0-threshold
#define RANDOM_THRESHOLD_MINUS 0.4f
#define RANDOM_THRESHOLD_NOTHING 1.0f
#define RANDOM_THRESHOLD_ADD 0.8f

class FishingSession
{
public:
  Player player;
  std::vector<Fish> fishs;
  std::vector<Fish> capturedFishs;
  Map map;
  IRng* rng;

  FishingSession();
  FishingSession(int fishAmount, int difficulty);
  ~FishingSession();
  
  int getScore();
  void startTimer();
  void updateTimer();
  double getRemainingTime_s();
  int getDifficulty();
  Fish getNearFish();
  Fish* getNearFishRef(); 
  bool getIsFinished();
  bool isPlayerNearFish();
  bool processInput(InputGame input);
  void randomMoveFish();
  bool isFishPositionOccupied(Position position);
  int difficulty;
private:
  Watershed watershed;
  Environment environment;
  IData* data;
  int score;
  double timer_s;
  double timeElapsed_s;
  std::chrono::system_clock::time_point startTime;
  const int CAPTURE_DISTANCE = 0;

  void setDifficulty(int difficulty);
  bool checkMovement(Movement movement);
  bool captureNearFish(float reelSpeed_rotPerSec, float duration_s);
};