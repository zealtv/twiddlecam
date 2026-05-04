#include "VideoProcessor.h"

namespace {
std::string buildCameraPipeline(const CameraConfig& camera) {
    if (camera.pipelineMode == "mjpeg_hd") {
        return "v4l2src device=/dev/video0 io-mode=2 ! "
            "image/jpeg,width=" + ofToString(camera.width) +
            ",height=" + ofToString(camera.height) +
            ",framerate=" + ofToString(camera.fps) + "/1 ! "
            "jpegdec ! videoconvert ! videoscale";
    }

    return "v4l2src device=/dev/video0 io-mode=2 do-timestamp=true ! "
        "video/x-raw,format=YUY2,width=" + ofToString(camera.width) +
        ",height=" + ofToString(camera.height) +
        ",framerate=" + ofToString(camera.fps) + "/1 ! "
        "videoconvert ! videoscale";
}
}

void VideoProcessor::setup(const AppConfig& config) {
    camera = config.camera;
    activeWidth = camera.width;
    activeHeight = camera.height;

    if (camera.forceFallback) {
        ofLogWarning("VideoProcessor") << "Camera fallback forced by config; running with black frame";
        allocateFrameBuffer(activeWidth, activeHeight);
        return;
    }

    const std::string pipeline = buildCameraPipeline(camera);
    ofLogNotice("VideoProcessor") << "Opening camera mode '" << camera.pipelineMode << "': " << pipeline;
    cameraReady = video.setPipeline(pipeline, OF_PIXELS_RGB, false, camera.width, camera.height);
    if (cameraReady) {
        cameraReady = video.startPipeline();
    }

    if (!cameraReady) {
        ofLogError("VideoProcessor") << "Could not open /dev/video0 mode '" << camera.pipelineMode
                                      << "' at " << camera.width << "x" << camera.height
                                      << "@" << camera.fps << "; running with black fallback frame";
        allocateFrameBuffer(activeWidth, activeHeight);
        return;
    }

    cameraTexture.allocate(activeWidth, activeHeight, GL_RGB);
    allocateFrameBuffer(activeWidth, activeHeight);
    ofLogNotice("VideoProcessor") << "Camera opened: /dev/video0 "
                                  << activeWidth << "x" << activeHeight
                                  << "@" << camera.fps << " " << camera.pipelineMode;
}

void VideoProcessor::update() {
    if (!cameraReady) {
        hasFrame = false;
        return;
    }

    video.update();
    if (!video.isFrameNew()) {
        return;
    }

    const ofPixels& pixels = video.getPixels();
    if (!pixels.isAllocated()) {
        return;
    }

    hasFrame = true;
    cameraTexture.loadData(pixels);

    frameBuffer.begin();
    ofClear(0, 0, 0, 255);
    cameraTexture.draw(0, 0, activeWidth, activeHeight);
    frameBuffer.end();
}

void VideoProcessor::draw(const ParameterList& parameters) const {
    ofBackground(0);

    if (cameraReady && hasFrame && frameBuffer.isAllocated()) {
        const ofRectangle bounds = getDrawBounds();
        ofSetColor(255);
        frameBuffer.draw(bounds);
    }

    ofSetColor(230);
    ofDrawBitmapString("VJCamera", 16, 24);
    ofSetColor(cameraReady ? ofColor(120, 220, 140) : ofColor(255, 90, 80));
    const std::string status = cameraReady
        ? "camera /dev/video0 " + camera.pipelineMode + " " + ofToString(activeWidth) + "x" + ofToString(activeHeight)
        : "camera fallback black frame";
    ofDrawBitmapString(status, 16, 42);

    int y = 64;
    ofSetColor(180);
    for (const auto& parameter : parameters) {
        ofDrawBitmapString(parameter.address + " = " + ofToString(parameter.value, 2), 16, y);
        y += 14;
        if (y > ofGetHeight() - 16) {
            break;
        }
    }
}

void VideoProcessor::allocateFrameBuffer(int width, int height) {
    frameBuffer.allocate(width, height, GL_RGB);
    frameBuffer.begin();
    ofClear(0, 0, 0, 255);
    frameBuffer.end();
}

ofRectangle VideoProcessor::getDrawBounds() const {
    if (activeWidth <= 0 || activeHeight <= 0) {
        return ofRectangle(0, 0, ofGetWidth(), ofGetHeight());
    }

    const float scale = std::min(ofGetWidth() / static_cast<float>(activeWidth),
                                 ofGetHeight() / static_cast<float>(activeHeight));
    const float width = activeWidth * scale;
    const float height = activeHeight * scale;
    return ofRectangle((ofGetWidth() - width) * 0.5f,
                       (ofGetHeight() - height) * 0.5f,
                       width,
                       height);
}
