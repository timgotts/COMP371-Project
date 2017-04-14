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
	GLuint EBO;

	std::vector<glm::vec3> vertices;
	std::vector<GLuint> indices;

	glm::mat4 model;

	Shader * shader;

	Material material;

	virtual void render(glm::mat4 view, glm::mat4 proj) {};
	virtual void animate(float deltaTime) {};

private:

};
