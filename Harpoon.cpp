#pragma once

#include "Harpoon.h"
#include <GLM\glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>


glm::vec3 Harpoon::calculateNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
{
    // Edge1, Edge2
    glm::vec3 e1, e2;
    glm::vec3 normal;
    
    // Find vectors for two edges sharing p1
    e1 = p2 - p1;
    e2 = p3 - p1;
    
    // Calculate normal
    normal = glm::normalize(glm::cross(e2, e1));
    
    return normal;
}

Harpoon::Harpoon(glm::vec3 position, glm::quat cameraQuat) : position(-position)
{
    
    //glm::vec3 harpoonVertices[] = {
    //    // face 1
    //    glm::vec3(0.0,0.0,0.0),
    //    glm::vec3(-0.1,0.2,0.0),
    //    glm::vec3(0.1,0.2,0.0),
    //    glm::vec3(0.2,0.1,0.0),
    //    glm::vec3(0.2,-0.1,0.0),
    //    glm::vec3(0.1,-0.2,0.0),
    //    glm::vec3(-0.1,-0.2,0.0),
    //    glm::vec3(-0.2,-0.1,0.0),
    //    glm::vec3(-0.2,0.1,0.0),
    //    // face 2
    //    glm::vec3(0.0,0.0,6.0),
    //    glm::vec3(-0.1,0.2,6.0),
    //    glm::vec3(0.1,0.2,6.0),
    //    glm::vec3(0.2,0.1,6.0),
    //    glm::vec3(0.2,-0.1,6.0),
    //    glm::vec3(0.1,-0.2,6.0),
    //    glm::vec3(-0.1,-0.2,6.0),
    //    glm::vec3(-0.2,-0.1,6.0),
    //    glm::vec3(-0.2,0.1,6.0)
    //};

	quat = cameraQuat * quat;
	quat = glm::normalize(quat);


	glm::vec3 harpoonVertices[] = {
	    // face 1
	    glm::vec3(0.0,0.0,0.0),
	    glm::vec3(0.0,0.2,-0.1),
	    glm::vec3(0.0,0.2,0.1),
	    glm::vec3(0.0,0.1,0.2),
	    glm::vec3(0.0,-0.1,0.2),
	    glm::vec3(0.0,-0.2,0.1),
	    glm::vec3(0.0,-0.2,-0.1),
	    glm::vec3(0.0,-0.1,-0.2),
	    glm::vec3(0.0,0.1,-0.2),
	    // face 2
	    glm::vec3(6.0,0.0,0.0),
	    glm::vec3(6.0,0.2,-0.1),
	    glm::vec3(6.0,0.2,0.1),
	    glm::vec3(6.0,0.1,0.2),
	    glm::vec3(6.0,-0.1,0.2),
	    glm::vec3(6.0,-0.2,0.1),
	    glm::vec3(6.0,-0.2,-0.1),
	    glm::vec3(6.0,-0.1,-0.2),
	    glm::vec3(6.0,0.1,-0.2)
	};

	// calculate surface normals
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
    
	// set vertices and normals for each side
    int surface = 0;
    vertices = {
		// face 1
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
        
		// long sides
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
        
		// face 2
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

	// Apply translation to model matrix
    //model = glm::translate(model, -position);

	
	
	//float t = asin(direction.z);
	//float p = pow(atan(-direction.y * direction.x), 2);

	//model = glm::rotate(model, glm::radians(t), glm::vec3(1.0f, 0.0f, 0.0f));
	// = glm::rotate(model, glm::radians(p), glm::vec3(0.0f, 1.0f, 0.0f));


	updateVectors();


	// Apply material properties
    material = Material(glm::vec3(0.2), glm::vec3(0.5),glm::vec3(0.5), 0.7);
}

bool Harpoon::load()
{
    if (VAO == 0)
    {
        
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

void Harpoon::updateVectors()
{

	glm::mat4 rotation = glm::mat4_cast(quat);

	glm::mat4 translation = glm::mat4(1.0f);
	translation = glm::translate(translation, position);

	glm::mat4 viewMatrix = rotation * translation;

	glm::mat4 mat = viewMatrix;

	front = glm::vec3(mat[0][2], mat[1][2], mat[2][2]);
	right = glm::vec3(mat[0][0], mat[1][0], mat[2][0]);
	up = glm::normalize(glm::cross(front, right));
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

// animate the harpoon over time to move it through the scene
void Harpoon::animate(float deltaTime, Terrain * terrain)
{
	if ((position.y < (terrain->getHeightAt((int)position.x, (int)position.z) + 5.0f)) && (isStuck == false))
	{
		isStuck = true;
	}
	
	// if the harpoon is stuck
    if(isStuck)
      return;
    
	totalTime += deltaTime;

	pitch -= 0.25f;
	updateVectors();
	position += front * velocity * deltaTime;

	// Model transformations
	glm::mat4 tempModel = glm::translate(glm::mat4(1.0f), position);

	glm::mat4 rotationMatrix = glm::mat4_cast(quat);
	tempModel = tempModel * rotationMatrix;


	model = tempModel;
}