#include "../Game.h"

namespace Game
{
	TextTextureAtlas::TextTextureAtlas(std::string fontFileLoc)
	{
		FT_Library lib; FT_Init_FreeType(&lib);
		FT_Face face; FT_New_Face(lib, fontFileLoc.c_str(), 0, &face);

		FT_Set_Pixel_Sizes(face, 0, 20.0F);

		FT_GlyphSlot g = face->glyph;

		auto max = [&](float x, float y) {
			return (x < y) ? y : x;
		};

		glm::vec2 dim(0);
		for (char c = 32; c < 128 && c > -1; c++)
		{
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				continue;
			}

			dim.x += g->bitmap.width;
			dim.y = max(dim.y, g->bitmap.rows);
		}

		m_Texture.initialize(dim, { GL_NEAREST, GL_REPEAT }, 1);

		float x{};
		for (char c = 32; c < 128 && c > -1; c++)
		{
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				continue;
			}

			unsigned int charIdx = c - 32;

			chars[charIdx].uv = { x / dim.x, 0.0F };
			chars[charIdx].dimension = { g->bitmap.width, g->bitmap.rows };
			chars[charIdx].normDimension = glm::vec2(chars[charIdx].dimension) / dim;
			chars[charIdx].bearing = { g->bitmap_left, g->bitmap_top };
			chars[charIdx].advance = { g->advance.x >> 6, g->advance.y >> 6 };

			if (!chars[charIdx].dimension.x || !chars[charIdx].dimension.y) continue;
			if (!g->bitmap.buffer) continue;

			m_Texture.subImage(glm::ivec2(x, 0), chars[charIdx].dimension, g->bitmap.buffer);

			x += chars[charIdx].dimension.x;
		}

		FT_Done_Face(face);
		FT_Done_FreeType(lib);

		std::vector<OGL::VBOInfo> vboInfos;
		vboInfos.push_back(OGL::VBOInfo(0, GL_DYNAMIC_DRAW, 2 * sizeof(float), { OGL::AttribInfo(0, 2, 0) }));
		vboInfos.push_back(OGL::VBOInfo(2, GL_DYNAMIC_DRAW, 4 * sizeof(float), { OGL::AttribInfo(1, 4, 0) }));
		vboInfos.push_back(OGL::VBOInfo(1, GL_DYNAMIC_DRAW, 2 * sizeof(float), { OGL::AttribInfo(2, 2, 0) }));
		m_VAO.initialize(m_CharacterCapacity * 6, { m_CharacterCapacity * 8, m_CharacterCapacity * 16, m_CharacterCapacity * 8 }, vboInfos);
		m_VAO.updateEB(0, { 0, 1, 2, 1, 2, 3 });
	}

	void TextTextureAtlas::updateSize()
	{
		std::vector<unsigned int> eBuffer;
		for (unsigned int i = 0; i < m_CharacterCapacity; i++)
		{
			unsigned int i4 = i * 4;
			eBuffer.push_back(i4);
			eBuffer.push_back(i4+1);
			eBuffer.push_back(i4+2);
			eBuffer.push_back(i4+1);
			eBuffer.push_back(i4+2);
			eBuffer.push_back(i4+3);
		}

		m_VAO.recreateEB(m_CharacterCapacity * 6, GL_STATIC_DRAW);
		m_VAO.updateEB(0, eBuffer);

		m_VAO.recreateVB(m_CharacterCapacity * 8, GL_DYNAMIC_DRAW, 0);
		m_VAO.recreateVB(m_CharacterCapacity * 16, GL_DYNAMIC_DRAW, 1);
		m_VAO.recreateVB(m_CharacterCapacity * 8, GL_DYNAMIC_DRAW, 2);
	}

	void TextTextureAtlas::renderText(std::string text, glm::vec2 pos, glm::vec4 color, float scale, const OGL::Program& program, const Camera& cam)
	{
		program.use();
		program.uniMat4("projMatrix", cam.getProjectionMatrix());

		unsigned int textLength = text.length();
		if (!textLength) return;
		m_Texture.bind(0);
		program.uni1i("tex", 0);

		if (m_CharacterCapacity < textLength)
		{
			m_CharacterCapacity = textLength;
			updateSize();
		}

		std::vector<float> posBuffer;
		std::vector<float> texCoordsBuffer;
		std::vector<float> colorBuffer;

		posBuffer.reserve(textLength * 8);
		texCoordsBuffer.reserve(textLength * 8);
		colorBuffer.reserve(textLength * 16);

		auto vectorPush = [&](std::vector<float>& vec, const std::vector<float>& other)
			{
				for (float f : other)
				{
					vec.push_back(f);
				}
			};

		glm::vec2 initialPosition = pos;

		unsigned int ch = 0;
		for (const char* c = text.c_str(); *c; c++, ch++)
		{
			if (*c != '\n')
			{
				if (((*c) - 32) < 0) continue;
				unsigned int charIdx = (*c) - 32;
				CharGlyphInfo info = chars[charIdx];

				glm::vec2 tl = glm::vec2(info.bearing) * scale + pos;
				glm::vec2 br = (glm::vec2(info.bearing) + glm::vec2(info.dimension.x, -info.dimension.y)) * scale + pos;

				vectorPush(posBuffer, {
					tl.x, tl.y,
					br.x, tl.y,
					tl.x, br.y,
					br.x, br.y,
					});

				vectorPush(texCoordsBuffer, {
					info.uv.s, info.uv.t,
					info.uv.s + info.normDimension.x, info.uv.t,
					info.uv.s, info.uv.t + info.normDimension.t,
					info.uv.s + info.normDimension.s, info.uv.t + info.normDimension.t
					});

				vectorPush(colorBuffer, {
						color.r, color.g, color.b, color.a,
						color.r, color.g, color.b, color.a,
						color.r, color.g, color.b, color.a,
						color.r, color.g, color.b, color.a,
					});

				pos += glm::vec2(info.advance) * scale;
			}
			else
			{
				pos = glm::vec2(initialPosition.x, pos.y - 30.0f * scale);
			}
		}

		m_VAO.updateVB(0, posBuffer, 0);
		m_VAO.updateVB(0, colorBuffer, 1);
		m_VAO.updateVB(0, texCoordsBuffer, 2);

		m_VAO.bind();
		glDrawElements(GL_TRIANGLES, 6 * textLength, GL_UNSIGNED_INT, nullptr);
	}

	float TextTextureAtlas::getTextWidth(std::string text, float scale) const
	{
		float width{};
		for (char c : text) width += chars[c - 32].advance.x;
		return width * scale;
	}
}