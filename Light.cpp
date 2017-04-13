#include "Light.h"



Light::Light()
{
	ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	diffuse = glm::vec3(0.3f, 0.3f, 0.3f);
	specular = glm::vec3(1.0f, 1.0f, 1.0f);
}

Light::Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;

}


Light::~Light()
{
}
