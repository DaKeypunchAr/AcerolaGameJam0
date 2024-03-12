#ifndef _ACEROLA_GAME_JAM_ENTITY_H
#define _ACEROLA_GAME_JAM_ENTITY_H

#include "../../OGL/OGL.h"

namespace Game
{
	class Camera;
	class Entity
	{
		public:
			Entity() = default;
			Entity(glm::vec2 size, glm::vec4 color, std::string imageLocation, OGL::TextureFilters filters);
			~Entity() = default;

			void draw(const OGL::Program& program, const Camera& cam);

			void setPos(glm::vec2);
			glm::vec2 getPos() const;

			void setSize(glm::vec2);
			glm::vec2 getSize() const;

			void setColor(glm::vec4);
			glm::vec4 getColor() const;

			void setUVs(glm::vec4 uv);
			glm::vec4 getUVs() const;

			void initialize(glm::vec2 size, glm::vec4 color, std::string imageLocation, OGL::TextureFilters filters);

		protected:
			glm::vec2 m_Position;
			glm::vec2 m_Size;
			glm::vec4 m_Color;
			OGL::Texture2D m_Texture;
			glm::vec4 m_TextureUVs;

		private:
			OGL::VAO m_VAO;
	};
}

#endif