#ifndef _ACEROLA_GAME_JAM_FLOOR_MANAGER
#define _ACEROLA_GAME_JAM_FLOOR_MANAGER

#include "Floor.h"

#include <array>

namespace Game
{
	class Game;
	class FloorManager
	{
		public:
			FloorManager();
			~FloorManager() = default;

			void drawFloors();
			void update(double dt);

			const Floor& isColliding(Rectangle& hitbox) const;

		private:
			std::array<Floor, 1> floors;
			OGL::Program textureProgram;
			Floor uninitializedFloor;
	};
}

#endif