#pragma once
#include <GL\glew.h>
#include <GL\freeglut.h>
#include "shader_compilation_exception.h"
class shader
{
public:
	shader();
	shader(int shaderType, const char** shaderCode);
	~shader();
	unsigned int getShaderId();
	void create(int shaderType, const char** shaderCode);

private:
	unsigned int shaderId;
};

