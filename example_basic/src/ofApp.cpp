#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	browser.setup(ofGetWidth(), ofGetHeight());
	browser.loadURL("http://www.google.com");
}

//--------------------------------------------------------------
void ofApp::update(){
	ofxAwesomium::updateCore();
	browser.update();
	
	ofSetWindowTitle(browser.getTitle());
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	//ofSetColor(255);
	browser.draw(0, 0);
	if(browser.getIsLoading()) {
		//ofSetColor(0);
		ofDrawBitmapStringHighlight("Loading...", 10, 15);
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
	browser.windowResized(w,h); //过大会报错，以后用到在检查 terry
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
