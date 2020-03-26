#include "sfpch.h"
#include "vertexArray.h"
#include "opengl/openGLVertexArray.h"
#include "rendererAPI.h"

namespace SF {

	VertexArray* VertexArray::create()
	{
		switch (RendererAPI::getRendererAPI())
		{
		case RendererAPIEnum::OpenGL:
			return (VertexArray*) new OpenGLVertexArray();
		default:
			break;
		}

		assert("RenderAPI not supported");
		return nullptr;
	}

}
