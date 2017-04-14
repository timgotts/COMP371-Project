#include "DirectionalLight.h"



DirectionalLight::DirectionalLight():
Light()
{
	this->direction = glm::vec3(-0.2f, -1.0f, -0.3f);
}


DirectionalLight::DirectionalLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 direction):
Light(ambient, diffuse, specular)
{
	this->direction = direction;
}

DirectionalLight::DirectionalLight(glm::vec3 direction): Light()
{
	this->direction = direction;
}

DirectionalLight::~DirectionalLight()
{
}
