//
//  slot.cpp
//  sys06_simulator
//
//  Created by Ovis aries on 2016/05/14.
//
//

#include "slot.hpp"

void slot::setup(ofxBt::World *world, ofVec3f pos)
{
	float angle_res = 30;
	ofVec3f box_scale = ofVec3f(30,50,5);
	axis = pos;
	
	for (int i = 0;i < 360;i += angle_res)
	{
		ofNode nd;
		nd.move(pos.x, pos.y, pos.z);
		nd.pan(-i + 90);
		nd.dolly(50);
		nd.tilt(15);
		
		ofxBt::RigidBody rd = world->addBox(box_scale, ofVec3f(0,0,0));
		
		rd.setMass(0);
		rd.setStatic(true);
		rd.setTransform(nd.getGlobalTransformMatrix());
		rd.setRestitution(0.75);
	
		boxes.push_back(rd);
	}
	
	ofBoxPrimitive box = ofBoxPrimitive(box_scale.x, box_scale.y, box_scale.z);
	mesh = box.getMesh();
	isCatch = false;
}

void slot::setShape(float rad, float angle, ofVec3f pos)
{
	axis = pos;
	float angle_res = 360 / boxes.size();
	for (int i = 0;i < 360;i += angle_res)
	{
		ofNode nd;
		nd.move(axis.x, axis.y, axis.z);
		nd.pan(-i + 90);
		nd.dolly(rad);
		nd.tilt(angle);
		
		boxes[i / angle_res].setTransform(nd.getGlobalTransformMatrix());
	}
}

void slot::draw(bool wire)
{
	for (int i = 0;i < boxes.size();i++)
	{
		ofPushMatrix();
		ofMultMatrix(boxes[i].getTransform());
		ofSetColor(50);
		if (isCatch) ofSetColor(150, 50, 50);
		mesh.drawFaces();
		ofSetColor(255);
		if (wire) mesh.drawWireframe();
		ofPopMatrix();
	}
}