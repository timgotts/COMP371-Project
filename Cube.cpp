#pragma once

#include <GLM\gtc\matrix_transform.hpp>
#include <GLM\gtc\type_ptr.hpp>

#include "Cube.h"
#include <GLFW/glfw3.h>
#include "Camera.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "DirectionalLight.h"


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
    

	// Apply translation to model matrix
	model = glm::translate(model, -position);

	// Apply scale to model matrix
	model = glm::scale(model, glm::vec3(edgeLength, edgeLength, edgeLength));

	// Apply rotations to model matrix
	model = glm::rotate(model, eulerXYZ.x, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, eulerXYZ.y, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, eulerXYZ.z, glm::vec3(0.0f, 0.0f, 1.0f));

	material = Material();
}


void Cube::render(Shader* shader)
{
	glm::mat3 normalMatrix = glm::transpose(glm::inverse(model));


	GLint matAmbientLoc = glGetUniformLocation(shader->program, "material.ambient");
	GLint matDiffuseLoc = glGetUniformLocation(shader->program, "material.diffuse");
	GLint matSpecularLoc = glGetUniformLocation(shader->program, "material.specular");
	GLint matShineLoc = glGetUniformLocation(shader->program, "material.shininess");
	GLint normalMatrixLoc = glGetUniformLocation(shader->program, "normalMatrix");
	GLuint modelLoc = glGetUniformLocation(shader->program, "model");

	glUniform3f(matAmbientLoc, material.ambient.x, material.ambient.y, material.ambient.z);
	glUniform3f(matDiffuseLoc, material.diffuse.x, material.diffuse.y, material.diffuse.z);
	glUniform3f(matSpecularLoc, material.specular.x, material.specular.y, material.specular.z);
	glUniform1f(matShineLoc, material.shininess);
	glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

