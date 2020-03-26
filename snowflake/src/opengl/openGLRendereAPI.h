#pragma once

#include "snowflake/renderer/rendererAPI.h"

namespace SF {

	class OpenGLRendererAPI : public RendererAPI
	{

	private:


	public:
		OpenGLRendererAPI();
		~OpenGLRendererAPI();

		inline void drawIndexed(const VertexArray* vao) override;

	};

}