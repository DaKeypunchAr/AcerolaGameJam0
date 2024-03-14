#ifndef _ACEROLA_GAME_JAM_H
#define _ACEROLA_GAME_JAM_H

#include "../OGL/OGL.h"
#include "Camera/Camera.h"
#include "Entity/Entity.h"
#include "Player/Player.h"
#include "Floor/FloorManager.h"
#include "TextRenderer/TextRenderer.h"
#include "UI/UI.h"
#include "Soloud/soloud.h"
#include "Soloud/soloud_wav.h"

#include <random>

static OGL::TextureFilters pixelArtFilter = { GL_NEAREST, GL_REPEAT };

#include <array>

namespace Game
{
	enum class GameState
	{
		PLAY,
		MAIN_MENU,
		PAUSE,
		ABOUT,
		END
	};

	class Game
	{
	public:
		Game();
		~Game() { soloud.deinit(); }

		void draw();
		void update();

		static glm::uvec2 windowDimension;

		glm::ivec2 randomTime() const;
		unsigned int randomKey() const;

		std::string getKeyName(unsigned int key) const;
		std::string getScore() const;

	public:
		Camera cam;

		OGL::Program uiColorProgram;
		OGL::Program uiTextureProgram;
		OGL::Program gameTextureProgram;
		OGL::Program textProgram;

		unsigned int leftButton = GLFW_KEY_A, rightButton = GLFW_KEY_D, jumpButton = GLFW_KEY_SPACE;
		glm::ivec2 twistTimer = randomTime();

		int menuIdx = 0;

		mutable bool upPressed = false, downPressed = false, leftPressed = false, rightPressed = false;

		int waitCounter = 0;

		GameState state = GameState::MAIN_MENU;

		unsigned int score = 0;

		double cameraMovementTime = 1.0f;
		double lastCameraMoveTime;
		glm::vec2 camTranslation;
		glm::vec2 lastTranslation = glm::vec2(3.0f, 0.0f);

		double lastTick = 0;

		TextTextureAtlas atlas;

		FloorManager floorManager;

		Player player;
		UI ui;

		SoLoud::Soloud soloud;
		SoLoud::Wav death;
		SoLoud::Wav jump;
		SoLoud::Wav menu;
		SoLoud::Wav beep;

		int beeped = 0;

		friend Player;
	};
}

#endif