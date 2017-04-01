#pragma once

#include <GLM\gtc\type_ptr.hpp>
#include "Renderable.h"



class Rock : public Renderable
{
public:

	Rock(glm::vec3 eulerXYZ, glm::vec3 position, glm::vec3 scale);

	void render(glm::mat4 view, glm::mat4 projection);

private:

};