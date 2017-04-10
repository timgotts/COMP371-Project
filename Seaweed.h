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

	//Function which animates the seaweed moving
	void animate();
	
	//Angle of rotation
	float rotAngle;
	//Seaweed's render function
	void render(glm::mat4 view, glm::mat4 projection);

	//Calulates the seaweeds translational sweep, which only happens once per seaweed type.
	void calculateSweep();

	//Final vertices for the seaweed
	 GLfloat* verticesVBO;
	//Indices for the ebo
	 int *indicesEBO;

	 //Length of the verticesVBO
	 int totalLength;
	//Length of the indicesEBO
	 int indexLength;

	//Added for now to generate different seaweed
	static int amount;
};