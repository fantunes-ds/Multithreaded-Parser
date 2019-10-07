#pragma once

#include <Rendering/Context/IWindow.h>
#include <glm/glm.hpp>

namespace Rendering::LowRenderer
{
	struct API_RENDERING LightSource
	{
		glm::vec3 Position;
		glm::vec3 Ambient;
		glm::vec3 Diffuse;
		glm::vec3 Specular;
		glm::vec3 Direction;
	};
		
}

