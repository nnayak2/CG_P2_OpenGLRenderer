#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "glm/glm.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "tiny_obj_loader.h"
#include <map>
#include "soil/SOIL.h"
#include <GL/glut.h>

extern int light;
extern int xx, yy, zz, rot;
extern float scale;
extern int activeTex;

class scene
{
	static scene *sceneinstance;
	scene(){}
public:
	std::vector<tinyobj::shape_t> shapes;
   std::vector<GLuint> textures;
   int texNum;
public:
	static scene* getScene();
	void loadScene(char *file);
	void draw();
   void loadTextures();
   void setupLights();
};

#endif