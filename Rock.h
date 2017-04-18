#pragma once

#include <GLM\gtc\type_ptr.hpp>
#include "Renderable.h"



class Rock : public Renderable
{
    public:
    
    Rock(glm::vec3 position);

    glm::vec3 calculateNormal(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3);
    
    void render(Shader* shader);
    
    bool load();
    void unload();
    
};