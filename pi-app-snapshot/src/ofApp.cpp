#include "ofApp.h"

void ofApp::setup() {
    ofSetWindowTitle("VJCamera");
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofBackground(0);

    config.load("config.json");
    parameters = makeDefaultParameters();
    osc.setup(config.get().osc.port);
    processor.setup(config.get());
}

void ofApp::update() {
    const float dt = ofGetLastFrameTime();
    osc.update(parameters);
    for (auto& parameter : parameters) {
        parameter.update(dt);
    }
    processor.update();
}

void ofApp::draw() {
    processor.draw(parameters);
}

void ofApp::keyPressed(int key) {
    if (key == 'f') {
        ofToggleFullscreen();
    }
    if (key == 'r') {
        for (auto& parameter : parameters) {
            parameter.reset();
        }
    }
}
