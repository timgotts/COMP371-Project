#include "PointLight.h"



PointLight::PointLight(): Light()
{
	this->position = glm::vec3(0.0f,0.0f,0.0f);
	this->constant = 1.0f;
	this->linear = 0.09f;
	this->quadratic = 0.032f;
}


PointLight::PointLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position, float constant, float linear, float quadratic)
: Light(ambient, diffuse, specular)
{
	this->position = position;
	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
}

PointLight::PointLight(glm::vec3 position) : Light()
{
	this->position = position;
	this->constant = 1.0f;
	this->linear = 0.09f;
	this->quadratic = 0.032f;
}


PointLight::~PointLight()
{
}
