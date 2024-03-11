#ifndef _ACEROLA_GAME_JAM_H
#define _ACEROLA_GAME_JAM_H

#include "../OGL/OGL.h"
#include "Camera/Camera.h"
#include "Entity/Entity.h"
#include "Player/Player.h"
#include "Floor/FloorManager.h"
#include "TextRenderer/TextRenderer.h"
#include "UI/UI.h"

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

	private:
		Camera cam;

		OGL::Program colorProgram;
		OGL::Program textureProgram;
		OGL::Program textProgram;

		TextTextureAtlas atlas;

		Player player;
		UI ui;

		FloorManager floorManager;

		double lastTick = 0;

		friend Player;
	};
}

#endif