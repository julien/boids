#ifndef TARGET_H
#define TARGET_H

#include "ofMain.h"

class Target {

    // ofPoint origin;

    ofPoint position;
    ofPoint target;

    ofPoint range;
    ofPoint angle;
    ofPoint speed;

    bool alive;
    float life;
    bool hurt;

    float maxsize;
    float growth;
    float size;

public:

    Target(int maxsize,
           float growth = 1): maxsize(maxsize),
                              growth(growth),
                              alive(true),
                              size(0) {
        life = ofMap(size, 0, maxsize, 0, 100);
    }

    void update() {
        // if we haven't reach max size grow
        if (size < maxsize && !hurt) {
            size += growth;
        }

        if (target.x != position.x && target.y != position.y) {
            // if we have a target gow there
            float x = target.x - position.x;
            float y = target.y - position.y;

            position.x += x * (0.03);
            position.y += y * (0.03);
        }

        if (!hurt && !dead()) {
            life = ofMap(size, 0, maxsize, 0, 100, true);
        }

        size = ofMap(life, 0, 100, 20, maxsize, true);
    }

    void draw() {
        ofSetColor(255, 0, 0, 120);
        ofDrawCircle(position, size);
    }

    void setPosition(float x, float y) {
      position.set(x, y);
    }

    ofVec2f getPosition() {
      return ofVec2f(position.x, position.y);
    }

    float getSize() { return size; }

    void setTarget(float x, float y) {
      target.set(x, y);
    }

    ofVec2f getTarget() {
      return ofVec2f(target.x, target.y);
    }

    bool dead() {
        return !alive;
    }

    void hit() {
        if (!hurt) hurt = true;
        life -= ofRandom(1);

        if (life <= 0) {
          life = 0;
          alive = false;
          hurt = false;
        }
    }
};


#endif // TARGET_H

