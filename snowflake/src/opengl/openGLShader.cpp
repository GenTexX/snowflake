#include <sfpch.h>
#include "openGLShader.h"

namespace SF {



	void OpenGLShader::setInt(const std::string& name, int32_t val)
	{

		glUniform1i(glGetUniformLocation(this->m_ProgramID, name.c_str()), val);

	}

	void OpenGLShader::setInt2(const std::string& name, const glm::ivec2& val)
	{

		glUniform2i(glGetUniformLocation(this->m_ProgramID, name.c_str()), val.x, val.y);

	}

}