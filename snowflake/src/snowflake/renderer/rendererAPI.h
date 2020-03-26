#pragma once

#include "snowflake/core/core.h"
#include "vertexArray.h"
#include "snowflake/core/core.h"

namespace SF {
	enum class RendererAPIEnum
	{
		OpenGL
	};

	class RendererAPI
	{

	private:

	public:
		RendererAPI();
		~RendererAPI();

		virtual inline void drawIndexed(const VertexArray* vao) = 0;

		static RendererAPIEnum getRendererAPI() { return RendererAPIEnum::OpenGL; }

	};

}