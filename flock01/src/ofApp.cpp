#include "ofApp.h"

void ofApp::setup() {

    ofSetBackgroundColor(0.3, 0.3, 0.3, 1.0);

    for (unsigned int i = 0; i < 300; i++) {
        flock.addBoid();
    }
}

void ofApp::update() {
    flock.update();
}

void ofApp::draw() {
    flock.draw();
}

void ofApp::keyPressed(int key) { }
void ofApp::keyReleased(int key) { }
void ofApp::mouseMoved(int x, int y) { }
void ofApp::mouseDragged(int x, int y, int button) { }
void ofApp::mousePressed(int x, int y, int button) { }
void ofApp::mouseReleased(int x, int y, int button) { }
void ofApp::mouseEntered(int x, int y) { }
void ofApp::mouseExited(int x, int y) { }
void ofApp::windowResized(int w, int h) { }
void ofApp::gotMessage(ofMessage msg) { }
void ofApp::dragEvent(ofDragInfo dragInfo) { }
