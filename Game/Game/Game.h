#ifndef _ACEROLA_GAME_JAM_H
#define _ACEROLA_GAME_JAM_H

#include "../OGL/OGL.h"
#include "Camera/Camera.h"
#include "Entity/Entity.h"
#include "Player/Player.h"
#include "Floor/FloorManager.h"
#include "TextRenderer/TextRenderer.h"
#include "UI/UI.h"

#include <random>

static OGL::TextureFilters pixelArtFilter = { GL_NEAREST, GL_REPEAT };

#include <array>

namespace Game
{
	class Game
	{
	public:
		Game();
		~Game() = default;

		void draw();
		void update();

		static constexpr glm::vec2 normalizedScreenSpace(glm::vec2 p);
		static glm::uvec2 windowDimension;

		glm::ivec2 randomTime() const;
		unsigned int randomKey() const;

		std::string getKeyName(unsigned int key) const;

	public:
		Camera cam;

		OGL::Program colorProgram;
		OGL::Program textureProgram;
		OGL::Program textProgram;

		unsigned int leftButton = GLFW_KEY_A, rightButton = GLFW_KEY_D, jumpButton = GLFW_KEY_SPACE;
		glm::ivec2 twistTimer = glm::ivec2(1);

		TextTextureAtlas atlas;

		Player player;
		UI ui;

		FloorManager floorManager;

		double lastTick = 0;

		friend Player;
	};
}

#endif