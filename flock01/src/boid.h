#ifndef BOID_H
#define BOID_H

#include "ofMain.h"

class Boid {

public:
    ofPoint loc;
    ofPoint vel;
    ofPoint acc;
    float r;
    float maxforce;
    float maxspeed;

    Boid() {
        loc.x = ofRandomWidth();
        loc.y = ofRandomHeight();

        vel.set(ofRandom(-2.0, 2.0), ofRandom(-2.0, 2.0), 0.0);
        acc.set(ofRandom(-2.0, 2.0), ofRandom(-2.0, 2.0), 0.0);
        r = 3.0;
        maxforce = 0.1;
        maxspeed = 4;
    }

    void update(vector<Boid*> boids) {
        flock(boids);

        // update velocity
        vel += acc;
        // limit speed
        vel.x = ofClamp(vel.x, -maxspeed, maxspeed);
        vel.y = ofClamp(vel.y, -maxspeed, maxspeed);
        loc += vel;
        // reset acceleration
        acc.set(0.0);

        if (loc.x < -r) loc.x = ofGetWidth() + r;
        if (loc.y < -r) loc.y = ofGetHeight() + r;
        if (loc.x > ofGetWidth() + r) loc.x = -r;
        if (loc.y > ofGetHeight() + r) loc.y = -r;
    }

    void seek(ofPoint target) {
        acc += steer(target, false);
    }

    void arrive(ofPoint target) {
        acc += steer(target, true);
    }

    ofPoint steer(ofPoint target, bool slowdown) {
        ofPoint steer;
        // a vector pointing from the location to the target
        ofPoint desired = target - loc;
        // distance from target = magnitued of the vector
        float d = ofDist(target.x, target.y, loc.x, loc.y);

        if (d > 0) {
            // normalize desired
            desired /= d;

            if ((slowdown) && (d < 100.0f)) {
                // damping
                desired *= maxspeed * (d/100.0f);
            } else {
                desired *= maxspeed;
            }

            steer = desired - vel;
            // limit
            steer.x = ofClamp(steer.x, -maxforce, maxforce);
            steer.y = ofClamp(steer.y, -maxforce, maxforce);
        }

        return steer;
    }

    void draw() {
        float angle = (float) atan2(-vel.y, vel.x);
        float theta = -1.0 * angle;
        float heading2D = ofRadToDeg(theta) + 90;

        ofEnableAlphaBlending();
        ofSetColor(255, 255, 255);
        ofFill();
        ofPushMatrix();
        ofTranslate(loc.x, loc.y);
        ofRotateZ(heading2D);
        ofBeginShape();
        ofVertex(0, -r);
        ofVertex(-r/2, r);
        ofVertex(r/2, r);
        ofEndShape(true);
        ofPopMatrix();
        ofDisableAlphaBlending();
    }

    void flock(vector<Boid*> boids) {
        ofPoint sep = separate(boids);
        ofPoint ali = align(boids);
        ofPoint coh = cohesion(boids);

        sep *= 1.5;
        ali *= 1.0;
        coh *= 1.0;

        acc += sep + ali + coh;
    }

    ofPoint separate(vector<Boid*> boids) {
        float desiredseparation = 25.0f;
        ofPoint steer;
        int count = 0;

        // for every boid in the system, check if it's too close
        for (unsigned int i = 0; i < boids.size(); i++) {
            Boid* other = boids[i];
            float d = ofDist(loc.x, loc.y, other->loc.x, other->loc.y);

            // if the distance is greater than 0 and less than an arbitrary amount
            if ((d > 0) && (d < desiredseparation)) {
                // calculate vector pointing away from neighbor
                ofPoint diff = loc - other->loc;
                diff /= d; // normalize
                diff /= d; // weight by distance
                steer += diff;
                count++;   // keep track of how many
            }

        }

        // avergae - divide by how many
        if (count > 0) {
            steer /= (float) count;
        }

        // as long as the vector is greater than 0
        float mag = sqrt(steer.x*steer.x + steer.y*steer.y);
        if (mag > 0) {
            // steering = desired - velocity
            steer /= mag;
            steer *= maxspeed;
            steer -= vel;
            steer.x = ofClamp(steer.x, -maxforce, maxforce);
            steer.y = ofClamp(steer.y, -maxforce, maxforce);
        }
        return steer;
    }

    ofPoint align(vector<Boid*> boids) {
        float neighbordist = 50.0;
        ofPoint steer;
        int count = 0;
        for (unsigned int i = 0; i < boids.size(); i++) {
            Boid* other = boids[i];
            float d = ofDist(loc.x, loc.y, other->loc.x, other->loc.y);
            if ((d > 0) && (d < neighbordist)) {
                steer += other->vel;
                count++;
            }
        }

        if (count > 0) {
            steer /= (float) count;
        }

        float mag = sqrt(steer.x*steer.x + steer.y*steer.y);
        if (mag > 0) {
            // steering = desired - velocity
            steer /= mag;
            steer *= maxspeed;
            steer -= vel;
            steer.x = ofClamp(steer.x, -maxforce, maxforce);
            steer.y = ofClamp(steer.y, -maxforce, maxforce);
        }

        return steer;
    }

    ofPoint cohesion(vector<Boid*> boids) {
        float neighbordist = 50.0;
        // start with empty vector to accumulate all locations
        ofPoint sum;
        int count = 0;
        for (unsigned int i = 0; i < boids.size(); i++) {
            Boid* other = boids[i];
            float d = ofDist(loc.x, loc.y, other->loc.x, other->loc.y);
            if ((d > 0) && (d < neighbordist)) {
                // add location
                sum += other->loc;
                count++;
            }
        }

        if (count > 0) {
            sum /= (float) count;
            // steer towards the location
            return steer(sum, false);
        }

        return sum;
    }
};



#endif // BOID_H
