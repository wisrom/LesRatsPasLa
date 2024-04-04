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

class FishingSession
{
public:
  Player player;
  std::vector<Fish> fishs;
  Map map;

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
  void processInput(InputGame input);
  bool isFishPositionOccupied(Position position);
private:
  Watershed watershed;
  Environment environment;
  IData* data;
  int score;
  std::vector<Fish> capturedFishs;
  double timer_s;
  double timeElapsed_s;
  int difficulty;
  std::chrono::system_clock::time_point startTime;
  const int CAPTURE_DISTANCE = 0;

  void setDifficulty(int difficulty);
  bool checkMovement(Movement movement);
  void captureNearFish(float reelSpeed_rotPerSec, float duration_s);
};