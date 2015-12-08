#pragma once

#include "ofMain.h"
#include "target.h"
#include "boid.h"

class ofApp : public ofBaseApp {

  vector<Target*> targets;

   vector<Boid*>   boids;
   int boidsPerTarget = 20;
   int maxBoids = 1000;

  const float updateMillis = 1000;
  float elapsedTime;

  void createEntities();
  void cleanTargets();

public:
  void setup();
  void update();
  void draw();

  void keyPressed(int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y );
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void mouseEntered(int x, int y);
  void mouseExited(int x, int y);
  void windowResized(int w, int h);
  void dragEvent(ofDragInfo dragInfo);
  void gotMessage(ofMessage msg);

};

