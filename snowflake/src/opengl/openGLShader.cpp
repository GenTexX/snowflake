#include <sfpch.h>
#include "openGLShader.h"
#include <gtc/type_ptr.hpp>

namespace SF {


	//INT
	void OpenGLShader::setInt(const std::string& name, int32_t val)
	{

		glUniform1i(glGetUniformLocation(this->m_ProgramID, name.c_str()), val);

	}

	void OpenGLShader::setInt2(const std::string& name, const glm::ivec2& val)
	{

		glUniform2i(glGetUniformLocation(this->m_ProgramID, name.c_str()), val.x, val.y);

	}

	void OpenGLShader::setInt3(const std::string& name, const glm::ivec3& val)
	{

		glUniform3i(glGetUniformLocation(this->m_ProgramID, name.c_str()), val.x, val.y, val.z);

	}

	void OpenGLShader::setInt4(const std::string& name, const glm::ivec4& val)
	{

		glUniform4i(glGetUniformLocation(this->m_ProgramID, name.c_str()), val.x, val.y, val.z, val.w);

	}


	//FLOAT
	void OpenGLShader::setFloat(const std::string& name, float val)
	{

		glUniform1f(glGetUniformLocation(this->m_ProgramID, name.c_str()), val);

	}

	void OpenGLShader::setFloat2(const std::string& name, const glm::vec2& val)
	{

		glUniform2f(glGetUniformLocation(this->m_ProgramID, name.c_str()), val.x, val.y);

	}

	void OpenGLShader::setFloat3(const std::string& name, const glm::vec3& val)
	{

		glUniform3f(glGetUniformLocation(this->m_ProgramID, name.c_str()), val.x, val.y, val.z);

	}

	void OpenGLShader::setFloat4(const std::string& name, const glm::vec4& val)
	{

		glUniform4f(glGetUniformLocation(this->m_ProgramID, name.c_str()), val.x, val.y, val.z, val.w);

	}


	//MATRICES

	//MAT2
	void OpenGLShader::setMat2(const std::string& name, const glm::mat2& mat)
	{

		glUniformMatrix2fv(glGetUniformLocation(this->m_ProgramID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));

	}

	void OpenGLShader::setMat2x3(const std::string& name, const glm::mat2x3& mat)
	{

		glUniformMatrix2x3fv(glGetUniformLocation(this->m_ProgramID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));

	}

	void OpenGLShader::setMat2x4(const std::string& name, const glm::mat2x4& mat)
	{

		glUniformMatrix2x4fv(glGetUniformLocation(this->m_ProgramID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));

	}

	//MAT3
	void OpenGLShader::setMat3(const std::string& name, const glm::mat3& mat)
	{

		glUniformMatrix3fv(glGetUniformLocation(this->m_ProgramID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));

	}

	void OpenGLShader::setMat3x2(const std::string& name, const glm::mat3x2& mat)
	{

		glUniformMatrix3x2fv(glGetUniformLocation(this->m_ProgramID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));

	}

	void OpenGLShader::setMat3x4(const std::string& name, const glm::mat3x4& mat)
	{

		glUniformMatrix3x4fv(glGetUniformLocation(this->m_ProgramID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));

	}

	//MAT4
	void OpenGLShader::setMat4(const std::string& name, const glm::mat4& mat)
	{

		glUniformMatrix4fv(glGetUniformLocation(this->m_ProgramID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));

	}

	void OpenGLShader::setMat4x2(const std::string& name, const glm::mat4x2& mat)
	{

		glUniformMatrix4x2fv(glGetUniformLocation(this->m_ProgramID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));

	}

	void OpenGLShader::setMat4x3(const std::string& name, const glm::mat4x3& mat)
	{

		glUniformMatrix4x3fv(glGetUniformLocation(this->m_ProgramID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));

	}


	

}