#include "OscController.h"

void OscController::setup(int nextPort) {
    port = nextPort;
    ofLogNotice("OscController") << "OSC scaffold configured for UDP port " << port;
}

void OscController::update(ParameterList& parameters) {
    (void)parameters;
}

int OscController::getPort() const {
    return port;
}
