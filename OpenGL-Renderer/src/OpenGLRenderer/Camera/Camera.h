#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace OpenGLRenderer
{
	class Camera
	{
	public:
		virtual const glm::mat4& GetProjectionMatrix() const = 0;
		virtual const glm::mat4& GetViewMatrix() const = 0;

		virtual const glm::vec3& GetPosition() const = 0;
		virtual const float GetRotation() const = 0;
	};
}