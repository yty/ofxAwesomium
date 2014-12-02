//
//  ofxAwesomium.h
//  basic
//
//  Created by jeff-cr on 11/6/13.
//
//

#pragma once
#include "ofMain.h"
#include <Awesomium/WebCore.h>
#include <Awesomium/BitmapSurface.h>
#include <Awesomium/STLHelpers.h>

using namespace Awesomium;

class ofxAwesomium : public ofBaseDraws {
public:

	//ofxAwesomium();
	~ofxAwesomium();
	void setup(int width, int height);
	void loadURL(string url);
	bool update();
	string getTitle();
	bool getIsLoading();
	JSValue doJavaScript(string js);
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseScrolled(int x,int y);
	void windowResized(int w, int h);
	
	void injectKey(int keyCode);
	// begin ofBaseDraws
	void draw(float x, float y) const;
	void draw(float x, float y, float w, float h) const;
	void draw(const ofPoint & point) const {
		draw(point.x, point.y);
	}
	void draw(const ofRectangle & rect) const {
		draw(rect.x, rect.y, rect.width, rect.height);
	}
	void draw(const ofPoint & point, float w, float h) const {
		draw(point.x, point.y, w, h);
	}
	float getHeight() const;
	float getWidth() const;
	// end ofBaseDraws
	
	ofImage frame;
	bool isResizing;
	static void initCore(string logsPath, string sessionPath);
	static void updateCore();
	static void shutdownCore();
	
	WebView* web_view;

protected:
	
	
	BitmapSurface* surface;
	

	static bool bCoreInited;
	static WebCore* core;
	static WebSession* session;
};