#include "sfpch.h"
#include "openGLVertexArray.h"

SF::OpenGLVertexArray::OpenGLVertexArray() {

	glGenVertexArrays(1, &(this->m_ID));

}

SF::OpenGLVertexArray::~OpenGLVertexArray()
{

	for (const auto buffer : this->m_VertexBuffers)
	{
		delete buffer;
	}

	glDeleteVertexArrays(1, &(this->m_ID));

}

void SF::OpenGLVertexArray::bind() const {

	glBindVertexArray(this->m_ID);

}

void SF::OpenGLVertexArray::unbind() const {

	glBindVertexArray(0);

}
