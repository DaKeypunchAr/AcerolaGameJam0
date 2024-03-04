#include "OGL/OGL.h"
#include "Image/Image.h"

#include <iostream>
#include <fstream>
#include <string>

int main()
{
	GLFWwindow* window{};
	constexpr glm::uvec2 windowDimensions = glm::uvec2(1600, 900);

	OGL::initializeContext(&window, windowDimensions, "Acerola Game Jam 0");

	constexpr glm::vec4 bgColor(0.3F, 0.3F, 0.3F, 1.0F);
	glClearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);

	std::vector<unsigned int> eb{
		0, 1, 2,
		1, 2, 3,
	};
	
	std::vector<float> vb{
		-0.5f, -0.5f, 0.0f, 0.0f,
		+0.5f, -0.5f, 1.0f, 0.0f,
		-0.5f, +0.5f, 0.0f, 1.0f,
		+0.5f, +0.5f, 1.0f, 1.0f,
	};

	OGL::TextureFilters filter = { GL_LINEAR, GL_REPEAT };
	OGL::Texture2D smTexture("Resources/Textures/sample.png", filter);
	OGL::Program smProgram("Resources/Shaders/Sample");

	OGL::VAO VAO(6, { 16 }, { OGL::VBOInfo(0, GL_STATIC_DRAW, 4 * sizeof(float), { OGL::AttribInfo(0, 2, 0), OGL::AttribInfo(1, 2, 2 * sizeof(float))}) });
	VAO.updateEB(0, 6, eb);
	VAO.updateVB(0, 16, vb, 0);

	VAO.bind();
	smProgram.use();
	smProgram.uni1i("tex", 0);
	smTexture.bind(0);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	OGL::terminateContext(&window);
}