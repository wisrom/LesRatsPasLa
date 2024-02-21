#pragma once

#include "IRng.hpp"

class RngMuons : public IRng
{
public:
    RngMuons();
    ~RngMuons();
    float getRandom();
};