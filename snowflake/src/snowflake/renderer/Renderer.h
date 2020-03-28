#pragma once
#include "vertexArray.h"
#include "rendererAPI.h"

namespace SF {



	class Renderer
	{

	private:
		static RendererAPI* s_Instance;

		static void drawIndexed(const Ref<VertexArray> vao);

	public:
		static void beginScene();
		static void endScene();

		static void submit(const Ref<VertexArray> vao);


	};



}