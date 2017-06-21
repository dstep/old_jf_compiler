#pragma once
#include "runtime.h"

struct VertexBufferInterface{
	static const size_t MAX_BYTES_PER_VERTEX = 1024;
	static const size_t MAX_VERTEX_COUNT = 65536;

	void (jfcc* upload) (void* thisobj, jfint firstVertex, jfint vertexCount, jfint size, void* data);
};

struct IndexBufferInterface{
	static const size_t MAX_INDEX_COUNT = 65536;
	void (jfcc* upload) (void* thisobj, jfint firstIndex, jfint indexCount, jfint size, void* data);
};

struct ShaderInterface{
	void (jfcc* upload)(void* thisobj, jfstring source);
	bool (jfcc* compile)(void* thisobj, jfstring* error);
	bool (jfcc* isCompleted)(void* thisobj);
};

struct VertexShaderInterface: public ShaderInterface{
};

struct FragmentShaderInterface: public ShaderInterface{
};

struct ProgramInterface: public ShaderInterface{
	bool (jfcc* link)(void* thisobj, jfstring* error);
	bool (jfcc* isCompleted)(void* thisobj);
	
	bool (jfcc* getVertexStreamIndex)(void* thisobj, jfint* index, jfstring name);
	bool (jfcc* getSamplerIndex)(void* thisobj, jfint* index, jfstring name);
	bool (jfcc* getConstantIndex)(void* thisobj, jfint* index, jfstring name);
};

struct Context3DInterface{	
	void (jfcc *setClearColor) (void* thisobj, double r, double g, double b, double a);
	void (jfcc *setClearDepth) (void* thisobj, double depth);
	void (jfcc *setClearStencil) (void* thisobj, jfint stencil);
	void (jfcc *clear) (void* thisobj, bool color, bool depth, bool stencil);

	VertexBufferInterface* (jfcc *createVertexBuffer) (void** vertexBufferObject, void* thisobj, bool isStatic, jfint bytesPerVertex, jfint vertexCount);
	IndexBufferInterface* (jfcc *createIndexBuffer) (void** indexBufferObject, void* thisobj, bool isStatic, jfint indexCount);

	/*
	method createVertexShader():VertexShader
	method createFragmentShader():FragmentShader
	method createProgram(VertexShader, FragmentShader):Program
	method createTexture(TextureFormat, width height:int):Texture
	
	method setVertexStream(index:int, vertexBuffer:VertexBuffer, VertexStreamFormat, bufferOffset:int)
	method unsetVertexStream(index:int)
	method setSampler(index:int, Texture)
	method unsetSampler(index:int)
	method setProgramConstant(index:int, x y z w:double)
	
	method setProgram(Program)
	method drawTriangles(indexBuffer:IndexBuffer, firstIndex:int, trianglesCount:int)
	*/
};