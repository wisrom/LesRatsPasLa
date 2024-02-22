#include "FishingSession.hpp"

FishingSession::FishingSession()
{
    score = 0;
    player = Player();
    watershed = Watershed();
    environment = Environment();

    // TEST
    std::vector<CaptureStep> captureSteps;
    CaptureStep captureStep;
    captureStep.duration_s = 0;
    captureStep.margin = 0;
    captureStep.speed_rotPerSec = 1;
    captureSteps.push_back(captureStep);

    Fish fish = Fish(captureSteps, "Fish", 0.25, 3.0f, 1);
    fish.setPosition({ 5, 4 });

    fishs.push_back(fish); // test

    captureStep.speed_rotPerSec = 2;
    captureSteps.push_back(captureStep);
    fish = Fish(captureSteps, "Fish", 0.25, 3.0f, 2);
    fish.setPosition({ 10, 6 });
    fishs.push_back(fish);
    map = Map(80, 20);
}

FishingSession::~FishingSession()
{

}

int FishingSession::getScore()
{
  return score;
}

void FishingSession::processInput(InputAction input)
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
    if (abs(fishs[fishIndex].getPosition().x - player.getPosition().x) <= 1 && abs(fishs[fishIndex].getPosition().y - player.getPosition().y) <= 1)
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