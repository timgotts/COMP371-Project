#pragma once

#include <vector>

#include <GL\glew.h>
#include <GLM\glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>
#include <GLM\gtc\type_ptr.hpp>

#include "Renderable.h"
#include "Shader.h"

class Seaweed : public Renderable
{
public:
	Seaweed(float rotAngle, glm::vec3 position);

	void render(glm::mat4 view, glm::mat4 projection);

	//Indices for the ebo
	int *indicesEBO;
	int indexLength;
};