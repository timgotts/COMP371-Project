#pragma once
#include "Light.h"
class PointLight :
	public Light
{
public:
	PointLight();
	PointLight(glm::vec3 position);
	PointLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position, 
		float constant, float linear, float quadratic);
	~PointLight();
	glm::vec3 position;
	float constant;
	float linear;
	float quadratic;

};

