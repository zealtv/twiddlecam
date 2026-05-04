#pragma once

#include "ofMain.h"
#include "Config.h"
#include "OscController.h"
#include "Parameter.h"
#include "VideoProcessor.h"

class ofApp : public ofBaseApp {
public:
    void setup() override;
    void update() override;
    void draw() override;
    void keyPressed(int key) override;

private:
    Config config;
    OscController osc;
    ParameterList parameters;
    VideoProcessor processor;
};
