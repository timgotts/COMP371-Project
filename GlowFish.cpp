#pragma once

#include <GLM\gtc\matrix_transform.hpp>
#include <GLM\gtc\type_ptr.hpp>
#include <random>

#include "GlowFish.h"


GlowFish::GlowFish(glm::vec3 position) : Fish(position), PointLight(position)
{

}



void GlowFish::render(Shader* shader)
{
	// Broadcast the uniform values to the shaders
	GLuint modelLoc = glGetUniformLocation(shader->program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	// Draw object
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 132);
	glBindVertexArray(0);
}

glm::vec3 GlowFish::getPosition()
{
	return Fish::position;
}
