#include "sfpch.h"
#include "texture.h"
#include "rendererAPI.h"
#include "opengl/openGLTexture.h"

namespace SF {

	std::unordered_map<std::string, Ref<Texture>> Texture::s_Textures = std::unordered_map<std::string, Ref<Texture>>();

	Texture::~Texture() {



	}

	int Texture::create(const std::string& path) {


		switch (RendererAPI::getRendererAPI())
		{

		case RendererAPIEnum::OpenGL:
			s_Textures.insert(std::pair<std::string, Ref<Texture>>(path, createRef<OpenGLTexture>(path)));
			return 0;
		default:
			break;
		}

		assert("RenderAPI not supported");
		return -1;

	}

}