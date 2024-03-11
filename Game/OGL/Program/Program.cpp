#include "Program.h"

#include <iostream>
#include <vector>

namespace OGL
{
 	Program::Program() {}
	Program::Program(std::string folderPath)
	{
		initialize(folderPath + "/vertex.glsl", folderPath + "/fragment.glsl");
	}
	Program::Program(std::string vsFilePath, std::string fsFilePath)
	{
		initialize(vsFilePath, fsFilePath);
	}
	Program::~Program()
	{
		glDeleteProgram(m_ID);
	}

	void Program::use() const
	{
		glUseProgram(m_ID);
	}
	void Program::uni1i(std::string uniName, int i) const
	{
		glUniform1i(getUniLoc(uniName), i);
	}
	void Program::uni1f(std::string uniName, float f) const
	{
		glUniform1f(getUniLoc(uniName), f);
	}
	void Program::uni2f(std::string uniName, glm::vec2 vec) const
	{
		glUniform2f(getUniLoc(uniName), vec.x, vec.y);
	}
	void Program::uni3f(std::string uniName, glm::vec3 vec) const
	{
		glUniform3f(getUniLoc(uniName), vec.x, vec.y, vec.z);
	}
	void Program::uni4f(std::string uniName, glm::vec4 vec) const
	{
		glUniform4f(getUniLoc(uniName), vec.x, vec.y, vec.z, vec.w);
	}
	void Program::uniMat4(std::string uniName, glm::mat4 mat) const
	{
		glUniformMatrix4fv(getUniLoc(uniName), 1, GL_FALSE, glm::value_ptr(mat));
	}

	unsigned int Program::getUniLoc(std::string uniName) const
	{
		return glGetUniformLocation(m_ID, uniName.c_str());
	}

	void Program::initialize(std::string vsFilePath, std::string fsFilePath)
	{
		m_ID = glCreateProgram();
		unsigned int vs = glCreateShader(GL_VERTEX_SHADER), fs = glCreateShader(GL_FRAGMENT_SHADER);

		std::string vsFile = readFile(vsFilePath), fsFile = readFile(fsFilePath);
		const char* vsSrc = vsFile.c_str(), * fsSrc = fsFile.c_str();

		glShaderSource(vs, 1, &vsSrc, nullptr);
		glShaderSource(fs, 1, &fsSrc, nullptr);

		compileShader(vs);
		compileShader(fs);

		glAttachShader(m_ID, vs);
		glAttachShader(m_ID, fs);

		linkProgram();

		glDetachShader(m_ID, vs);
		glDetachShader(m_ID, fs);

		glDeleteShader(vs);
		glDeleteShader(fs);
	}
	std::string Program::readFile(std::string fileLoc) const
	{
		std::ifstream reader(fileLoc);
		std::string fileContents;
		for (std::string line; std::getline(reader, line); fileContents += '\n') fileContents += line;
		return fileContents;
	}
	void Program::compileShader(unsigned int shaderID) const
	{
		glCompileShader(shaderID);

		int compileStatus{};
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);

		if (!compileStatus)
		{
			std::vector<char> message;
			int length{};
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
			message.reserve(length);
			glGetShaderInfoLog(shaderID, length, nullptr, message.data());

			int type{};
			glGetShaderiv(shaderID, GL_SHADER_TYPE, &type);
			std::string shaderType = (type == GL_VERTEX_SHADER) ? "Vertex Shader" : (type == GL_FRAGMENT_SHADER) ? "Fragment Shader" : "Unknown Shader";

			std::cerr << "Failed to compile " << shaderType << ":\n" << message.data() << '\n';
			__debugbreak();
		}
	}
	void Program::linkProgram() const
	{
		glLinkProgram(m_ID);

		int linkStatus{};
		glGetProgramiv(m_ID, GL_LINK_STATUS, &linkStatus);

		if (!linkStatus)
		{
			std::vector<char> message;
			int length{};
			glGetProgramiv(m_ID, GL_INFO_LOG_LENGTH, &length);
			message.reserve(length);
			glGetShaderInfoLog(m_ID, length, nullptr, message.data());

			std::cerr << "Failed to link program:\n" << message.data() << '\n';
			__debugbreak();
		}
	}
}