//
//  ofxAwesomium.cpp
//  basic
//
//  Created by jeff-cr on 11/6/13.
//
//

#include "ofxAwesomium.h"
int getWebKeyFromOFKey(int key);
// ----------------------------------------------------------------
ofxAwesomium::~ofxAwesomium(){
	web_view->Destroy();
	WebCore::Shutdown();
}

// ----------------------------------------------------------------
void ofxAwesomium::setup(int width, int height) {
	if(!bCoreInited) {
		initCore(ofToDataPath("Logs"), ofToDataPath("SessionData"));
	}
	web_view = core->CreateWebView(width, height, session);
	frame.allocate(width, height, OF_IMAGE_COLOR_ALPHA);
    //texture.allocate(width, height, GL_RGBA);
	isResizing = false;
}

// ----------------------------------------------------------------
void ofxAwesomium::loadURL(string url) {
	web_view->LoadURL(WebURL(WSLit(url.c_str())));
    web_view->Focus();
}

// ----------------------------------------------------------------
JSValue ofxAwesomium::doJavaScript(string js) {
	return web_view->ExecuteJavascriptWithResult(WSLit(js.c_str()), WSLit(""));
}

// ----------------------------------------------------------------
bool ofxAwesomium::update() {
	isResizing = false;
    surface = (BitmapSurface*)web_view->surface();
    //实现参考http://wiki.awesomium.com/tutorials/tutorial-1-hello-awesomium.html
    if(surface && surface->buffer() && surface->is_dirty()) {
        //texture.loadData(surface->buffer(), texture.getWidth(), texture.getHeight(), GL_BGRA);
		frame.setFromPixels(surface->buffer(), frame.getWidth(), frame.getHeight(), OF_IMAGE_COLOR_ALPHA);
		frame.getPixelsRef().swapRgb();
		frame.update();
		return true;
    }
	return false;
}

// ----------------------------------------------------------------
void ofxAwesomium::draw(float x, float y) const {
	if (isResizing == false) {
		frame.draw(x, y);
	}
}

// ----------------------------------------------------------------
void ofxAwesomium::draw(float x, float y, float w, float h) const {
	if (isResizing == false) {
		frame.draw(x, y, w, h);
	}
}

// ----------------------------------------------------------------
float ofxAwesomium::getHeight() const {
	return frame.getHeight();
}

// ----------------------------------------------------------------
float ofxAwesomium::getWidth() const {
	return frame.getWidth();
}

// ----------------------------------------------------------------
string ofxAwesomium::getTitle(){
	char buf[1024];
    web_view->title().ToUTF8( buf, 1024 );
	return string(buf);
}

// ----------------------------------------------------------------
bool ofxAwesomium::getIsLoading(){
	return web_view->IsLoading();
}

void ofxAwesomium::injectKey(int keyCode) {

	Awesomium::WebKeyboardEvent keyEvent;
	keyEvent.type = Awesomium::WebKeyboardEvent::kTypeKeyDown;
	keyEvent.virtual_key_code = getWebKeyFromOFKey(keyCode); //keyCode;	//根据虚拟键码创建
	keyEvent.native_key_code = 0; //因为多平台
	keyEvent.text[0] = (char)keyCode;
    keyEvent.unmodified_text[0] = (char)keyCode;
	char* buf = new char[20]; 
	Awesomium::GetKeyIdentifierFromVirtualKeyCode(keyEvent.virtual_key_code,&buf);//api规定必须至少为20个char
	strcpy(keyEvent.key_identifier, buf);//添加这个可以返回
	delete[] buf; 
	
	keyEvent.modifiers = 0; //当前键盘状态    
	web_view->InjectKeyboardEvent(keyEvent);
    

}

// ----------------------------------------------------------------
void ofxAwesomium::keyPressed(int key) {

	web_view->Focus();
	injectKey(key);
	    
	Awesomium::WebKeyboardEvent keyEvent;
	keyEvent.type = Awesomium::WebKeyboardEvent::kTypeChar;
	keyEvent.virtual_key_code = (char)key;
	keyEvent.native_key_code = (char)key;
	keyEvent.text[0] = (char)key;
	keyEvent.unmodified_text[0] = (char)key;
	keyEvent.modifiers = 0;
	web_view->InjectKeyboardEvent(keyEvent);
}

// ----------------------------------------------------------------
void ofxAwesomium::keyReleased(int key) {
	web_view->Focus();

	Awesomium::WebKeyboardEvent keyEvent;
	keyEvent.type = Awesomium::WebKeyboardEvent::kTypeKeyUp;
    keyEvent.virtual_key_code = (char)key;
    keyEvent.native_key_code = (char)key;
    keyEvent.text[0] = (char)key;
    keyEvent.unmodified_text[0] = (char)key;
    keyEvent.modifiers = 0;
    web_view->InjectKeyboardEvent(keyEvent);
}

//--------------------------------------------------------------
void ofxAwesomium::mouseMoved(int x, int y ){
    web_view->InjectMouseMove( x, y );
}

//--------------------------------------------------------------
void ofxAwesomium::mouseDragged(int x, int y, int button){
    web_view->InjectMouseMove( x, y );
}

//--------------------------------------------------------------
void ofxAwesomium::mousePressed(int x, int y, int button){
    if( button ==  OF_MOUSE_BUTTON_1)
        web_view->InjectMouseDown( Awesomium::kMouseButton_Left );
    else if( button == OF_MOUSE_BUTTON_2 )
        web_view->InjectMouseDown( Awesomium::kMouseButton_Middle );
    else if( button== OF_MOUSE_BUTTON_3 )
        web_view->InjectMouseDown( Awesomium::kMouseButton_Right );
}

//--------------------------------------------------------------
void ofxAwesomium::mouseReleased(int x, int y, int button){
    if( button ==  OF_MOUSE_BUTTON_1)
        web_view->InjectMouseUp( Awesomium::kMouseButton_Left );
    else if( button == OF_MOUSE_BUTTON_2 )
        web_view->InjectMouseUp( Awesomium::kMouseButton_Middle );
    else if( button== OF_MOUSE_BUTTON_3 )
        web_view->InjectMouseUp( Awesomium::kMouseButton_Right );
}

//--------------------------------------------------------------
void ofxAwesomium::mouseScrolled(int x,int y){
	web_view->InjectMouseWheel(y,x);
}

//--------------------------------------------------------------
void ofxAwesomium::windowResized(int w, int h){
	isResizing = true;
	frame.allocate(w, h, OF_IMAGE_COLOR_ALPHA);
	
	web_view->Resize(w, h);
	core->Update();
}

/// Helper Macro
#define mapKey(a, b) case OF_KEY_##a: return Awesomium::KeyCodes::AK_##b;

/// Get an Awesomium KeyCode from an OFKey Code 2014.12.2 terry
int getWebKeyFromOFKey(int key) {

  switch (key) {

	mapKey(RETURN, RETURN)
	mapKey(ESC, ESCAPE)
	mapKey(TAB, TAB)


    mapKey(BACKSPACE, BACK)
    mapKey(DEL, DELETE)

    mapKey(F1, F1)
    mapKey(F2, F2)
    mapKey(F3, F3)
    mapKey(F4, F4)
    mapKey(F5, F5)
    mapKey(F6, F6)
    mapKey(F7, F7)
    mapKey(F8, F8)
    mapKey(F9, F9)
    mapKey(F10, F10)
    mapKey(F11, F11)
    mapKey(F12, F12)
    mapKey(LEFT, LEFT)
	mapKey(UP, UP)
    mapKey(RIGHT, RIGHT)
    mapKey(DOWN, DOWN)

    mapKey(PAGE_UP, PRIOR)
    mapKey(PAGE_DOWN, NEXT)

	
    mapKey(HOME, HOME)
    mapKey(END, END)
	mapKey(INSERT, INSERT)
	mapKey(CONTROL, CONTROL)
	mapKey(ALT, MENU)
	mapKey(SHIFT, SHIFT)
	mapKey(LEFT_SHIFT, LSHIFT)
	mapKey(RIGHT_SHIFT, RSHIFT)
	mapKey(LEFT_CONTROL, LCONTROL)
	mapKey(RIGHT_CONTROL, RCONTROL)
	mapKey(LEFT_ALT, LMENU)
	mapKey(RIGHT_ALT, RMENU)
	mapKey(LEFT_SUPER, LWIN)
	mapKey(RIGHT_SUPER, RWIN)

  default:
    return Awesomium::KeyCodes::AK_UNKNOWN;
  }
}


// ----------------------------------------------------------------
//  _       __     __    ______
// | |     / /__  / /_  / ____/___  ________
// | | /| / / _ \/ __ \/ /   / __ \/ ___/ _ \
// | |/ |/ /  __/ /_/ / /___/ /_/ / /  /  __/
// |__/|__/\___/_.___/\____/\____/_/   \___/
// ----------------------------------------------------------------

bool ofxAwesomium::bCoreInited;
WebCore* ofxAwesomium::core;
WebSession* ofxAwesomium::session;

// ----------------------------------------------------------------
void ofxAwesomium::initCore(string logsPath, string sessionPath) {
	WebConfig config;
    config.log_path = WSLit(logsPath.c_str());
    config.log_level = kLogLevel_Verbose; //kLogLevel_Normal;
    
    core = WebCore::Initialize(config);
    
    WebPreferences prefs;
    prefs.enable_plugins = true;
    prefs.enable_smooth_scrolling = true;
    
    session = core->CreateWebSession(WSLit(sessionPath.c_str()), prefs);
	
	bCoreInited = true;
}

// ----------------------------------------------------------------
void ofxAwesomium::updateCore() {
	core->Update();
}

// ----------------------------------------------------------------
void ofxAwesomium::shutdownCore() {
	WebCore::Shutdown();
}

