#include "runtime.h"
#include "context3d.h"

struct ITouchListenerInterface{
	void (jfcc *onTouchBoundToMouse) (void* thisobj, jfint touchIndex);
	void (jfcc *onTouchBegin) (void* thisobj, jfint touchIndex, double x, double y);
	void (jfcc *onTouchEnd) (void* thisobj, jfint touchIndex, double x, double y);
	void (jfcc *onTouchMove) (void* thisobj, jfint touchIndex, double oldX, double oldY, double newX, double newY);
	void (jfcc *onTouchPassiveMove) (void* thisobj, jfint touchIndex, double oldX, double oldY, double newX, double newY);
	void (jfcc *onTouchCancel) (void* thisobj, jfint touchIndex);
};

struct ISceneInterface{
	void (jfcc *acquireContext) (void* thisobj, Context3DInterface* context3DInterface, void* context3DObject);
	ITouchListenerInterface* (jfcc *requestTouchListener) (void* thisobj, void** object);
	void (jfcc *update)(void* thisobj);
	void (jfcc *render)(void* render);
};