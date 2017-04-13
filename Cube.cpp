#pragma once

#include <GLM\gtc\matrix_transform.hpp>
#include <GLM\gtc\type_ptr.hpp>

#include "Cube.h"
#include <GLFW/glfw3.h>


Cube::Cube(float edgeLength, glm::vec3 eulerXYZ, glm::vec3 position)
{
	
	
	//Compute surface normals for cube
	glm::vec3 surfaceNormals[6] = {
		glm::vec3(0.f, 0.f, -1.f),
		glm::vec3(0.f, 0.f, 1.f),
		glm::vec3(-1.f,0.f, 0.f),
		glm::vec3(1.f, 0.f, 0.f),
		glm::vec3(0.f, -1.f, 0.f),
		glm::vec3(0.f, 1.f, 0.f) };

	int surface = 0;

    // Base cube vertice data
	vertices = {
		glm::vec3(-0.5f, -0.5f, -0.5f), surfaceNormals[surface],
		glm::vec3(0.5f, -0.5f, -0.5f),  surfaceNormals[surface],
		glm::vec3(0.5f,  0.5f, -0.5f),  surfaceNormals[surface],
		glm::vec3(0.5f,  0.5f, -0.5f),  surfaceNormals[surface],
		glm::vec3(-0.5f,  0.5f, -0.5f), surfaceNormals[surface],
		glm::vec3(-0.5f, -0.5f, -0.5f), surfaceNormals[surface++],

		glm::vec3(-0.5f, -0.5f,  0.5f), surfaceNormals[surface],
		glm::vec3(0.5f, -0.5f,  0.5f),  surfaceNormals[surface],
		glm::vec3(0.5f,  0.5f,  0.5f),  surfaceNormals[surface],
		glm::vec3(0.5f,  0.5f,  0.5f),  surfaceNormals[surface],
		glm::vec3(-0.5f,  0.5f,  0.5f),  surfaceNormals[surface],
		glm::vec3(-0.5f, -0.5f,  0.5f),  surfaceNormals[surface++],

		glm::vec3(-0.5f,  0.5f,  0.5f), surfaceNormals[surface],
		glm::vec3(-0.5f,  0.5f, -0.5f), surfaceNormals[surface],
		glm::vec3(-0.5f, -0.5f, -0.5f), surfaceNormals[surface],
		glm::vec3(-0.5f, -0.5f, -0.5f), surfaceNormals[surface],
		glm::vec3(-0.5f, -0.5f,  0.5f), surfaceNormals[surface],
		glm::vec3(-0.5f,  0.5f,  0.5f), surfaceNormals[surface++],

		glm::vec3(0.5f,  0.5f,  0.5f),  surfaceNormals[surface],
		glm::vec3(0.5f,  0.5f, -0.5f),  surfaceNormals[surface],
		glm::vec3(0.5f, -0.5f, -0.5f),  surfaceNormals[surface],
		glm::vec3(0.5f, -0.5f, -0.5f),  surfaceNormals[surface],
		glm::vec3(0.5f, -0.5f,  0.5f),  surfaceNormals[surface],
		glm::vec3(0.5f,  0.5f,  0.5f),  surfaceNormals[surface++],

		glm::vec3(-0.5f, -0.5f, -0.5f),  surfaceNormals[surface],
		glm::vec3(0.5f, -0.5f, -0.5f),  surfaceNormals[surface],
		glm::vec3(0.5f, -0.5f,  0.5f),  surfaceNormals[surface],
		glm::vec3(0.5f, -0.5f,  0.5f),  surfaceNormals[surface],
		glm::vec3(-0.5f, -0.5f,  0.5f),  surfaceNormals[surface],
		glm::vec3(-0.5f, -0.5f, -0.5f),  surfaceNormals[surface++],

		glm::vec3(-0.5f,  0.5f, -0.5f),  surfaceNormals[surface],
		glm::vec3(0.5f,  0.5f, -0.5f),  surfaceNormals[surface],
		glm::vec3(0.5f,  0.5f,  0.5f),  surfaceNormals[surface],
		glm::vec3(0.5f,  0.5f,  0.5f), surfaceNormals[surface],
		glm::vec3(-0.5f,  0.5f,  0.5f),  surfaceNormals[surface],
		glm::vec3(-0.5f,  0.5f, -0.5f),  surfaceNormals[surface]
	};
    
    // Generate buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    // Buffer object data
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    
	//Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);    
    
    // Compile and load shaders
    shader = new Shader("res/shaders/mainlit.vs", "res/shaders/mainlit.fs");

	// Apply translation to model matrix
	model = glm::translate(model, -position);

	// Apply scale to model matrix
	model = glm::scale(model, glm::vec3(edgeLength, edgeLength, edgeLength));

	// Apply rotations to model matrix
	model = glm::rotate(model, eulerXYZ.x, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, eulerXYZ.y, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, eulerXYZ.z, glm::vec3(0.0f, 0.0f, 1.0f));

	lastFrame = 0;
}

void Cube::render(glm::mat4 view, glm::mat4 projection)
{
	render(view, projection, glm::vec3(0, 0, 0));
}

void Cube::render(glm::mat4 view, glm::mat4 projection, glm::vec3 camPos)
{
    shader->use();
	glm::mat3 normalMatrix = glm::transpose(glm::inverse(model));

	GLint lightPosLoc = glGetUniformLocation(shader->program, "light.position");
	GLint viewPosLoc = glGetUniformLocation(shader->program, "viewPos");
	
    // Broadcast the uniform values to the shaders

	GLint matAmbientLoc = glGetUniformLocation(shader->program, "material.ambient");
	GLint matDiffuseLoc = glGetUniformLocation(shader->program, "material.diffuse");
	GLint matSpecularLoc = glGetUniformLocation(shader->program, "material.specular");
	GLint matShineLoc = glGetUniformLocation(shader->program, "material.shininess");
	GLint lightAmbientLoc = glGetUniformLocation(shader->program, "light.ambient");
	GLint lightDiffuseLoc = glGetUniformLocation(shader->program, "light.diffuse");
	GLint lightSpecularLoc = glGetUniformLocation(shader->program, "light.specular");

	glUniform3f(matAmbientLoc, 1.0f, 0.5f, 0.31f);
	glUniform3f(matDiffuseLoc, 1.0f, 0.5f, 0.31f);
	glUniform3f(matSpecularLoc, 0.5f, 0.5f, 0.5f);
	glUniform1f(matShineLoc, 32.0f);
	glUniform3f(lightAmbientLoc, 0.2f, 0.2f, 0.2f);
	glUniform3f(lightDiffuseLoc, 0.5f, 0.5f, 0.5f);
	glUniform3f(lightSpecularLoc, 1.0f, 1.0f, 1.0f);

	GLint normalMatrixLoc = glGetUniformLocation(shader->program, "normalMatrix");
	glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
	glUniform3f(viewPosLoc, camPos.x, camPos.y, camPos.z);
	glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));

	GLuint modelLoc = glGetUniformLocation(shader->program, "model");
	GLuint viewLoc = glGetUniformLocation(shader->program, "view");
	GLuint projectionLoc = glGetUniformLocation(shader->program, "projection");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}
