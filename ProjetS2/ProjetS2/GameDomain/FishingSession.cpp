#include "FishingSession.hpp"

FishingSession::FishingSession()
{
    score = 0;
    player = Player();
    data = new DataFile();
    watershed = Watershed();
    environment = Environment();
    map = Map(1, 29, 19);
    rng = new RngClassic();
    timer_s = 120.0f;
    timeElapsed_s = 0.0;
}

FishingSession::FishingSession(int fishAmount, int difficulty)
{
	score = 0;
	player = Player();
	data = new DataFile();
	watershed = data->getWatershed(1); // MODIFY DEPENDING ON SETTINGS
	environment = Environment();
	rng = new RngClassic();
	setDifficulty(difficulty);
	timeElapsed_s = 0.0;
	startTime = std::chrono::system_clock::now();

	fishs = data->getRandomFish(fishAmount);

	map = Map(1, 29, 19);
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

void FishingSession::setDifficulty(int difficulty)
{
  this->difficulty = difficulty;
  switch (difficulty)
  {
    case SESSION_DIFFICULTY_EASY:
      timer_s = 120.0;
      break;
    case SESSION_DIFFICULTY_MEDIUM:
      timer_s = 90.0;
      break;
    case SESSION_DIFFICULTY_HARD:
      timer_s = 60.0;
      break;
    case SESSION_DIFFICULTY_DOOM:
      timer_s = 30.0;
      fishs = data->getRandomFish(20);
      break;
  default:
    break;
  }
}

int FishingSession::getScore()
{
	return score;
}

void FishingSession::startTimer()
{
	startTime = std::chrono::system_clock::now();
}

void FishingSession::updateTimer()
{
	std::chrono::system_clock::time_point currentTime = std::chrono::system_clock::now();

	std::chrono::duration<double> duration = currentTime - startTime;

	timeElapsed_s = duration.count();
}

double FishingSession::getRemainingTime_s()
{
	return timer_s - timeElapsed_s;
}

int FishingSession::getDifficulty()
{
	return difficulty;
}

bool FishingSession::processInput(InputGame input)
{
	bool finish = false;
	updateTimer();

	if (checkMovement(input.movement))
	{
		player.move(input.movement);
	}

	if (input.reelSpeed_rpm > 0)
	{
		finish = captureNearFish(input.reelSpeed_rpm, input.inputDuration_s);
	}

	if (input.hasPulled)
	{
		getNearFishRef()->setIsCapturing(true);
	}

	if (input.muon || difficulty == SESSION_DIFFICULTY_DOOM)
	{
		randomMoveFish();
	}
	return finish;
}

void FishingSession::randomMoveFish()
{
  Movement randomMovement = { 0 ,0 };
  float random = 0.0f;
  for (int i = 0; i < fishs.size(); i++)
  {
    if (!(fishs[i].getPosition().x == player.getPosition().x && fishs[i].getPosition().y == player.getPosition().y))
    {
      random = rng->getRandom();
      if (random > (1 / difficulty) || difficulty == SESSION_DIFFICULTY_DOOM)
      {
        // X
        random = rng->getRandom();
        if (random <= RANDOM_THRESHOLD_MINUS)
        {
          randomMovement.x = -1;
        }
        else if (random <= RANDOM_THRESHOLD_ADD)
        {
          randomMovement.x = 1;
        }
        else
        {
          randomMovement.x = 0;
        }

        // Y
        random = rng->getRandom();
        if (random <= RANDOM_THRESHOLD_MINUS)
        {
          randomMovement.y = -1;
        }
        else if (random <= RANDOM_THRESHOLD_ADD)
        {
          randomMovement.y = 1;
        }
        else
        {
          randomMovement.y = 0;
        }
      }
      if (checkFishMovement(fishs[i], randomMovement))
      {
        fishs[i].move(randomMovement);
      }
      else
      {
        i--;
        continue;
      }
    }
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

Fish* FishingSession::getNearFishRef()
{
	for (int i = 0; i < fishs.size(); i++)
	{
		if (abs(fishs[i].getPosition().x - player.getPosition().x) <= CAPTURE_DISTANCE
			&& abs(fishs[i].getPosition().y - player.getPosition().y) <= CAPTURE_DISTANCE)
		{
			return &fishs[i];
		}
	}
	return new Fish();
}

bool FishingSession::getIsFinished()
{
  if (fishs.size() == 0 || score >= 999 || timer_s - timeElapsed_s <= 0.0)
  {
    data->addScore(score);
    return true;
  }
  return false;
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

bool FishingSession::checkFishMovement(Fish fish, Movement movement)
{
  Position aimedPosition;
  aimedPosition.x = fish.getPosition().x + movement.x;
  aimedPosition.y = fish.getPosition().y + movement.y;

  for (Fish fish : fishs)
  {
    if (fish.getPosition().x == aimedPosition.x && fish.getPosition().y == aimedPosition.y)
    {
      return true;
    }
  }
  return map.isInMap(aimedPosition);
}

bool FishingSession::captureNearFish(float reelSpeed_rotPerSec, float duration_s)
{
	for (int fishIndex = 0; fishIndex < fishs.size(); fishIndex++)
	{
		if (abs(fishs[fishIndex].getPosition().x - player.getPosition().x) <= CAPTURE_DISTANCE
			&& abs(fishs[fishIndex].getPosition().y - player.getPosition().y) <= CAPTURE_DISTANCE)
		{
			if (fishs[fishIndex].capture(reelSpeed_rotPerSec, duration_s))
			{
				score += fishs[fishIndex].getScore();
				capturedFishs.push_back(fishs[fishIndex]);
				fishs.erase(fishs.begin() + fishIndex);
				return true;
			}
		}
	}
	return false;
}