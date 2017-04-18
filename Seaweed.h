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
	Seaweed(glm::vec3 position);
	//rotation angle
	//Seaweed's render function
	void render(Shader* shader);

	void animate(float deltaTime);
	//The seaweed's position used in the animate function
	glm::vec3 positionSeaweed;

	//Final vertices for the seaweed
	GLfloat* verticesVBO;
	//Indices for the ebo
	GLuint* indicesEBO;

	//Length of the verticesVBO
	int totalLength;
	//Length of the indicesEBO
	int indexLength;

	//seaweed type
	int type;

	//Added for now to generate different seaweed
	static int amount;

	//Static VBOs and VAOs
	static GLfloat greenVBO[];
	static GLfloat redVBO[];

	static GLuint gVAO;
	static GLuint gVBO;

	static GLuint rVAO;
	static GLuint rVBO;

	//variables used for the animate function
	GLfloat totalTime = 0.0f;
	GLfloat oscOffset;

protected:
	GLfloat rotRand;
	GLfloat rotAngle;
	GLfloat scaleRand;
	GLfloat xScaleRand;
	GLfloat yScaleRand;
};