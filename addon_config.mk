meta:
	ADDON_NAME = ofxImAnim
	ADDON_DESCRIPTION = use ImGui ImAnim inside openFrameworks
	ADDON_AUTHOR = Dan Rosser
	ADDON_TAGS = "gui" "imgui" "animation" "ofxImGui"
	ADDON_URL = https://github.com/Danoli3/ofxImAnim     # ← change to your actual repo

common:
	# Dependencies
	ADDON_DEPENDENCIES = ofxImGui

	# Include paths
	ADDON_INCLUDES = src libs/ImAnim

	# Source files (explicit so it always picks up the wrapper + ImAnim lib)
	ADDON_SOURCES = src/ofxImAnim.cpp libs/ImAnim/im_anim.cpp

	# No special flags or frameworks needed — ImAnim is pure header+cpp + ImGui
	# ADDON_CFLAGS =
	# ADDON_CPPFLAGS =
	# ADDON_LDFLAGS =
	# ADDON_FRAMEWORKS =

	# If you ever add data files or extra libs later, put them here
	# ADDON_DATA =

# Platform-specific sections (you can leave them empty unless you need something special)
linux64:
linux:
linuxarmv6l:
linuxarmv7l:
msys2:
android/armeabi:
android/armeabi-v7a:
osx:
ios:
tvos:
