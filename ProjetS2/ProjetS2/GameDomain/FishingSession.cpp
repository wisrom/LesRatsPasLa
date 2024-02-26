#include "FishingSession.hpp"

FishingSession::FishingSession()
{
    score = 0;
    player = Player();
    data = new DataMemory();
    watershed = Watershed();
    environment = Environment();
    map = Map(1, 80, 20);
}

FishingSession::FishingSession(int fishAmount)
{
  score = 0;
  player = Player();
  data = new DataMemory();
  watershed = data->getWatershed(1); // MODIFY DEPENDING ON SETTINGS
  environment = Environment();

  for (int i = 0; i < fishAmount; i++)
  {
    fishs.push_back(watershed.getRandomFish());
  }

  map = Map(1, 80, 20);
  for (int i = 0; i < fishs.size(); i++)
  {
    Position randomPosition = map.getRandomPosition();
    if (isFishPositionOccupied(randomPosition))
    {
      i--;
      continue;
    }
    fishs[i].setPosition(randomPosition);
  }
}

FishingSession::~FishingSession()
{
  //delete data;
}

int FishingSession::getScore()
{
  return score;
}

void FishingSession::processInput(InputGame input)
{
  if (checkMovement(input.movement))
  {
    player.move(input.movement);
  }

  if (input.reelSpeed_rotPerSec > 0)
  {
    captureNearFish(input.reelSpeed_rotPerSec, 1); // CHANGE 1 WHEN TIME HAS BEEN FIGURED OUT
  }
}

bool FishingSession::isFishPositionOccupied(Position position)
{
  Position fishPosition;
  for (Fish fish : fishs)
  {
    fishPosition = fish.getPosition();
    if (fishPosition.x == position.x && fishPosition.y == position.y)
    {
      return true;
    }
  }
  return false;
}

Fish FishingSession::getNearFish()
{
  Fish nearFish = Fish();

  for (Fish fish : fishs)
  {
    if (abs(fish.getPosition().x - player.getPosition().x) <= CAPTURE_DISTANCE
      && abs(fish.getPosition().y - player.getPosition().y) <= CAPTURE_DISTANCE)
    {
      nearFish = fish;
      return nearFish;
    }
  }
  return nearFish;
}

bool FishingSession::isPlayerNearFish()
{
  if (getNearFish().getScore() != 0)
  {
    return true;
  }
  return false;
}

bool FishingSession::checkMovement(Movement movement)
{
  Position position = player.getPosition();
  position.x = position.x + movement.x;
  position.y = position.y + movement.y;

  return map.isInMap(position);
}

void FishingSession::captureNearFish(float reelSpeed_rotPerSec, float duration_s)
{
  for (int fishIndex = 0; fishIndex < fishs.size(); fishIndex++)
  {
    if (abs(fishs[fishIndex].getPosition().x - player.getPosition().x) <= CAPTURE_DISTANCE 
      && abs(fishs[fishIndex].getPosition().y - player.getPosition().y) <= CAPTURE_DISTANCE)
    {
      if (fishs[fishIndex].capture(reelSpeed_rotPerSec, duration_s))
      {
        score += fishs[fishIndex].getScore();
        // SAVE FISH
        fishs.erase(fishs.begin() + fishIndex);
        return;
      }
    }
  }
}