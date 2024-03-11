#include "Game/Game.h"

#include <iostream>

int main()
{
	GLFWwindow* window{};

	OGL::initializeContext(&window, Game::Game::windowDimension, "Acerola Game Jam 0");

	Game::Game game;

	constexpr glm::vec4 bgColor = glm::vec4(39, 0, 34, 255) / 255.0f;
	glClearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);

	glfwMakeContextCurrent(window);

	int width{}, height{};
	glfwGetWindowSize(window, &width, &height);

	Game::Game::windowDimension = { width, height };

	unsigned int FPS = 60u;
	double frameTime = 1.0 / FPS;

	double lastTime = glfwGetTime();

	while (!glfwWindowShouldClose(window))
	{
		if (glfwGetTime() > lastTime + frameTime)
		{
			glClear(GL_COLOR_BUFFER_BIT);

			game.update();
			game.draw();

			glfwSwapBuffers(window);
			lastTime = glfwGetTime();
		}

		if (glfwGetKey(window, GLFW_KEY_ESCAPE)) break;

		glfwPollEvents();
	}

	OGL::terminateContext(&window);
}