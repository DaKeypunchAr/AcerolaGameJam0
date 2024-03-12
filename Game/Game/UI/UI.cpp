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
	}

	void UI::drawUI()
	{
		game->uiColorProgram.use();
		game->uiColorProgram.uniMat4("viewMatrix", game->cam.getViewMatrix());
		game->uiColorProgram.uniMat4("projMatrix", game->cam.getProjectionMatrix());
		barVAO.bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		game->uiTextureProgram.use();
		game->uiTextureProgram.uniMat4("viewMatrix", game->cam.getViewMatrix());
		game->uiTextureProgram.uniMat4("projMatrix", game->cam.getProjectionMatrix());
		clockTexture.bind(0);
		game->uiTextureProgram.uni1i("tex", 0);
		clockVAO.bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		keys.bind(0);
		keyVAO.bind();
		glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, nullptr);

		game->atlas.renderText(getTime(), timePos, timeColor, timeFontSize, game->textProgram, game->cam);
		game->atlas.renderText(game->getKeyName(game->jumpButton), jumpButtonPos, timeColor, timeFontSize, game->textProgram, game->cam);
		game->atlas.renderText(game->getKeyName(game->leftButton), leftButtonPos, timeColor, timeFontSize, game->textProgram, game->cam);
		game->atlas.renderText(game->getKeyName(game->rightButton), rightButtonPos, timeColor, timeFontSize, game->textProgram, game->cam);
		game->atlas.renderText(game->getScore(), scorePos, timeColor, timeFontSize, game->textProgram, game->cam);
	}

	void UI::updateUI(double dt)
	{
		if (++clockCounter > 59)
		{
			clockCounter = 0;
			clockIdx = (clockIdx + 1) % 8;

			game->twistTimer.y--;
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