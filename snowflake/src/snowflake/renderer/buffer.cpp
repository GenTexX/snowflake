#include <sfpch.h>
#include "buffer.h"
#include "opengl/openGLBuffer.h"
#include "rendererAPI.h"


namespace SF{

	VertexBuffer* VertexBuffer::create(float* data, uint32_t size) {

		switch (RendererAPI::getRendererAPI())
		{

		case RendererAPIEnum::OpenGL:
			return (VertexBuffer*) new OpenGLVertexBuffer(data, size);
			break;
		default:
			break;
		}

		assert("RenderAPI not supported");
		return nullptr;

	}

	IndexBuffer* IndexBuffer::create(uint32_t* data, uint32_t size) {

		switch (RendererAPI::getRendererAPI())
		{

		case RendererAPIEnum::OpenGL:
			return (IndexBuffer*) new OpenGLIndexBuffer(data, size);
			break;
		default:
			break;
		}

		assert("RenderAPI not supported");
		return nullptr;

	}

	Buffer::~Buffer()
	{



	}

	BufferElement::BufferElement(BufferElementType type, const std::string& name, const bool& normalized) :m_ElementName(name), m_Type(type), m_Normalized(normalized) {
	
		this->m_Size = getBufferElementTypeSize(this->m_Type);
		this->m_Offset = 0;

	}

}