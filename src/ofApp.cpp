#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	world.setup(ofVec3f(0, -7808, 0));
	
	floor = world.addPlane(ofVec3f(0,1,0), ofVec3f(0,0,0));
	floor.setRestitution(0.8);

//	ball = world.addSphere(50, ofVec3f(0,150,0));
//	ball.setMass(0.1);
//	ball.setRestitution(0.8);

	ofAddListener(world.collisionEvent, this, &ofApp::hit);

	
	for (int i = 0;i < 49;i++)
	{
		ofVec3f axis = ofVec3f((i % 7) * 150 - 450, 50,
							   (i / 7) * 150 - 450);
		
		balls[i] = world.addSphere(60, ofVec3f(0, 50, 0) + axis);
		balls[i].setMass(0.1);
		balls[i].setRestitution(0.8);
		 
		slots[i].setup(&world, axis);
	}
	
	spMesh.set(60, 10);
	camera.setDistance(1000);
	camera.setPosition(1000, 1000, 1000);
	camera.lookAt(ofVec3f(0,0,0));
	
	ofxBt::RigidBody wall;
	
	for (int i = 0;i < 4;i++)
	{
		walls[i] = world.addBox(ofVec3f(2000, 500, 10),
								ofVec3f((i < 2 ? 550 : 0) * (i % 2 == 0 ? -1.0 : 1.0),
										150,
										(i > 1 ? 550 : 0) * (i % 2 == 0 ? -1.0 : 1.0)),
								ofVec3f((i < 2 ? 90 : 0), 0, 0));
		walls[i].setMass(0);
		walls[i].setStatic(true);
	}
	
	gui.setup();
	gui.add(slot_rad.set("slot_rad", 50.0, 0.0, 100.0));
	gui.add(slot_angle.set("slot_angle", 15.0, 0.0, 90.0));
	gui.add(slot_margine_w.set("slot_margine_w", 150, 10, 300));
	gui.add(slot_margine_h.set("slot_margine_h", 150, 10, 300));
	gui.add(tenban_height.set("tenban_height", 70, 0, 200));
	gui.add(drawWire.set("wire", false));
	
	tenban_height.addListener(this, &ofApp::renewSlot);
	slot_rad.addListener(this, &ofApp::renewSlot);
	slot_angle.addListener(this, &ofApp::renewSlot);
	slot_margine_w.addListener(this, &ofApp::renewSlot);
	slot_margine_h.addListener(this, &ofApp::renewSlot);
	float d = 0.0;
	renewSlot(d);
}

//--------------------------------------------------------------
void ofApp::update()
{
	world.update();
	
	if (ofGetFrameNum() % 15 == 0)
	{
		bool currentCatch[49];
		for (int i = 0;i < 49;i++) currentCatch[i] = slots[i].isCatch;
		
		for (int i = 0;i < 49;i++)
		{
			bool ext_t = false, ext_r = false, ext_l = false, ext_b = false;
			
			if (i % 7 != 0) ext_l = true;
			if (i % 6 != 0) ext_r = true;
			if (i / 7 != 0) ext_t = true;
			if (i / 7 != 6) ext_b = true;
			int ext_counter = 0;
			int ext_flag = 0;
			
			if (ext_t && ext_l)
			{
				ext_counter++;
				ext_flag += currentCatch[i - 8] ? 1 : 0;
			}
			if (ext_t)
			{
				ext_counter++;
				ext_flag += currentCatch[i - 7] ? 1 : 0;
			}
			if (ext_t && ext_r)
			{
				ext_counter++;
				ext_flag += currentCatch[i - 6] ? 1 : 0;
			}
			if (ext_l)
			{
				ext_counter++;
				ext_flag += currentCatch[i - 1] ? 1 : 0;
			}
			if (ext_r)
			{
				ext_counter++;
				ext_flag += currentCatch[i + 1] ? 1 : 0;
			}
			if (ext_b && ext_l)
			{
				ext_counter++;
				ext_flag += currentCatch[i + 6] ? 1 : 0;
			}
			if (ext_b && ext_r)
			{
				ext_counter++;
				ext_flag += currentCatch[i + 8] ? 1 : 0;
			}
			if (ext_b)
			{
				ext_counter++;
				ext_flag += currentCatch[i + 7] ? 1 : 0;
			}
			
			if ((ext_counter - ext_flag) < 3)
			{
				if (slots[i].isCatch)
				{
					int idx = ofClamp(slots[i].lastId, 0, 49);
					balls[idx].applyForce(ofVec3f(ofRandomf() * 500,150 * 100,
												  ofRandomf() * 500));
				}
			}
		}
	}

}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackground(0, 0, 0);
	camera.begin();
	ofEnableDepthTest();
	for (int i = 0;i < 49;i++)
	{
		ofPushMatrix();
		ofMultMatrix(balls[i].getTransform());
		ofFloatColor c;
		c.setHsb(1.0 / 49.0 * i / 4.0 + 0.4, 0.8, 0.7);
		ofSetColor(c);
		spMesh.drawFaces();
		ofSetColor(255);
		if (drawWire) spMesh.drawWireframe();
		ofPopMatrix();
		
		slots[i].draw(drawWire);
	}
	if (drawWire) world.draw();
	
	for (int i = 0;i < 49;i++)
	{
		ofVec3f slPos = slots[i].axis;
		slPos.y = 0;
		slots[i].isCatch = false;
		for (int j = 0;j < 49;j++)
		{
			ofVec3f blPos = balls[j].getPosition();
			blPos.y = 0;
			if (slPos.squareDistance(blPos) < 100)
			{
				if (abs(slots[i].axis.y - balls[j].getPosition().y) < 100)
				{
					slots[i].lastId = j;
					slots[i].isCatch = true;
				}
			}
		}
	}
	
	ofDisableDepthTest();
	camera.end();
	
	if ((bangSW > 0) && (ofGetFrameNum() % 7 == 0))
	{
		if (slots[bangSW - 1].isCatch)
		{
			int idx = ofClamp(slots[bangSW - 1].lastId, 0, 49);
			balls[idx].applyForce(ofVec3f(ofRandomf() * 500,150 * 100,
											 ofRandomf() * 500));
		}
		bangSW++;
		if (bangSW == 50) bangSW = 0;
	}
	gui.draw();
}

void ofApp::renewSlot(float & val)
{
	for (int i = 0;i < 49;i++)
	{
		ofVec3f axis = ofVec3f((i % 7) * slot_margine_w - slot_margine_w * 3, 50,
							   (i / 7) * slot_margine_h - slot_margine_h * 3);
		
		slots[i].setShape(slot_rad, slot_angle, axis);
	}
	
	for (int i = 0;i < 4;i++)
	{
		ofNode nd;
		nd.setPosition((i < 2 ? (slot_margine_w * 3 + 100) : 0) * (i % 2 == 0 ? -1.0 : 1.0),
					   150,
					   (i > 1 ? (slot_margine_h * 3 + 100) : 0) * (i % 2 == 0 ? -1.0 : 1.0));
		nd.pan(i < 2 ? 90 : 0);
		
		walls[i].setTransform(nd.getGlobalTransformMatrix());
	}
	
	for (int i = 0;i < 6;i++)
	{
		if (tenban[i]) world.removeRigidBody(tenban[i]);
		tenban[i] = world.addBox(ofVec3f(slot_margine_w - slot_rad*2, 10, slot_margine_h * 7),
								 ofVec3f(slot_margine_w * (i + 0.5 - 3), tenban_height.get(), 0));
		tenban[i].setMass(0);
		tenban[i].setStatic(true);
	}
	for (int i = 6;i < 12;i++)
	{
		if (tenban[i]) world.removeRigidBody(tenban[i]);
		tenban[i] = world.addBox(ofVec3f(slot_margine_w * 7, 10, slot_margine_h - slot_rad*2),
								 ofVec3f(0, tenban_height.get(), slot_margine_h * ((i - 6) + 0.5 - 3)));
		tenban[i].setMass(0);
		tenban[i].setStatic(true);
	}
}

void ofApp::hit(ofxBt::World::CollisionEventArg &arg)
{
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == 'b') bangSW = 1;
	if (key == 'r')
	{
		int targ = ofRandom(50);
		for (int i = 0;i < 1000;i++)
		{
			targ = ofRandom(50);
			if (slots[targ].isCatch)
			{
				int idx = ofClamp(slots[targ].lastId, 0, 49);
				balls[idx].applyForce(ofVec3f(ofRandomf() * 500,150 * 100,
											  ofRandomf() * 500));
				break;
			}
		}
	}
//	for (int i = 0;i < 49;i++)
//	{
//		balls[i].applyForce(ofVec3f(ofRandomf() * 500,ofGetMouseY() * 100,
//									ofRandomf() * 500));
//	}
	
//	ball.applyForce(ofVec3f(ofRandomf() * 500,ofGetMouseY() * 100,
//							ofRandomf() * 500));

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
