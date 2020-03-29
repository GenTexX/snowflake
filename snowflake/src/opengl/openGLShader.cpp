#include <sfpch.h>
#include "openGLShader.h"
#include <gtc/type_ptr.hpp>

namespace SF {

	OpenGLShader::OpenGLShader(std::string file)
	{

		auto lastSlash = file.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash++;
		auto lastDot = file.rfind('.');

		this->m_Filename = file.substr(lastSlash + 1);
		this->m_Filepath = file.substr(0, lastSlash + 1);

	}

	void OpenGLShader::bind() const
	{

		glUseProgram(this->m_ProgramID);

	}

	void OpenGLShader::unbind() const
	{

		glUseProgram(0);

	}

	void OpenGLShader::readFile()
	{
		/* open shader file */
		FILE* shaderFile;
		shaderFile = fopen((this->m_Filepath + this->m_Filename).c_str(), "r");
		
		std::stringstream vertex;
		std::stringstream tessControl;
		std::stringstream tessEvaluation;
		std::stringstream geometry;
		std::stringstream fragment;

		char code_line[150];
		enum ShaderReadMode { None = 0, Vertex = 1, Control = 2, Evaluation = 3, Geometry = 4, Fragment = 5 };
		ShaderReadMode mode = None;
		
		SF_ASSERT(shaderFile,  "Shaderfile not existing");


		while (fgets(code_line, 150, shaderFile) != NULL) {
			
			std::string line = code_line;
			/* select shader type */
			if (line.find("#shader") != std::string::npos) {

				if (line.find("vertex") != std::string::npos)
					mode = Vertex;

				if (line.find("control") != std::string::npos)
					mode = Control;

				if (line.find("evaluation") != std::string::npos)
					mode = Evaluation;

				if (line.find("geometry") != std::string::npos)
					mode = Geometry;

				if (line.find("fragment") != std::string::npos)
					mode = Fragment;

				continue;

			}

			/* read shader source */
			switch (mode) {

			case None:
				break;

			case Vertex:
				vertex << line << std::endl;
				break;

			case Control:
				tessControl << line << std::endl;
				break;

			case Evaluation:
				tessEvaluation << line << std::endl;
				break;

			case Geometry:
				geometry << line << std::endl;
				break;

			case Fragment:
				fragment << line << std::endl;
				break;

			default:
				break;
			}

		}

		fclose(shaderFile);

		this->m_VertexSource = vertex.str();
		this->m_TessControlSource = tessControl.str();
		this->m_TessEvaluationSource = tessEvaluation.str();
		this->m_GeometrySource = geometry.str();
		this->m_FragmentSource = fragment.str();

	}

	void OpenGLShader::compile()
	{

		/* create empty shader objects*/
		if (!this->m_VertexSource.empty()) this->m_VertexID = glCreateShader(GL_VERTEX_SHADER);
		if (!this->m_TessControlSource.empty()) this->m_TessControlID = glCreateShader(GL_TESS_CONTROL_SHADER);
		if (!this->m_TessEvaluationSource.empty()) this->m_TessEvaluationID = glCreateShader(GL_TESS_EVALUATION_SHADER);
		if (!this->m_GeometrySource.empty()) this->m_GeometryID = glCreateShader(GL_GEOMETRY_SHADER);
		if (!this->m_FragmentSource.empty()) this->m_FragmentID = glCreateShader(GL_FRAGMENT_SHADER);

		/************************************/
		/********** VERTEX SHADER ***********/
		/************************************/
		if (this->m_VertexID) {

			/* set vertex shader source */
			const char* vertexShaderSource = this->m_VertexSource.c_str();
			glShaderSource(this->m_VertexID, 1, &vertexShaderSource, nullptr);

			/* compile fragment shader */
			glCompileShader(this->m_VertexID);

			/* check for compilation errors */
			int vertexCompilationResult;
			glGetShaderiv(this->m_VertexID, GL_COMPILE_STATUS, &vertexCompilationResult);
			if (vertexCompilationResult == GL_FALSE) {

				int length;
				glGetShaderiv(this->m_VertexID, GL_INFO_LOG_LENGTH, &length);

				char* msg = (char*)_malloca(length * sizeof(char));
				glGetShaderInfoLog(this->m_VertexID, length, &length, msg);

				SF_CORE_ERROR("Failed to compile Vertex Shader");
				SF_CORE_ERROR(msg);

			}

		}

		/************************************/
		/********* FRAGMENT SHADER **********/
		/************************************/
		if (this->m_FragmentID) {

			/* set fragment shader source */
			const char* fragmentShaderSource = this->m_FragmentSource.c_str();
			glShaderSource(this->m_FragmentID, 1, &fragmentShaderSource, nullptr);

			/* compile fragment shader */
			glCompileShader(this->m_FragmentID);

			/* check for compilation errors*/
			int fragmentCompilationResult;
			glGetShaderiv(this->m_FragmentID, GL_COMPILE_STATUS, &fragmentCompilationResult);
			if (fragmentCompilationResult == GL_FALSE) {

				int length;
				glGetShaderiv(this->m_FragmentID, GL_INFO_LOG_LENGTH, &length);

				char* msg = (char*)_malloca(length * sizeof(char));
				glGetShaderInfoLog(this->m_FragmentID, length, &length, msg);

				SF_CORE_ERROR("Failed to compile Fragment Shader");
				SF_CORE_ERROR(msg);


			}

		}

		//linkProgram
		this->m_ProgramID = glCreateProgram();
		glAttachShader(this->m_ProgramID, this->m_VertexID);
		glAttachShader(this->m_ProgramID, this->m_FragmentID);
		glLinkProgram(this->m_ProgramID);

		int length = 0;
		glGetProgramiv(this->m_ProgramID, GL_INFO_LOG_LENGTH, &length);
		char* msg = (char*)_malloca(length * sizeof(char));
		if (length > 0) {
			glGetProgramInfoLog(this->m_ProgramID, length, NULL, &msg[0]);
			SF_CORE_ERROR(msg);
		}

		//glDetachShader(this->m_ProgramID, this->m_VertexID);
		//glDetachShader(this->m_ProgramID, this->m_FragmentID);

		glDeleteShader(this->m_VertexID);
		glDeleteShader(this->m_FragmentID);

	}

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