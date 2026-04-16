# ofxImAnim

![ofxaddons_thumbnail](ofxaddons_thumbnail.png)

[![License](https://img.shields.io/badge/license-MIT-green.svg)](../LICENSE)

![ImAnimDemo_Hero_1 0 0](https://github.com/user-attachments/assets/a9e7931c-7e31-4585-80dc-9ac93664ec3e)

**openFrameworks wrapper addon for [ImAnim](https://github.com/soufianekhiat/ImAnim)** — a lightweight, zero-dependency animation engine for Dear ImGui.

ImAnim brings modern, buttery-smooth UI animations (tweens, timeline clips, paths, procedural effects, color blending, etc.) to ImGui while staying true to its immediate-mode philosophy.
`ofxImAnim` makes it dead-simple to use all of that power inside openFrameworks (together with `ofxImGui`).

## Example

![ofxImAnim](ofxImAnim.png)

---

## Features

- Animate `float`, `ImVec2`, `ImVec4`, `int`, and `ImColor` properties
- Timeline **Clips** with keyframes, looping, staggering, chaining and callbacks
- 30+ easing functions (springs, bounce, cubic-bezier, steps, etc.) + per-axis control
- Bézier curves, Catmull-Rom splines, motion paths and text-along-path
- Procedural animations (Perlin/Simplex noise, oscillators, shake, wiggle)
- Perceptual color blending (OKLAB / OKLCH)
- Transform animations (position, rotation, scale)
- Built-in debug inspector, profiler, save/load and memory tools

---

## Installation

1. Clone or download this repository into your `openFrameworks/addons/` folder (or use the Project Generator).
2. Add `ofxImAnim` (and its dependency `ofxImGui`) to your project.
3. Make sure you have a working ImGui integration (recommended: [ofxImGui](https://github.com/Daandelange/ofxImGui)).

---

## Dependencies

- [`ofxImGui`](https://github.com/Daandelange/ofxImGui) (or any compatible Dear ImGui addon)

- Embedded [![Version](https://img.shields.io/badge/version-1.0.0-blue.svg)](https://github.com/soufianekhiat/ImAnim)

---

## Quick Usage

After `ImGui::NewFrame()` in your `ofApp::draw()`:

```cpp
// Update animation engine
iam_update_begin_frame();
iam_clip_update(ImGui::GetIO().DeltaTime);

// Your ImGui code with animations...
if (ImGui::Button("Animate Me")) {
    // example tween (see original ImAnim for full API)
    iam_tween_float("myValue", 0.0f, 1.0f, 0.6f, IAM_EASE_OUT_BOUNCE);
}

// After ImGui rendering
iam_clip_update(); // (or call once per frame as shown above)



```

| Animated Tag |
|:------------:|
| ![ImAnimDemo_a1h8amHeJp](https://github.com/user-attachments/assets/6ac30639-b737-47be-9c47-be4f4de48af3) |

| Ripple Button |
|:------------:|
| ![ImAnimDemo_XVoOtKSf3G](https://github.com/user-attachments/assets/9f3cac6f-b1bf-4fd5-b746-16ef93bf8cc4) |

| "Wait" Button |
|:------------:|
| ![ImAnimDemo_2RPgqEAHHm](https://github.com/user-attachments/assets/274de702-f79c-4589-acac-b61d8a91900b) |

| Data Visualization |
|:------------:|
| ![ImAnimDemo_VnmpjDbMZh](https://github.com/user-attachments/assets/cd01aab9-6dd8-46a6-9614-92491f8f9b60) |
| ![ImAnimDemo_zI6R85WazP](https://github.com/user-attachments/assets/7027587b-f2b7-4bfc-aa15-bbadccd87baa) |

## Showcase

Visual examples of ImAnim capabilities in action.

### Stagger Animations

| List Stagger | Grid Stagger | Card Stagger |
|:------------:|:------------:|:------------:|
| ![List](https://github.com/user-attachments/assets/a59968c6-5cbf-405f-8e67-f12e15205512) | ![Grid](https://github.com/user-attachments/assets/6618002b-8326-45ec-aa16-11feed26b75f) | ![Cards](https://github.com/user-attachments/assets/ef29a857-c64c-45e0-bad2-3b67952da36d) |

### Easing & Curves

| Easing Gallery | Custom Bezier | Wave Animations |
|:-------------:|:-------------:|:---------------:|
| ![Easing](https://github.com/user-attachments/assets/d918c4d9-6e22-4fa8-b591-68d6b3afec7e) | ![Bezier](https://github.com/user-attachments/assets/c9f35054-cd26-475e-bb49-7875922fa273) | ![Waves](https://github.com/user-attachments/assets/19c3fd48-10b7-4350-9eea-4cffc4ef4984) |

### Colors & Transforms

| Color Blending | Gradient | Transforms |
|:-------------:|:--------:|:----------:|
| ![Color](https://github.com/user-attachments/assets/364e9fff-cc0f-46ab-97fd-e56a1e1618a9) | ![Gradient](https://github.com/user-attachments/assets/04d10e9f-1303-4fdc-acda-83dd18fbaf85) | ![Transform](https://github.com/user-attachments/assets/d93dd1f6-9204-4687-9e90-ee8d11312a8b) |

### Paths & Text

| Motion Path | Text Effects | Variations |
|:-----------:|:------------:|:----------:|
| ![Path](https://github.com/user-attachments/assets/aa2fc751-36fb-4c7b-aae7-e2bac04b5f45) | ![Text](https://github.com/user-attachments/assets/b389a9f3-89a6-4e5f-b632-74acc8dea3b6) | ![Variations](https://github.com/user-attachments/assets/d660b2a8-78a1-4d94-8bb8-8a9632127e64) |

### Procedural & Integration

| Noise | ImGui Widgets | ImDrawList |
|:-----:|:-------------:|:----------:|
| ![Noise](https://github.com/user-attachments/assets/8a644f6a-4516-4246-9d80-41a2ee036ea5) | ![ImGui](https://github.com/user-attachments/assets/f6cdb73f-2712-4b7e-8f27-5cbfb884b7ce) | ![DrawList](https://github.com/user-attachments/assets/c22f0855-4853-474d-b0d7-e1191e9d4789) |

### Additional Examples

| Oscillator Waves | Transform Layers |
|:----------------:|:----------------:|
| ![Waves2](https://github.com/user-attachments/assets/2a9aa767-6886-4737-8b90-9bee2792a225) | ![Transform2](https://github.com/user-attachments/assets/62f67980-94d5-48b4-ba01-483e960ada89) |
