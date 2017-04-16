#pragma once

#include "Renderable.h"


class Coral : public Renderable
{

public:
	Coral();

	void render(Shader* shader);

	std::vector<glm::vec3> normals;

private:

	void tree(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, int r);
	void pushTriangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, glm::vec3 n);
	void loadBuffers();
};
