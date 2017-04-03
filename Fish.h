#pragma once

#include "Renderable.h"


class Fish : public Renderable
{

public:

	Fish(glm::vec3 scale, glm::vec3 eulerXYZ, glm::vec3 position);

	void render(glm::mat4 view, glm::mat4 projection);

	void animate(float deltaTime);

	float time = 0.0f;

};