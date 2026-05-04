#include "ofMain.h"
#include "ofApp.h"

int main() {
    ofGLFWWindowSettings settings;
    settings.setSize(1280, 720);
    settings.windowMode = OF_WINDOW;
    settings.resizable = true;
    settings.title = "VJCamera";

    auto window = ofCreateWindow(settings);
    ofRunApp(window, make_shared<ofApp>());
    ofRunMainLoop();
}
