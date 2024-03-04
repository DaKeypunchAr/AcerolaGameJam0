#ifndef _ACEROLA_GAME_JAM_H
#define _ACEROLA_GAME_JAM_H

#include "../OGL/OGL.h"
#include "Camera/Camera.h"

namespace Game
{
	class Game
	{
		public:
			Game(glm::uvec2 windowDimensions);
			~Game() = default;

			void draw();
			void update();

		private:
			Camera cam;

			OGL::VAO vao;
			OGL::Program program;
			OGL::Texture2D texture;

		private:
			/* Constants */
			const OGL::TextureFilters pixelArtFilter = { GL_NEAREST, GL_REPEAT };
	};
}

#endif