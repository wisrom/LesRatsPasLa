#pragma once

class Environment
{
public:
    Environment();
    ~Environment();

    void generateRandomEnvironment();
private:
    float temperature_C;
    float windSpeed_kmPerHour;
    // date et heure
};