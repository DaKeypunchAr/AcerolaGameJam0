#ifndef _OGL_PROGRAM_H
#define _OGL_PROGRAM_H

#include "GLEW/glew.h"
#include "glm/glm.hpp"

#include <string>
#include <fstream>

namespace OGL
{
	class Program
	{
		public:
			Program() = delete;
			Program(const Program& other) = delete;
			Program(std::string folderPath);
			Program(std::string vsFilePath, std::string fsFilePath);
			~Program();

			void use() const;
			void uni1i(std::string uniName, int i) const;
			void uni1f(std::string uniName, float f) const;
			void uni2f(std::string uniName, glm::vec2 vec) const;
			void uni3f(std::string uniName, glm::vec3 vec) const;
			void uni4f(std::string uniName, glm::vec4 vec) const;

			unsigned int getUniLoc(std::string uniName) const;

		private:
			void initialize(std::string vsFilePath, std::string fsFilePath);
			std::string readFile(std::string filePath) const;
			void compileShader(unsigned int shaderID) const;
			void linkProgram() const;

		private:
			unsigned int m_ID;
	};
}

#endif