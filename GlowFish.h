#pragma once
#include "PointLight.h"
#include <GL/glew.h>
#include "Fish.h"


class GlowFish : public Fish, public PointLight
{
public:
	GlowFish(glm::vec3 position);
	~GlowFish();
	void render(Shader* shader);
	glm::vec3 getPosition();
};

