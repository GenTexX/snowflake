#pragma once

namespace SF {

	enum class RendererAPI
	{
		OpenGL
	};
	class Renderer
	{
	public:

		static RendererAPI getRendererAPI() { return RendererAPI::OpenGL; }

	};



}