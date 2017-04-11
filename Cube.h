#pragma once

#include "Renderable.h"


class Cube : public Renderable
{
public:

	Cube(float edgeLength, glm::vec3 eulerXYZ, glm::vec3 position);
	
	void render(glm::mat4 view, glm::mat4 projection);

private:

};