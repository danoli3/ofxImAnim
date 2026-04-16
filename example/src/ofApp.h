#pragma once

#include "ofMain.h"
#include "ofxImGui.h"
#include "ofxImAnim.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	
		ofxImGui::Gui gui;
	
	
		bool  soundOn = true;
		float health = 0.75f;
		int   selectedMenu = 0;
		char  emailBuf[128] = "";
		bool  emailValid = true;

		ofxImAnim::Toast toast;   // single toast demo
};
