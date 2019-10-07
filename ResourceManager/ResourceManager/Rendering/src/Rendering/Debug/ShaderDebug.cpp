#include <stdafx.h>

#include <Rendering/Debug/ShaderDebug.h>

#include <sstream>
#include <iostream>

using namespace Debug::OpenGL::Shader;

void ShaderDebug::CheckShaderErrors(GLuint& p_shaderId, const GLuint p_type)
{
	GLint statusCompilation;

	glGetShaderiv(p_shaderId, GL_COMPILE_STATUS, &statusCompilation);
	if (statusCompilation == GL_FALSE)
	{
		GLint lengthMessage = 0;
		glGetShaderiv(p_shaderId, GL_INFO_LOG_LENGTH, &lengthMessage);
		GLchar* message = new char[lengthMessage];

		glGetShaderInfoLog(p_shaderId, lengthMessage, &lengthMessage, message);

		std::cerr << "Shader compilation failed [" << static_cast<const std::string>(
			p_type == GL_VERTEX_SHADER
			? "VERTEX SHADER] : "
			: "FRAGMENT SHADER] : ")
			<< message;

		glDeleteShader(p_shaderId);
		p_shaderId = 0;
		delete[] message;
	}
}

void ShaderDebug::CheckLinkingShaderErrors(GLuint& p_programId)
{
	GLint statusLinking;

	glGetProgramiv(p_programId, GL_LINK_STATUS, &statusLinking);
	if (statusLinking == GL_FALSE)
	{
		GLint lengthMessage = 0;
		glGetProgramiv(p_programId, GL_INFO_LOG_LENGTH, &lengthMessage);
		GLchar* message = new char[lengthMessage];

		glGetProgramInfoLog(p_programId, lengthMessage, &lengthMessage, message);

		std::cerr << "Shader compilation failed [SHADER PROGRAM] : "
			<< static_cast<std::string>(message);

		glDeleteProgram(p_programId);
		p_programId = 0;
		delete[] message;
	}
}
