#pragma once

#include <GLM\gtc\type_ptr.hpp>
#include "Renderable.h"



class Rock : public Renderable
{
    public:
    
	// normal constructor
    Rock(glm::vec3 position);

	// function to calculate normals
    glm::vec3 calculateNormal(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3);
    
	// render function
    void render(Shader* shader);
    
	// load unload function for loading chunks
    bool load();
    void unload();
    
};