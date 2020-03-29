#include "sfpch.h"
#include "renderer.h"
#include "opengl/openGLRendereAPI.h"
#include "shader.h"


namespace SF {

	RendererAPI* Renderer::s_Instance = new OpenGLRendererAPI();

	static Ref<Shader> s_Shader;
	static OrthographicCamera s_Camera;

	void Renderer::drawIndexed(const Ref<VertexArray> vao) {
	
		s_Instance->drawIndexed(vao);
	
	}
	
	void Renderer::init() {

		s_Shader = SF::Shader::create("src/basic.shader");

		s_Shader->readFile();
		s_Shader->compile();

	}

	void Renderer::beginScene(OrthographicCamera& camera) {
	
		s_Camera = camera;
	
	}

	void Renderer::endScene() {

	
	}

	void Renderer::submit(const Ref<VertexArray> vao) {
	
		drawIndexed(vao);
	
	}

	void Renderer::drawQuad(glm::vec2& position, glm::vec2& size, float rotation) {

		float verts[4 * 4] = {

			/*######## COORDS ########*/
			-0.5f,	-0.5f,  0.0f,  1.0f,
			 0.5f,	-0.5f,  0.0f,  1.0f,
			 0.5f,	 0.5f,  0.0f,  1.0f,
			-0.5f,	 0.5f,  0.0f,  1.0f

		};

		GLuint ind[6] = { 0, 1, 2, 0, 2, 3 };

		SF::Ref<SF::VertexBuffer> vertexBuffer = SF::VertexBuffer::create(verts, sizeof(verts));
		SF::Ref<SF::IndexBuffer> indexBuffer = SF::IndexBuffer::create(ind, sizeof(ind));
		SF_ERROR(glGetError());

		SF::BufferLayout bl = { {SF::BufferElementType::Float4, "VertexCoordinates"} };

		vertexBuffer->setLayout(bl);
		SF_ERROR(glGetError());

		SF::Ref<SF::VertexArray> vao = SF::VertexArray::create();
		vao->addVertexBuffer(vertexBuffer);
		vao->setIndexBuffer(indexBuffer);
		SF_ERROR(glGetError());

		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(position, 1.0f)) * 
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)) * 
			glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));

		s_Shader->bind();
		s_Shader->setMat4("u_View", s_Camera.getViewMatrix());
		s_Shader->setMat4("u_Projection", s_Camera.getProjectionMatrix());
		s_Shader->setMat4("u_Model", model);

		Renderer::submit(vao);

	}

}