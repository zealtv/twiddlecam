#pragma once

#include "ofMain.h"
#include "ofGstUtils.h"
#include "Config.h"
#include "Parameter.h"

class VideoProcessor {
public:
    void setup(const AppConfig& config);
    void update();
    void draw(const ParameterList& parameters) const;

private:
    void allocateFrameBuffer(int width, int height);
    ofRectangle getDrawBounds() const;

    CameraConfig camera;
    ofGstVideoUtils video;
    ofTexture cameraTexture;
    ofFbo frameBuffer;
    int activeWidth = 0;
    int activeHeight = 0;
    bool cameraReady = false;
    bool hasFrame = false;
};
