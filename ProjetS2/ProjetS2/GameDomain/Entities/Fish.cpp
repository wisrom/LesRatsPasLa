#include "Fish.hpp"

Fish::Fish()
{
    std::vector<CaptureStep> tmpCaptureSteps;
    this->captureSteps = tmpCaptureSteps;
    this->length_m = 0;
    this->weight_kg = 0;
}

Fish::Fish(std::vector<CaptureStep> captureSteps, float length_m, float weight_kg)
{
    std::vector<CaptureStep> tmpCaptureSteps;
    for (CaptureStep captureStep : captureSteps)
    {
        tmpCaptureSteps.push_back(captureStep);
    }
    this->captureSteps = tmpCaptureSteps;
    this->length_m = length_m;
    this->weight_kg = weight_kg;
}

Fish::~Fish()
{

}