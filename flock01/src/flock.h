#ifndef FLOCK_H
#define FLOCK_H

#include "ofMain.h"
#include "boid.h"

class Flock {
public:
    vector<Boid *> boids;

    Flock() {}

    void update() {
        for (unsigned int i = 0; i < boids.size(); i++) {
            boids.at(i)->update(boids);
        }
    }

    void draw() {
        for (unsigned int i = 0; i < boids.size(); i++) {
            boids.at(i)->draw();
        }
    }

    void addBoid() {
        boids.push_back(new Boid());
    }

    void removeAll() {
        for (unsigned int i = 0; i < boids.size(); i++) {
            boids.erase(boids.begin() + i);
        }
    }
};
#endif // FLOCK_H
