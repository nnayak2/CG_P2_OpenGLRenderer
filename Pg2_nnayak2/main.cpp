#include "main.h"

//Define all key press handlers here. Declaration of extern in header
int light = 1;

//Define my light source here
GLfloat LightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat LightDiffuse[] = { 0.6f, 0.6f, 0.6f, 1.0f };
GLfloat LightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[] = { 0.0f, 5.0f, 0.0f, 1.0f };

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'l':
		if (light) light = 0;
		else light = 1;
		break;
	}
}


void draw()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	scene::getScene()->draw();
	glutSwapBuffers();
}

void redraw()
{
	glutPostRedisplay();
}

void initialiseGLUT(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	glutCreateWindow("\t CSC561: Rasterization");

	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//enable light
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
	glEnable(GL_LIGHT0);

	//glDisable(GL_BLEND);

	glutKeyboardFunc(Keyboard);
	glutDisplayFunc(draw);
	glutIdleFunc(redraw);
	glutMainLoop();
}

int main(int argc, char* argv[])
{
	//This class loads the obj file, and does the intersection calculations
	scene *scn = scene::getScene();

	std::string obj = "cube2.obj";

	//load the obj file
	scn->loadScene(const_cast<char*>(obj.c_str()));

	initialiseGLUT(argc, argv);
}