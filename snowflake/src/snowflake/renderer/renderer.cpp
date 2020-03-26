#include "sfpch.h"
#include "renderer.h"
#include "opengl/openGLRendereAPI.h"

namespace SF {

	RendererAPI* Renderer::s_Instance = new OpenGLRendererAPI();

	void Renderer::drawIndexed(const VertexArray* vao) {
	
		s_Instance->drawIndexed(vao);
	
	}
	
	void Renderer::beginScene() {
	
	
	}

	void Renderer::endScene() {

	
	}

	void Renderer::submit(const VertexArray* vao) {
	
		drawIndexed(vao);
	
	}

}