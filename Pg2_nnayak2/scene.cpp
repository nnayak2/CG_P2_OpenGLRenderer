#include "scene.h"
#include <math.h>

scene* scene::sceneinstance = NULL;

scene* scene::getScene()
{
	if (sceneinstance == NULL)
		sceneinstance = new scene;
	return sceneinstance;
}

//HACK: This variable is a workaround for bug in tiny obj loader
std::map<std::string, tinyobj::material_t> workaroundMaterialStore;

void scene::loadScene(char *filename)
{
	tinyobj::LoadObj(shapes, filename, "./");
	
	//all this code is because tinyobj was spoiling materials in the shapes structure, so i'm reloadig them with this hack.
	for (std::vector<tinyobj::shape_t>::iterator iter = shapes.begin();
		iter != shapes.end(); iter++)
	{
		std::string shapeName = iter->name;
		std::map<std::string, tinyobj::material_t>::iterator it;
		it = workaroundMaterialStore.find(shapeName);
		iter->material = it->second;
	}
}

void scene::draw()
{
	GLuint tex_2d;
	glEnable(GL_TEXTURE_2D);
	tex_2d = SOIL_load_OGL_texture( "Crate.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0 );
	glBindTexture(GL_TEXTURE_2D, tex_2d);

	glViewport(0, 0, 512, 512);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (float)1, 1.0, 5000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(r_horz, 0.0, 1.0, 0.0);
	glRotatef(r_vert, 1.0, 0.0, 0.0);
	glTranslatef(0, 0, -10);

	if (light) glEnable(GL_LIGHTING);
	else glDisable(GL_LIGHTING);

	for (std::vector<tinyobj::shape_t>::iterator iter = shapes.begin();
		iter != shapes.end(); iter++)
	{
		for (std::vector<unsigned int>::iterator ind = iter->mesh.indices.begin();
			ind != iter->mesh.indices.end(); ind++)
		{
			GLfloat tri_ambient[] = { (iter->material).ambient[0], (iter->material).ambient[1], (iter->material).ambient[2], 1.0f };
			GLfloat tri_diffuse[] = { (iter->material).diffuse[0], (iter->material).diffuse[1], (iter->material).diffuse[2], 1.0f };
			GLfloat tri_specular[] = { (iter->material).specular[0], (iter->material).specular[1], (iter->material).specular[2], 1.0f };

			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, tri_ambient);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, tri_diffuse);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, tri_specular);

			glBegin(GL_TRIANGLES);
			glNormal3f(0.0f, 1.0f, 0.0f);

			glTexCoord2f(1.0f, 0.0f);
			glVertex3f((iter->mesh.positions)[*ind*3], (iter->mesh.positions)[*ind*3 +1], (iter->mesh.positions)[*ind*3 +2]);
			ind++;

			glTexCoord2f(0.0f, 1.0f);
			glVertex3f((iter->mesh.positions)[*ind*3], (iter->mesh.positions)[*ind*3 + 1], (iter->mesh.positions)[*ind*3 + 2]);
			ind++;

			glTexCoord2f(1.0f, 1.0f);
			glVertex3f((iter->mesh.positions)[*ind*3], (iter->mesh.positions)[*ind*3 + 1], (iter->mesh.positions)[*ind*3 + 2]);

			glEnd();
		}
	}
}