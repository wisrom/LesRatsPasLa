#pragma once

#include "Entities/Player.hpp"
#include "Entities/Fish.hpp"
#include "../Types/InputAction.hpp"
#include "Map/Map.hpp"
#include "Watershed.hpp"

class FishingSession
{
public:
  Player player;
  std::vector<Fish> fishs;
  Map map;

  FishingSession();
  ~FishingSession();

  int getScore();
  void processInput(InputAction input);
private:
  Watershed watershed;
  Environment environment;
  int score;
  const int CAPTURE_DISTANCE = 0;

  bool checkMovement(Movement movement);
  void captureNearFish(float reelSpeed_rotPerSec, float duration_s);
};