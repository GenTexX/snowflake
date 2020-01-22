#include <sfpch.h>
#include "buffer.h"
#include "opengl/openGLBuffer.h"

namespace SF{
	VertexBuffer* VertexBuffer::create(float* data, uint32_t size) {

		return (VertexBuffer*) OpenGLVertexBuffer::create(data, size);

	}

}