#pragma once

#include <Rendering/Export.h>

namespace Rendering::Resources
{
	class API_RENDERING Texture
	{
	public:
		Texture();
		~Texture();

		void Bind() const;
		void Unbind() const;

		void Load(const std::string& p_filepath);

		bool IsTextureSet() const { return m_loaded; }

	private:
		GLuint m_id{ 0u };
		bool m_loaded{false};
	};
}
