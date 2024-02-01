#include "glpch.h"
#include "PerspectiveCamera.h"

namespace OpenGLRenderer
{
	PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float nearPlane, float farPlane)
		: m_ProjectionMatrix(glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane)),
		m_ViewMatrix(glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp))
	{
	}
}