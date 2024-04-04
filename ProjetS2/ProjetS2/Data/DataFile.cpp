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
    std::ifstream file("../GameData/Fish/Fish.csv");
    std::string line;
    std::vector<FishDTO> fishList;
    std::vector<Fish> randomFish;
    std::getline(file, line);
    // Read the file line by line
    while (std::getline(file, line)) {
        // Split the line by the delimiter ';'

        std::string s = line;
        std::string delimiter = ";";

        size_t pos = 0;
        std::vector<std::string> fields;
   
        while ((pos = s.find(delimiter)) != std::string::npos) {
             fields.push_back(s.substr(0, pos));
            s.erase(0, pos + delimiter.length());
        }
        //std::cout << fields.size() << std::endl;
        // Check if the line has the expected number of fields
        //if (fields.size() == 6) {
        //    std::cerr<< line << std::endl;
        //    continue; // Skip this line
        //}
        // Create a FishDTO object and populate its fields
        FishDTO fish;
        fish.id = std::stoi(fields[0]);
        fish.name = fields[1];
        fish.minLength_mm = std::stoi(fields[2]);
        fish.maxLength_mm = std::stoi(fields[3]);
        fish.minWeight_g = std::stoi(fields[4]);
        fish.maxWeight_g = std::stoi(fields[5]);
        fish.score = std::stoi(fields[6]);

        // Add the FishDTO object to the list
        fishList.push_back(fish);
    }

    // Print the information (just for verification)
    for (const auto& fish : fishList) {
        std::cout << "ID: " << fish.id << ", Name: " << fish.name << ", Min Length: " << fish.minLength_mm
            << ", Max Length: " << fish.maxLength_mm << ", Min Weight: " << fish.minWeight_g
            << ", Max Weight: " << fish.maxWeight_g << ", Score: " << fish.score << std::endl;
    }
    return randomFish;
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
    int BiggestScore = 0;
    std::ifstream file("../GameData/Scores/Scores.csv");
    std::string lineText;
   // file.open("../../GameData/Scores/Scores.csv", std::ios::in | std::ios::app);
    while (getline(file, lineText))
    {   
        score = std::stoi(lineText);
        if (BiggestScore < score) 
        {
            BiggestScore = score;
        }
        std::cout << BiggestScore<<std::endl;
        
    }
   
    file.close();
    return BiggestScore;
}