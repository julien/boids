#include "ofApp.h"

void ofApp::createEntities() {
    Target* target = new Target(ofRandom(40, 200), ofRandom(0.03, 1.3));
    target->setPosition(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
    target->setTarget(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
    targets.push_back(target);

    unsigned int i;
    for (i = 0; i < boidsPerTarget; i++) {
        Boid* b = new Boid(ofGetWidth() / 2, ofGetHeight() / 2);
        b->setTarget(target);
        boids.push_back(b);
    }
}

void ofApp::cleanTargets() {
    for (unsigned int i = 0; i < targets.size(); i++) {
        Target* t = targets.at(i);
        if (t->dead()) {

            targets.erase(targets.begin() + i);
            if (t != NULL) delete t;
        }
    }
}

void ofApp::setup() {
    ofBackground(0);

    elapsedTime = ofGetElapsedTimeMillis();
    createEntities();
}

void ofApp::update() {

    // update time
    if (ofGetElapsedTimeMillis() - elapsedTime >= updateMillis) {
        elapsedTime = ofGetElapsedTimeMillis();

        int totalBoids = boids.size();
        if (totalBoids < maxBoids + boidsPerTarget) {
            createEntities();
        }
    }

    unsigned int i;
    for (i = 0; i  < targets.size(); i++) {
      targets.at(i)->update();
    }

    for (i = 0; i < boids.size(); i++) {
        Boid* b = boids.at(i);
        Target *t = b->getTarget();

        if (b != NULL && b->alive()) {

            if (t != NULL) {
                b->seek(t->getPosition());

                // check collision
                float dist = b->getPosition().distance(t->getPosition());
                if (dist < t->getSize()) {
                    t->hit();

                    if (t->dead()) {
                        cleanTargets();

                        boids.erase(boids.begin() + i);
                        if (b != NULL) delete b;

                        continue;
                    }
                }
            }

            if (!b->alive()) {
              boids.erase(boids.begin() + i);
              if (b != NULL)  delete b;
            }

            b->update();
        }
    }
}

void ofApp::draw() {
    unsigned int i;
    for (i = 0; i < targets.size(); i++) {
        targets.at(i)->draw();
    }

    for (i = 0; i < boids.size(); i++) {
        boids.at(i)->draw();
    }

}

void ofApp::keyPressed(int key)  { }
void ofApp::keyReleased(int key) { }
void ofApp::mouseMoved(int x, int y) { }
void ofApp::mouseDragged(int x, int y, int button) { }
void ofApp::mousePressed(int x, int y, int button) { }
void ofApp::mouseReleased(int x, int y, int button) {  }
void ofApp::mouseEntered(int x, int y)      { }
void ofApp::mouseExited(int x, int y)       { }
void ofApp::windowResized(int w, int h)     { }
void ofApp::gotMessage(ofMessage msg)       { }
void ofApp::dragEvent(ofDragInfo dragInfo)  { }
