#ifndef TARGET_H
#define TARGET_H

#include "ofMain.h"

class Target {

    ofPoint origin;
    ofPoint location;
    ofPoint range;
    ofPoint angle;
    ofPoint speed;

    bool alive;
    float life;

public:
    float size;

    Target(float x, float y, int rangeMin, int rangeMax) {
        alive = true;
        life = 100;

        origin.set(x, y);
        location.set(x, y);
        angle.set(0, 0);
        range.set(ofRandom(rangeMin, rangeMax), ofRandom(rangeMin, rangeMax));
        speed.set(ofRandom(0.02), ofRandom(0.04));
    }

    void update() {
        float x = origin.x + cos(angle.x) * range.x;
        float y = origin.y + sin(angle.y) * range.y;
        angle.x += speed.x;
        angle.y += speed.y;
        location.set(x, y);
        size = ofMap(life, 0, 100, 1, 80, true);
    }

    void draw() {
        ofSetColor(255, 0, 0, 120);
        ofDrawCircle(location, size);
    }

    ofVec2f position() {
        return ofVec2f(location.x, location.y);
    }

    bool dead() {
        return !alive;
    }

    void hit() {
        life -= ofRandom(1, 1.2);

        if (life <= 0) {
            life = 0;
            alive = false;
        }
    }

    void reset() {

        float x = ofRandom(ofGetWidth());
        float y = ofRandom(ofGetHeight());
        origin.set(x, y);
        location.set(x, y);
        angle.set(0, 0);
        range.set(ofRandom(range.x), ofRandom(range.y));
        speed.set(ofRandom(0.02), ofRandom(0.04));

        life = 100;
        alive = true;
    }
};


#endif // TARGET_H
