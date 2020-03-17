#include <sfpch.h>
#include "shader.h"
#include <opengl/openGLShader.h>

namespace SF {

	Shader* Shader::create(const std::string& path) {

		return (Shader*)OpenGLShader::create(path);

	}

}