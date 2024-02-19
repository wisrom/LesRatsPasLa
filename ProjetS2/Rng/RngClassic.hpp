#pragma once

#include "IRng.hpp"

class RngClassic : public IRng
{
public:
    RngClassic();
    ~RngClassic();
    float getRandom();
};