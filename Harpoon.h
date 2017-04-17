#pragma once

#include <GLM\gtc\type_ptr.hpp>
#include "Renderable.h"
#include "Terrain.h"



class Harpoon : public Renderable
{
public:

	Harpoon(glm::vec3 position, glm::vec3 direction);
	glm::vec3 calculateNormal(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3);

	void render(Shader* shader);

	void animate(float deltaTime, Terrain * terrain);

	bool load();
	void unload();

	glm::vec3 position;
	glm::vec3 direction;

protected:
	bool belowTerrain = false;
	bool outsideTerrain = false;

	// Harpoon movement speed
	GLfloat velocity = 0.005f;

	// periodic animation variables
	GLfloat totalTime;


};