#ifndef _OGL_H
#define _OGL_H

#include "GLEW/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

namespace OGL
{
	void initializeContext(GLFWwindow** window, glm::uvec2 windowDimensions, const char* title);
	void terminateContext(GLFWwindow** window);
}

#include "Program/Program.h"
#include "Texture/Texture.h"
#include "VAO/VAO.h"

#endif