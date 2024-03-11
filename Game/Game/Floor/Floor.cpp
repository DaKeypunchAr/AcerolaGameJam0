#include "Floor.h"

namespace Game
{
	Floor::Floor(std::string imageLocation, OGL::TextureFilters filters)
		: rect()
	{
		initializeFloor(imageLocation, filters);
	}

	void Floor::initializeFloor(std::string imageLocation, OGL::TextureFilters filters)
	{
		initialize(glm::vec2(0.0F), glm::vec4(0.0F), imageLocation, filters);
		m_Size = glm::vec2(m_Texture.getTextureDimensions()) * 4.5F;
		m_TextureUVs = glm::vec4(0.0F, 0.0F, 1.0F, 1.0F);
		rect.dim = m_Size;
		initialized = true;
	}

	void Floor::update()
	{
		rect.pos = m_Position;
	}
}