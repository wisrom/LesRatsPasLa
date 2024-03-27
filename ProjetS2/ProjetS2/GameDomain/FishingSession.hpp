#pragma once

#include "Entities/Player.hpp"
#include "Entities/Fish.hpp"
#include "../Types/InputGame.hpp"
#include "Map/Map.hpp"
#include "Watershed.hpp"
#include "../Data/IData.hpp"
#include "../Data/DataMemory.hpp"

class FishingSession
{
public:
  Player player;
  std::vector<Fish> fishs;
  Map map;

  FishingSession();
  FishingSession(int fishAmount);
  ~FishingSession();

  int getScore();
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
  const int CAPTURE_DISTANCE = 0;

  bool checkMovement(Movement movement);
  void captureNearFish(float reelSpeed_rotPerSec, float duration_s);
};