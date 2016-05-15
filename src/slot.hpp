//
//  slot.hpp
//  sys06_simulator
//
//  Created by Ovis aries on 2016/05/14.
//
//

#ifndef slot_hpp
#define slot_hpp

#include "ofMain.h"
#include "ofxBt.h"

class slot{
public:
	
	void setup(ofxBt::World *world, ofVec3f pos);
	void draw(bool wire);
	
	void setShape(float rad, float angle, ofVec3f pos);
	
	vector<ofxBt::RigidBody> boxes;
	ofMesh mesh;
	
	ofVec3f axis;
	
	int lastId;
	bool isCatch;
};

#endif /* slot_hpp */
