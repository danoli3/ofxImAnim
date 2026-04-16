#pragma once

#ifndef __ofxImAni_h__
#define __ofxImAni_h__

#include "ofMain.h"
#include "ofxImGui.h"
#include "imgui.h"
#include "im_anim.h"
#include "im_anim_demo.cpp"

class ofxImAnim {
public:
    /// Call once in setup() (optional — ImAnim is very lightweight)
    static void setup();

    /// MUST call this **right after** ImGui::NewFrame() / ofxImGui::begin()
    /// (or gui.begin() in your ofApp::draw())
    static void beginFrame();

    /// Call this every frame to advance clips/tweens.
    /// Pass ImGui delta time if available, otherwise falls back to ofGetLastFrameTime()
    static void update(float dt = 0.0f);

    /// Optional garbage collection (cleans up old animation IDs — call occasionally)
    static void gc(unsigned int maxAgeFrames = 600);

    // Convenience wrappers can be added later (e.g. tween ofVec2f, ofColor, ofParameter, etc.)
	
	static inline void showDemoWindow() {
		ImAnimDemoWindow();
	}
	
	static ofVec2f tween(ofVec2f target, float duration, iam_ease_desc ease,
						 int policy = iam_policy_crossfade, float dt = 0.0f,
						 ImGuiID id = 0, ImGuiID channel = 0);

	static ofColor tween(ofColor target, float duration, iam_ease_desc ease,
						 int policy = iam_policy_crossfade, int colorSpace = iam_col_oklab,
						 float dt = 0.0f, ImGuiID id = 0, ImGuiID channel = 0);

	static ofVec2f tweenRel(ofVec2f percent, ofVec2f pxBias, float duration,
							iam_ease_desc ease, int anchorSpace = iam_anchor_window_content,
							int policy = iam_policy_crossfade, float dt = 0.0f,
							ImGuiID id = 0, ImGuiID channel = 0);

	static ofVec2f tweenResolved(std::function<ofVec2f()> resolver, float duration,
								 iam_ease_desc ease, int policy = iam_policy_crossfade,
								 float dt = 0.0f, ImGuiID id = 0, ImGuiID channel = 0);

	

};

#endif
