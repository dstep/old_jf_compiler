#include "runtime.h"
#include "scene.h"

#define nominmax
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace win{
	extern ObjectHeader SceneContainerHeader;

	struct SceneContainer{
		ObjectHeader* header;
		HWND windowHandle;
		void* iSceneObject;
		ISceneInterface* iSceneInterface;

		bool mouseDown;
		double lastMouseX, lastMouseY;

		void* iTouchListenerObject;
		ITouchListenerInterface* iTouchListenerInterface;
	};
}

JFAPI
void _StartApplicationScene(ISceneInterface* iSceneInterface, void* iSceneObject);