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
		std::string shapeName = iter->material.name;
		std::map<std::string, tinyobj::material_t>::iterator it;
		it = workaroundMaterialStore.find(shapeName);
		iter->material = it->second;
	}
}

void scene::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_COLOR_MATERIAL);
	
	//GLuint tex_2d;
	
	//tex_2d = SOIL_load_OGL_texture("Crate.bmp", SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, 0);
	glBindTexture(GL_TEXTURE_2D, textures[activeTex]);
	
	glViewport(0, 0, 512, 512);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (float)1, 1.0, 5000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//glScalef(2.0f, 2.0f, 2.0f);
	glTranslatef(0, 0, -10);

	if (light) glEnable(GL_LIGHTING);
	else glDisable(GL_LIGHTING);

	//Don't apply the transformations to light source
	glPushMatrix();

	glScalef(scale, scale, scale);

	glTranslatef(xx, 0.0f, 0.0f);
	glTranslatef(0.0f, yy, 0.0f);
	glTranslatef(0.0f, 0.0f, zz);

	glRotatef(rot, 1.0f, 1.0f, 1.0f);

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

			//Read and store individual vertices, normals and tex coords of the triangle
			glm::vec3 v1((iter->mesh.positions)[*ind * 3], (iter->mesh.positions)[*ind * 3 + 1], (iter->mesh.positions)[*ind * 3 + 2]);
			glm::vec3 n1((iter->mesh.normals)[*ind * 3], (iter->mesh.normals)[*ind * 3 + 1], (iter->mesh.normals)[*ind * 3 + 2]);
			glm::vec2 t1((iter->mesh.texcoords)[*ind * 2], (iter->mesh.positions)[*ind * 2 + 1]);
			ind++;
			glm::vec3 v2((iter->mesh.positions)[*ind * 3], (iter->mesh.positions)[*ind * 3 + 1], (iter->mesh.positions)[*ind * 3 + 2]);
			glm::vec3 n2((iter->mesh.normals)[*ind * 3], (iter->mesh.normals)[*ind * 3 + 1], (iter->mesh.normals)[*ind * 3 + 2]);
			glm::vec2 t2((iter->mesh.texcoords)[*ind * 2], (iter->mesh.positions)[*ind * 2 + 1]);
			ind++;
			glm::vec3 v3((iter->mesh.positions)[*ind * 3], (iter->mesh.positions)[*ind * 3 + 1], (iter->mesh.positions)[*ind * 3 + 2]);
			glm::vec3 n3((iter->mesh.normals)[*ind * 3], (iter->mesh.normals)[*ind * 3 + 1], (iter->mesh.normals)[*ind * 3 + 2]);
			glm::vec2 t3((iter->mesh.texcoords)[*ind * 2], (iter->mesh.positions)[*ind * 2 + 1]);

			//glm::vec3 mNormal = -glm::normalize(glm::cross((v3 - v1), (v2 - v1)));

			glBegin(GL_TRIANGLES);

			glNormal3f(n1.x,n1.y,n1.z);
			glTexCoord2f(t1.x,t1.y);
			glVertex3f(v1.x,v1.y,v1.z);

			glNormal3f(n2.x,n2.y,n2.z);
			glTexCoord2f(t2.x,t2.y);
			glVertex3f(v2.x,v2.y,v2.z);

			glNormal3f(n3.x,n3.y,n3.z);
			glTexCoord2f(t3.x,t3.y);
			glVertex3f(v3.x,v3.y,v3.z);

			glEnd();
		}
	}

	//Dont apply transformations to lights
	glPopMatrix();
}

void scene::loadTextures()
{
   glEnable(GL_TEXTURE_2D);

   printf("How many textures do you want to load ?\n");
   scanf("%d", &texNum);
   for (int i = 0; i < texNum; i++)
   {
      std::string texName;
      printf("Enter texture %d name: ", i + 1);
      std::cin >> texName;
      GLuint tex2d = SOIL_load_OGL_texture(texName.c_str(), SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, 0);
      textures.push_back(tex2d);
   }
}