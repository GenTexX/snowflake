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

void SF::OpenGLVertexArray::addVertexBuffer(VertexBuffer* vertexBuffer) {

	this->bind();
	vertexBuffer->bind();

	uint32_t index = 0;
	const auto& layout = vertexBuffer->getLayout();
	for (const auto element : layout) {

		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, element.getComponentSize(), bufferElementTypeToGLenum(element.m_Type), element.m_Normalized, layout.getStride(), (void*)(element.m_Offset));
		index++;
	}

	this->m_VertexBuffers.push_back(vertexBuffer);

}

void SF::OpenGLVertexArray::setIndexBuffer(IndexBuffer* indexBuffer) {

	this->bind();
	indexBuffer->bind();

	this->m_IndexBuffer = indexBuffer;

}
