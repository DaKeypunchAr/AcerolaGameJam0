#ifndef _ACEROLA_GAME_JAM_PLAYER_H
#define _ACEROLA_GAME_JAM_PLAYER_H

#include "../Entity/Entity.h"
#include "../Shapes/Shapes.h"

namespace Game
{
	class Game;

	class Player : public Entity
	{
		public:
			Player(const Game* const game);
			~Player() = default;

			void update(double dt);
			void solveCollisions();

			void handleAnimation();

		private:
			glm::vec2 vel;

			Rectangle hitbox;

			float maximumPlayerJumpHeight = 200.0F;
			float playerJumpXVel = 230.0F;
			float playerJumpPeakX = 130.0F;
			float playerJumpPeakToGroundX = 60.0F;

			float playerInitJumpVelY = 2 * maximumPlayerJumpHeight * playerJumpXVel / playerJumpPeakX;
			float jumpGravity = -playerInitJumpVelY * playerJumpXVel / playerJumpPeakX;
			float fallGravity = -2 * maximumPlayerJumpHeight * playerJumpXVel * playerJumpXVel / (playerJumpPeakToGroundX * playerJumpPeakToGroundX);

			float oldY = 0.0F;
			bool onFloor = false;
			float playerSpeed = 230.0F;
			float jumpVel = 130.0F;

			unsigned int maxAnimationCounter = 5;
			unsigned int animationCounter = 0;
			unsigned int animationIdx = 0;
			bool mirrorHorizontal = false;

		private:
			const Game* const game;

			const float playerSize = 4.5F;
	};
}

#endif