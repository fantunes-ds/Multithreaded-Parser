#pragma once

namespace Debug::OpenGL::Shader
{
	class ShaderDebug
	{
	public:
		ShaderDebug() = delete;
		~ShaderDebug() = delete;

		static void CheckShaderErrors(GLuint& p_shaderId, const GLuint p_type);
		static void CheckLinkingShaderErrors(GLuint& p_programId);
	};
};
