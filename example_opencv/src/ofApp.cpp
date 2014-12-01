#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	browser.setup(ofGetWidth(), ofGetHeight());
	
	moustache.loadImage("moustache.png");
	browser.loadURL("https://www.google.com/search?q=faces");
	//browser.loadURL("https://www.google.com/search?q=moustache+competition");
	
	finder.setup("haarcascade_frontalface_default.xml");
	scale.set(0.25, 0.25);
}

//--------------------------------------------------------------
void ofApp::update(){
	ofSetWindowTitle(ofToString(ofGetFrameRate())+"fps");
	ofxAwesomium::updateCore();
	bool bIsFrameNew = browser.update();
	
	if(bIsFrameNew) {
		grayFrame = browser.frame;
		grayFrame.setImageType(OF_IMAGE_GRAYSCALE);
		ofPoint size = ofGetWindowSize()*scale;
		grayFrame.resize(size.x, size.y);
		finder.findHaarObjects(grayFrame);
	}
	
	//ofSetWindowTitle(browser.getTitle());
}

//--------------------------------------------------------------
void ofApp::draw(){
	if(browser.getIsLoading()) {
		ofSetColor(0);
		ofDrawBitmapString("Loading...", 10, 15);
	}
	
	ofSetColor(255);
	browser.draw(0, 0);

	
	ofNoFill();
	ofSetColor(255);
	//ofSetLineWidth(2);
	for(unsigned int i = 0; i < finder.blobs.size(); i++) {
		ofRectangle cur = finder.blobs[i].boundingRect;
		cur.x *= 1/scale.x;
		cur.y *= 1/scale.y;
		cur.width *= 1/scale.x;
		cur.height *= 1/scale.y;
		moustache.draw(cur);
		//ofRect(cur.x, cur.y, cur.width, cur.height);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	browser.keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	browser.keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	browser.mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	browser.mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	browser.mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	browser.mouseReleased(x, y, button);
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
