#pragma once

#include <GLM\gtc\type_ptr.hpp>
#include "Renderable.h"




class Hud : public Renderable
{
public:

	Hud(int height, int width);

	void render(glm::mat4 view, glm::mat4 projection);

	void swapHuds();

private:

};