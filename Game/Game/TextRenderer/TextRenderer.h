#ifndef _ACEROLA_GAME_JAM_TEXTRENDERER
#define _ACEROLA_GAME_JAM_TEXTRENDERER

#include "../../OGL/OGL.h"
#include "ft2build.h"
#include FT_FREETYPE_H

#include <array>

namespace Game
{
	struct CharGlyphInfo
	{
		glm::vec2 uv;
		glm::ivec2 bearing;
		glm::ivec2 advance;
		glm::ivec2 dimension;
		glm::vec2 normDimension;

		CharGlyphInfo() : uv(0.0F), bearing(0), advance(0), dimension(0), normDimension(0) {}
	};

	class TextTextureAtlas
	{
		public:
			TextTextureAtlas(std::string fontFileLoc);
			void renderText(std::string text, glm::vec2 pos, glm::vec4 color, float scale);

			float getTextWidth(std::string text, float scale) const;

		private:
			void updateSize();

		private:
			OGL::Texture2D m_Texture;
			OGL::VAO m_VAO;
			std::array<CharGlyphInfo, 96> chars;
			unsigned int m_CharacterCapacity = 1;
	};
}

#endif