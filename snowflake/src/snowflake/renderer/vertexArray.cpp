#include "sfpch.h"
#include "vertexArray.h"
#include "opengl/openGLVertexArray.h"

namespace SF {

	VertexArray* VertexArray::create()
	{
		switch (Renderer::getRendererAPI())
		{
		case RendererAPI::OpenGL:
			return (VertexArray*) new OpenGLVertexArray();
		default:
			break;
		}

		assert("RenderAPI not supported");
		return nullptr;
	}

}
