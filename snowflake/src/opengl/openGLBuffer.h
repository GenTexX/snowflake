#pragma once
#include <GL/glew.h>
#include <snowflake/renderer/buffer.h>
#include <EventSys.h>

namespace SF {

	class OpenGLVertexBuffer : VertexBuffer {

	private:
		uint32_t m_ID;
		BufferLayout m_Layout;

	public:
		OpenGLVertexBuffer(float* data, uint32_t size);

		~OpenGLVertexBuffer();
	
		virtual void bind() const override;
		virtual void unbind() const override;

		virtual const BufferLayout& getLayout() const;
		virtual void setLayout(const BufferLayout& layout);

		virtual float* map() const override;
		virtual void unmap() const override;
		
	};

	class OpenGLIndexBuffer : IndexBuffer {

	private:
		uint32_t m_ID;

	public:
		OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* data, uint32_t size);
		~OpenGLIndexBuffer();

		static OpenGLIndexBuffer* create(uint32_t* data, uint32_t size);
		
		virtual void bind() const override;
		virtual void unbind() const override;

		virtual uint32_t* map() const override;
		virtual void unmap() const override;
	};

}