#pragma once
#include "Light.h"
class SpotLight :
	public Light
{
public:
	SpotLight();
	SpotLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position, glm::vec3 direction,
		float cutOff, float outerCutOff, float constant, float linear, float quadratic);
	SpotLight(glm::vec3 position, glm::vec3 direction);
	~SpotLight();
	glm::vec3 position;
	glm::vec3 direction;
	float cutOff;
	float outerCutOff;
	float constant;
	float linear;
	float quadratic;
};

