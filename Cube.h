#pragma once

#include "Renderable.h"
#include "DirectionalLight.h"
#include "SpotLight.h"
#include "PointLight.h"
#include "Camera.h"
#include "Material.h"


class Cube : public Renderable
{
public:

	Cube(float edgeLength, glm::vec3 eulerXYZ, glm::vec3 position);
	
	void Cube::render(Shader* shader) override;


private:
	glm::vec3 lightPos;
	Material material;

};
