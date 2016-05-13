#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	world.setup(ofVec3f(0, -7808, 0));
	
//	bulb = world.addBox(ofVec3f(40,40,40), ofVec3f(0, 50, 0));
//	bulb.setRestitution(0.5);
////	bulb.setKinematic(false);
//	bulb.setMass(0);
//	bulb.setStatic(true);
	
	floor = world.addPlane(ofVec3f(0,1,0), ofVec3f(0,0,0));
//	floor.setStatic(true);
	floor.setRestitution(0.8);

	ball = world.addSphere(50, ofVec3f(0,150,0));
	ball.setMass(0.1);
	ball.setRestitution(0.8);
	
	for (int i = 0;i < 10;i++)
	{
		ofNode nd;
		nd.move(0, 50, 0);
		nd.pan(-i * 36 + 90);
		nd.dolly(50);
		nd.tilt(45);
		
		ofMatrix4x4 mat;
//		mat.rotate(-i * 36 + 90, 0.0, 1.0, 0.0);
//		
//		mat.rotate(45, 1.0, 0.0, 0.0);
//		mat.translate(cos(ofDegToRad(i * 36)) * 50, 100,
//					  sin(ofDegToRad(i * 36)) * 50);
		mat = nd.getGlobalTransformMatrix();
		
		cylinderCube[i] = world.addBox(ofVec3f(150, 100, 5), ofVec3f(0,0,0));
		cylinderCube[i].setMass(0);
		cylinderCube[i].setStatic(true);
		cylinderCube[i].setTransform(mat);
		cylinderCube[i].setRestitution(0.75);
	}
	
	ofAddListener(world.collisionEvent, this, &ofApp::hit);
}

//--------------------------------------------------------------
void ofApp::update()
{
	world.update();
	
//	ofMatrix4x4 mat;
//	mat.translate(0, ofGetMouseY(), 0);
//	bulb.setTransform(mat);
	
	if (ofGetKeyPressed())
	{
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackground(0, 0, 0);
	camera.begin();
	world.draw();
	camera.end();
}

void ofApp::hit(ofxBt::World::CollisionEventArg &arg)
{
	cout << "Hit " << ofGetFrameNum() << endl;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	ball.applyForce(ofVec3f(ofRandomf() * 500,ofGetMouseY() * 100,
							ofRandomf() * 500));

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
