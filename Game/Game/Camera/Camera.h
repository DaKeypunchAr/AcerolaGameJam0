#ifndef _ACEROLA_GAME_CAM_H
#define _ACEROLA_GAME_CAM_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Game
{
	class Camera
	{
		public:
			Camera(glm::vec2 windowSize)
				: m_Translation(0), m_WindowSize(windowSize) {}
			~Camera() = default;

			glm::mat4 getViewMatrix() const
			{
				return glm::translate(glm::mat4(1.0f), glm::vec3(m_Translation, 0.0f));
			}
			glm::mat4 getProjectionMatrix() const
			{
				return glm::ortho(0.0f, m_WindowSize.x,
					0.0f, m_WindowSize.y,
					-1.0f, 1.0f);
			}

			void setTranslation(glm::vec2 translation) { m_Translation = translation; }
			glm::vec2 getTranslation() const { return m_Translation; }

		private:
			glm::vec2 m_Translation;
			const glm::vec2 m_WindowSize;
	};
}

#endif