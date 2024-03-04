#ifndef _ACEROLA_GAME_CAM_H
#define _ACEROLA_GAME_CAM_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Game
{
	class Camera
	{
		public:
			Camera(glm::vec2 xbounds, glm::vec2 ybounds)
				: m_Pos(), m_CamXBounds(xbounds), m_CamYBounds(ybounds) {}
			~Camera() = default;

			glm::mat4 getViewMatrix() const
			{
				return glm::lookAt(glm::vec3(m_Pos.x, m_Pos.y, -3.0F), glm::vec3(m_Pos.x, m_Pos.y, 100.0F), glm::vec3(0.0F, 1.0F, 0.0F));
			}
			glm::mat4 getProjectionMatrix() const
			{
				return glm::ortho(m_CamXBounds.x, m_CamXBounds.y, m_CamYBounds.x, m_CamYBounds.y);
			}

			void setPosition(glm::vec2 pos) { m_Pos = pos; }
			glm::vec2 getPosition() const { return m_Pos; }

		private:
			glm::vec2 m_Pos;
			const glm::vec2 m_CamYBounds;
			const glm::vec2 m_CamXBounds;
	};
}

#endif