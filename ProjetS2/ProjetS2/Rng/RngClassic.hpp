#pragma once

#include "IRng.hpp"
#include <random>
#include <time.h>
#include <chrono>

class RngClassic : public IRng
{
public:
    RngClassic();
    ~RngClassic();
    float getRandom();
};