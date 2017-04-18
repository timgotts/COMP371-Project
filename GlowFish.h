#pragma once
#include "PointLight.h"
#include <GL/glew.h>
#include "Fish.h"

/**
 * The glowfish class represents an animated fish which also acts as a point light, illuminating surrounding surfaces
 */
class GlowFish : public Fish, public PointLight
{
public:
	GlowFish(glm::vec3 position);
	~GlowFish();
	void render(Shader* shader);
	glm::vec3 getPosition();
};

