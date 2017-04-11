#pragma once

#include "Rock.h"
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.inl>
#include <random>


Rock::Rock(glm::vec3 eulerXYZ, glm::vec3 position, glm::vec3 scale)
{
	float const X = 0.525731112119133606f;
	float const Z = 0.850650808352039932f;
	vertices = { glm::vec3(-X,0,Z),
		glm::vec3(X,0,Z),
		glm::vec3(-X,0,-Z),
		glm::vec3(X,0,-Z),
		glm::vec3(0,Z,X),
		glm::vec3(0,Z,-X),
		glm::vec3(0,-Z,X),
		glm::vec3(0.0,-Z,-X),
		glm::vec3(Z,X,0),
		glm::vec3(-Z,X,0),
		glm::vec3(Z,-X,0),
		glm::vec3(-Z,-X,0)
	};
	indices = 
	{
		1,4,0, 		4,9,0,		4,5,9,
		8,5,4,		1,8,4,		1,10,8,
		10,3,8,		8,3,5,		3,2,5,
		3,7,2,		3,10,7,		10,6,7,
		6,11,7,		6,0,11,		6,1,0,
		10,1,6,		11,0,9,		2,11,9,
		5,2,9,		11,2,7 
	};
	static const GLfloat color[] = { 
		0.6588, 0.6588, 0.6588,
		0.6588, 0.6588, 0.6588,
		0.6588, 0.6588, 0.6588,
		0.6588, 0.6588, 0.6588,
		0.6588, 0.6588, 0.6588,
		0.6588, 0.6588, 0.6588,
		0.6588, 0.6588, 0.6588,
		0.6588, 0.6588, 0.6588,
		0.6588, 0.6588, 0.6588,
		0.6588, 0.6588, 0.6588,
		0.6588, 0.6588, 0.6588,
		0.6588, 0.6588, 0.6588
	};
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(-0.3, 0.3);
	for (int i=0; i<vertices.size(); i++)
	{
		vertices.at(i).x += dis(gen);
		vertices.at(i).y += dis(gen);
		vertices.at(i).z += dis(gen);
		//point.y += dis(gen)* 
	}

	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

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

	// Apply scale to model matrix
	model = glm::scale(model, glm::vec3(scale.x, scale.y, scale.z));

	// Apply rotations to model matrix
	model = glm::rotate(model, eulerXYZ.x, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, eulerXYZ.y, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, eulerXYZ.z, glm::vec3(0.0f, 0.0f, 1.0f));





	// Compile and load shaders
	shader = new Shader("res/shaders/rock.vs", "res/shaders/rock.fs");
}

void Rock::render(glm::mat4 view, glm::mat4 projection)
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
