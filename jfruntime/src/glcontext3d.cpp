#include <glcontext3d.h>
#include <gl/GLEW.h>
#include <gl/GL.h>
#include <intrinsics.h>

namespace gl{
	ObjectHeader GLContext3DHeader;

	struct Color{
		double r, g, b, a;

		Color()
			: r(0)
			, g(0)
			, b(0)
			, a(0){
		}

		Color(double r, double g, double b, double a)
			: r(r)
			, g(g)
			, b(b)
			, a(a){
		}
	};

	static ObjectHeader GLIndexBufferObjectHeader;
	struct GLIndexBufferObject{
		const ObjectHeader* objectHeader;
		GLuint name;
		size_t indexCount;
		bool uploaded;
		bool isStatic;
		JFFinalizer<GLIndexBufferObject>* finalizer;

		GLIndexBufferObject(bool isStatic, size_t indexCount)
			: objectHeader(&GLIndexBufferObjectHeader)
			, name(0)
			, isStatic(isStatic)
			, indexCount(indexCount)
			, uploaded(false)
			, finalizer(nullptr){
		}

		static void jfcc Finalize(GLIndexBufferObject* buffer){
			if ( buffer->name ){
				glDeleteBuffers(1, &buffer->name);
			}
		}
	};
	void jfcc IndexBufferUpload(void* thisobj, jfint firstIndex, jfint indexCount, jfint size, void* data){
		GLIndexBufferObject* indexBuffer = (GLIndexBufferObject*)thisobj;
		if ( firstIndex < 0 ){
			__jf_warning("index buffer upload with negative index");
			return;
		}
		if ( indexCount < 0 ){
			__jf_warning("index buffer upload with negative count");
			return;
		}
		if ( indexBuffer->indexCount <= firstIndex || indexBuffer->indexCount - firstIndex < indexCount ){
			__jf_warning("index buffer upload out of range");
			return;
		}
		size_t uploadSize = size;
		if ( uploadSize < sizeof(unsigned short) * indexCount ){
			__jf_warning("index buffer upload: not enough data");
			return;
		}
		uploadSize = sizeof(unsigned short) * indexCount;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->name);
		if ( uploadSize == sizeof(unsigned short) * indexBuffer->indexCount ){
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, uploadSize, data, indexBuffer->isStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW); 
			indexBuffer->uploaded = true;
		}else{
			if ( !indexBuffer->uploaded ){
				__jf_warning("index buffer upload: uploading part of the uncomplited buffer");
				return;
			}
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, firstIndex * sizeof(unsigned short), uploadSize, data);
		}
	}
	static IndexBufferInterface GLIndexBufferInterface = {IndexBufferUpload};

	static ObjectHeader GLVertexBufferObjectHeader;
	struct GLVertexBufferObject{
		const ObjectHeader* objectHeader;
		GLuint name;
		size_t vertexCount;
		size_t bytesPerVertex;
		bool uploaded;
		bool isStatic;
		JFFinalizer<GLVertexBufferObject>* finalizer;
		
		GLVertexBufferObject(bool isStatic, size_t vertexCount, size_t bytesPerVertex)
			: objectHeader(&GLVertexBufferObjectHeader)
			, name(0)
			, isStatic(isStatic)
			, vertexCount(vertexCount)
			, bytesPerVertex(bytesPerVertex)
			, uploaded(false)
			, finalizer(nullptr)
			{
		}

		static void jfcc Finalize(GLVertexBufferObject* buffer){
			if ( buffer->name ){
				glDeleteBuffers(1, &buffer->name);
			}
		}
	};

	void jfcc VertexBufferUpload(void* thisobj, jfint firstVertex, jfint vertexCount, jfint size, void* data){
		GLVertexBufferObject* vertexBufer = (GLVertexBufferObject*)thisobj;
		if ( firstVertex < 0 ){
			__jf_warning("vertex buffer upload with negative index");
			return;
		}
		if ( vertexCount < 0 ){
			__jf_warning("vertex buffer upload with negative count");
			return;
		}
		if ( vertexBufer->vertexCount <= firstVertex || vertexBufer->vertexCount - firstVertex < vertexCount ){
			__jf_warning("vertex buffer upload out of range");
			return;
		}
		size_t uploadSize = size;
		if ( uploadSize < vertexBufer->bytesPerVertex * vertexCount ){
			__jf_warning("vertex buffer upload: not enough data");
			return;
		}
		uploadSize = vertexBufer->bytesPerVertex * vertexCount;
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufer->name);
		if ( uploadSize == vertexBufer->bytesPerVertex * vertexBufer->vertexCount ){
			glBufferData(GL_ARRAY_BUFFER, uploadSize, data, vertexBufer->isStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW); 
			vertexBufer->uploaded = true;
		}else{
			if ( !vertexBufer->uploaded ){
				__jf_warning("vertex buffer upload: uploading part of the uncomplited buffer");
				return;
			}
			glBufferSubData(GL_ARRAY_BUFFER, firstVertex * vertexBufer->bytesPerVertex, uploadSize, data);
		}
	}
	static VertexBufferInterface GLVertexBufferInterface = {VertexBufferUpload};

	struct GLContext3DObject{
		ObjectHeader* objectHeader;
		Color clearColor;
		double clearDepth;
		jfint clearStencil;
	};
	static GLContext3DObject contextObjectInstance;
	
	void* GetContext3DObject(){
		static bool initialized = false;
		if ( !initialized ){
			contextObjectInstance.objectHeader = &GLContext3DHeader;
			contextObjectInstance.clearColor = Color(0, 0, 0, 0);
			contextObjectInstance.clearDepth = 0;
			contextObjectInstance.clearStencil = 0;
			initialized = true;
		}	
		return &contextObjectInstance;
	}

	void jfcc setClearColor(void* thisobj, double r, double g, double b, double a){
		GLContext3DObject* context = (GLContext3DObject*)thisobj;
		context->clearColor.r = r;
		context->clearColor.g = g;
		context->clearColor.b = b;
		context->clearColor.a = a;
		glClearColor((GLclampf)r, (GLclampf)g, (GLclampf)b, (GLclampf)a);
	}

	void jfcc setClearDepth(void* thisobj, double depth){
		GLContext3DObject* context = (GLContext3DObject*)thisobj;
		context->clearDepth = depth;
		glClearDepth(depth);
	}

	void jfcc setClearStencil(void* thisobj, jfint stencil){
		GLContext3DObject* context = (GLContext3DObject*)thisobj;
		context->clearStencil = stencil;
		glClearStencil(stencil);
	}

	void jfcc clear(void* thisobj, bool color, bool depth, bool stencil){
		GLContext3DObject* context = (GLContext3DObject*)thisobj;
		GLbitfield clearMask = 0;
		if ( color ){
			clearMask |= GL_COLOR_BUFFER_BIT;
		}
		if ( depth ){
			clearMask |= GL_DEPTH_BUFFER_BIT;
		}
		if ( stencil ){
			clearMask |= GL_STENCIL_BUFFER_BIT;
		}
		glClear(clearMask);
	}

	VertexBufferInterface* jfcc createVertexBuffer(void** vertexBufferObject, void* thisobj, bool isStatic, jfint bytesPerVertex, jfint vertexCount){
		if ( bytesPerVertex <= 0 ){
			__jf_fatal_error("vertex buffer bytesPerVertex is non-positive");
		}
		if ( vertexCount <= 0 ){
			__jf_fatal_error("vertex buffer vertexCount is non-positive");
		}
		if ( bytesPerVertex > VertexBufferInterface::MAX_BYTES_PER_VERTEX ){
			__jf_fatal_error("vertex buffer bytesPerVertex is too large");
		}
		if ( vertexCount > VertexBufferInterface::MAX_VERTEX_COUNT ){
			__jf_fatal_error("vertex buffer vertexCount is too large");
		}
		
		GLVertexBufferObject* vertexBuffer = jfnew(GLVertexBufferObject)(isStatic, vertexCount, bytesPerVertex);
		vertexBuffer->finalizer = jfnewfinalizer(GLVertexBufferObject)(vertexBuffer);
		GLuint bufferName;
		glGenBuffers(1, &bufferName);
		vertexBuffer->name = bufferName;
		if ( !bufferName ){
			__jf_fatal_error("can't allocate vertex buffer");
		}

		*vertexBufferObject = vertexBuffer;
		return &GLVertexBufferInterface;
	}

	IndexBufferInterface* jfcc createIndexBuffer(void** indexBufferObject, void* thisobj, bool isStatic, jfint indexCount){
		if ( indexCount <= 0 ){
			__jf_fatal_error("index buffer indexCount is non-positive");
		}
		if ( indexCount > IndexBufferInterface::MAX_INDEX_COUNT ){
			__jf_fatal_error("index buffer indexCount is too large");
		}
		
		GLIndexBufferObject* indexBuffer = jfnew(GLIndexBufferObject)(isStatic, indexCount);
		indexBuffer->finalizer = jfnewfinalizer(GLIndexBufferObject)(indexBuffer);
		GLuint bufferName;
		glGenBuffers(1, &bufferName);
		indexBuffer->name = bufferName;
		if ( !bufferName ){
			__jf_fatal_error("can't allocate index buffer");
		}

		*indexBufferObject = indexBuffer;
		return &GLIndexBufferInterface;
	}
}

Context3DInterface GLContext3DInterface = {
		gl::setClearColor,
		gl::setClearDepth,
		gl::setClearStencil,
		gl::clear,
		gl::createVertexBuffer,
		gl::createIndexBuffer
	};

