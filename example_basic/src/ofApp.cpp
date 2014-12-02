#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	browser.setup(ofGetWidth(), ofGetHeight());
	browser.loadURL("http://www.163.com");

	browser.web_view->SetTransparent(true);

	ofAddListener(ofEvents().mouseScrolled,this,&ofApp::mouseScrolled);//应该是of的问题，目前此事件不能被响应。
}

//--------------------------------------------------------------
void ofApp::update(){
	ofxAwesomium::updateCore();
	browser.update();
	
	ofSetWindowTitle(browser.getTitle());
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackgroundGradient(ofColor::black,ofColor::white);
	//ofSetColor(255);
	ofPushStyle();
	ofEnableAlphaBlending();
	browser.draw(0, 0);
	ofPopStyle();
	if(browser.getIsLoading()) {
		//ofSetColor(0);
		ofDrawBitmapStringHighlight("Loading...", 10, 15);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
	//cout<<key<<endl;
	if(key==3){//ctrl+c
		browser.web_view->Copy();
	}else if(key==22){//ctrl+v
		browser.web_view->Paste();
	}else if(ofGetKeyPressed(OF_KEY_F5)){
		browser.web_view->Reload(true);
	}else if(key==356){//alt+left
		browser.web_view->GoBack();
	}else if(key==358){//alt+right
		browser.web_view->GoForward();
	}else if(key==45){//alt+-
		browser.web_view->ZoomIn();
	}else if(key==61){//alt++
		browser.web_view->ZoomOut();
	}else{
		browser.keyPressed(key);
	}
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
void ofApp::mouseScrolled(ofMouseEventArgs & mouse){
	browser.mouseScrolled(mouse.x*10,mouse.y*10); 
	//cout<<"mouseScrolled"<<mouse.x<<","<<mouse.y<<endl;
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
