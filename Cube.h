#pragma once

#include "Renderable.h"


class Cube : public Renderable
{
public:

	Cube(float edgeLength, glm::vec3 eulerXYZ, glm::vec3 position);
	
	void render(glm::mat4 view, glm::mat4 projection) override;
	void render(glm::mat4 view, glm::mat4 projection, glm::vec3 camPos);

private:
	GLfloat lastFrame;
	glm::vec3 lightPos;

};