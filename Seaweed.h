#pragma once

#include <vector>

#include <GL\glew.h>
#include <GLM\glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>
#include <GLM\gtc\type_ptr.hpp>
#include <GLFW\glfw3.h>
#include "Renderable.h"
#include "Shader.h"

class Seaweed : public Renderable
{
public:
	//Non-default constructor
	Seaweed(float rotAngle, glm::vec3 position);
	//Seaweed's render function
	void render(glm::mat4 view, glm::mat4 projection);

	//Indices for the ebo
	int *indicesEBO;
	//Lenght of the index needed for our VBO in the render function
	int indexLength;
};