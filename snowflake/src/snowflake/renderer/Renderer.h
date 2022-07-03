#pragma once
#include "vertexArray.h"
#include "camera.h"
#include "rendererAPI.h"
#include "texture.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "snowflake/scene/scene.h"

namespace SF {

	class Renderer
	{

	private:
		static RendererAPI* s_Instance;

		static void drawIndexed(const Ref<VertexArray> vao);

	public:
		static void init();

		static void drawScene(Ref<Scene> scene);

		static void beginScene(OrthographicCamera& camera);
		static void endScene();

		static void submit(const Ref<VertexArray> vao);
		static void drawQuad(glm::vec2& position = glm::vec2(0.0f, 0.0f), glm::vec2& size = glm::vec2(1.0f, 1.0f), float rotation = 0.0f, glm::vec4& color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		static void drawQuad(glm::vec2& position = glm::vec2(0.0f, 0.0f), glm::vec2& size = glm::vec2(1.0f, 1.0f), float rotation = 0.0f, Ref<Texture> texture = nullptr);

	};



}