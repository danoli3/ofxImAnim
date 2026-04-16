#include "ofxImAnim.h"

#ifndef __ofxImAni_cpp__
#define __ofxImAni_cpp__

void ofxImAnim::setup() {
}

void ofxImAnim::beginFrame() {
    iam_update_begin_frame();
}

void ofxImAnim::update(float dt) {
    if (dt <= 0.0f) {
        dt = ofGetLastFrameTime();
    }
    iam_clip_update(dt); // Advances all clips/tweens
}

void ofxImAnim::gc(unsigned int maxAgeFrames) {
    // ImAnim has internal cleanup helpers — expose if you need it
}

static ImVec2 ofVec2f_resolver(void* user_data)
{
	auto& func = *static_cast<std::function<ofVec2f()>*>(user_data);
	ofVec2f v = func();
	return ImVec2(v.x, v.y);
}

// ------------------------------------------------------------------
// OF-native tween helpers
// ------------------------------------------------------------------
ofVec2f ofxImAnim::tween(ofVec2f target, float duration, iam_ease_desc ease,
						 int policy, float dt, ImGuiID id, ImGuiID channel)
{
	if (id == 0) id = ImGui::GetID("ofxImAnim");
	if (channel == 0) channel = ImGui::GetID("vec2");

	ImVec2 t = iam_tween_vec2(id, channel, ImVec2(target.x, target.y),
							  duration, ease, policy, dt);
	return ofVec2f(t.x, t.y);
}

ofColor ofxImAnim::tween(ofColor target, float duration, iam_ease_desc ease,
						 int policy, int colorSpace, float dt, ImGuiID id, ImGuiID channel)
{
	if (id == 0) id = ImGui::GetID("ofxImAnim");
	if (channel == 0) channel = ImGui::GetID("color");

	ImVec4 t = iam_tween_color(id, channel,
							   ImVec4(target.r/255.f, target.g/255.f, target.b/255.f, target.a/255.f),
							   duration, ease, policy, colorSpace, dt);
	return ofColor((int)(t.x*255), (int)(t.y*255), (int)(t.z*255), (int)(t.w*255));
}

ofVec2f ofxImAnim::tweenRel(ofVec2f percent, ofVec2f pxBias, float duration,
							iam_ease_desc ease, int anchorSpace, int policy, float dt,
							ImGuiID id, ImGuiID channel)
{
	if (id == 0) id = ImGui::GetID("ofxImAnim");
	if (channel == 0) channel = ImGui::GetID("vec2_rel");

	ImVec2 t = iam_tween_vec2_rel(id, channel,
								  ImVec2(percent.x, percent.y),
								  ImVec2(pxBias.x, pxBias.y),
								  duration, ease, policy, anchorSpace, dt);
	return ofVec2f(t.x, t.y);
}

ofVec2f ofxImAnim::tweenResolved(std::function<ofVec2f()> resolver,
								 float duration, iam_ease_desc ease,
								 int policy, float dt, ImGuiID id, ImGuiID channel)
{
	if (id == 0) id = ImGui::GetID("ofxImAnim");
	if (channel == 0) channel = ImGui::GetID("vec2_resolved");

	ImVec2 t = iam_tween_vec2_resolved(id, channel,
									   ofVec2f_resolver,
									   &resolver,
									   duration, ease, policy, dt);

	return ofVec2f(t.x, t.y);
}

#endif
