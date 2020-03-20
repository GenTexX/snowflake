#include <sfpch.h>
#include "shader.h"
#include <opengl/openGLShader.h>

namespace SF {

	std::string Shader::getFilePath()
	{
		return this->m_Filepath + m_Filename;
	}
	
	Shader* Shader::create(const std::string& path) {

		switch (Renderer::getRendererAPI())
		{

		case RendererAPI::OpenGL:
			return (OpenGLShader*) new OpenGLShader(path);
			break;
		default:
			break;
		}

		assert("RenderAPI not supported");
		return nullptr;

	}

}