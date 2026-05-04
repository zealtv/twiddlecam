#include "Parameter.h"

void Parameter::setTarget(float nextTarget) {
    target = ofClamp(nextTarget, minValue, maxValue);
}

void Parameter::update(float dt) {
    if (slurpSeconds <= 0.0f || dt <= 0.0f) {
        value = target;
        return;
    }

    const float amount = 1.0f - expf(-dt / slurpSeconds);
    value = ofLerp(value, target, amount);
}

void Parameter::reset() {
    target = defaultValue;
    value = defaultValue;
}

ParameterList makeDefaultParameters() {
    return {
        {"/brightness", 0.0f, 0.0f, 0.0f, -1.0f, 1.0f},
        {"/contrast", 1.0f, 1.0f, 1.0f, 0.0f, 4.0f},
        {"/saturation", 1.0f, 1.0f, 1.0f, 0.0f, 4.0f},
        {"/hue", 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, true},
        {"/invert", 0.0f, 0.0f, 0.0f, 0.0f, 1.0f},
        {"/x", 0.0f, 0.0f, 0.0f, -1.0f, 1.0f},
        {"/y", 0.0f, 0.0f, 0.0f, -1.0f, 1.0f},
        {"/zoom", 1.0f, 1.0f, 1.0f, 0.1f, 4.0f},
        {"/rotate", 0.0f, 0.0f, 0.0f, -180.0f, 180.0f},
        {"/blur", 0.0f, 0.0f, 0.0f, 0.0f, 12.0f},
        {"/slurp", 0.0f, 0.0f, 0.0f, 0.0f, 2.0f},
        {"/color_hue", 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, true},
        {"/color_saturation", 1.0f, 1.0f, 1.0f, 0.0f, 2.0f},
        {"/color_luminance", 0.5f, 0.5f, 0.5f, 0.0f, 1.0f},
        {"/color_mix_mode", 0.0f, 0.0f, 0.0f, 0.0f, 3.0f},
        {"/rotation_lfo_speed", 0.0f, 0.0f, 0.0f, 0.0f, 10.0f}
    };
}
