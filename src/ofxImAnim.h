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
	
	
	static bool AnimatedButton(const char* label,
								   float hoverScale = 1.12f,
								   float pressDepth = 2.0f,
								   float duration = 0.18f);

	static bool AnimatedToggle(const char* label, bool* v, float duration = 0.25f);

	static bool HoverCard(const char* label, ImVec2 size = ImVec2(0, 0));

	static void AnimatedProgressBar(float fraction, const char* label = nullptr);

	static bool InputTextWithShake(const char* label, char* buf, size_t buf_size, bool isError);

	static float AnimatedSliderFloat(const char* label, float* v, float v_min, float v_max, float duration = 0.25f);

	static bool StaggeredList(const char* items[], int item_count, int* selected, float delay = 0.04f);

	static void PulsingIcon(const char* icon, ImU32 color = IM_COL32(255, 80, 80, 255));

	// Toast system
	struct Toast {
		std::string text;
		float timer = 0.0f;
		float duration = 4.0f;
		bool active = false;
	};

	static void FireToast(Toast& toast, const char* message, float duration = 4.0f);
	static void UpdateToasts(Toast* toasts, int count);
	static void ShowToast(Toast& toast);   // internal
	
	static ofVec2f tween(ofVec2f target, float duration, iam_ease_desc ease,
						 int policy = iam_policy_crossfade, float dt = 0.0f,
						 ImGuiID id = 0, ImGuiID channel = 0);
	
	static float tween_float(ImGuiID id, float target, float duration,
							 iam_ease_desc ease, int policy = iam_policy_crossfade,
							 float dt = 0.0f, ImGuiID channel = 0);

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
