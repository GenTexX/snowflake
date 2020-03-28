#include <sfpch.h>
#include "shader.h"
#include <opengl/openGLShader.h>
#include "rendererAPI.h"

namespace SF {

	std::string Shader::getFilePath()
	{
		return this->m_Filepath + m_Filename;
	}
	
	Ref<Shader> Shader::create(const std::string& path) {

		switch (RendererAPI::getRendererAPI())
		{

		case RendererAPIEnum::OpenGL:
			return createRef<OpenGLShader>(path);
			break;
		default:
			break;
		}

		assert("RenderAPI not supported");
		return nullptr;

	}

}