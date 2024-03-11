#include "../Game.h"

namespace Game
{
	FloorManager::FloorManager()
	{
		floors[0].initializeFloor("Resources/Textures/floatingFloor.png", pixelArtFilter);
		floors[0].setPos(glm::vec2(600, 200));
		textureProgram.initialize("Resources/Shaders/Texture");
	}

	void FloorManager::drawFloors()
	{
		for (Floor& floor : floors) floor.draw(textureProgram);
	}

	void FloorManager::update(double dt)
	{
		for (Floor& floor : floors) floor.update();
	}

	const Floor& FloorManager::isColliding(Rectangle& hitbox) const
	{
		for (const Floor& floor : floors)
		{
			if (floor.rect.isColliding(hitbox) || hitbox.isColliding(floor.rect)) return floor;
		}
		return uninitializedFloor;
	}
}