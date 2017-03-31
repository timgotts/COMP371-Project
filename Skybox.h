#pragma once

#include <vector>

#include <GL\glew.h>
#include <GLM\glm.hpp>
#include <GLM\gtc\type_ptr.hpp>

#include "Renderable.h"
#include "Shader.h"
#include "objloader.hpp"

class Skybox: public Renderable
{
public:
	Skybox();
	void render(glm::mat4 view, glm::mat4 projection) override;
	static GLuint loadCubemap(std::vector<const GLchar*> faces);
private:

};
