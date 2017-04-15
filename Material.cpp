#include "Material.h"



Material::Material()
{
	ambient = glm::vec3(1.0f, 0.5f, 0.31f);
	diffuse = glm::vec3(1.0f, 0.5f, 0.31f);
	specular = glm::vec3(0.5f, 0.5f, 0.5f);
	shininess = 32.0f;
}

Material::Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess)
{
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->shininess = shininess;
}


Material::~Material()
{
}
