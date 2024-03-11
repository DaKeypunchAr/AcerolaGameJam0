#include "Game.h"

#include "GLFW/glfw3.h"

#include <iostream>

namespace Game
{
	Game::Game()
		: cam(glm::vec2(0, windowDimension.x), glm::vec2(0, windowDimension.y)), atlas("Resources/Fonts/teeny-tiny-font.ttf"), player(this)
	{
		colorProgram.initialize("Resources/Shaders/Color");
		textureProgram.initialize("Resources/Shaders/Texture");
		textProgram.initialize("Resources/Shaders/Text");
	}

	void Game::draw()
	{
		player.draw(textureProgram);
		floorManager.drawFloors();
		ui.drawUI();
	}

	void Game::update()
	{
		double dt = glfwGetTime() - lastTick;

		floorManager.update(dt);
		player.update(dt);
		ui.updateUI(dt);

		lastTick = glfwGetTime();
	}

	/* normalizeScreenSpace() is in Entity.cpp */

	glm::uvec2 Game::windowDimension = glm::uvec2(1920, 1080);
}