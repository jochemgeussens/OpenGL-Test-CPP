//#if __cplusplus <= 199711L
//#error This library needs at least a C++11 compliant compiler
//#endif


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
#include "scene.h"

using namespace std;


scene myScene = scene();
int fps = 240;
int frameTime = 1000 / fps;
int start;


void readTextResource(string path){
	string line;
	ifstream myfile(path);
	if (myfile.is_open())
	{
		while (myfile.good())
		{
			getline(myfile, line);
			cout << line << endl;
		}
		myfile.close();
	}

	else cout << "Unable to open file";
}

void timerTick(int t){
	// Reset timer
	glutTimerFunc(0, timerTick, 0);

	// Animation code

	// Update display
	glutPostRedisplay();
}

//void changeViewport(int w, int h){
//	glViewport(0, 0, w, h);
//}
//
//void drawGradientBackGround(){
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	glBegin(GL_QUADS);
//	//bottom color
//	glColor3d(0, 0, 0);
//	glVertex2d(-1.0, -1.0);
//	glVertex2d(1.0, -1.0);
//
//	//top color
//	glColor3d(0.573, 0.525, 0.737);
//	glVertex2d(1.0, 1.0);
//	glVertex2d(-1.0, 1.0);
//
//	glEnd();
//}
//
//void drawText(int x, int y, float r, float g, float b, void* font, string str) {
//	glColor3f(r, g, b);
//	glRasterPos2f(x, y);
//	int len, i;
//	len = str.length();
//	for (i = 0; i < len; i++) {
//		glutBitmapCharacter(font, str.at(i));
//	}
//}
//
//void render() {
//	unsigned int start = clock();
//	drawGradientBackGround();
//
//
//	auto currentTime = glutGet(GLUT_ELAPSED_TIME);
//	string myStr = "frame time = " + std::to_string(currentTime - lastTime);
//	lastTime = currentTime;
//	drawText(-1, 0, 100, 100, 100, GLUT_BITMAP_TIMES_ROMAN_24, myStr);
//	glutSwapBuffers();
//	//frametime = clock() - start;
//}



void changeViewport(int x, int y) {
	myScene.changeViewport(x, y);
}

void render(){
	myScene.render();
}


int main(int argc, char** argv) {
	// Inititialize window.
	glutInit(&argc, argv);


	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowSize(800, 600);

	glutCreateWindow("OpenGL test, using C++.");
	glutReshapeFunc(changeViewport);
	glutDisplayFunc(render);


	GLenum err = glewInit();
	if (err != GLEW_OK) {
		fprintf(stderr, "GLEW error");
		return 1;
	}

	// Initialize our scene.
	myScene.init();

	// Start timer.
	glutTimerFunc(0, timerTick, 0);

	glutMainLoop();
	return 0;
}