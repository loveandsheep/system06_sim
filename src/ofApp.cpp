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
	
	ofxBt::RigidBody wall;
	
	wall = world.addBox(ofVec3f(1000, 500, 10), ofVec3f(-520, 150, 0), ofVec3f(90, 0, 0));
	wall.setMass(0);
	wall.setStatic(true);
	
	wall = world.addBox(ofVec3f(1000, 500, 10), ofVec3f( 520, 150, 0), ofVec3f(90, 0, 0));
	wall.setMass(0);
	wall.setStatic(true);
	
	wall = world.addBox(ofVec3f(1000, 500, 10), ofVec3f(0, 150, 520), ofVec3f(0, 0, 0));
	wall.setMass(0);
	wall.setStatic(true);
	
	wall = world.addBox(ofVec3f(1000, 500, 10), ofVec3f(0, 150, -520), ofVec3f(0, 0, 0));
	wall.setMass(0);
	wall.setStatic(true);
}

//--------------------------------------------------------------
void ofApp::update()
{
	world.update();
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
//		ofSetColor(255);
//		spMesh.drawWireframe();
		ofPopMatrix();
		
		slots[i].draw();
	}
//	world.draw();
	ofDisableDepthTest();
	camera.end();
	
	if ((bangSW > 0) && (ofGetFrameNum() % 5 == 0))
	{
		balls[bangSW - 1].applyForce(ofVec3f(ofRandomf() * 500,150 * 100,
											 ofRandomf() * 500));
		bangSW++;
		if (bangSW == 49) bangSW = 0;
	}
}

void ofApp::hit(ofxBt::World::CollisionEventArg &arg)
{
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	bangSW = 1;
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
