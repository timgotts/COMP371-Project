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
	
	void Cube::render(glm::mat4 view, glm::mat4 projection, Camera& camera, std::vector<PointLight> & pointlights, DirectionalLight & dirlight, SpotLight & spotLight);


private:
	glm::vec3 lightPos;
	Material material;

};
