#pragma once

#include "Harpoon.h"
#include <GLM\glm.hpp>
#include <GLM\gtc\matrix_transform.inl>

glm::vec3 Harpoon::calculateNormal(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3)
{
	return glm::vec3();
}

Harpoon::Harpoon(glm::vec3 position)
{

	glm::vec3 harpoonVertices[] = {
		// face 1
		glm::vec3(0.0,0.0,0.0),
		glm::vec3(-0.2,0.4,0.0),
		glm::vec3(0.2,0.4,0.0),
		glm::vec3(0.4,0.2,0.0),
		glm::vec3(0.4,-0.2,0.0),
		glm::vec3(0.2,-0.4,0.0),
		glm::vec3(-0.2,-0.4,0.0),
		glm::vec3(-0.4,-0.2,0.0),
		glm::vec3(-0.4,0.2,0.0),
		// face 2
		glm::vec3(0.0,0.0,1.0),
		glm::vec3(-0.2,0.4,1.0),
		glm::vec3(0.2,0.4,1.0),
		glm::vec3(0.4,0.2,1.0),
		glm::vec3(0.4,-0.2,1.0),
		glm::vec3(0.2,-0.4,1.0),
		glm::vec3(-0.2,-0.4,1.0),
		glm::vec3(-0.4,-0.2,1.0),
		glm::vec3(-0.4,0.2,1.0)
	};
	glm::vec3 surfaceNormals[] = {
		calculateNormal(harpoonVertices[0],harpoonVertices[2],harpoonVertices[1]),

		calculateNormal(harpoonVertices[1],harpoonVertices[11],harpoonVertices[10]),
		calculateNormal(harpoonVertices[2],harpoonVertices[12],harpoonVertices[11]),
		calculateNormal(harpoonVertices[3],harpoonVertices[13],harpoonVertices[12]),
		calculateNormal(harpoonVertices[4],harpoonVertices[14],harpoonVertices[13]),
		calculateNormal(harpoonVertices[5],harpoonVertices[15],harpoonVertices[14]),
		calculateNormal(harpoonVertices[6],harpoonVertices[16],harpoonVertices[15]),
		calculateNormal(harpoonVertices[7],harpoonVertices[17],harpoonVertices[16]),
		calculateNormal(harpoonVertices[8],harpoonVertices[10],harpoonVertices[17]),

		calculateNormal(harpoonVertices[9],harpoonVertices[11],harpoonVertices[10])
	};

	int surface = 0;
	vertices = {
		harpoonVertices[0], surfaceNormals[surface],
		harpoonVertices[2], surfaceNormals[surface],
		harpoonVertices[1], surfaceNormals[surface],
		harpoonVertices[0], surfaceNormals[surface],
		harpoonVertices[3], surfaceNormals[surface],
		harpoonVertices[2], surfaceNormals[surface],
		harpoonVertices[0], surfaceNormals[surface],
		harpoonVertices[4], surfaceNormals[surface],
		harpoonVertices[3], surfaceNormals[surface],
		harpoonVertices[0], surfaceNormals[surface],
		harpoonVertices[5], surfaceNormals[surface],
		harpoonVertices[4], surfaceNormals[surface],
		harpoonVertices[0], surfaceNormals[surface],
		harpoonVertices[6], surfaceNormals[surface],
		harpoonVertices[5], surfaceNormals[surface],
		harpoonVertices[0], surfaceNormals[surface],
		harpoonVertices[7], surfaceNormals[surface],
		harpoonVertices[6], surfaceNormals[surface],
		harpoonVertices[0], surfaceNormals[surface],
		harpoonVertices[8], surfaceNormals[surface],
		harpoonVertices[7], surfaceNormals[surface],
		harpoonVertices[0], surfaceNormals[surface],
		harpoonVertices[1], surfaceNormals[surface],
		harpoonVertices[8], surfaceNormals[surface++],
		
		harpoonVertices[1], surfaceNormals[surface],
		harpoonVertices[11], surfaceNormals[surface],
		harpoonVertices[10], surfaceNormals[surface],
		harpoonVertices[2], surfaceNormals[surface],
		harpoonVertices[11], surfaceNormals[surface],
		harpoonVertices[1], surfaceNormals[surface++],

		harpoonVertices[2], surfaceNormals[surface],
		harpoonVertices[12], surfaceNormals[surface],
		harpoonVertices[11], surfaceNormals[surface],
		harpoonVertices[3], surfaceNormals[surface],
		harpoonVertices[12], surfaceNormals[surface],
		harpoonVertices[2], surfaceNormals[surface++],

		harpoonVertices[3], surfaceNormals[surface],
		harpoonVertices[13], surfaceNormals[surface],
		harpoonVertices[12], surfaceNormals[surface],
		harpoonVertices[4], surfaceNormals[surface],
		harpoonVertices[13], surfaceNormals[surface],
		harpoonVertices[3], surfaceNormals[surface++],

		harpoonVertices[4], surfaceNormals[surface],
		harpoonVertices[14], surfaceNormals[surface],
		harpoonVertices[13], surfaceNormals[surface],
		harpoonVertices[5], surfaceNormals[surface],
		harpoonVertices[14], surfaceNormals[surface],
		harpoonVertices[4], surfaceNormals[surface++],
		 
		harpoonVertices[5], surfaceNormals[surface],
		harpoonVertices[15], surfaceNormals[surface],
		harpoonVertices[14], surfaceNormals[surface],
		harpoonVertices[6], surfaceNormals[surface],
		harpoonVertices[15], surfaceNormals[surface],
		harpoonVertices[5], surfaceNormals[surface++],
		 
		harpoonVertices[6], surfaceNormals[surface],
		harpoonVertices[16], surfaceNormals[surface],
		harpoonVertices[15], surfaceNormals[surface],
		harpoonVertices[7], surfaceNormals[surface],
		harpoonVertices[16], surfaceNormals[surface],
		harpoonVertices[6], surfaceNormals[surface++],

		harpoonVertices[7], surfaceNormals[surface],
		harpoonVertices[17], surfaceNormals[surface],
		harpoonVertices[16], surfaceNormals[surface],
		harpoonVertices[8], surfaceNormals[surface],
		harpoonVertices[17], surfaceNormals[surface],
		harpoonVertices[7], surfaceNormals[surface++],

		harpoonVertices[8], surfaceNormals[surface],
		harpoonVertices[10], surfaceNormals[surface],
		harpoonVertices[17], surfaceNormals[surface],
		harpoonVertices[1], surfaceNormals[surface],
		harpoonVertices[10], surfaceNormals[surface],
		harpoonVertices[8], surfaceNormals[surface++],

		harpoonVertices[9], surfaceNormals[surface],
		harpoonVertices[11], surfaceNormals[surface],
		harpoonVertices[10], surfaceNormals[surface],
		harpoonVertices[9], surfaceNormals[surface],
		harpoonVertices[12], surfaceNormals[surface],
		harpoonVertices[11], surfaceNormals[surface],
		harpoonVertices[9], surfaceNormals[surface],
		harpoonVertices[13], surfaceNormals[surface],
		harpoonVertices[12], surfaceNormals[surface],
		harpoonVertices[9], surfaceNormals[surface],
		harpoonVertices[14], surfaceNormals[surface],
		harpoonVertices[13], surfaceNormals[surface],
		harpoonVertices[9], surfaceNormals[surface],
		harpoonVertices[15], surfaceNormals[surface],
		harpoonVertices[14], surfaceNormals[surface],
		harpoonVertices[9], surfaceNormals[surface],
		harpoonVertices[16], surfaceNormals[surface],
		harpoonVertices[15], surfaceNormals[surface],
		harpoonVertices[9], surfaceNormals[surface],
		harpoonVertices[17], surfaceNormals[surface],
		harpoonVertices[16], surfaceNormals[surface],
		harpoonVertices[9], surfaceNormals[surface],
		harpoonVertices[10], surfaceNormals[surface],
		harpoonVertices[17], surfaceNormals[surface],
	};

	model = glm::translate(model, -position);
	material = Material();
}

bool Harpoon::load()
{
	if (VAO == 0)
	{
		// Generate buffers
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		// Buffer object data
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

		// Position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		// Normal attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		return true;
	}
	return false;
}

void Harpoon::unload()
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);

	VBO = 0;
	VAO = 0;
}

void Harpoon::render(Shader * shader)
{
	//shader->use();
	glm::mat3 normalMatrix = glm::transpose(glm::inverse(model));


	// Broadcast the uniform values to the shaders


	GLint matAmbientLoc = glGetUniformLocation(shader->program, "material.ambient");
	GLint matDiffuseLoc = glGetUniformLocation(shader->program, "material.diffuse");
	GLint matSpecularLoc = glGetUniformLocation(shader->program, "material.specular");
	GLint matShineLoc = glGetUniformLocation(shader->program, "material.shininess");
	GLuint modelLoc = glGetUniformLocation(shader->program, "model");
	GLint normalMatrixLoc = glGetUniformLocation(shader->program, "normalMatrix");

	glUniform3f(matAmbientLoc, material.ambient.x, material.ambient.y, material.ambient.z);
	glUniform3f(matDiffuseLoc, material.diffuse.x, material.diffuse.y, material.diffuse.z);
	glUniform3f(matSpecularLoc, material.specular.x, material.specular.y, material.specular.z);
	glUniform1f(matShineLoc, material.shininess);
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));


	//GLuint viewLoc = glGetUniformLocation(shader->program, "view");
	//GLuint projectionLoc = glGetUniformLocation(shader->program, "projection");


	//glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	//glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// Draw object
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 96);
	glBindVertexArray(0);
}