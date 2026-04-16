#include "ofApp.h"
void ofApp::setup() {
	ofSetWindowTitle("ofxImAnim - Widget Demo");
    gui.setup();
    ofxImAnim::setup();
}

void ofApp::update() {
	ofxImAnim::update();   // ← advances all animations (uses ofGetLastFrameTime())
}

void ofApp::draw() {
    gui.begin();                     // ← ImGui::NewFrame()
    ofxImAnim::beginFrame();         // ← required

	
	
	
	ImGui::SetNextWindowPos(ImVec2(30, 30), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(720, 680), ImGuiCond_FirstUseEver);

	if (ImGui::Begin("ofxImAnim Widgets")) {

		ImGui::Text("High-level animated widgets from ofxImAnim");
		ImGui::Separator();

		// Buttons & Toggle
		if (ImGui::CollapsingHeader("Buttons & Toggle", ImGuiTreeNodeFlags_DefaultOpen)) {
			ImGui::Dummy(ImVec2(0, 8));

			if (ofxImAnim::AnimatedButton("Hover Me!", 1.15f)) {
				ofLogNotice() << "AnimatedButton clicked!";
			}

			ImGui::SameLine(280);
			ofxImAnim::AnimatedToggle("Sound FX", &soundOn);

			ImGui::SameLine(480);
			if (ofxImAnim::HoverCard("Special Card")) {
				// toggle something
			}
		}

		// Progress & Sliders
		if (ImGui::CollapsingHeader("Progress & Sliders")) {
			ofxImAnim::AnimatedProgressBar(health, "Health");
			ImGui::SliderFloat("Health", &health, 0.0f, 1.0f);

			float val = health;
			if (ofxImAnim::AnimatedSliderFloat("Animated Slider", &val, 0.0f, 1.0f)) {
				health = val;
			}
		}

		// Staggered List + Icons
		if (ImGui::CollapsingHeader("Staggered List & Icons")) {
			const char* menuItems[4] = { "Dashboard", "Projects", "Analytics", "Settings" };
			ofxImAnim::StaggeredList(menuItems, 4, &selectedMenu);

			ImGui::SameLine(320);
			ofxImAnim::PulsingIcon("❤️");
			ImGui::SameLine();
			ofxImAnim::PulsingIcon("🔥", IM_COL32(255, 140, 40, 255));
		}

		// Input with shake + Toast
		if (ImGui::CollapsingHeader("Input & Toast")) {
			emailValid = (strchr(emailBuf, '@') != nullptr && strlen(emailBuf) > 3);
			ofxImAnim::InputTextWithShake("Email", emailBuf, sizeof(emailBuf), !emailValid);

			if (ImGui::Button("Send Test Toast")) {
				ofxImAnim::FireToast(toast, "Operation completed successfully!", 3.5f);
			}
		}
		

		if (ImGui::CollapsingHeader("Interactive Text Animations (click to retrigger)", ImGuiTreeNodeFlags_DefaultOpen)) {

			// 1. Fade Text - click to fade in again
			if (ImGui::InvisibleButton("FadeTextArea", ImVec2(ImGui::GetContentRegionAvail().x, 40))) {
				// Force retrigger by using a new ID or resetting
				static int fadeCounter = 0;
				fadeCounter++;
				ofxImAnim::FadeText("This text fades in smoothly", 0.0f, 1.2f); // start from invisible
			}
			ofxImAnim::FadeText("This text fades in smoothly", 1.0f, 1.2f);

			ImGui::Spacing();

			// 2. Complex Text - click to replay the full sequence
			if (ImGui::InvisibleButton("ComplexTextArea", ImVec2(ImGui::GetContentRegionAvail().x, 40))) {
				// Retrigger the clip
				static ImGuiID complexInst = ImHashStr("complex_text_inst");
				iam_instance inst = iam_get_instance(complexInst);
				if (inst.valid()) inst.destroy();
				ofxImAnim::ComplexText("Complex sequenced text!");
			}
			ofxImAnim::ComplexText("Complex sequenced text!");

			ImGui::Spacing();

			// 3. Looping Text - click to reset the pulse
			if (ImGui::InvisibleButton("LoopingTextArea", ImVec2(ImGui::GetContentRegionAvail().x, 40))) {
				static int loopCounter = 0;
				loopCounter++;
				ofxImAnim::LoopingText("Looping pulse animation");
			}
			ofxImAnim::LoopingText("Looping pulse animation");
		}

		ImGui::Separator();
		// Show any active toast
		ofxImAnim::UpdateToasts(&toast, 1);

		ImGui::Separator();
		ImGui::Text("All widgets use spring easing, crossfade, and automatic IDs.");
	}
	ImGui::End();
	
	
	
	
	ofxImAnim::showDemoWindow();

    gui.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
