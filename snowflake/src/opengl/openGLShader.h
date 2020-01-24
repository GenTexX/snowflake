#pragma once
#include "snowflake/renderer/shader.h"
#include <GL/glew.h>

namespace SF {

	class OpenGLShader	: public Shader{


	private:
		uint32_t m_ProgramID;
		
	
	public:
		OpenGLShader();
		~OpenGLShader();

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		/* UNIFORMS */

		//INT
		virtual void setInt(const std::string& name, int32_t val) override;
		virtual void setInt2(const std::string& name, const glm::ivec2& val) override;
		virtual void setInt3(const std::string& name, const glm::ivec3& val) override;
		virtual void setInt4(const std::string& name, const glm::ivec4& val)override;

		//FLOAT
		virtual void setFloat(const std::string& name, float val)override;
		virtual void setFloat2(const std::string& name, const glm::vec2& val)override;
		virtual void setFloat3(const std::string& name, const glm::vec3& val)override;
		virtual void setFloat4(const std::string& name, const glm::vec4& val)override;

		//MAT2
		virtual void setMat2(const std::string& name, const glm::mat2& mat)override;
		virtual void setMat2x3(const std::string& name, const glm::mat2x3& mat)override;
		virtual void setMat2x4(const std::string& name, const glm::mat2x4& mat)override;

		//MAT3
		virtual void setMat3(const std::string& name, const glm::mat3& mat)override;
		virtual void setMat3x2(const std::string& name, const glm::mat3x2& mat)override;
		virtual void setMat3x4(const std::string& name, const glm::mat3x4& mat)override;

		//MAT4
		virtual void setMat4(const std::string& name, const glm::mat4& mat)override;
		virtual void setMat4x2(const std::string& name, const glm::mat4x2& mat)override;
		virtual void setMat4x3(const std::string& name, const glm::mat4x3& mat)override;

	};

}