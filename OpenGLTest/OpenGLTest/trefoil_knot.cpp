#include "trefoil_knot.h"

/// The number of slices and stacks.
const int slices = 128;
const int stacks = 32;
const int vertexCount = slices * stacks;


trefoil_knot::trefoil_knot()
{
	this->vertices.resize(vertexCount * 3); // * 3 for convert vec3 to float[3]
	this->normals.resize(vertexCount * 3); // * 3 for convert vec3 to float[3]
	this->indices.resize(vertexCount * 6);

	createIndexBuffer();
	createVertexNormalBuffer();
}


trefoil_knot::~trefoil_knot()
{
}

vec3 trefoil_knot::evaluateTrefoil(float s, float t)
{
	const float TwoPi = 2 * M_PI;

	float a = 0.5f;
	float b = 0.3f;
	float c = 0.5f;
	float d = 0.1f;
	float u = (1 - s) * 2 * TwoPi;
	float v = t * TwoPi;
	float r = (float)(a + b * glm::cos(1.5f * u));
	float x = (float)(r * glm::cos(u));
	float y = (float)(r * glm::sin(u));
	float z = (float)(c * glm::sin(1.5f * u));
	
	vec3 dv = vec3();
	dv.x = (float)(-1.5f * b * glm::sin(1.5f * u) * glm::cos(u) - (a + b * glm::cos(1.5f * u)) * glm::sin(u));
	dv.y = (float)(-1.5f * b * glm::sin(1.5f * u) * glm::sin(u) + (a + b * glm::cos(1.5f * u)) * glm::cos(u));
	dv.z = (float)(1.5f * c * glm::cos(1.5f * u));

	vec3 q = glm::normalize(dv);
	vec3 qvn = glm::normalize(vec3(q.y, -q.x, 0.0f));
	vec3 ww = glm::cross(q, qvn);

	vec3 range = vec3();
	range.x = (float)(x + d * (qvn.x * glm::cos(v) + ww.x * glm::sin(v)));
	range.y = (float)(y + d * (qvn.y * glm::cos(v) + ww.y * glm::sin(v)));
	range.z = (float)(z + d * ww.z * glm::sin(v));

	return range;
}

void trefoil_knot::createVertexNormalBuffer()
{

	auto countVert = 0;
	auto countNorm = 0;

	float ds = 1.0f / slices;
	float dt = 1.0f / stacks;

	// The upper bounds in these loops are tweaked to reduce the
	// chance of precision error causing an incorrect # of iterations.

	for (float s = 0; s < 1 - ds / 2; s += ds)
	{
		for (float t = 0; t < 1 - dt / 2; t += dt)
		{
			const float E = 0.01f;
			vec3 p = evaluateTrefoil(s, t);
			vec3 u = evaluateTrefoil(s + E, t) - p;
			vec3 v = evaluateTrefoil(s, t + E) - p;
			vec3 n = glm::normalize(glm::cross(u, v));
			for (int i = 0; i < 3; i++)
			{
				vertices[countVert] = p[i];
				normals[countNorm] = n[i];
				countVert ++;
				countNorm++;
			}
		}
	}
}

void trefoil_knot::createIndexBuffer()
{
	auto count = 0;

	int n = 0;
	for (int i = 0; i < slices; i++)
	{
		for (int j = 0; j < stacks; j++)
		{
			indices[count++] = (GLuint)n + j;
			indices[count++] = (GLuint)((n + (j + 1) % stacks));
			indices[count++] = (GLuint)(((n + j + stacks) % vertexCount));

			indices[count++] = (GLuint)(((n + j + stacks) % vertexCount));
			indices[count++] = (GLuint)(((n + (j + 1) % stacks) % vertexCount));
			indices[count++] = (GLuint)(((n + (j + 1) % stacks + stacks) % vertexCount));
		}

		n += (int)stacks;
	}
}