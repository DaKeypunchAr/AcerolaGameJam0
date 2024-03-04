#include "Game.h"

namespace Game
{
	Game::Game(glm::uvec2 windowDimensions)
		: cam(glm::vec2(0, windowDimensions.x), glm::vec2(0, windowDimensions.y))
	{
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

		texture.initialize("Resources/Textures/sample.png", pixelArtFilter);
		program.initialize("Resources/Shaders/Sample");

		vao.initialize(6, { 16 }, { OGL::VBOInfo(0, GL_STATIC_DRAW, 4 * sizeof(float), { OGL::AttribInfo(0, 2, 0), OGL::AttribInfo(1, 2, 2 * sizeof(float))}) });
		vao.updateEB(0, 6, eb);
		vao.updateVB(0, 16, vb, 0);
	}

	void Game::draw()
	{
		vao.bind();
		texture.bind(0);
		program.use();
		program.uni1i("tex", 0);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}

	void Game::update()
	{

	}
}