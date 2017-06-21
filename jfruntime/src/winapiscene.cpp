#include <winapiscene.h>
#include <intrinsics.h>
#include <glcontext3d.h>
#include <gl/GLEW.h>
#include <Windowsx.h>

namespace win{
	ObjectHeader SceneContainerHeader;

	static LRESULT CALLBACK SceneContainerWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){
		SceneContainer* sceneContainer = (SceneContainer*)GetWindowLongPtrW(hWnd, GWLP_USERDATA);
		switch ( msg ){
		case WM_MOUSEMOVE:{
			int xPos = GET_X_LPARAM(lParam);
			int yPos = GET_Y_LPARAM(lParam);
			if ( sceneContainer->mouseDown ){
				sceneContainer->iTouchListenerInterface->onTouchMove(sceneContainer->iSceneObject, 0, sceneContainer->lastMouseX, sceneContainer->lastMouseY, xPos, yPos);
			}else{
				sceneContainer->iTouchListenerInterface->onTouchPassiveMove(sceneContainer->iSceneObject, 0, sceneContainer->lastMouseX, sceneContainer->lastMouseY, xPos, yPos);
			}
			sceneContainer->lastMouseX = xPos;
			sceneContainer->lastMouseY = yPos;
		}break;
		case WM_LBUTTONDOWN:{
			int xPos = GET_X_LPARAM(lParam);
			int yPos = GET_Y_LPARAM(lParam);
			sceneContainer->mouseDown = true;
			sceneContainer->lastMouseX = xPos;
			sceneContainer->lastMouseY = yPos;
			sceneContainer->iTouchListenerInterface->onTouchBegin(sceneContainer->iSceneObject, 0, xPos, yPos);
		}break;
		case WM_LBUTTONUP:{
			int xPos = GET_X_LPARAM(lParam);
			int yPos = GET_Y_LPARAM(lParam);
			sceneContainer->mouseDown = false;
			sceneContainer->lastMouseX = xPos;
			sceneContainer->lastMouseY = yPos;
			sceneContainer->iTouchListenerInterface->onTouchEnd(sceneContainer->iSceneObject, 0, xPos, yPos);
		}break;
		case WM_TIMER:{
			sceneContainer->iSceneInterface->update(sceneContainer->iSceneObject);
			RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);
			return 0;
		}break;
		case WM_PAINT:{
			PAINTSTRUCT paintStruct;
			BeginPaint(hWnd, &paintStruct);
			sceneContainer->iSceneInterface->render(sceneContainer->iSceneObject);
			SwapBuffers(GetWindowDC(hWnd));
			EndPaint(hWnd, &paintStruct);
			return 1;
		}break;
		}
		return DefWindowProcW(hWnd, msg, wParam, lParam);
	}

	SceneContainer* CreateSceneContainer(HINSTANCE applicationInstance, void* iSceneObject, ISceneInterface* iSceneInterface, int width, int height){
		SceneContainer* sceneContainer = jfnew(SceneContainer);
		sceneContainer->header = &SceneContainerHeader;
		sceneContainer->iSceneObject = iSceneObject;
		sceneContainer->iSceneInterface = iSceneInterface;

		sceneContainer->iTouchListenerInterface = iSceneInterface->requestTouchListener(iSceneObject, &sceneContainer->iTouchListenerObject); 

		sceneContainer->iTouchListenerInterface->onTouchBoundToMouse(sceneContainer->iTouchListenerObject, 0);

		sceneContainer->lastMouseX = 0;
		sceneContainer->lastMouseY = 0;
		sceneContainer->mouseDown = false;

		WNDCLASSEXW windowClass;
		::memset(&windowClass, 0, sizeof(windowClass));
		windowClass.cbSize = sizeof(windowClass);
		windowClass.lpszClassName = L"JFScene";
		windowClass.lpfnWndProc = SceneContainerWindowProc;
		windowClass.hInstance = applicationInstance;
		windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		windowClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
		if ( !RegisterClassExW(&windowClass) ){
			__jf_fatal_error("Can't register window class");
		}

		HWND windowHandle = CreateWindowW
			(
				L"JFScene", 
				L"jf scene", 
				WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME, 
				CW_USEDEFAULT, 
				CW_USEDEFAULT,
				width,
				height,
				NULL,
				NULL,
				applicationInstance,
				sceneContainer
			);

		if ( !windowHandle ){
			__jf_fatal_error("Can't create window");
		}

		SetWindowLongPtrW(windowHandle, GWLP_USERDATA, (LONG_PTR)sceneContainer);

		PIXELFORMATDESCRIPTOR pfd;
		int pixelFormat;
		::memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 32;
		pfd.cDepthBits = 16;
		pfd.cStencilBits = 8;
		pfd.iLayerType = PFD_MAIN_PLANE;

		HDC hdc = GetDC(windowHandle);
		pixelFormat = ChoosePixelFormat(hdc, &pfd);
		if ( !SetPixelFormat(hdc,pixelFormat, &pfd) ){
			__jf_fatal_error("Can't set pixel format");
		}
		wglMakeCurrent(hdc, wglCreateContext(hdc));
		if ( !wglGetCurrentContext() ){
			__jf_fatal_error("Can't create opengl context");
		}
		
		GLenum glewInitResult = glewInit();
		if ( glewInitResult != GLEW_OK ){
			__jf_fatal_error((const char*)glewGetErrorString(glewInitResult));
		}

		sceneContainer->windowHandle = windowHandle;

		ShowWindow(windowHandle, SW_SHOW);

		SetTimer(windowHandle, NULL, (UINT)(1000.0 / 60.0), NULL);

		sceneContainer->iSceneInterface->acquireContext(sceneContainer->iSceneObject, &GLContext3DInterface, gl::GetContext3DObject());

		return sceneContainer;
	}
}

static bool applicationSceneExists = false;

JFAPI
void _StartApplicationScene(ISceneInterface* iSceneInterface, void* iSceneObject){
	if ( applicationSceneExists ){
		__jf_fatal_error("Application scene already exists");
	}
	applicationSceneExists = true;
	
	HINSTANCE applicationInstance = GetModuleHandleW(NULL);
	win::SceneContainer* sceneContainer = win::CreateSceneContainer(applicationInstance, iSceneObject, iSceneInterface, 1024, 768);
	
	BOOL bRet;
	MSG msg;
	while( (bRet = GetMessageW(&msg, sceneContainer->windowHandle, 0, 0) ) != 0)
	{ 
		if (bRet == -1)
		{
			return;
		}
		else
		{
			TranslateMessage(&msg); 
			DispatchMessageW(&msg); 
		}
	}
}