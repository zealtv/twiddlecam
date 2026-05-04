#pragma once

#include "ofMain.h"

struct Parameter {
    std::string address;
    float value = 0.0f;
    float target = 0.0f;
    float defaultValue = 0.0f;
    float minValue = 0.0f;
    float maxValue = 1.0f;
    float slurpSeconds = 0.0f;
    bool wraps = false;

    void setTarget(float nextTarget);
    void update(float dt);
    void reset();
};

using ParameterList = std::vector<Parameter>;

ParameterList makeDefaultParameters();
