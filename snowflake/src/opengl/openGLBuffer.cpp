#include <sfpch.h>
#include "openGLBuffer.h"

namespace SF {

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* data, uint32_t size) {

		this->m_Size = size;

		glGenBuffers(1, &(this->m_ID));

		glBindBuffer(GL_ARRAY_BUFFER, this->m_ID);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer() {

		glDeleteBuffers(1, &(this->m_ID));

	}

	void OpenGLVertexBuffer::bind() const {

		glBindBuffer(GL_ARRAY_BUFFER, this->m_ID);

	}

	void OpenGLVertexBuffer::unbind() const {


		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}

	const BufferLayout& OpenGLVertexBuffer::getLayout() const
	{
		return this->m_Layout;
	}

	void OpenGLVertexBuffer::setLayout(const BufferLayout& layout)
	{

		this->m_Layout = layout;

	}

	float* OpenGLVertexBuffer::map() const {

		return (float*) glMapBuffer(GL_ARRAY_BUFFER, this->m_ID);

	}

	void OpenGLVertexBuffer::unmap() const {

		glUnmapBuffer(GL_ARRAY_BUFFER);

	}



	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* data, uint32_t size) {

		this->m_Size = size;

		glCreateBuffers(1, &(this->m_ID));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer() {

		glDeleteBuffers(1, &(this->m_ID));

	}

	OpenGLIndexBuffer* OpenGLIndexBuffer::create(uint32_t* data, uint32_t size) {

		OpenGLIndexBuffer* buffer = new OpenGLIndexBuffer(data, size);

		return buffer;

	}

	void OpenGLIndexBuffer::bind() const {

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ID);
	}

	void OpenGLIndexBuffer::unbind() const {

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	uint32_t* OpenGLIndexBuffer::map() const {

		return (uint32_t*) glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ID);

	}

	void OpenGLIndexBuffer::unmap() const {

		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);

	}
}