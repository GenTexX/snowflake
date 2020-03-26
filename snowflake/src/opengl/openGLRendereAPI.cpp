#include "sfpch.h"
#include "openGLRendereAPI.h"

SF::OpenGLRendererAPI::OpenGLRendererAPI()
{
}

SF::OpenGLRendererAPI::~OpenGLRendererAPI()
{
}

inline void SF::OpenGLRendererAPI::drawIndexed(const VertexArray* vao) {

	vao->bind();
	glDrawElements(GL_TRIANGLES, vao->getIndexBuffer()->getSize(), GL_UNSIGNED_INT, nullptr);

}


