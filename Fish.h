#pragma once

#include "Renderable.h"
#include "Terrain.h"


class Fish : public Renderable
{

public:
	Fish(glm::vec3 position);

	void render(Shader* shader);
	void animate(float deltaTime, Terrain * terrain);

protected:

	// Position and orientation	
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;

	// Euler angles
	GLfloat yawTotal;
	GLfloat yawTurn1 = 0.0f;
	GLfloat yawTurn2 = 0.0f;
	GLfloat pitch;
	GLfloat pitchTotal = 0.0f;

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

	// Swim speed
	GLfloat velocity;


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