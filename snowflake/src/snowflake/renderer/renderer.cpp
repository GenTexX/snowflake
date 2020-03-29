#include "sfpch.h"
#include "renderer.h"
#include "opengl/openGLRendereAPI.h"
#include "shader.h"


namespace SF {

	struct RenderData {

		SF::Ref<SF::VertexArray> vao;
		SF::Ref<SF::VertexBuffer> vertexBuffer;
		SF::Ref<SF::IndexBuffer> indexBuffer;
		Ref<Shader> shader;

	};

	static RenderData s_QuadRenderData;

	RendererAPI* Renderer::s_Instance = new OpenGLRendererAPI();

	static OrthographicCamera s_Camera;

	void Renderer::drawIndexed(const Ref<VertexArray> vao) {

		s_Instance->drawIndexed(vao);

	}

	void Renderer::init() {

		s_QuadRenderData.shader = SF::Shader::create("src/basic.shader");

		s_QuadRenderData.shader->readFile();
		s_QuadRenderData.shader->compile();

		float verts[4 * 4] = {

			/*######## COORDS ########*/
			-0.5f,	-0.5f,  0.0f,  1.0f,
			 0.5f,	-0.5f,  0.0f,  1.0f,
			 0.5f,	 0.5f,  0.0f,  1.0f,
			-0.5f,	 0.5f,  0.0f,  1.0f

		};

		GLuint ind[6] = { 0, 1, 2, 0, 2, 3 };

		s_QuadRenderData.vertexBuffer = SF::VertexBuffer::create(verts, sizeof(verts));
		s_QuadRenderData.indexBuffer = SF::IndexBuffer::create(ind, sizeof(ind));

		SF::BufferLayout bl = { {SF::BufferElementType::Float4, "VertexCoordinates"} };

		s_QuadRenderData.vertexBuffer->setLayout(bl);

		s_QuadRenderData.vao = SF::VertexArray::create();
		s_QuadRenderData.vao->addVertexBuffer(s_QuadRenderData.vertexBuffer);
		s_QuadRenderData.vao->setIndexBuffer(s_QuadRenderData.indexBuffer);

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

		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(position, 1.0f)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)) *
			glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));

		s_QuadRenderData.shader->bind();

		s_QuadRenderData.shader->setMat4("u_View", s_Camera.getViewMatrix());
		s_QuadRenderData.shader->setMat4("u_Projection", s_Camera.getProjectionMatrix());
		s_QuadRenderData.shader->setMat4("u_Model", model);

		Renderer::submit(s_QuadRenderData.vao);

	}

}