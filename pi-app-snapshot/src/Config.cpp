#include "Config.h"

bool Config::load(const std::string& path) {
    const std::string resolvedPath = ofToDataPath(path);
    if (!ofFile::doesFileExist(resolvedPath)) {
        ofLogWarning("Config") << "Missing config at " << resolvedPath << "; using defaults";
        return false;
    }

    try {
        const ofJson json = ofLoadJson(path);
        if (json.contains("osc")) {
            settings.osc.port = json["osc"].value("port", settings.osc.port);
        }
        if (json.contains("camera")) {
            const ofJson& camera = json["camera"];
            settings.camera.deviceIndex = camera.value("deviceIndex", settings.camera.deviceIndex);
            settings.camera.width = camera.value("width", settings.camera.width);
            settings.camera.height = camera.value("height", settings.camera.height);
            settings.camera.fps = camera.value("fps", settings.camera.fps);
            settings.camera.forceFallback = camera.value("forceFallback", settings.camera.forceFallback);
            settings.camera.pipelineMode = camera.value("pipelineMode", settings.camera.pipelineMode);
        }
        if (json.contains("effects")) {
            const ofJson& effects = json["effects"];
            settings.effects.maxZoom = effects.value("maxZoom", settings.effects.maxZoom);
            settings.effects.maxBlur = effects.value("maxBlur", settings.effects.maxBlur);
            settings.effects.maxSlurpSeconds = effects.value("maxSlurpSeconds", settings.effects.maxSlurpSeconds);
        }
        if (json.contains("performance")) {
            const ofJson& performance = json["performance"];
            settings.performance.useShaders = performance.value("useShaders", settings.performance.useShaders);
            settings.performance.showDebugOverlay = performance.value("showDebugOverlay", settings.performance.showDebugOverlay);
        }
    } catch (const std::exception& error) {
        ofLogError("Config") << "Could not parse " << resolvedPath << ": " << error.what();
        return false;
    }

    return true;
}

const AppConfig& Config::get() const {
    return settings;
}
