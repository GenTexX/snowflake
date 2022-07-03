#include "sfpch.h"
#include "renderer.h"
#include "opengl/openGLRendereAPI.h"
#include "shader.h"
#include "snowflake/scene/scene.h"
#include "snowflake/scene/sceneobjects/sceneObject.h"
#include "snowflake/scene/sceneobjects/cameraObject.h"
#include "snowflake/scene/sceneobjects/renderableObject.h"


namespace SF {

	struct RenderData {

		SF::Ref<SF::VertexArray> vao;
		SF::Ref<SF::VertexBuffer> vertexBuffer;
		SF::Ref<SF::IndexBuffer> indexBuffer;
		Ref<Shader> shader;

	};

	static RenderData s_ColoredQuadRenderData;
	static RenderData s_TexturedQuadRenderData;

	RendererAPI* Renderer::s_Instance = new OpenGLRendererAPI();

	static OrthographicCamera s_Camera;

	void Renderer::drawIndexed(const Ref<VertexArray> vao) {

		s_Instance->drawIndexed(vao);

	}

	void Renderer::init() {
		
			/************************************************/
			/*************** COLORED QUAD *******************/
			/************************************************/
		{
			s_ColoredQuadRenderData.shader = SF::Shader::create("src/basic_quad.shader");

			s_ColoredQuadRenderData.shader->readFile();
			s_ColoredQuadRenderData.shader->compile();

			float verts[4 * 4] = {

				/*######## COORDS ########*/
				-0.5f,	-0.5f,  0.0f,  1.0f,
				 0.5f,	-0.5f,  0.0f,  1.0f,
				 0.5f,	 0.5f,  0.0f,  1.0f,
				-0.5f,	 0.5f,  0.0f,  1.0f

			};

			GLuint ind[6] = { 0, 1, 2, 0, 2, 3 };

			s_ColoredQuadRenderData.vertexBuffer = SF::VertexBuffer::create(verts, sizeof(verts));
			s_ColoredQuadRenderData.indexBuffer = SF::IndexBuffer::create(ind, sizeof(ind));

			SF::BufferLayout bl = { {SF::BufferElementType::Float4, "VertexCoordinates"} };

			s_ColoredQuadRenderData.vertexBuffer->setLayout(bl);

			s_ColoredQuadRenderData.vao = SF::VertexArray::create();
			s_ColoredQuadRenderData.vao->addVertexBuffer(s_ColoredQuadRenderData.vertexBuffer);
			s_ColoredQuadRenderData.vao->setIndexBuffer(s_ColoredQuadRenderData.indexBuffer);
		}

		/************************************************/
		/*************** COLORED QUAD *******************/
		/************************************************/
		{
			s_TexturedQuadRenderData.shader = SF::Shader::create("src/basic_texquad.shader");

			s_TexturedQuadRenderData.shader->readFile();
			s_TexturedQuadRenderData.shader->compile();

			float verts[4 * 6] = {

				/*######## COORDS ########*/		/*##TEX COORDS ###*/
				-0.5f,	-0.5f,  0.0f,  1.0f,			 0.0f,  0.0f,
				 0.5f,	-0.5f,  0.0f,  1.0f,			1.0f,  0.0f,
				 0.5f,	 0.5f,  0.0f,  1.0f,			1.0f, 1.0f,
				-0.5f,	 0.5f,  0.0f,  1.0f,			 0.0f, 1.0f

			};

			GLuint ind[6] = { 0, 1, 2, 0, 2, 3 };

			s_TexturedQuadRenderData.vertexBuffer = SF::VertexBuffer::create(verts, sizeof(verts));
			s_TexturedQuadRenderData.indexBuffer = SF::IndexBuffer::create(ind, sizeof(ind));

			SF::BufferLayout bl = { {SF::BufferElementType::Float4, "VertexCoordinates"}, {SF::BufferElementType::Float2, "TextureCoordinates"} };

			s_TexturedQuadRenderData.vertexBuffer->setLayout(bl);

			s_TexturedQuadRenderData.vao = SF::VertexArray::create();
			s_TexturedQuadRenderData.vao->addVertexBuffer(s_TexturedQuadRenderData.vertexBuffer);
			s_TexturedQuadRenderData.vao->setIndexBuffer(s_TexturedQuadRenderData.indexBuffer);

		}
	}

	void Renderer::drawScene(Ref<Scene> scene) {

		Renderer::beginScene(scene->getCamera()->getCamera());

		for (auto sceneObject : *scene)	{
			switch (sceneObject->type())
			{

			case SceneObjectType::RENDERABLE_OBJECT:
			{
				Ref<RenderableObject> renderableObject = std::static_pointer_cast<RenderableObject>(sceneObject);
				switch (renderableObject->getRenderable().type())
				{
				case RenderableType::TEXTURED_QUAD:
				{
					TexturedQuad quad = static_cast<TexturedQuad&>(renderableObject->getRenderable());
					Renderer::drawQuad(glm::vec2(quad.getPosition()), glm::vec2(quad.getSize()), 0.0f, quad.getTexture());
					break;
				}
				case RenderableType::COLORED_QUAD:
					break;

				default:
					break;
				}

				break;
			}
			case SceneObjectType::CAMERA_OBJECT:
				break;

			default:
				break;
			}
		}

		Renderer::endScene();

	}

	void Renderer::beginScene(OrthographicCamera& camera) {

		s_Camera = camera;

	}

	void Renderer::endScene() {


	}

	void Renderer::submit(const Ref<VertexArray> vao) {

		drawIndexed(vao);

	}

	void Renderer::drawQuad(glm::vec2& position, glm::vec2& size, float rotation, glm::vec4& color) {

		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(position, 1.0f)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)) *
			glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));

		s_ColoredQuadRenderData.shader->bind();

		s_ColoredQuadRenderData.shader->setMat4("u_View", s_Camera.getViewMatrix());
		s_ColoredQuadRenderData.shader->setMat4("u_Projection", s_Camera.getProjectionMatrix());
		s_ColoredQuadRenderData.shader->setMat4("u_Model", model);

		s_ColoredQuadRenderData.shader->setFloat4("u_Color", color);

		Renderer::submit(s_ColoredQuadRenderData.vao);

	}

	void Renderer::drawQuad(glm::vec2& position, glm::vec2& size, float rotation, Ref<Texture> texture) {
	
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(position, 1.0f)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)) *
			glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));

		s_TexturedQuadRenderData.shader->bind();

		s_TexturedQuadRenderData.shader->setMat4("u_View", s_Camera.getViewMatrix());
		s_TexturedQuadRenderData.shader->setMat4("u_Projection", s_Camera.getProjectionMatrix());
		s_TexturedQuadRenderData.shader->setMat4("u_Model", model);

		texture->bind(0);
		s_TexturedQuadRenderData.shader->setInt("u_Texture", texture->getSlot());

		Renderer::submit(s_TexturedQuadRenderData.vao);

	}

}