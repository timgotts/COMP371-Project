#pragma once
#include "Renderable.h"
class LightSource :
	public Renderable
{
public:
	GLuint LightVAO;
	void render(glm::mat4 view, glm::mat4 projection) override;
	LightSource(float edgeLength, glm::vec3 eulerXYZ, glm::vec3 position);
	~LightSource();
};

