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
	Seaweed( glm::vec3 position);
	float rotAngle;
	//Seaweed's render function
	void render(glm::mat4 view, glm::mat4 projection);

	//Calulates the seaweeds translational sweep, which only happens once per seaweed type.
	void calculateSweep();

	//Final vertices for the seaweed
	 GLfloat* verticesVBO;
	//Indices for the ebo
	 int *indicesEBO;

	 int totalLength;
	//Lenght of the index needed for our VBO in the render function
	 int indexLength;

	static int amount;
};