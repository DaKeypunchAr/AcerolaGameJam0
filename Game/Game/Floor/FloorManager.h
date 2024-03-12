#ifndef _ACEROLA_GAME_JAM_FLOOR_MANAGER
#define _ACEROLA_GAME_JAM_FLOOR_MANAGER

#include "Floor.h"

#include <array>

namespace Game
{
	class Game;
	class Camera;
	class FloorManager
	{
		public:
			FloorManager(const Game* const game);
			~FloorManager() = default;

			void drawFloors(const Camera& cam);
			void update(double dt);

			const Floor& isColliding(Rectangle& hitbox) const;
			glm::vec2 playerCoords() const;

		private:
			std::array<Floor, 10> floors;
			OGL::Program textureProgram;
			Floor uninitializedFloor;
			Floor* highestFloor;
			float highestY = 300;
			float yDiff = 250;
			float maximumFloorOffset = 300.0f;
			const Game* const game;
	};
}

#endif