#pragma once

#include "ofMain.h"
#include "ofxBt.h"

#include "slot.hpp"

class ofApp : public ofBaseApp{

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
	
	ofxBt::World world;
	ofxBt::RigidBody ball;
	ofxBt::RigidBody floor;
	
	ofEasyCam camera;
	
	void hit(ofxBt::World::CollisionEventArg & arg);
	
	ofxBt::RigidBody balls[49];
	slot slots[49];
	
	ofSpherePrimitive spMesh;
	
	int bangSW;
};
