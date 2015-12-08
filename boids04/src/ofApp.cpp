#include "ofApp.h"

void ofApp::setup() {
    ofBackground(0);

}

void ofApp::update() {

    if (target != NULL && !target->dead()) {
      target->update();
    }

    unsigned int i;

    for (i = 0; i < boids.size(); ++i) {
        Boid* b = boids.at(i);

        if (target != NULL) {
            b->seek(target->getPosition());

            // check collision
            float dist = b->getPosition().distance(target->getPosition());
            if (dist < target->getSize()) {
                target->hit();

                if (target->dead()) {
                    delete target;
                    target = NULL;
                }
            }
        }

        b->update();
    }
}

void ofApp::draw() {


    if (target != NULL && !target->dead()) {
        target->draw();
    }

    unsigned int i;

    for (i = 0; i < boids.size(); ++i) {
        boids.at(i)->draw();
    }

}

void ofApp::keyPressed(int key)  { }
void ofApp::keyReleased(int key) { }

void ofApp::mouseMoved(int x, int y) {

    if (target != NULL) {
        target->setTarget(x, y);
    }
}

void ofApp::mouseDragged(int x, int y, int button)  {  }

void ofApp::mousePressed(int x, int y, int button)  {

    if (target == NULL) {
        target = new Target(ofRandom(40, 200), ofRandom(0.03, 1.3));
        target->setPosition(x, y);
        target->setTarget(x, y);

        // check if we have boids
        unsigned int i;

        for (i = 0; i < maxEntities; ++i) {
            Boid* b = new Boid(ofGetWidth() / 2, ofGetHeight() / 2);
            boids.push_back(b);
        }
    }
}

void ofApp::mouseReleased(int x, int y, int button) {  }

void ofApp::mouseEntered(int x, int y)      { }
void ofApp::mouseExited(int x, int y)       { }
void ofApp::windowResized(int w, int h)     { }
void ofApp::gotMessage(ofMessage msg)       { }
void ofApp::dragEvent(ofDragInfo dragInfo)  { }

