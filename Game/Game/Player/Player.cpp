#include "../Game.h"

#include <iostream>

namespace Game
{
	Player::Player(Game* const game)
		: Entity(glm::vec2(0), glm::vec4(1), "Resources/Textures/player-Sheet.png", pixelArtFilter), game(game), vel()
	{
		m_TextureUVs = glm::vec4(0.0F, 0.0F, 1.0F / 9.0F, 1.0F);
		m_Position = game->floorManager.playerCoords();
		m_Size = glm::vec2(m_Texture.getTextureDimensions().x / 9.0F, m_Texture.getTextureDimensions().y)*playerSize;

		hitbox.setPos(m_Position);
		hitbox.setDimension(m_Size);
	}

	void Player::restart()
	{
		m_Position = game->floorManager.playerCoords();
		hitbox.setPos(m_Position);
		hitbox.setDimension(m_Size);
		vel.y = 0;
	}

	void Player::update(double dt)
	{
		solveCollisions();
		const Floor& collidedFloor = game->floorManager.isColliding(hitbox);
		onFloor = collidedFloor.initialized;

		if (!onFloor)
		{
			if (vel.y > 0) vel.y += jumpGravity * dt;
			else vel.y += fallGravity * dt;
		}

		vel.x = glfwGetKey(glfwGetCurrentContext(), game->rightButton) - glfwGetKey(glfwGetCurrentContext(), game->leftButton);
		vel.x *= (onFloor) ? playerSpeed : playerJumpXVel;

		if (onFloor && glfwGetKey(glfwGetCurrentContext(), game->jumpButton) && jumpLanded)
		{
			vel.y = playerInitJumpVelY;
			onFloor = false;
			jumpLanded = false;
		}

		oldY = m_Position.y;
		m_Position += vel * (float) dt;

		hitbox.setPos(m_Position);
		hitbox.setDimension(m_Size);

		solveCollisions();
		handleAnimation();

		if (m_Position.y < -game->cam.getTranslation().y)
		{
			game->state = GameState::END;
		}
	}

    void Player::solveCollisions()
    {
		const Floor& collidedFloor = game->floorManager.isColliding(hitbox);
        
		if (collidedFloor.initialized)
		{
			glm::vec2 floorTR = collidedFloor.getPos() + collidedFloor.getSize();

			if (vel.y <= 0 && oldY >= floorTR.y)
			{
				m_Position.y = floorTR.y;
				vel.y = 0;
				game->camTranslation = glm::vec2(0, -(collidedFloor.getPos().y - 300));
				jumpLanded = true;
			}
		}
    }

	void Player::handleAnimation()
	{
		animationCounter++;
		if (vel.x == 0)
		{
			animationCounter = 0;
			animationIdx = 0;
		}
		else if (vel.x > 0)
		{
			mirrorHorizontal = false;
			if (animationCounter == maxAnimationCounter)
			{
				animationCounter = 0;
				animationIdx = (animationIdx % 8) + 1;
			}
		}
		else if (vel.x < 0)
		{
			mirrorHorizontal = true;
			if (animationCounter == maxAnimationCounter)
			{
				animationCounter = 0;
				animationIdx = (animationIdx % 8) + 1;
			}
		}

		if (!mirrorHorizontal)
		{
			m_TextureUVs = glm::vec4(animationIdx * (1.0F / 9.0F), 0.0F, (animationIdx + 1) * (1.0F / 9.0F), 1.0F);
		}
		else
		{
			m_TextureUVs = glm::vec4((animationIdx + 1) * (1.0F / 9.0F), 0.0F, animationIdx * (1.0F / 9.0F), 1.0F);
		}
	}
}