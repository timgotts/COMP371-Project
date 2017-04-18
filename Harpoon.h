#pragma once

//#include <GLM\gtc\type_ptr.hpp>
#include "Renderable.h"
#include "Terrain.h"
#include "Camera.h"



class Harpoon : public Renderable
{
    public:
    
    Harpoon(glm::vec3 position, glm::vec3 cameraFront);
    glm::vec3 calculateNormal(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3);
    
    void render(Shader* shader);
    
    void animate(float deltaTime, Terrain * terrain);
    
    bool load();
    void unload();
   
   

protected:

	// determine whether harpoon is stuck or not
	bool isStuck = false;

	// Harpoon movement speed
	GLfloat velocity = 40.0f;


	// Position and orientation	
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::mat4 rotationMatrix;




	// Variables for periodic animations
	GLfloat totalTime;


    
};