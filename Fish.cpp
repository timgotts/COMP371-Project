#pragma once

#include <GLM\gtc\matrix_transform.hpp>
#include <GLM\gtc\type_ptr.hpp>
#include <random>

#include "Fish.h"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> dis(0, 1);


Fish::Fish(glm::vec3 scale, glm::vec3 eulerXYZ, glm::vec3 position)
{
	vertices = {
		glm::vec3(-0.4, 0.0, 0.0),	// 0. Center tail
		glm::vec3(-0.5, 0.5, 0.0),	// 1. Top tail
		glm::vec3(-0.4, 0.45, 0.0),	// 2.	
		glm::vec3(-0.2, 0.2, 0.0),	// 3.
		glm::vec3(0.0, 0.4, 0.0),	// 4.
		glm::vec3(0.2, 0.5, 0.0),	// 5.
		glm::vec3(0.4, 0.4, 0.0),	// 6.
		glm::vec3(0.5, 0.0, 0.0),	// 7. Nose
		glm::vec3(0.4, -0.4, 0.0),	// 8.
		glm::vec3(0.2, -0.5, 0.0),	// 9.
		glm::vec3(0.0, -0.4, 0.0),	// 10.
		glm::vec3(-0.2, -0.2, 0.0),	// 11.
		glm::vec3(-0.4, -0.45, 0.0),	// 12.
		glm::vec3(-0.5, -0.5, 0.0),	// 13. Bottom tail
		glm::vec3(-0.2, 0.0, -0.05),	// 14.
		glm::vec3(0.0, 0.2, -0.1),	// 15.
		glm::vec3(0.2, 0.2, -0.1),	// 16.
		glm::vec3(0.2, -0.2, -0.1),	// 17.
		glm::vec3(0.0, -0.2, -0.1),	// 18.
		glm::vec3(-0.2, 0.0, 0.05),	// 19.
		glm::vec3(0.0, -0.2, 0.1),	// 20.
		glm::vec3(0.2, -0.2, 0.1),	// 21.
		glm::vec3(0.2, 0.2, 0.1),	// 22.
		glm::vec3(0.0, 0.2, 0.1),	// 23.
	};

	indices = {
		0, 1, 14,
		1, 2, 14,
		2, 3, 14,
		3, 15, 14,
		3, 4, 15,
		4, 5, 15,
		5, 16, 15,
		5, 6, 16,
		6, 7, 16,
		7, 17, 16,
		7, 8, 17,
		8, 9, 17,
		9, 18, 17,
		9, 10, 18,
		10, 11, 18,
		11, 14, 18,
		11, 12, 14,
		12, 13, 14,
		13, 0, 14,
		14, 15, 18,
		15, 16, 17,
		15, 17, 18,

		0, 19, 1,
		1, 19, 2,
		2, 19, 3,
		3, 19, 23,
		3, 23, 4,
		4, 23, 5,
		5, 23, 22,
		5, 22, 6,
		6, 22, 7,
		7, 22, 21,
		7, 21, 8,
		8, 21, 9,
		9, 21, 20,
		9, 20, 10,
		10, 20, 11,
		11, 20, 19,
		11, 19, 12,
		12, 19, 13,
		13, 19, 0,
		19, 20, 23,
		20, 21, 23,
		21, 22, 23
	};

	// Generate buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Buffer object data
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Apply translation to model matrix
	model = glm::translate(model, -position);

	// Apply rotations to model matrix
	model = glm::rotate(model, eulerXYZ.x, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, eulerXYZ.y, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, eulerXYZ.z, glm::vec3(0.0f, 0.0f, 1.0f));

	// Apply scale to model matrix
	model = glm::scale(model, glm::vec3(scale.x, 1.0f, 1.0f));
	model = glm::scale(model, glm::vec3(1.0f, scale.y, 1.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, scale.z));





	// Compile and load shaders
	shader = new Shader("res/shaders/fish.vs", "res/shaders/fish.fs");


}

void Fish::render(glm::mat4 view, glm::mat4 projection)
{
	shader->use();

	// Broadcast the uniform values to the shaders
	GLuint modelLoc = glGetUniformLocation(shader->program, "model");
	GLuint viewLoc = glGetUniformLocation(shader->program, "view");
	GLuint projectionLoc = glGetUniformLocation(shader->program, "projection");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// Draw object
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Fish::animate(float deltaTime)
{
	time += dis(gen) * deltaTime;
	float speed = 3.0;

	model = glm::rotate(model, sin(time) / 100, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, sin(time*1.23275f) / 200, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::rotate(model, float((dis(gen) - 0.5) / 100), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(speed *deltaTime, 0.0f, 0.0f));
}
