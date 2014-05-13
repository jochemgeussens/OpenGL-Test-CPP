#include "Shader.h"


shader::shader()
{
}

shader::shader(int shaderType, const char** shaderCode)
{
	create(shaderType, shaderCode);
}


shader::~shader()
{
}

void shader::create(int shaderType, const char** shaderCode)
{
	shaderId = glCreateShader(shaderType);
	glShaderSource(shaderId, 1, shaderCode, NULL);
	glCompileShader(shaderId);


	int parameters[1];
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, parameters);

	if (parameters[0] == GL_FALSE)
	{
		throw exception("Failed to compile shader.");
	}
}