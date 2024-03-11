#ifndef _ACEROLA_GAME_JAM_FLOOR
#define _ACEROLA_GAME_JAM_FLOOR

#include "../Entity/Entity.h"
#include "../Shapes/Shapes.h"

namespace Game
{
	class Floor : public Entity
	{
		public:
			Floor() : rect() {};
			Floor(std::string imageLocation, OGL::TextureFilters filters);

			void initializeFloor(std::string imageLocation, OGL::TextureFilters filters);
			void update();

			Rectangle rect;
			bool initialized = false;
	};
}

#endif