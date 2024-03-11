#include "Shapes.h"

namespace Game
{
	bool Rectangle::isColliding(const Rectangle& other) const
	{
		return pos.x >= other.pos.x && pos.x <= other.pos.x + other.dim.x &&
			pos.y + dim.y >= other.pos.y && pos.y <= other.pos.y + other.dim.y;
	}
}