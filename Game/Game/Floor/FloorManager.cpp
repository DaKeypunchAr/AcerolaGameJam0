#include "../Game.h"

namespace Game
{
	FloorManager::FloorManager(const Game* const game)
		: game(game)
	{
		bool first = true;
		for (unsigned int i = 0; i < floors.size(); i++)
		{
			floors[i].initializeFloor("Resources/Textures/floatingFloor.png", pixelArtFilter);
			std::random_device rd;
			std::mt19937 gen(rd());
			if (i == 0)
			{
				std::uniform_real_distribution<float> distribution(0.0f, 1920.0f - floors[i].getSize().x);
				floors[i].setPos(glm::vec2(distribution(gen), highestY));
			}
			else
			{
				float lowerX = floors[i - 1].getPos().x - (floors[i].getSize().x + maximumFloorOffset);
				if (lowerX < 10) lowerX = 10.0f;
				float greaterX = floors[i - 1].getPos().x + floors[i].getSize().x + maximumFloorOffset;
				if (greaterX > 1920.0f - floors[i].getSize().x) greaterX = 1920.0f - floors[i].getSize().x;
				std::uniform_real_distribution<float> distribution(lowerX, greaterX);
				floors[i].setPos(glm::vec2(distribution(gen), highestY));
			}
			highestY += yDiff;
			first = false;
		}
		highestFloor = &floors[floors.size() - 1];
	}

	void FloorManager::drawFloors(const Camera& cam)
	{
		for (Floor& floor : floors) floor.draw(game->gameTextureProgram, cam);
	}

	void FloorManager::update(double dt)
	{
		for (Floor& floor : floors)
		{
			if (floor.getPos().y < -game->cam.getTranslation().y)
			{
				std::random_device rd;
				std::mt19937 gen(rd());
				float lowerX = highestFloor->getPos().x - (highestFloor->getSize().x + maximumFloorOffset);
				if (lowerX < 10) lowerX = 10.0f;
				float greaterX = highestFloor->getPos().x + highestFloor->getSize().x + maximumFloorOffset;
				if (greaterX > 1920.0f - highestFloor->getSize().x) greaterX = 1920.0f - highestFloor->getSize().x;
				std::uniform_real_distribution<float> distribution(lowerX, greaterX);
				floor.setPos(glm::vec2(distribution(gen), highestY));
				highestFloor = &floor;
				highestY += yDiff;
			}
			floor.update();
		}
	}

	const Floor& FloorManager::isColliding(Rectangle& hitbox) const
	{
		for (const Floor& floor : floors)
		{
			if (floor.rect.isColliding(hitbox) || hitbox.isColliding(floor.rect)) return floor;
		}
		return uninitializedFloor;
	}
	
	glm::vec2 FloorManager::playerCoords() const
	{
		return glm::vec2(floors[0].getPos().x + floors[0].getSize().x/2.0f, floors[0].getPos().y + floors[0].getSize().y);
	}
}