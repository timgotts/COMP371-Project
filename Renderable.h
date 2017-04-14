#pragma once

#include <vector>
#include <GL\glew.h>
#include <GLM\glm.hpp>
#include <vector>


#include "Shader.h"
#include "Material.h"

class Renderable 
{
public:

	GLuint VAO;
	GLuint VBO;

	std::vector<glm::vec3> vertices;
	std::vector<GLuint> indices;

	glm::mat4 model;

	Material material;

	virtual void render(Shader* shader) {};
	virtual void animate(float deltaTime) {};

private:

};
