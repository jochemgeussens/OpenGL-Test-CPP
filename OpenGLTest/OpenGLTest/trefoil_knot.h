#pragma once
#include <glm.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <gl\glew.h>

using glm::vec3;
using std::vector;

class trefoil_knot
{
public:
	trefoil_knot();
	~trefoil_knot();

	vector<GLfloat> vertices;
	vector<GLfloat> normals;
	vector<GLuint> indices;

private:
	vec3 evaluateTrefoil(float s, float t);
	void createVertexNormalBuffer();
	void createIndexBuffer();
};

