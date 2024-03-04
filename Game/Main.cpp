#include "Game/Game.h"

constexpr glm::uvec2 windowDimensions = glm::uvec2(1600, 900);

int main()
{
	GLFWwindow* window{};

	OGL::initializeContext(&window, windowDimensions, "Acerola Game Jam 0");

	Game::Game game(windowDimensions);

	constexpr glm::vec4 bgColor(0.3F, 0.3F, 0.3F, 1.0F);
	glClearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		game.draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	OGL::terminateContext(&window);
}