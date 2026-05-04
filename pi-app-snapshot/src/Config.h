#pragma once

#include "ofMain.h"

struct OscConfig {
    int port = 1111;
};

struct CameraConfig {
    int deviceIndex = 0;
    int width = 640;
    int height = 480;
    int fps = 30;
    bool forceFallback = false;
    std::string pipelineMode = "yuy2_low_latency";
};

struct EffectConfig {
    float maxZoom = 4.0f;
    float maxBlur = 12.0f;
    float maxSlurpSeconds = 2.0f;
};

struct PerformanceConfig {
    bool useShaders = true;
    bool showDebugOverlay = true;
};

struct AppConfig {
    OscConfig osc;
    CameraConfig camera;
    EffectConfig effects;
    PerformanceConfig performance;
};

class Config {
public:
    bool load(const std::string& path);
    const AppConfig& get() const;

private:
    AppConfig settings;
};
