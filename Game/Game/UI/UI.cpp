#include "../Game.h"

namespace Game
{
	void UI::initialize()
	{
#pragma region Initializing Bar
		std::vector<OGL::VBOInfo> infos;
		infos.push_back(OGL::VBOInfo(0, GL_STATIC_DRAW, sizeof(float) * 2, { OGL::AttribInfo(0, 2, 0) }));
		infos.push_back(OGL::VBOInfo(1, GL_STATIC_DRAW, sizeof(float) * 4, { OGL::AttribInfo(1, 4, 0) }));
		barVAO.initialize(6, { 8, 16 }, infos);

		std::vector<float> barPosBuffer
		{
			0.0f, 0.0f,
			1920.0f, 0.0f,
			0.0f, barHeight * scalingFactor,
			1920.0f, barHeight * scalingFactor
		};
		std::vector<float> barColorBuffer
		{
			barColor.r, barColor.g, barColor.b, barColor.a,
			barColor.r, barColor.g, barColor.b, barColor.a,
			barColor.r, barColor.g, barColor.b, barColor.a,
			barColor.r, barColor.g, barColor.b, barColor.a,
		};
		barVAO.updateEB(0, { 0, 1, 2, 1, 2, 3 });
		barVAO.updateVB(0, barPosBuffer, 0);
		barVAO.updateVB(0, barColorBuffer, 1);

#pragma endregion

#pragma region Initializing Clock
		glm::vec2 clockBL = glm::vec2(paddingX, paddingY) * scalingFactor;
		glm::vec2 clockTR = clockBL + glm::vec2(15, 15) * clockScale; // Jump Key Size
		timePos = { clockTR.x + paddingX, clockBL.y + 10.0f };

		infos[1] = OGL::VBOInfo(1, GL_DYNAMIC_DRAW, 2 * sizeof(float), { OGL::AttribInfo(1, 2, 0) });
		clockVAO.initialize(6, { 8, 8 }, infos);
		clockVAO.updateEB(0, { 0, 1, 2, 1, 2, 3 });

		std::vector<float> clockPosBuffer
		{
			clockBL.x, clockBL.y,
			clockTR.x, clockBL.y,
			clockBL.x, clockTR.y,
			clockTR.x, clockTR.y,
		};
		std::vector<float> clockTexCoords
		{
			0.0f, 0.0f,
			0.125f, 0.0f,
			0.0f, 0.125f,
			0.125f, 0.125f
		};

		clockVAO.updateVB(0, clockPosBuffer, 0);
		clockVAO.updateVB(0, clockTexCoords, 1);

		clockTexture.initialize("Resources/Textures/clockSpriteSheet.png", pixelArtFilter);
#pragma endregion

#pragma region Initializing Keys
		keys.initialize("Resources/Textures/keys.png", pixelArtFilter);

		infos.clear();
		infos.push_back(OGL::VBOInfo(0, GL_STATIC_DRAW, 2 * sizeof(float), { OGL::AttribInfo(0, 2, 0) }));
		infos.push_back(OGL::VBOInfo(1, GL_STATIC_DRAW, 2 * sizeof(float), { OGL::AttribInfo(1, 2, 0) }));

		keyVAO.initialize(36, { 48, 48 }, infos);

		float jumpCoords = 35.0F / keys.getTextureDimensions().x;
		float leftCoords = 64.0F / keys.getTextureDimensions().x;
		float rightCoords = 103.0F / keys.getTextureDimensions().x;

		glm::vec2 jumpBL = glm::vec2(480, paddingY * scalingFactor);
		glm::vec2 jumpTR = jumpBL + glm::vec2(35, 12) * scalingFactor;
		jumpButtonPos = glm::vec2(jumpTR.x + 30.0f, jumpBL.y + 15.0f);

		glm::vec2 leftBL = glm::vec2(960, paddingY * scalingFactor);
		glm::vec2 leftTR = leftBL + glm::vec2(29, 12) * scalingFactor;
		leftButtonPos = glm::vec2(leftTR.x + 30.0f, leftBL.y + 15.0f);

		glm::vec2 rightBL = glm::vec2(1440, paddingY * scalingFactor);
		glm::vec2 rightTR = rightBL + glm::vec2(39, 12) * scalingFactor;
		rightButtonPos = glm::vec2(rightTR.x + 30.0f, rightBL.y + 15.0f);

		std::vector<float> keyPosBuffer
		{
			jumpBL.x, jumpBL.y,
			jumpTR.x, jumpBL.y,
			jumpBL.x, jumpTR.y,
			jumpTR.x, jumpTR.y,

			leftBL.x, leftBL.y,
			leftTR.x, leftBL.y,
			leftBL.x, leftTR.y,
			leftTR.x, leftTR.y,

			rightBL.x, rightBL.y,
			rightTR.x, rightBL.y,
			rightBL.x, rightTR.y,
			rightTR.x, rightTR.y,
		};

		std::vector<float> keyTexCoordsBuffer
		{
			0.0f, 0.0f,
			jumpCoords, 0.0f,
			0.0f, 1.0f,
			jumpCoords, 1.0f,

			jumpCoords, 0.0f,
			leftCoords, 0.0f,
			jumpCoords, 1.0f,
			leftCoords, 1.0f,

			leftCoords, 0.0f,
			rightCoords, 0.0f,
			leftCoords, 1.0f,
			rightCoords, 1.0f,
		};

		keyVAO.updateEB(0, {
			0, 1, 2, 1, 2, 3,
			4, 5, 6, 5, 6, 7,
			8, 9, 10, 9, 10, 11,
			12, 13, 14, 13, 14, 15,
			16, 17, 18, 17, 18, 19,
			20, 21, 22, 21, 22, 23,
		});
		keyVAO.updateVB(0, keyPosBuffer, 0);
		keyVAO.updateVB(0, keyTexCoordsBuffer, 1);
#pragma endregion

		scorePos = glm::vec2(Game::windowDimension.x - game->atlas.getTextWidth("Score: 0000", timeFontSize) - 60.0f, Game::windowDimension.y - timeFontSize * 20.0f - 40.0f);

#pragma region Initializing Title

		title.initialize("Resources/Textures/gametitle.png", pixelArtFilter);

		infos.clear();
		infos.push_back(OGL::VBOInfo(0, GL_STATIC_DRAW, sizeof(float) * 2, { OGL::AttribInfo(0, 2, 0) }));
		infos.push_back(OGL::VBOInfo(1, GL_STATIC_DRAW, sizeof(float) * 2, { OGL::AttribInfo(1, 2, 0) }));

		titleVAO.initialize(6, { 8, 8 }, infos);
		titleVAO.updateEB(0, { 0, 1, 2, 1, 2, 3 });

		glm::vec2 titleBL = glm::vec2((game->windowDimension.x - title.getTextureDimensions().x * titleScaler) / 2.0f, game->windowDimension.y / 2.0f - 50.0f);
		glm::vec2 titleTR = titleBL + glm::vec2(title.getTextureDimensions()) * titleScaler;

		std::vector<float> titleVB
		{
			titleBL.x, titleBL.y,
			titleTR.x, titleBL.y,
			titleBL.x, titleTR.y,
			titleTR.x, titleTR.y,
		};
		titleVAO.updateVB(0, titleVB, 0);
		titleVAO.updateVB(0, {
				0.0f, 0.0f,
				1.0f, 0.0f,
				0.0f, 1.0f,
				1.0f, 1.0f,
			}, 1);

#pragma endregion

#pragma region Intializing Menu Buttons

		playButton.initialize("Resources/Textures/playButton.png", pixelArtFilter);
		aboutButton.initialize("Resources/Textures/about.png", pixelArtFilter);
		exitButton.initialize("Resources/Textures/exit.png", pixelArtFilter);

		glm::vec2 buttonDimension = glm::vec2(playButton.getTextureDimensions().x / 2.0f, playButton.getTextureDimensions().y) * buttonScaler;
		float allButtonX = (Game::windowDimension.x - buttonDimension.x) / 2.0f;
		float buttonDiff = Game::windowDimension.y / 10.0f;

		glm::vec2 exitBL = glm::vec2(allButtonX, buttonDiff);
		glm::vec2 exitTR = exitBL + buttonDimension;

		glm::vec2 aboutBL = glm::vec2(allButtonX, buttonDiff * 1.5f + buttonDimension.y);
		glm::vec2 aboutTR = aboutBL + buttonDimension;

		glm::vec2 playBL = glm::vec2(allButtonX, buttonDiff * 2.0f + buttonDimension.y * 2.0f);
		glm::vec2 playTR = playBL + buttonDimension;

		infos.clear();
		infos.push_back(OGL::VBOInfo(0, GL_STATIC_DRAW, sizeof(float) * 2, { OGL::AttribInfo(0, 2, 0) }));
		infos.push_back(OGL::VBOInfo(1, GL_STATIC_DRAW, sizeof(float) * 2, { OGL::AttribInfo(1, 2, 0) }));

		playVAO.initialize(6, { 8, 8 }, infos);
		aboutVAO.initialize(6, { 8, 8 }, infos);
		exitVAO.initialize(6, { 8, 8 }, infos);

		playVAO.updateEB(0, { 0, 1, 2, 1, 2, 3 });
		aboutVAO.updateEB(0, { 0, 1, 2, 1, 2, 3 });
		exitVAO.updateEB(0, { 0, 1, 2, 1, 2, 3 });

		std::vector<float> playVB
		{
			playBL.x, playBL.y,
			playTR.x, playBL.y,
			playBL.x, playTR.y,
			playTR.x, playTR.y,
		};

		std::vector<float> aboutVB
		{
			aboutBL.x, aboutBL.y,
			aboutTR.x, aboutBL.y,
			aboutBL.x, aboutTR.y,
			aboutTR.x, aboutTR.y,
		};

		std::vector<float> exitVB
		{
			exitBL.x, exitBL.y,
			exitTR.x, exitBL.y,
			exitBL.x, exitTR.y,
			exitTR.x, exitTR.y,
		};

		playVAO.updateVB(0, playVB, 0);
		aboutVAO.updateVB(0, aboutVB, 0);
		exitVAO.updateVB(0, exitVB, 0);

		playVAO.updateVB(0, {
				0.0f, 0.0f,
				0.5f, 0.0f,
				0.0f, 1.0f,
				0.5f, 1.0f
			}, 1);
		aboutVAO.updateVB(0, {
				0.0f, 0.0f,
				0.5f, 0.0f,
				0.0f, 1.0f,
				0.5f, 1.0f
			}, 1);
		exitVAO.updateVB(0, {
				0.0f, 0.0f,
				0.5f, 0.0f,
				0.0f, 1.0f,
				0.5f, 1.0f
			}, 1);

#pragma endregion

#pragma region Initializing About Page
		aboutPage.initialize("Resources/Textures/aboutPage.png", pixelArtFilter);

		infos.clear();
		infos.push_back(OGL::VBOInfo(0, GL_STATIC_DRAW, sizeof(float) * 2, { OGL::AttribInfo(0, 2, 0) }));
		infos.push_back(OGL::VBOInfo(1, GL_STATIC_DRAW, sizeof(float) * 2, { OGL::AttribInfo(1, 2, 0) }));
		aboutPageVAO.initialize(6, { 8, 8 }, infos);

		aboutPageVAO.updateEB(0, { 0, 1, 2, 1, 2, 3 });
		aboutPageVAO.updateVB(0, {
				0, 0,
				(float)Game::windowDimension.x, 0,
				0, (float)Game::windowDimension.y,
				(float)Game::windowDimension.x, (float)Game::windowDimension.y
			}, 0);
		aboutPageVAO.updateVB(0, {
			0.0f, 0.0f,
			1.0f, 0.0f,
			0.0f, 1.0f,
			1.0f, 1.0f
			}, 1);

		backVAO.initialize(6, { 8, 8 }, infos);
		backVAO.updateEB(0, { 0, 1, 2, 1, 2, 3 });
		backVAO.updateVB(0, {
			exitBL.x, exitBL.y - 80.0f,
			exitTR.x, exitBL.y - 80.0f,
			exitBL.x, exitTR.y - 80.0f,
			exitTR.x, exitTR.y - 80.0f,
			}, 0);
		backVAO.updateVB(0, {
				0.5f, 0.0f,
				1.0f, 0.0f,
				0.5f, 1.0f,
				1.0f, 1.0f,
			}, 1);

#pragma endregion

#pragma region Initializing Pause Menu

		pause.initialize("Resources/Textures/playPauseLogo.png", pixelArtFilter);
		menu.initialize("Resources/Textures/menu.png", pixelArtFilter);
		restart.initialize("Resources/Textures/restart.png", pixelArtFilter);

		infos.clear();
		infos.push_back(OGL::VBOInfo(0, GL_STATIC_DRAW, sizeof(float) * 2, { OGL::AttribInfo(0, 2, 0) }));
		infos.push_back(OGL::VBOInfo(1, GL_STATIC_DRAW, sizeof(float) * 2, { OGL::AttribInfo(1, 2, 0) }));

		pauseVAO.initialize(6, { 8, 8 }, infos);
		menuVAO.initialize(6, { 8, 8 }, infos);
		restartVAO.initialize(6, { 8, 8 }, infos);

		pauseVAO.updateEB(0, { 0, 1, 2, 1, 2, 3 });
		menuVAO.updateEB(0, { 0, 1, 2, 1, 2, 3 });
		restartVAO.updateEB(0, { 0, 1, 2, 1, 2, 3 });

		glm::vec2 pauseBL = glm::vec2(30.0f, Game::windowDimension.y - (30.0f + pause.getTextureDimensions().y * pauseScaler));
		glm::vec2 pauseTR = pauseBL + glm::vec2(pause.getTextureDimensions().x / 2.0f, pause.getTextureDimensions().y) * pauseScaler;

		pauseVAO.updateVB(0, {
				pauseBL.x, pauseBL.y,
				pauseTR.x, pauseBL.y,
				pauseBL.x, pauseTR.y,
				pauseTR.x, pauseTR.y,
			}, 0);

		pauseVAO.updateVB(0,
			{
				0.0f, 0.0f,
				0.5f, 0.0f,
				0.0f, 1.0f,
				0.5f, 1.0f,
			}, 1);

		glm::vec2 menuBL = glm::vec2((Game::windowDimension.x - menu.getTextureDimensions().x * 0.5f * menuScaler) / 2.0f, (Game::windowDimension.y - menu.getTextureDimensions().y - 200) / 2.0f);
		glm::vec2 menuTR = menuBL + glm::vec2(menu.getTextureDimensions().x/2.0f, menu.getTextureDimensions().y) * menuScaler;

		menuVAO.updateVB(0, {
				menuBL.x, menuBL.y,
				menuTR.x, menuBL.y,
				menuBL.x, menuTR.y,
				menuTR.x, menuTR.y,
			}, 0);

		menuVAO.updateVB(0, {
				0.5f, 0.0f,
				1.0f, 0.0f,
				0.5f, 1.0f,
				1.0f, 1.0f,
			}, 1);

		glm::vec2 restartBL = glm::vec2(50.0f, 100.0f);
		glm::vec2 restartTR = restartBL + glm::vec2(restart.getTextureDimensions()) * restartScaler;

		restartVAO.updateVB(0, {
				restartBL.x, restartBL.y,
				restartTR.x, restartBL.y,
				restartBL.x, restartTR.y,
				restartTR.x, restartTR.y,
			}, 0);

		restartVAO.updateVB(0, {
				0.0f, 0.0f,
				1.0f, 0.0f,
				0.0f, 1.0f,
				1.0f, 1.0f,
			}, 1);

#pragma endregion
	}

	void UI::drawUI()
	{
		if (game->state == GameState::PLAY || game->state == GameState::PAUSE || game->state == GameState::END)
		{
			game->uiColorProgram.use();
			game->uiColorProgram.uniMat4("projMatrix", game->cam.getProjectionMatrix());
			barVAO.bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

			game->uiTextureProgram.use();
			game->uiTextureProgram.uniMat4("projMatrix", game->cam.getProjectionMatrix());
			clockTexture.bind(0);
			game->uiTextureProgram.uni1i("tex", 0);
			clockVAO.bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

			keys.bind(0);
			keyVAO.bind();
			glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, nullptr);

			pause.bind(0);
			pauseVAO.bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

			game->atlas.renderText(getTime(), timePos, timeColor, timeFontSize, game->textProgram, game->cam);
			game->atlas.renderText(game->getKeyName(game->jumpButton), jumpButtonPos, timeColor, timeFontSize, game->textProgram, game->cam);
			game->atlas.renderText(game->getKeyName(game->leftButton), leftButtonPos, timeColor, timeFontSize, game->textProgram, game->cam);
			game->atlas.renderText(game->getKeyName(game->rightButton), rightButtonPos, timeColor, timeFontSize, game->textProgram, game->cam);
			game->atlas.renderText(game->getScore(), scorePos, timeColor, timeFontSize, game->textProgram, game->cam);

			if (game->state == GameState::PAUSE)
			{
				game->uiTextureProgram.use();
				game->uiTextureProgram.uni1i("tex", 0);
				game->uiTextureProgram.uniMat4("projMatrix", game->cam.getProjectionMatrix());

				menu.bind(0);
				menuVAO.bind();
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

				restart.bind(0);
				restartVAO.bind();
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

				game->atlas.renderText("PAUSED!", glm::vec2((Game::windowDimension.x - game->atlas.getTextWidth("PAUSED!", 3.0f)) / 2.0f, Game::windowDimension.y / 2.0f), timeColor, 3.0f, game->textProgram, game->cam);
			}
			if (game->state == GameState::END)
			{
				game->uiTextureProgram.use();
				game->uiTextureProgram.uni1i("tex", 0);
				game->uiTextureProgram.uniMat4("projMatrix", game->cam.getProjectionMatrix());

				menu.bind(0);
				menuVAO.bind();
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

				restart.bind(0);
				restartVAO.bind();
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

				game->atlas.renderText("Try Again!", glm::vec2((Game::windowDimension.x - game->atlas.getTextWidth("Try Again!", 3.0f)) / 2.0f, Game::windowDimension.y / 2.0f), timeColor, 3.0f, game->textProgram, game->cam);
			}
		}
		else if (game->state == GameState::MAIN_MENU)
		{
			game->uiTextureProgram.use();
			titleVAO.bind();
			title.bind(0);
			game->uiTextureProgram.uni1i("tex", 0);
			game->uiTextureProgram.uniMat4("projMatrix", game->cam.getProjectionMatrix());
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

			playButton.bind(0);
			playVAO.bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

			aboutButton.bind(0);
			aboutVAO.bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

			exitButton.bind(0);
			exitVAO.bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		}
		else if (game->state == GameState::ABOUT)
		{
			game->uiTextureProgram.use();
			game->uiTextureProgram.uniMat4("projMatrix", game->cam.getProjectionMatrix());
			aboutPage.bind(0);
			game->uiTextureProgram.uni1i("tex", 0);
			aboutPageVAO.bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

			exitButton.bind(0);
			backVAO.bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		}
	}

	void UI::updateUI(double dt)
	{
		if (game->state == GameState::PLAY)
		{
			if (++clockCounter > 59)
			{
				clockCounter = 0;
				clockIdx = (clockIdx + 1) % 8;

				game->twistTimer.y--;
				if (game->twistTimer.y < 4 && game->twistTimer.y > 0 && game->twistTimer.x == 0)
				{
					game->soloud.play(game->beep);
				}
				if (game->twistTimer.y < 0)
				{
					game->twistTimer.y = 59; game->twistTimer.x--;
					if (game->twistTimer.x < 0) game->twistTimer.x = 0;
				}

				std::vector<float> newCoords
				{
					0.125F * clockIdx, 0.0f,
					0.125F * clockIdx + 0.125f, 0.0f,
					0.125F * clockIdx, 1.0f,
					0.125F * clockIdx + 0.125f, 1.0f,
				};
				clockVAO.updateVB(0, newCoords, 1);
			}
			if (!setOnPlay)
			{
				setOnPlay = true;
				pauseVAO.updateVB(0, {
					0.0f, 0.0f,
					0.5f, 0.0f,
					0.0f, 1.0f,
					0.5f, 1.0f,
					}, 1);
			}
		}
		else if (game->state == GameState::MAIN_MENU)
		{
			if (prevIdx != game->menuIdx)
			{
				if (prevIdx == 0)
				{
					playVAO.updateVB(0, {
						0.0f, 0.0f,
						0.5f, 0.0f,
						0.0f, 1.0f,
						0.5f, 1.0f
						}, 1);
				}
				else if (prevIdx == 1)
				{
					aboutVAO.updateVB(0, {
						0.0f, 0.0f,
						0.5f, 0.0f,
						0.0f, 1.0f,
						0.5f, 1.0f
						}, 1);
				}
				else if (prevIdx == 2)
				{
					exitVAO.updateVB(0, {
						0.0f, 0.0f,
						0.5f, 0.0f,
						0.0f, 1.0f,
						0.5f, 1.0f
						}, 1);
				}

				if (game->menuIdx == 0)
				{
					playVAO.updateVB(0, {
						0.5f, 0.0f,
						1.0f, 0.0f,
						0.5f, 1.0f,
						1.0f, 1.0f
						}, 1);
				}
				else if (game->menuIdx == 1)
				{
					aboutVAO.updateVB(0, {
						0.5f, 0.0f,
						1.0f, 0.0f,
						0.5f, 1.0f,
						1.0f, 1.0f
						}, 1);
				}
				else
				{
					exitVAO.updateVB(0, {
						0.5f, 0.0f,
						1.0f, 0.0f,
						0.5f, 1.0f,
						1.0f, 1.0f
						}, 1);
				}
				prevIdx = game->menuIdx;
			}
		}
		else if (game->state == GameState::PAUSE)
		{
			if (setOnPlay)
			{
				setOnPlay = false;
				pauseVAO.updateVB(0, {
					0.5f, 0.0f,
					1.0f, 0.0f,
					0.5f, 1.0f,
					1.0f, 1.0f,
					}, 1);
			}
		}
	}

	std::string UI::getTime() const
	{
		auto getNumberAs2Digit = [&](int i)
			{
				if (i > 9) return std::to_string(i);
				else return std::string("0") + std::to_string(i);
			};
		return getNumberAs2Digit(game->twistTimer.x) + ":" + getNumberAs2Digit(game->twistTimer.y);
	}
}