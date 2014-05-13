#include "scene.h"
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

trefoil_knot knot;

// List of indices in the generated buffers 
// and ultimately the buffer IDs.
unsigned int ibo = 10;
unsigned int vert = 0;
unsigned int norm = 1;
unsigned int tCol1 = 2;
unsigned int tCol2 = 3;
unsigned int tCol3 = 4;
unsigned int tCol4 = 5;
unsigned int amb = 6;
unsigned int diff = 7;
unsigned int spec = 8;
unsigned int shini = 9;


unsigned int iboPos = 10;
unsigned int vertPos = 0;
unsigned int normPos = 1;
unsigned int tCol1Pos = 2;
unsigned int tCol2Pos = 3;
unsigned int tCol3Pos = 4;
unsigned int tCol4Pos = 5;
unsigned int ambPos = 6;
unsigned int diffPos = 7;
unsigned int specPos = 8;
unsigned int shiniPos = 9;

// Uniform positions
int lightPos = 0;
int modelView = 1;
int normMatrix = 2;
int projection = 3;

// Shader program;
int programId;

scene::scene()
{
}



scene::~scene()
{
}

void scene::drawGradientBackGround(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_QUADS);
	//bottom color
	glColor3d(0, 0, 0);
	glVertex2d(-1.0, -1.0);
	glVertex2d(1.0, -1.0);

	//top color
	glColor3d(0.573, 0.525, 0.737);
	glVertex2d(1.0, 1.0);
	glVertex2d(-1.0, 1.0);

	glEnd();
}

void scene::drawText(int x, int y, float r, float g, float b, void* font, string str) {
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	int len, i;
	len = str.length();
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(font, str.at(i));
	}
}


void scene::changeViewport(int w, int h){
	glViewport(0, 0, w, h);
}


void scene::init()
{
	// Create vert and frag NormalMaterialParticle shader.
	//scene::vertShader = shader(GL_VERTEX_SHADER, &NORMAL_MATERIAL_PARTICLE_VERT);
	auto vertShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShaderId, 1, &NORMAL_MATERIAL_PARTICLE_VERT, NULL);
	glCompileShader(vertShaderId);
	//scene::fragShader = shader(GL_FRAGMENT_SHADER, &NORMAL_MATERIAL_PARTICLE_FRAG);
	auto fragShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShaderId, 1, &NORMAL_MATERIAL_PARTICLE_FRAG, NULL);
	glCompileShader(fragShaderId);

	// Create Program from shaders.
	programId = glCreateProgram();
	glAttachShader(programId, vertShaderId);
	glAttachShader(programId, fragShaderId);

	glBindAttribLocation(programId, vertPos, "Position");
	glBindAttribLocation(programId, normPos, "Normal");
	glBindAttribLocation(programId, tCol1Pos, "TCol1");
	glBindAttribLocation(programId, tCol2Pos, "TCol2");
	glBindAttribLocation(programId, tCol3Pos, "TCol3");
	glBindAttribLocation(programId, tCol4Pos, "TCol4");
	glBindAttribLocation(programId, ambPos, "AmbientMaterial");
	glBindAttribLocation(programId, diffPos, "DiffuseMaterial");
	glBindAttribLocation(programId, specPos, "SpecularMaterial");
	glBindAttribLocation(programId, shiniPos, "ShininessValue");

	glLinkProgram(programId);


	knot = trefoil_knot();

	// Create the IBO and VBO's.
	GLuint buffers[11];
	glGenBuffers(11, buffers);
	ibo = buffers[iboPos];
	vert = buffers[vertPos];
	norm = buffers[normPos];
	tCol1 = buffers[tCol1Pos];
	tCol2 = buffers[tCol2Pos];
	tCol3 = buffers[tCol3Pos];
	tCol4 = buffers[tCol4Pos];
	amb = buffers[ambPos];
	diff = buffers[diffPos];
	spec = buffers[specPos];
	shini = buffers[shiniPos];

	auto indices = &knot.indices[0];
	// Set trefoil knot data.
	glBindBuffer(GL_ARRAY_BUFFER, ibo);
	glBufferData(GL_ARRAY_BUFFER, knot.indices.size() * sizeof(GLuint), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vert);
	glBufferData(GL_ARRAY_BUFFER, knot.vertices.size() * sizeof(GLfloat), &knot.vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, norm);
	glBufferData(GL_ARRAY_BUFFER, knot.normals.size() * sizeof(GLfloat), &knot.normals[0], GL_STATIC_DRAW);

	// Set transformation data.
	glBindBuffer(GL_ARRAY_BUFFER, tCol1);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(float), new float[4]{1, 0, 0, 0}, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, tCol2);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(float), new float[4]{0, 1, 0, 0}, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, tCol3);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(float), new float[4]{0, 0, 1, 0}, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, tCol4);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(float), new float[4]{0, 0, 0, 1}, GL_STATIC_DRAW);

	// Set material data.
	glBindBuffer(GL_ARRAY_BUFFER, amb);
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float), new float[3]{0, 200, 0}, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, diff);
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float), new float[3]{0, 200, 200}, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, spec);
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float), new float[3]{200, 200, 0}, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, shini);
	glBufferData(GL_ARRAY_BUFFER, 1 * sizeof(float), new float[1]{5}, GL_STATIC_DRAW);

	// Apply uniforms.
	glUseProgram(programId);
	glm::mat4 identity4 = glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	glm::mat3 identity3 = glm::mat3(1, 0, 0, 0, 1, 0, 0, 0, 1);
	
	
	glUniform3f(lightPos, 5, 10, 15);
	glUniformMatrix4fv(modelView, 1, false, glm::value_ptr(identity4));
	glUniformMatrix4fv(projection, 1, false, glm::value_ptr(identity4));
	glUniformMatrix3fv(normMatrix, 1, false, glm::value_ptr(identity3));
	glUseProgram(0);


	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
}
glm::mat4x4 modelViewMat = glm::mat4x4();
void scene::render()
{
	// Get start time.
	auto startTime = glutGet(GLUT_ELAPSED_TIME);

	modelViewMat= glm::rotate(modelViewMat, 0.5f, vec3(0, 1, 0));

	// Draw background.
	drawGradientBackGround();

	//Bind buffers.
	glUseProgram(programId);

	glUniformMatrix4fv(modelView, 1, false, glm::value_ptr(modelViewMat));


	glBindBuffer(GL_ARRAY_BUFFER, vert);
	glVertexAttribPointer(vertPos, 3, GL_FLOAT, false, 0, 0);
	glEnableVertexAttribArray(vertPos);

	glBindBuffer(GL_ARRAY_BUFFER, norm);
	glVertexAttribPointer(normPos, 3, GL_FLOAT, false, 0, 0);
	glEnableVertexAttribArray(normPos);


	glBindBuffer(GL_ARRAY_BUFFER, tCol1);
	glVertexAttribPointer(tCol1Pos, 4, GL_FLOAT, false, 0, 0);
	glVertexAttribDivisor(tCol1Pos, 1);
	glEnableVertexAttribArray(tCol1Pos);

	glBindBuffer(GL_ARRAY_BUFFER, tCol2);
	glVertexAttribPointer(tCol2Pos, 4, GL_FLOAT, false, 0, 0);
	glVertexAttribDivisor(tCol2Pos, 1);
	glEnableVertexAttribArray(tCol2Pos);

	glBindBuffer(GL_ARRAY_BUFFER, tCol3);
	glVertexAttribPointer(tCol3Pos, 4, GL_FLOAT, false, 0, 0);
	glVertexAttribDivisor(tCol3Pos, 1);
	glEnableVertexAttribArray(tCol3Pos);

	glBindBuffer(GL_ARRAY_BUFFER, tCol4);
	glVertexAttribPointer(tCol4Pos, 4, GL_FLOAT, false, 0, 0);
	glVertexAttribDivisor(tCol4Pos, 1);
	glEnableVertexAttribArray(tCol4Pos);


	glBindBuffer(GL_ARRAY_BUFFER, amb);
	glVertexAttribPointer(ambPos, 3, GL_FLOAT, false, 0, 0);
	glVertexAttribDivisor(ambPos, 1);
	glEnableVertexAttribArray(ambPos);

	glBindBuffer(GL_ARRAY_BUFFER, diff);
	glVertexAttribPointer(diffPos, 3, GL_FLOAT, false, 0, 0);
	glVertexAttribDivisor(diffPos, 1);
	glEnableVertexAttribArray(diffPos);

	glBindBuffer(GL_ARRAY_BUFFER, spec);
	glVertexAttribPointer(specPos, 3, GL_FLOAT, false, 0, 0);
	glVertexAttribDivisor(specPos, 1);
	glEnableVertexAttribArray(specPos);
	glBindBuffer(GL_ARRAY_BUFFER, shini);
	glVertexAttribPointer(shiniPos, 1, GL_FLOAT, false, 0, 0);
	glVertexAttribDivisor(shiniPos, 1);
	glEnableVertexAttribArray(shiniPos);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	glDrawElementsInstanced(GL_TRIANGLES, knot.indices.size(), GL_UNSIGNED_INT, 0, 1);
	glUseProgram(0);
		

	string myStr = "frame time = " + std::to_string(frameTime);
	drawText(-1, 0, 100, 100, 100, GLUT_BITMAP_TIMES_ROMAN_24, myStr);
	glutSwapBuffers();
	frameTime = glutGet(GLUT_ELAPSED_TIME) - startTime;
}
