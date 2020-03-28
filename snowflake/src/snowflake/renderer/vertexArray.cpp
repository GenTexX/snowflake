#include "sfpch.h"
#include "vertexArray.h"
#include "opengl/openGLVertexArray.h"
#include "rendererAPI.h"

namespace SF {

	Ref<VertexArray> VertexArray::create()
	{
		switch (RendererAPI::getRendererAPI())
		{
		case RendererAPIEnum::OpenGL:
			return createRef<OpenGLVertexArray>();
		default:
			break;
		}

		assert("RenderAPI not supported");
		return nullptr;
	}

}
