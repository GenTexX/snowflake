#pragma once
#include "vertexArray.h"
#include "camera.h"
#include "rendererAPI.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

namespace SF {



	class Renderer
	{

	private:
		static RendererAPI* s_Instance;

		static void drawIndexed(const Ref<VertexArray> vao);

	public:
		static void init();

		static void beginScene(OrthographicCamera& camera);
		static void endScene();

		static void submit(const Ref<VertexArray> vao);
		static void drawQuad(glm::vec2& position, glm::vec2& size, float rotation);


	};



}