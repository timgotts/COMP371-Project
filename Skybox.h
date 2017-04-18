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
	void render(Shader* shader) const;
	static GLuint loadCubemap(std::vector<const GLchar*> faces);
	GLuint VAO;
	GLuint VBO;
	std::vector<glm::vec3> vertices;
	std::vector<GLuint> indices;
	glm::mat4 model;
private:

};
