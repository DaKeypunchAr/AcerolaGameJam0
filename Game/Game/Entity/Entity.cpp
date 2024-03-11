#include "../Game.h"

namespace Game
{
	Entity::Entity(glm::vec2 size, glm::vec4 color, std::string imageLocation, OGL::TextureFilters filters)
		: m_Position(), m_Size(size), m_VAO(), m_Color(color), m_Texture(), m_TextureUVs(0.0F, 0.0F, 1.0F, 1.0F)
	{
		initialize(size, color, imageLocation, filters);
	}
	void Entity::initialize(glm::vec2 size, glm::vec4 color, std::string imageLocation, OGL::TextureFilters filters)
	{
		m_Size = size;
		m_Color = color;

		std::vector<unsigned int> eb{ 0, 1, 2, 1, 2, 3 };

		// VBO Format: VBO 0 - Position, VBO 1 - Color, VBO 2 - TextureCoords
		std::vector<OGL::VBOInfo> vboInfos
		{
			OGL::VBOInfo(0, GL_DYNAMIC_DRAW, 2 * sizeof(float), { OGL::AttribInfo(0, 2, 0)}),
			OGL::VBOInfo(1, GL_DYNAMIC_DRAW, 4 * sizeof(float), { OGL::AttribInfo(1, 4, 0)}),
			OGL::VBOInfo(2, GL_DYNAMIC_DRAW, 2 * sizeof(float), { OGL::AttribInfo(2, 2, 0)}),
		};

		m_VAO.initialize(eb.size(), { 8, 16, 8 }, vboInfos);
		m_VAO.updateEB(0, eb);

		m_Texture.initialize(imageLocation, filters);
	}

	void Entity::setPos(glm::vec2 pos)
	{
		m_Position = pos;
	}
	glm::vec2 Entity::getPos() const
	{
		return m_Position;
	}
	void Entity::setSize(glm::vec2 size)
	{
		m_Size = size;
	}
	glm::vec2 Entity::getSize() const
	{
		return m_Size;
	}
	void Entity::setColor(glm::vec4 color)
	{
		m_Color = color;
	}
	glm::vec4 Entity::getColor() const
	{
		return m_Color;
	}
	void Entity::setUVs(glm::vec4 uv)
	{
		m_TextureUVs = uv;
	}
	glm::vec4 Entity::getUVs() const { return m_TextureUVs; }

	void Entity::draw(const OGL::Program& program)
	{
		glm::vec2 normBL = Game::normalizedScreenSpace(m_Position);
		glm::vec2 normTR = Game::normalizedScreenSpace(m_Position + m_Size);

		std::vector<float> posVB
		{
			normBL.x, normBL.y,
			normTR.x, normBL.y,
			normBL.x, normTR.y,
			normTR.x, normTR.y
		};

		m_VAO.updateVB(0, posVB, 0);

		std::vector<float> colorVB
		{
			m_Color.r, m_Color.g, m_Color.b, m_Color.a,
			m_Color.r, m_Color.g, m_Color.b, m_Color.a,
			m_Color.r, m_Color.g, m_Color.b, m_Color.a,
			m_Color.r, m_Color.g, m_Color.b, m_Color.a,
		};

		m_VAO.updateVB(0, colorVB, 1);

		std::vector<float> textureUVs
		{
			m_TextureUVs.x, m_TextureUVs.y,
			m_TextureUVs.z, m_TextureUVs.y,
			m_TextureUVs.x, m_TextureUVs.w,
			m_TextureUVs.z, m_TextureUVs.w,
		};

		m_VAO.updateVB(0, textureUVs, 2);

		m_VAO.bind();
		program.use();

		m_Texture.bind(0);
		program.uni1i("tex", 0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}

	constexpr glm::vec2 Game::normalizedScreenSpace(glm::vec2 p)
	{
		glm::vec2 slope = glm::vec2(2.0F) / glm::vec2(windowDimension.x, windowDimension.y);
		return p * slope - glm::vec2(1.0F);
	}
}