#pragma once

#include <vector>

#include <GL\glew.h>
#include <GLM\glm.hpp>
#include <GLM\gtc\type_ptr.hpp>

#include "Renderable.h"
#include "Shader.h"

class Skybox
{
public:
	Skybox();
	void render(glm::mat4 view, glm::mat4 projection);
	static GLuint loadCubemap(std::vector<const GLchar*> faces);

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	std::vector<glm::vec3> vertices;
	std::vector<GLuint> indices;

	glm::mat4 model;

	Shader * shader;
private:

};
