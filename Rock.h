#pragma once

#include <GLM\gtc\type_ptr.hpp>
#include "Renderable.h"



class Rock : public Renderable
{
public:

	Rock(glm::vec3 position);

	void render(glm::mat4 view, glm::mat4 projection);

private:

};