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

	material = Material();
}


void Cube::render(glm::mat4 view, glm::mat4 projection, Camera& camera, std::vector<PointLight> & pointlights, DirectionalLight & dirlight, SpotLight &spotLight)
{
    shader->use();
	glm::mat3 normalMatrix = glm::transpose(glm::inverse(model));

	GLint viewPosLoc = glGetUniformLocation(shader->program, "viewPos");
	glUniform3f(viewPosLoc, camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
	
    // Broadcast the uniform values to the shaders

	GLint matAmbientLoc = glGetUniformLocation(shader->program, "material.ambient");
	GLint matDiffuseLoc = glGetUniformLocation(shader->program, "material.diffuse");
	GLint matSpecularLoc = glGetUniformLocation(shader->program, "material.specular");
	GLint matShineLoc = glGetUniformLocation(shader->program, "material.shininess");

	// Directional light
	glUniform3f(glGetUniformLocation(shader->program, "dirLight.direction"), dirlight.direction.x, dirlight.direction.y, dirlight.direction.z);
	glUniform3f(glGetUniformLocation(shader->program, "dirLight.ambient"), dirlight.ambient.x, dirlight.ambient.y, dirlight.ambient.z);
	glUniform3f(glGetUniformLocation(shader->program, "dirLight.diffuse"), dirlight.diffuse.x, dirlight.diffuse.y, dirlight.diffuse.z);
	glUniform3f(glGetUniformLocation(shader->program, "dirLight.specular"), dirlight.specular.x, dirlight.specular.y, dirlight.specular.z);

	//Point Lights
	//for(int i=0; i<pointlights.size(); i++)
	//{
	//	std::string identifier = "pointlights[" + std::to_string(i) + "]";
	//	//glUniform3f(glGetUniformLocation(shader->program, identifier), pointlights.at(0).position.x, );
	//	glUniform3f(glGetUniformLocation(shader->program, (identifier+".position").c_str()), 
	//		pointlights.at(i).position.x, pointlights.at(i).position.y, pointlights.at(i).position.z);
	//	glUniform3f(glGetUniformLocation(shader->program, (identifier + ".ambient").c_str()),
	//		pointlights.at(i).ambient.x, pointlights.at(i).ambient.y, pointlights.at(i).ambient.z);
	//	glUniform3f(glGetUniformLocation(shader->program, (identifier + ".diffuse").c_str()),
	//		pointlights.at(i).diffuse.x, pointlights.at(i).diffuse.y, pointlights.at(i).diffuse.z);
	//	glUniform3f(glGetUniformLocation(shader->program, (identifier + ".specular").c_str()),
	//		pointlights.at(i).specular.x, pointlights.at(i).specular.y, pointlights.at(i).specular.z);
	//	
	//	glUniform1f(glGetUniformLocation(shader->program, (identifier + ".constant").c_str()),
	//		pointlights.at(i).constant);
	//	glUniform1f(glGetUniformLocation(shader->program, (identifier + ".linear").c_str()),
	//		pointlights.at(i).linear);
	//	glUniform1f(glGetUniformLocation(shader->program, (identifier + ".quadratic").c_str()),
	//		pointlights.at(i).quadratic);
	//}

	// Point light 1
	glUniform3f(glGetUniformLocation(shader->program, "pointLights[0].position"), pointlights[0].position.x, pointlights[0].position.y, pointlights[0].position.z);
	glUniform3f(glGetUniformLocation(shader->program, "pointLights[0].ambient"), pointlights[0].ambient.x, pointlights[0].ambient.y, pointlights[0].ambient.z);
	glUniform3f(glGetUniformLocation(shader->program, "pointLights[0].diffuse"), pointlights[0].diffuse.x, pointlights[0].diffuse.y, pointlights[0].diffuse.z);
	glUniform3f(glGetUniformLocation(shader->program, "pointLights[0].specular"), pointlights[0].specular.x, pointlights[0].specular.y, pointlights[0].specular.z);
	glUniform1f(glGetUniformLocation(shader->program, "pointLights[0].constant"), pointlights[0].constant);
	glUniform1f(glGetUniformLocation(shader->program, "pointLights[0].linear"), pointlights[0].linear);
	glUniform1f(glGetUniformLocation(shader->program, "pointLights[0].quadratic"), pointlights[0].quadratic);
	// Point light 2
	glUniform3f(glGetUniformLocation(shader->program, "pointLights[1].position"), pointlights[1].position.x, pointlights[1].position.y, pointlights[1].position.z);
	glUniform3f(glGetUniformLocation(shader->program, "pointLights[1].ambient"), pointlights[1].ambient.x, pointlights[1].ambient.y, pointlights[1].ambient.z);
	glUniform3f(glGetUniformLocation(shader->program, "pointLights[1].diffuse"), pointlights[1].diffuse.x, pointlights[1].diffuse.y, pointlights[1].diffuse.z);
	glUniform3f(glGetUniformLocation(shader->program, "pointLights[1].specular"), pointlights[1].specular.x, pointlights[1].specular.y, pointlights[1].specular.z);
	glUniform1f(glGetUniformLocation(shader->program, "pointLights[1].constant"), pointlights[1].constant);
	glUniform1f(glGetUniformLocation(shader->program, "pointLights[1].linear"), pointlights[1].linear);
	glUniform1f(glGetUniformLocation(shader->program, "pointLights[1].quadratic"), pointlights[1].quadratic);
	// Point light 3
	glUniform3f(glGetUniformLocation(shader->program, "pointLights[2].position"), pointlights[2].position.x, pointlights[2].position.y, pointlights[2].position.z);
	glUniform3f(glGetUniformLocation(shader->program, "pointLights[2].ambient"), pointlights[2].ambient.x, pointlights[2].ambient.y, pointlights[2].ambient.z);
	glUniform3f(glGetUniformLocation(shader->program, "pointLights[2].diffuse"), pointlights[2].diffuse.x, pointlights[2].diffuse.y, pointlights[2].diffuse.z);
	glUniform3f(glGetUniformLocation(shader->program, "pointLights[2].specular"), pointlights[2].specular.x, pointlights[2].specular.y, pointlights[2].specular.z);
	glUniform1f(glGetUniformLocation(shader->program, "pointLights[2].constant"), pointlights[2].constant);
	glUniform1f(glGetUniformLocation(shader->program, "pointLights[2].linear"), pointlights[2].linear);
	glUniform1f(glGetUniformLocation(shader->program, "pointLights[2].quadratic"), pointlights[2].quadratic);
	// Point light 4
	glUniform3f(glGetUniformLocation(shader->program, "pointLights[3].position"), pointlights[3].position.x, pointlights[3].position.y, pointlights[3].position.z);
	glUniform3f(glGetUniformLocation(shader->program, "pointLights[3].ambient"), pointlights[3].ambient.x, pointlights[3].ambient.y, pointlights[3].ambient.z);
	glUniform3f(glGetUniformLocation(shader->program, "pointLights[3].diffuse"), pointlights[3].diffuse.x, pointlights[3].diffuse.y, pointlights[3].diffuse.z);
	glUniform3f(glGetUniformLocation(shader->program, "pointLights[3].specular"), pointlights[3].specular.x, pointlights[3].specular.y, pointlights[3].specular.z);
	glUniform1f(glGetUniformLocation(shader->program, "pointLights[3].constant"), pointlights[3].constant);
	glUniform1f(glGetUniformLocation(shader->program, "pointLights[3].linear"), pointlights[3].linear);
	glUniform1f(glGetUniformLocation(shader->program, "pointLights[3].quadratic"), pointlights[3].quadratic);

	// Spotlight
	// SpotLight
	glUniform3f(glGetUniformLocation(shader->program, "spotLight.position"), spotLight.position.x, spotLight.position.y, spotLight.position.z);
	glUniform3f(glGetUniformLocation(shader->program, "spotLight.direction"), camera.getFront().x, camera.getFront().y, camera.getFront().z);
	glUniform3f(glGetUniformLocation(shader->program, "spotLight.ambient"), spotLight.ambient.x, spotLight.ambient.y, spotLight.ambient.z);
	glUniform3f(glGetUniformLocation(shader->program, "spotLight.diffuse"), spotLight.diffuse.x, spotLight.diffuse.y, spotLight.diffuse.z);
	glUniform3f(glGetUniformLocation(shader->program, "spotLight.specular"), spotLight.specular.x, spotLight.specular.y, spotLight.specular.z);
	glUniform1f(glGetUniformLocation(shader->program, "spotLight.constant"), spotLight.constant);
	glUniform1f(glGetUniformLocation(shader->program, "spotLight.linear"), spotLight.linear);
	glUniform1f(glGetUniformLocation(shader->program, "spotLight.quadratic"), spotLight.quadratic);
	glUniform1f(glGetUniformLocation(shader->program, "spotLight.cutOff"), spotLight.cutOff);
	glUniform1f(glGetUniformLocation(shader->program, "spotLight.outerCutOff"), spotLight.cutOff);

	glUniform3f(matAmbientLoc, material.ambient.x, material.ambient.y, material.ambient.z);
	glUniform3f(matDiffuseLoc, material.diffuse.x, material.diffuse.y, material.diffuse.z);
	glUniform3f(matSpecularLoc,material.specular.x, material.specular.y, material.specular.z);
	glUniform1f(matShineLoc, material.shininess);


	GLint normalMatrixLoc = glGetUniformLocation(shader->program, "normalMatrix");

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

