#pragma once
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include <ctime>
#include <string>
#include <netfw.h>
#include <vector>
#include <fstream>
#include <string>
#include "shader.h"
#include "shader_code.h"
#include "trefoil_knot.h"

using namespace std;

class scene
{
public:
	scene();
	~scene();
	void init();
	void render();
	void changeViewport(int w, int h);

private:
	shader vertShader;
	shader fragShader;
	int frameTime;

	void drawGradientBackGround();
	void drawText(int x, int y, float r, float g, float b, void* font, string str);
};

