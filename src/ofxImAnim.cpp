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

bool ofxImAnim::AnimatedButton(const char* label, float hoverScale,
							   float pressDepth, float duration) {
	ImGuiID id = ImGui::GetID(label);
	bool hovered = ImGui::IsItemHovered();
	bool active  = ImGui::IsItemActive();

	// Safe easing (no raw enum)
	iam_ease_desc scaleEase = iam_ease_preset(iam_ease_out_back);
	iam_ease_desc offsetEase = iam_ease_preset(iam_ease_out_quad);

	float scale   = tween_float(id,     hovered ? hoverScale : 1.0f, duration, scaleEase);
	float offsetY = tween_float(id + 1, active  ? pressDepth : 0.0f, 0.12f,    offsetEase);

	// Manual size scaling (avoids ImGuiStyleVar_Scale error)
	ImVec2 originalSize = ImGui::CalcTextSize(label);
	originalSize.x += ImGui::GetStyle().FramePadding.x * 2.0f + 20.0f; // extra padding for button
	originalSize.y += ImGui::GetStyle().FramePadding.y * 2.0f + 8.0f;

	ImVec2 buttonSize(originalSize.x * scale, originalSize.y * scale);

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + offsetY);

	return ImGui::Button(label, buttonSize);
}

bool ofxImAnim::AnimatedToggle(const char* label, bool* v, float duration) {
	ImGuiID id = ImGui::GetID(label);

	// 4 arguments required for iam_ease_spring_desc
	iam_ease_desc spring = iam_ease_spring_desc(1.0f, 180.0f, 15.0f, 0.0f);

	float knob = tween_float(id, *v ? 1.0f : 0.0f, duration, spring);

	ImVec2 size(58, 32);
	ImVec2 pos = ImGui::GetCursorScreenPos();

	ImDrawList* dl = ImGui::GetWindowDrawList();
	ImU32 bg = *v ? IM_COL32(80, 200, 120, 255) : IM_COL32(60, 60, 70, 255);

	dl->AddRectFilled(pos, ImVec2(pos.x + size.x, pos.y + size.y), bg, size.y * 0.5f);
	dl->AddCircleFilled(ImVec2(pos.x + 8 + knob * (size.x - 22), pos.y + size.y * 0.5f), 13, IM_COL32(255, 255, 255, 255));

	if (ImGui::InvisibleButton(label, size)) *v = !*v;

	ImGui::SameLine();
	ImGui::Text("%s", label);
	return *v;
}

bool ofxImAnim::HoverCard(const char* label, ImVec2 size) {
	ImGuiID id = ImGui::GetID(label);
	bool hovered = ImGui::IsItemHovered();

	float lift  = tween_float(id,     hovered ? -8.0f : 0.0f, 0.25f, iam_ease_preset(iam_ease_out_cubic));
	float scale = tween_float(id + 1, hovered ? 1.04f : 1.0f, 0.20f, iam_ease_preset(iam_ease_out_back));

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + lift);

	// Manual scaling for compatibility
	ImVec2 textSize = ImGui::CalcTextSize(label);
	ImVec2 buttonSize = (size.x > 0 && size.y > 0) ? size : ImVec2(textSize.x * scale + 24, textSize.y * scale + 16);

	return ImGui::Button(label, buttonSize);
}

// PulsingIcon
void ofxImAnim::PulsingIcon(const char* icon, ImU32 color) {
	ImGuiID id = ImGui::GetID(icon);
	float pulse = tween_float(id, 1.0f, 0.8f, iam_ease_preset(iam_ease_in_out_sine));
	float scale = 1.0f + pulse * 0.15f;

	// Manual scale using SetWindowFontScale (compatible with older ImGui)
	ImGui::SetWindowFontScale(scale);
	ImGui::TextColored(ImColor(color), "%s", icon);
	ImGui::SetWindowFontScale(1.0f);
}

// StaggeredList
bool ofxImAnim::StaggeredList(const char* items[], int item_count, int* selected, float delay) {
	ImGuiID base_id = ImGui::GetID("stagger_list");
	bool any_clicked = false;

	for (int i = 0; i < item_count; i++) {
		ImGuiID id = base_id + i;
		float progress = tween_float(id, 1.0f, 0.4f, iam_ease_preset(iam_ease_out_back));

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + (1.0f - progress) * 12.0f);

		if (ImGui::Selectable(items[i], *selected == i)) {
			*selected = i;
			any_clicked = true;
		}
	}
	return any_clicked;
}

void ofxImAnim::AnimatedProgressBar(float fraction, const char* label) {
	ImGuiID id = ImGui::GetID("prog");
	float animated = tween_float(id, fraction, 0.6f, iam_ease_preset(iam_ease_out_cubic));

	ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0.2f, 0.8f, 0.4f, 1.0f));
	ImGui::ProgressBar(animated, ImVec2(-1, 0), label);
	ImGui::PopStyleColor();
}

// AnimatedSliderFloat
float ofxImAnim::AnimatedSliderFloat(const char* label, float* v, float v_min, float v_max, float duration) {
	ImGuiID id = ImGui::GetID(label);
	float animated = tween_float(id, *v, duration, iam_ease_preset(iam_ease_out_cubic));

	if (ImGui::SliderFloat(label, &animated, v_min, v_max)) {
		*v = animated;
		return true;
	}
	return false;
}

// InputTextWithShake
bool ofxImAnim::InputTextWithShake(const char* label, char* buf, size_t buf_size, bool isError) {
	ImGuiID id = ImGui::GetID(label);
	if (isError) {
		iam_trigger_shake(id);
	}

	ImVec2 offset = iam_shake_vec2(id, ImVec2(6, 0), 25.0f, 0.4f, ofGetLastFrameTime());
	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + offset.x);

	return ImGui::InputText(label, buf, buf_size);
}

void ofxImAnim::ShowToast(Toast& toast) {
	if (!toast.active) return;

	toast.timer += ofGetLastFrameTime();
	if (toast.timer > toast.duration) {
		toast.active = false;
		return;
	}

	float progress = toast.timer / toast.duration;
	float slide = tween_float(ImGui::GetID("toast_slide"),
							  progress < 0.15f ? 1.0f : 0.0f,
							  0.3f, iam_ease_preset(iam_ease_out_back));

	ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - 320, 40 + slide * 60), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(300, 0));

	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1f, 0.1f, 0.12f, 0.95f));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 8.0f);

	if (ImGui::Begin("##Toast", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Text("%s", toast.text.c_str());
	}
	ImGui::End();

	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}

// UpdateToasts
void ofxImAnim::UpdateToasts(Toast* toasts, int count) {
	for (int i = 0; i < count; i++) {
		if (toasts[i].active) ShowToast(toasts[i]);
	}
}

void ofxImAnim::FireToast(Toast& toast, const char* message, float duration) {
	toast.text = message;
	toast.duration = duration;
	toast.timer = 0.0f;
	toast.active = true;
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

float ofxImAnim::tween_float(ImGuiID id, float target, float duration,
							 iam_ease_desc ease, int policy, float dt, ImGuiID channel) {
	if (id == 0) id = ImGui::GetID("ofxImAnim");
	if (channel == 0) channel = ImGui::GetID("float");
	if (dt <= 0.0f) dt = ofGetLastFrameTime();
	return iam_tween_float(id, channel, target, duration, ease, policy, dt);
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
