#include "sfpch.h"
#include "texture.h"
#include "rendererAPI.h"
#include "opengl/openGLTexture.h"

namespace SF {

	Texture::~Texture() {



	}

	Ref<Texture> Texture::create(const std::string& path) {


		switch (RendererAPI::getRendererAPI())
		{

		case RendererAPIEnum::OpenGL:
			return createRef<OpenGLTexture>(path);
			break;
		default:
			break;
		}

		assert("RenderAPI not supported");
		return nullptr;

	}

}