#pragma once

#include <GL\glew.h>
#include <GLM\glm.hpp>


#include "Shader.h"

class Renderable 
{
public:

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	std::vector<glm::vec3> vertices;
	std::vector<GLuint> indices;

	glm::mat4 model;

	Shader * shader;

	virtual void render(glm::mat4 view, glm::mat4 proj) {};

private:

};