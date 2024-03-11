#ifndef _ACEROLA_GAME_JAM_SHAPES
#define _ACEROLA_GAME_JAM_SHAPES

#include "glm/glm.hpp"

namespace Game
{
	class Rectangle
	{
		public:
			Rectangle()
				: pos(0), dim(0) {}
			Rectangle(glm::vec2 pos, glm::vec2 dimension)
				: pos(pos), dim(dimension) {}
			Rectangle(glm::vec2 dimension)
				: pos(0), dim(dimension) {}

			void setPos(glm::vec2 pos) { this->pos = pos; }
			glm::vec2 getPos() const { return pos; }

			void setDimension(glm::vec2 dim) { this->dim = dim; }
			glm::vec2 getDimension() const { return dim; }

			bool isColliding(const Rectangle& rect) const;

			glm::vec2 pos, dim;
	};
}

#endif