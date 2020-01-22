#pragma once
#include <GL/glew.h>
#include <snowflake/renderer/buffer.h>

namespace SF {

	class OpenGLVertexBuffer : VertexBuffer {

	private:
		uint32_t m_ID;

	public:
		OpenGLVertexBuffer(float* data, uint32_t size);

		~OpenGLVertexBuffer();

		static OpenGLVertexBuffer* create(float* data, uint32_t size);
		
		virtual void bind() const override;
		virtual void unbind() const override;

		virtual float* map() const override;
		virtual void unmap() const override;

	};

	class OpenGLIndexBuffer : IndexBuffer {

	private:
		uint32_t m_ID;

		OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* data, uint32_t size);

	public:
		~OpenGLIndexBuffer();

		static OpenGLIndexBuffer* create(uint32_t* data, uint32_t size);
		
		virtual void bind() const override;
		virtual void unbind() const override;

		virtual uint32_t* map() const override;
		virtual void unmap() const override;
	};

}