#include "OGL.h"

#include <iostream>

void GLFWDebugCallback(int errorCode, const char* description)
{
	std::cerr << "Error Code: " << errorCode << "\nDescription: " << description << '\n';
	__debugbreak();
}
void __stdcall OGLDebugCallback(unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char* message, const void* userParam)
{
	std::string sourceStr;
	switch (source)
	{
	case GL_DEBUG_SOURCE_API:
		sourceStr = "Source: API"; break;
	case GL_DEBUG_SOURCE_APPLICATION:
		sourceStr = "Source: Application"; break;
	case GL_DEBUG_SOURCE_OTHER:
		sourceStr = "Source: Other"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER:
		sourceStr = "Source: Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:
		sourceStr = "Source: Third Party"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
		sourceStr = "Source: Window System"; break;
	default:
		sourceStr = "Source: Unknown";
	}

	std::string typeStr;
	switch (type)
	{
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		typeStr = "Type: Deprecated Behaviour"; break;
	case GL_DEBUG_TYPE_ERROR:
		typeStr = "Type: Error"; break;
	case GL_DEBUG_TYPE_MARKER:
		typeStr = "Type: Marker"; break;
	case GL_DEBUG_TYPE_OTHER:
		typeStr = "Type: Other"; break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		typeStr = "Type: Performance"; break;
	case GL_DEBUG_TYPE_POP_GROUP:
		typeStr = "Type: Pop Group"; break;
	case GL_DEBUG_TYPE_PORTABILITY:
		typeStr = "Type: Portability"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP:
		typeStr = "Type: Push Group"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		typeStr = "Type: Undefined Behaviour"; break;
	default:
		typeStr = "Type: Unknown";
	}

	std::string severityStr;
	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:
		severityStr = "Severity: High"; break;
	case GL_DEBUG_SEVERITY_LOW:
		severityStr = "Severity: Low"; break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		severityStr = "Severity: Medium"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		severityStr = "Severity: Notification"; break;
	default:
		severityStr = "Severity: Unknown";
	}

	std::cerr << "Debug Callback:\n\t" << sourceStr << "\n\t" << typeStr << "\n\tID: " << id << "\n\t" << severityStr << "\n\tLength: " << length << "\nMessage:\n" << message << "\n";
	__debugbreak();
}

namespace OGL
{
	void initializeContext(GLFWwindow** window, glm::uvec2 windowDimensions, const char* title)
	{
		if (!glfwInit())
		{
			std::cerr << "Failed to initialize GLFW!\n";
			exit(EXIT_FAILURE);
		}

		glfwSetErrorCallback(GLFWDebugCallback);

		glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

		*window = glfwCreateWindow(windowDimensions.x, windowDimensions.y, title, nullptr, nullptr);

		if (!(*window))
		{
			std::cerr << "Failed to create Window!\n";
			glfwTerminate();
			exit(EXIT_FAILURE);
		}
		glfwMakeContextCurrent(*window);
		glfwMaximizeWindow(*window);

		if (glewInit())
		{
			std::cerr << "Failed to initialize GLEW!\n";
			glfwDestroyWindow(*window);
			glfwTerminate();
			exit(EXIT_FAILURE);
		}

		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(OGLDebugCallback, nullptr);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	void terminateContext(GLFWwindow** window)
	{
		glfwDestroyWindow(*window);
		glfwTerminate();
	}
}