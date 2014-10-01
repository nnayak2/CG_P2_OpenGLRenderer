#include "main.h"

//Define all key press handlers here. Declaration of extern in header
int light = 1;
int xx = 0, yy = 0, zz = 0, rot = 0;
float scale = 1.0f;
int activeTex = 0;

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

	case 'z':
		scale += 0.1f;
		break;
	case 'x':
		scale -= 0.1f;
		break;

	case '[':
		zz++;
		break;
	case ']':
		zz--;
		break;

	case 'q':
		rot++;
		break;
	case 'w':
		rot--;
		break;

   case ',':
      (activeTex - 1 < 0) ? 0 : activeTex--;
      break;
   case '.':
      (activeTex + 1 >= scene::getScene()->texNum) ? scene::getScene()->texNum - 1 : activeTex++;
      break;
	}
}

void SpecialInput(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		yy++;
		break;
	case GLUT_KEY_DOWN:
		yy--;
		break;
	case GLUT_KEY_LEFT:
		xx--;
		break;
	case GLUT_KEY_RIGHT:
		xx++;
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
	glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
   glEnable(GL_CULL_FACE);
   glCullFace(GL_BACK);

	//enable light
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
	glEnable(GL_LIGHT0);

	//glDisable(GL_BLEND);
   scene *scn = scene::getScene();
   scn->loadTextures();

	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialInput);
	glutDisplayFunc(draw);
	glutIdleFunc(redraw);
	glutMainLoop();
}

int main(int argc, char* argv[])
{
	//This class loads the obj file, and does the intersection calculations
	scene *scn = scene::getScene();

	std::string obj = "cube-textures.obj";

	//load the obj file
	scn->loadScene(const_cast<char*>(obj.c_str()));

	initialiseGLUT(argc, argv);
}