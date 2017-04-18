#pragma once

//#include <GLM\gtc\type_ptr.hpp>
#include "Renderable.h"
#include "Terrain.h"
#include "Camera.h"



class Harpoon : public Renderable
{
    public:
    
    Harpoon(glm::vec3 position, glm::quat);
    glm::vec3 calculateNormal(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3);
    
    void render(Shader* shader);
    
    void animate(float deltaTime, Terrain * terrain);
    
    bool load();
    void unload();
   
    
    protected:
   

protected:

	// determine whether harpoon is stuck or not
	bool isStuck = false;

	// Harpoon movement speed
	GLfloat velocity = 50.0f;

	glm::quat quat = glm::angleAxis(float(PI), glm::vec3(0.0f, 1.0f, 0.0f));

	// Position and orientation	
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;

	// Euler angles
	GLfloat yaw = 0.0f;
	GLfloat pitch = 0.0f;

	float lastYawTotal;
	float lastYawTotal2;

	bool outsideSafeZone = false;
	bool aboveSurface = false;
	bool belowTerrain = false;
	bool turnedAround = false;
	bool ascending = false;
	bool descending = false;
	bool levelingOut = false;
	bool outsideTerrain = false;

	// Variables for periodic animations
	GLfloat totalTime;
	GLfloat yawOsc;
	GLfloat yawDir;
	GLfloat pitchOsc;

	// Pseudorandom variables
	GLfloat initYaw;
	glm::vec3 scale;
	GLfloat oscOffset;
	GLfloat oscRate;

	void updateVectors();
    
};