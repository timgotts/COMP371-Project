#pragma once

#include <GLM\gtc\matrix_transform.hpp>
#include <GLM\gtc\type_ptr.hpp>
#include <random>

#include "Fish.h"


Fish::Fish(glm::vec3 position) :	position(position),	pitch(0.0f), yawOsc(0.0f), totalTime(0.0f), yawTotal(0.0f)
{
	GLfloat vertices[] = {
		-0.4, 0, 0, 0.242251, 0.0484502, 0.969003,
		-0.5, 0.5, 0, 0.242251, 0.0484502, 0.969003,
		-0.2, 0, -0.05, 0.242251, 0.0484502, 0.969003,
		-0.5, 0.5, 0, -0.0705346, -0.141069, 0.987484,
		-0.4, 0.45, 0, -0.0705346, -0.141069, 0.987484,
		-0.2, 0, -0.05, -0.0705346, -0.141069, 0.987484,
		-0.4, 0.45, 0, -0.290129, -0.232104, 0.928414,
		-0.2, 0.2, 0, -0.290129, -0.232104, 0.928414,
		-0.2, 0, -0.05, -0.290129, -0.232104, 0.928414,
		-0.2, 0.2, 0, 0.436436, -0.218218, 0.872872,
		0, 0.2, -0.1, 0.436436, -0.218218, 0.872872,
		-0.2, 0, -0.05, 0.436436, -0.218218, 0.872872,
		-0.2, 0.2, 0, 0.408248, -0.408248, 0.816497,
		0, 0.4, 0, 0.408248, -0.408248, 0.816497,
		0, 0.2, -0.1, 0.408248, -0.408248, 0.816497,
		0, 0.4, 0, 0.218218, -0.436436, 0.872872,
		0.2, 0.5, 0, 0.218218, -0.436436, 0.872872,
		0, 0.2, -0.1, 0.218218, -0.436436, 0.872872,
		0.2, 0.5, 0, 0, -0.316228, 0.948683,
		0.2, 0.2, -0.1, 0, -0.316228, 0.948683,
		0, 0.2, -0.1, 0, -0.316228, 0.948683,
		0.2, 0.5, 0, -0.156174, -0.312348, 0.937043,
		0.4, 0.4, 0, -0.156174, -0.312348, 0.937043,
		0.2, 0.2, -0.1, -0.156174, -0.312348, 0.937043,
		0.4, 0.4, 0, -0.3698, -0.09245, 0.9245,
		0.5, 0, 0, -0.3698, -0.09245, 0.9245,
		0.2, 0.2, -0.1, -0.3698, -0.09245, 0.9245,
		0.5, 0, 0, -0.316228, 0, 0.948683,
		0.2, -0.2, -0.1, -0.316228, 0, 0.948683,
		0.2, 0.2, -0.1, -0.316228, 0, 0.948683,
		0.5, 0, 0, -0.3698, 0.09245, 0.9245,
		0.4, -0.4, 0, -0.3698, 0.09245, 0.9245,
		0.2, -0.2, -0.1, -0.3698, 0.09245, 0.9245,
		0.4, -0.4, 0, -0.156174, 0.312348, 0.937043,
		0.2, -0.5, 0, -0.156174, 0.312348, 0.937043,
		0.2, -0.2, -0.1, -0.156174, 0.312348, 0.937043,
		0.2, -0.5, 0, 0, 0.316228, 0.948683,
		0, -0.2, -0.1, 0, 0.316228, 0.948683,
		0.2, -0.2, -0.1, 0, 0.316228, 0.948683,
		0.2, -0.5, 0, 0.218218, 0.436436, 0.872872,
		0, -0.4, 0, 0.218218, 0.436436, 0.872872,
		0, -0.2, -0.1, 0.218218, 0.436436, 0.872872,
		0, -0.4, 0, 0.408248, 0.408248, 0.816497,
		-0.2, -0.2, 0, 0.408248, 0.408248, 0.816497,
		0, -0.2, -0.1, 0.408248, 0.408248, 0.816497,
		-0.2, -0.2, 0, 0.436436, 0.218218, 0.872872,
		-0.2, 0, -0.05, 0.436436, 0.218218, 0.872872,
		0, -0.2, -0.1, 0.436436, 0.218218, 0.872872,
		-0.2, -0.2, 0, -0.290129, 0.232104, 0.928414,
		-0.4, -0.45, 0, -0.290129, 0.232104, 0.928414,
		-0.2, 0, -0.05, -0.290129, 0.232104, 0.928414,
		-0.4, -0.45, 0, -0.0705346, 0.141069, 0.987484,
		-0.5, -0.5, 0, -0.0705346, 0.141069, 0.987484,
		-0.2, 0, -0.05, -0.0705346, 0.141069, 0.987484,
		-0.5, -0.5, 0, 0.242251, -0.0484502, 0.969003,
		-0.4, 0, 0, 0.242251, -0.0484502, 0.969003,
		-0.2, 0, -0.05, 0.242251, -0.0484502, 0.969003,
		-0.2, 0, -0.05, 0.242536, 0, 0.970142,
		0, 0.2, -0.1, 0.242536, 0, 0.970142,
		0, -0.2, -0.1, 0.242536, 0, 0.970142,
		0, 0.2, -0.1, 0, 0, 1,
		0.2, 0.2, -0.1, 0, 0, 1,
		0.2, -0.2, -0.1, 0, 0, 1,
		0, 0.2, -0.1, 0, 0, 1,
		0.2, -0.2, -0.1, 0, 0, 1,
		0, -0.2, -0.1, 0, 0, 1,
		-0.4, 0, 0, 0.242251, 0.0484502, -0.969003,
		-0.2, 0, 0.05, 0.242251, 0.0484502, -0.969003,
		-0.5, 0.5, 0, 0.242251, 0.0484502, -0.969003,
		-0.5, 0.5, 0, -0.0705346, -0.141069, -0.987484,
		-0.2, 0, 0.05, -0.0705346, -0.141069, -0.987484,
		-0.4, 0.45, 0, -0.0705346, -0.141069, -0.987484,
		-0.4, 0.45, 0, -0.290129, -0.232104, -0.928414,
		-0.2, 0, 0.05, -0.290129, -0.232104, -0.928414,
		-0.2, 0.2, 0, -0.290129, -0.232104, -0.928414,
		-0.2, 0.2, 0, 0.436436, -0.218218, -0.872872,
		-0.2, 0, 0.05, 0.436436, -0.218218, -0.872872,
		0, 0.2, 0.1, 0.436436, -0.218218, -0.872872,
		-0.2, 0.2, 0, 0.408248, -0.408248, -0.816497,
		0, 0.2, 0.1, 0.408248, -0.408248, -0.816497,
		0, 0.4, 0, 0.408248, -0.408248, -0.816497,
		0, 0.4, 0, 0.218218, -0.436436, -0.872872,
		0, 0.2, 0.1, 0.218218, -0.436436, -0.872872,
		0.2, 0.5, 0, 0.218218, -0.436436, -0.872872,
		0.2, 0.5, 0, 0, -0.316228, -0.948683,
		0, 0.2, 0.1, 0, -0.316228, -0.948683,
		0.2, 0.2, 0.1, 0, -0.316228, -0.948683,
		0.2, 0.5, 0, -0.156174, -0.312348, -0.937043,
		0.2, 0.2, 0.1, -0.156174, -0.312348, -0.937043,
		0.4, 0.4, 0, -0.156174, -0.312348, -0.937043,
		0.4, 0.4, 0, -0.3698, -0.09245, -0.9245,
		0.2, 0.2, 0.1, -0.3698, -0.09245, -0.9245,
		0.5, 0, 0, -0.3698, -0.09245, -0.9245,
		0.5, 0, 0, -0.316228, 0, -0.948683,
		0.2, 0.2, 0.1, -0.316228, 0, -0.948683,
		0.2, -0.2, 0.1, -0.316228, 0, -0.948683,
		0.5, 0, 0, -0.3698, 0.09245, -0.9245,
		0.2, -0.2, 0.1, -0.3698, 0.09245, -0.9245,
		0.4, -0.4, 0, -0.3698, 0.09245, -0.9245,
		0.4, -0.4, 0, -0.156174, 0.312348, -0.937043,
		0.2, -0.2, 0.1, -0.156174, 0.312348, -0.937043,
		0.2, -0.5, 0, -0.156174, 0.312348, -0.937043,
		0.2, -0.5, 0, 0, 0.316228, -0.948683,
		0.2, -0.2, 0.1, 0, 0.316228, -0.948683,
		0, -0.2, 0.1, 0, 0.316228, -0.948683,
		0.2, -0.5, 0, 0.218218, 0.436436, -0.872872,
		0, -0.2, 0.1, 0.218218, 0.436436, -0.872872,
		0, -0.4, 0, 0.218218, 0.436436, -0.872872,
		0, -0.4, 0, 0.408248, 0.408248, -0.816497,
		0, -0.2, 0.1, 0.408248, 0.408248, -0.816497,
		-0.2, -0.2, 0, 0.408248, 0.408248, -0.816497,
		-0.2, -0.2, 0, 0.436436, 0.218218, -0.872872,
		0, -0.2, 0.1, 0.436436, 0.218218, -0.872872,
		-0.2, 0, 0.05, 0.436436, 0.218218, -0.872872,
		-0.2, -0.2, 0, -0.290129, 0.232104, -0.928414,
		-0.2, 0, 0.05, -0.290129, 0.232104, -0.928414,
		-0.4, -0.45, 0, -0.290129, 0.232104, -0.928414,
		-0.4, -0.45, 0, -0.0705346, 0.141069, -0.987484,
		-0.2, 0, 0.05, -0.0705346, 0.141069, -0.987484,
		-0.5, -0.5, 0, -0.0705346, 0.141069, -0.987484,
		-0.5, -0.5, 0, 0.242251, -0.0484502, -0.969003,
		-0.2, 0, 0.05, 0.242251, -0.0484502, -0.969003,
		-0.4, 0, 0, 0.242251, -0.0484502, -0.969003,
		-0.2, 0, 0.05, 0.242536, 0, -0.970142,
		0, -0.2, 0.1, 0.242536, 0, -0.970142,
		0, 0.2, 0.1, 0.242536, 0, -0.970142,
		0, -0.2, 0.1, 0, 0, -1,
		0.2, -0.2, 0.1, 0, 0, -1,
		0, 0.2, 0.1, 0, 0, -1,
		0.2, -0.2, 0.1, 0, 0, -1,
		0.2, 0.2, 0.1, 0, 0, -1,
		0, 0.2, 0.1, 0, 0, -1,
	};
	
	// Generate buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// Buffer object data
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 132*(sizeof(GLfloat)*6), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);



	// Random devices and distributions
	std::random_device rd;
	std::mt19937 gen(rd());
	std::poisson_distribution<> p(10);
	std::uniform_real_distribution<> u(0, 1);
	std::uniform_real_distribution<> u1(0.5, 1.5);
	std::uniform_real_distribution<> u2(1.0, 3.0);

	// Pseudorandomize animation and scale variables
	float pRand = float(p(gen)) / 10.0f;
	float pRand2 = float(p(gen)) / 8.0f;


	scale = pRand2 * glm::vec3(pRand * u2(gen) * 1.5, pRand * u2(gen), pRand * u2(gen) *1.5);
	velocity = pRand * u2(gen) * 3.0f;
	initYaw = u(gen) * 360.0f;
	oscRate = u1(gen);
	oscOffset = u(gen) * 3.14159265;



	// Update orientation vectors
	updateVectors();

	// Random devices and distributions
	std::uniform_real_distribution<> randColor(0.0, 1.0);
	std::uniform_real_distribution<> v(-0.1, 0.1);
	float baseColor = v(gen);
	glm::vec3 color = glm::vec3(randColor(gen) + baseColor, randColor(gen) + baseColor, randColor(gen) + baseColor);

	// Assign material 
	material = Material(0.5f *color, 0.5f * color, glm::vec3(0.5f), 1.0f);


}



void Fish::render(Shader* shader)
{

	//shader->use();
	glm::mat3 normalMatrix = glm::transpose(glm::inverse(model));

	// Broadcast the uniform values to the shaders
	GLuint modelLoc = glGetUniformLocation(shader->program, "model");
	GLint matAmbientLoc = glGetUniformLocation(shader->program, "material.ambient");
	GLint matDiffuseLoc = glGetUniformLocation(shader->program, "material.diffuse");
	GLint matSpecularLoc = glGetUniformLocation(shader->program, "material.specular");
	GLint matShineLoc = glGetUniformLocation(shader->program, "material.shininess");
	GLint normalMatrixLoc = glGetUniformLocation(shader->program, "normalMatrix");
	//GLuint viewLoc = glGetUniformLocation(shader->program, "view");
	//GLuint projectionLoc = glGetUniformLocation(shader->program, "projection");


	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniform3f(matAmbientLoc, material.ambient.x, material.ambient.y, material.ambient.z);
	glUniform3f(matDiffuseLoc, material.diffuse.x, material.diffuse.y, material.diffuse.z);
	glUniform3f(matSpecularLoc, material.specular.x, material.specular.y, material.specular.z);
	glUniform1f(matShineLoc, material.shininess);
	glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
	//glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	//glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// Draw object
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 132);
	glBindVertexArray(0);
}



void Fish::animate(float deltaTime, Terrain * terrain)
{
	
	totalTime += deltaTime;

	


	// Short swimming yaw oscillation
	yawOsc = sin((totalTime*2.5 + oscOffset)*oscRate) * 25.0f;

	// Long trajectory yaw oscillation
	yawDir = 180 * sin((totalTime*0.1 + oscOffset)*oscRate) + initYaw;

	yawTotal = yawOsc + yawDir + yawTurn1 + yawTurn2;

	pitchOsc = sin((totalTime + oscOffset)*oscRate) * 20.0f;


	// Short pitch oscillation
	pitch = pitchOsc + pitchTotal;
	updateVectors();
	position += front * velocity * deltaTime;

	// Model transformations
	glm::mat4 tempModel = glm::translate(glm::mat4(1.0f), position);

	tempModel = glm::rotate(tempModel, glm::radians(-yawTotal), glm::vec3(0.0f, 1.0f, 0.0f));
	tempModel = glm::rotate(tempModel, glm::radians(pitch), glm::vec3(0.0f, 0.0f, 1.0f));


	float terrainSize = (terrain->getSize()) * (terrain->getPointsPerChunk() - 1);



	if (belowTerrain && !turnedAround)
	{
		yawTurn1 += 3.0f;
	}

	if (yawTurn1 >= lastYawTotal + 180.0f)
	{
		turnedAround = true;
	}


	if (ascending && pitchTotal < 20.0f)
	{
		pitchTotal += 1.0f;
	}

	if (descending && pitchTotal > -20.0f)
	{
		pitchTotal -= 1.0f;
	}

	if (levelingOut)
	{
		if (pitchTotal > 0.0f)
			pitchTotal -= 1.0f;
		if (pitchTotal < 0.0f);
			pitchTotal += 1.0f;
		if (pitchTotal == 0.0f)
			levelingOut = false;
	}

	// Below terrain
	if ((position.y < (terrain->getHeightAt((int)position.x, (int)position.z) + 6.0f)) && (belowTerrain == false))
	{
		belowTerrain = true;
		descending = false;
		ascending = true;
		turnedAround = false;
		lastYawTotal = yawTotal;
	}

	// Above terrain
	if ((position.y >(terrain->getHeightAt((int)position.x, (int)position.z) + 8.0f)) && (belowTerrain == true))
	{
		belowTerrain = false;
		levelingOut = true;
	}

	// Above surface
	if ((position.y > (terrain->getHeightAt((int)position.x, (int)position.z) + 20.0f)) && (aboveSurface == false))
	{
		aboveSurface = true;
		ascending = false;
		descending = true;
	}

	// Below surface
	if ((position.y < (terrain->getHeightAt((int)position.x, (int)position.z) + 10.0f)) && (aboveSurface == true))
	{
		aboveSurface = false;
		levelingOut = true;
	}

	// Outside terrain
	if ((position.x < 0.0f || position.z < 0.0f || position.x > terrainSize || position.z > terrainSize) && (outsideTerrain == false))
	{
		outsideTerrain = true;
		yawTurn2 += 180.0f;
	}

	// Inside terrain
	if (!(position.x < 0.0f || position.z < 0.0f || position.x > terrainSize || position.z > terrainSize) && (outsideTerrain == true))
	{
		outsideTerrain = false;
	}




	tempModel = glm::scale(tempModel, scale);



	model = tempModel;

}



void Fish::updateVectors()
{
	// Same as LearnOpenGL camera
	glm::vec3 tempFront;
	tempFront.x = cos(glm::radians(-yawTotal)) * cos(glm::radians(pitch));
	tempFront.y = sin(glm::radians(pitch));
	tempFront.z = sin(glm::radians(yawTotal)) * cos(glm::radians(pitch));

	front = glm::normalize(tempFront);
	right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
	up = glm::normalize(glm::cross(right, front));
}
