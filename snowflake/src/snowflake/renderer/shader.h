#pragma once

#include <string>
#include <glm.hpp>
#include "renderer.h"

namespace SF {

	class Shader {

	protected:
		std::string m_Name;
		
		std::string m_Filename;
		std::string m_Filepath;

		uint32_t m_VertexID;
		uint32_t m_TessControlID;
		uint32_t m_TessEvaluationID;
		uint32_t m_GeometryID;
		uint32_t m_FragmentID;

	public:
		Shader() {}
		~Shader() {}

		std::string getFilePath();

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual std::string readFile() = 0;
		virtual void compile() = 0;

		static Shader* create(const std::string& path);

		/* UNIFORMS */
		virtual void setInt(const std::string& name, int32_t val) = 0;
		virtual void setInt2(const std::string& name, const glm::ivec2& val) = 0;
		virtual void setInt3(const std::string& name, const glm::ivec3& val) = 0;
		virtual void setInt4(const std::string& name, const glm::ivec4& val) = 0;

		//FLOAT
		virtual void setFloat(const std::string& name, float val) = 0;
		virtual void setFloat2(const std::string& name, const glm::vec2& val) = 0;
		virtual void setFloat3(const std::string& name, const glm::vec3& val) = 0;
		virtual void setFloat4(const std::string& name, const glm::vec4& val) = 0;

		//MAT2
		virtual void setMat2(const std::string& name, const glm::mat2& mat) = 0;
		virtual void setMat2x3(const std::string& name, const glm::mat2x3& mat) = 0;
		virtual void setMat2x4(const std::string& name, const glm::mat2x4& mat) = 0;

		//MAT3
		virtual void setMat3(const std::string& name, const glm::mat3& mat) = 0;
		virtual void setMat3x2(const std::string& name, const glm::mat3x2& mat) = 0;
		virtual void setMat3x4(const std::string& name, const glm::mat3x4& mat) = 0;

		//MAT4
		virtual void setMat4(const std::string& name, const glm::mat4& mat) = 0;
		virtual void setMat4x2(const std::string& name, const glm::mat4x2& mat) = 0;
		virtual void setMat4x3(const std::string& name, const glm::mat4x3& mat) = 0;


	};

}