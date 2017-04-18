#pragma once

//#include <GLM\gtc\type_ptr.hpp>
#include "Renderable.h"
#include "Terrain.h"



class Harpoon : public Renderable
{
    public:
    
	// normal constructor
    Harpoon(glm::vec3 position, glm::vec3 direction);

	// function to calculate the normal
    glm::vec3 calculateNormal(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3);
    
	// render function
    void render(Shader* shader);
    
	// function to animate harpoon
    void animate(float deltaTime, Terrain * terrain);
    
    //bool load();
    //void unload();
    
	// harpoon position & direction vector
    glm::vec3 position;
    glm::vec3 direction;
    
    protected:
    // determine whether harpoon is stuck or not
    bool isStuck = false;
    
    // Harpoon movement speed
    GLfloat velocity = 30.0f;    
    
};