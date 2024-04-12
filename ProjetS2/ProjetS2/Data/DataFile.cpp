#include "DataFile.hpp"
#include <QFile>
#include <QTextStream>
#include <QDir>


DataFile::DataFile()
{

}

DataFile::~DataFile()
{

}

std::vector<int> DataFile::getScores()
{
	std::vector<int> scores;
	int score;
	QFile file(":/GameData/Scores/Scores.csv");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		return scores; // Renvoyer un vecteur vide si le fichier ne peut pas être ouvert
	}

	file.readLine();

	while (!file.atEnd())
	{
		QByteArray line = file.readLine();
		QString s = QString::fromUtf8(line).trimmed(); // Convertir la ligne en QString

		score = s.toInt();

		scores.push_back(score);
	}

	file.close();

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
	std::vector<FishDTO> fishs;
	QFile file(":/GameData/Fish/Fish.csv");

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) 
	{
		return fishs; // Renvoyer un vecteur vide si le fichier ne peut pas être ouvert
	}

	file.readLine();

	while (!file.atEnd()) 
	{
		QByteArray line = file.readLine();
		QString s = QString::fromUtf8(line).trimmed(); // Convertir la ligne en QString

		QStringList fields = s.split(';'); // Divise la ligne en champs en utilisant ';'

		if (fields.size() != 8) {
			
			continue; // Ignorer les lignes avec un format invalide
		}

		FishDTO fish;
		fish.id = fields[0].toInt();
		fish.name = fields[1].toStdString();
		fish.minLength_mm = fields[2].toInt();
		fish.maxLength_mm = fields[3].toInt();
		fish.minWeight_g = fields[4].toInt();
		fish.maxWeight_g = fields[5].toInt();
		fish.score = fields[6].toInt();
		fish.difficulty = fields[7].toInt();

		fishs.push_back(fish);
	}

	file.close();

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
	QFile file("C:/Users/pitch/Desktop/QtBackup/ProjetS2/GameData/Scores/Scores.csv");
	if (file.open(QIODevice::Append | QIODevice::Text)) 
	{
		QTextStream stream(&file);
		// Writing each element of the rowData list separated by commas
		stream << score << "\n";
		file.close();
	}
}

std::vector<int> DataFile::get5HighScores()
{
	std::vector<int> scores = getScores();
	int highScore = 0;
	int highScoreIndex = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < scores.size(); j++)
		{
			if (scores[j] > highScore)
			{
				highScore = scores[j];
				highScoreIndex = j;
			}
		}
		scores.push_back(highScore);
		scores.erase(scores.begin() + highScoreIndex);
	}
	
	return scores;
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
	int baseMargin_rpm = 35;

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
	captureStep.speed_rpm = 80.0f;
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
	captureStep.speed_rpm = 100.0f;
	captureSteps.push_back(captureStep);

	captureStep.duration_s = 2.0f;
	captureStep.margin = (int)(baseMargin_rpm / margin);
	captureStep.speed_rpm = 80.0f;
	captureSteps.push_back(captureStep);

	captureStep.duration_s = 1.0f;
	captureStep.margin = (int)(baseMargin_rpm / margin);
	captureStep.speed_rpm = 120.0f;
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
	captureStep.speed_rpm = 120.0f;
	captureSteps.push_back(captureStep);

	captureStep.duration_s = 2.0f;
	captureStep.margin = (int)(baseMargin_rpm / margin);
	captureStep.speed_rpm = 110.0f;
	captureSteps.push_back(captureStep);

	captureStep.duration_s = 3.0f;
	captureStep.margin = (int)(baseMargin_rpm / margin);
	captureStep.speed_rpm = 100.0f;
	captureSteps.push_back(captureStep);

	captureStep.duration_s = 1.0f;
	captureStep.margin = (int)(baseMargin_rpm / margin);
	captureStep.speed_rpm = 60.0f;
	captureSteps.push_back(captureStep);

	captureStep.duration_s = 1.0f;
	captureStep.margin = (int)(baseMargin_rpm / margin);
	captureStep.speed_rpm = 120.0f;
	captureSteps.push_back(captureStep);

	return captureSteps;
}
