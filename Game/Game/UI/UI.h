#ifndef _ACEROLA_GAME_JAM_UI
#define _ACEROLA_GAME_JAM_UI

#include "../../OGL/OGL.h"

namespace Game
{
	class UI
	{
		public:
			UI(Game* const game) : game(game) { initialize(); }
			~UI() = default;

			void drawUI();
			void updateUI(double dt);

		private:
			void initialize();
			std::string getTime() const;

		private:
			float scalingFactor = 4.0F;

			/* Bar Stuff */
			OGL::VAO barVAO;
			glm::vec4 barColor = glm::vec4(69, 3, 3, 255) / 255.0f;
			float barHeight = 20.0F;

			/* Clock Stuff */
			OGL::Texture2D clockTexture;
			OGL::VAO clockVAO;
			unsigned int clockCounter;
			unsigned int clockIdx;
			float clockScale = 7.0F;

			glm::vec2 timePos;
			glm::vec4 timeColor = glm::vec4(30, 87, 156, 255) / 255.0f;
			float timeFontSize = 1.0f;

			/* Keys stuff */
			OGL::Texture2D keys;
			OGL::VAO keyVAO;
			float paddingX = 6.0F;
			float paddingY = 4.0F;

			glm::vec2 leftButtonPos, rightButtonPos, jumpButtonPos, scorePos;

			Game* const game;
	};
}

#endif