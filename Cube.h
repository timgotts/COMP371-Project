#pragma once

#include <vector>

#include <GL\glew.h>
#include <GLM\glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>
#include <GLM\gtc\type_ptr.hpp>

#include "Renderable.h"
#include "Shader.h"


class Cube : public Renderable
{
public:

	Cube(float edgeLength, glm::vec3 eulerXYZ, glm::vec3 position);
	
	void render(glm::mat4 view, glm::mat4 projection);

private:

};