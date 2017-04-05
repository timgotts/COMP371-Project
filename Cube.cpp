#pragma once

#include "Cube.h"



Cube::Cube(float edgeLength, glm::vec3 eulerXYZ, glm::vec3 position)
{
    
    // Base cube vertice data
    vertices =
    {
        glm::vec3(-0.5f,-0.5f,-0.5f),	// 0 Left bottom back
        glm::vec3(-0.5f,-0.5f,0.5f),	// 1 Left bottom front
        glm::vec3(-0.5f,0.5f,-0.5f),	// 2 Left top back
        glm::vec3(-0.5f,0.5f,0.5f),		// 3 Left top front
        glm::vec3(0.5f,-0.5f,-0.5f),	// 4 Right bottom back
        glm::vec3(0.5f,-0.5f,0.5f),		// 5 Right bottom front
        glm::vec3(0.5f,0.5f,-0.5f),		// 6 Right top back
        glm::vec3(0.5f,0.5f,0.5f)		// 7 Right top front
    };
    
    indices =
    {
        // Left face
        0, 1, 2,
        2, 1, 3,
        
        // Right face
        4, 5, 6,
        6, 5, 7,
        
        // Front face
        1, 5, 3,
        3, 5, 7,
        
        // Back face
        0, 4, 2,
        2, 4, 6,
        
        // Bottom face
        1, 5, 0,
        0, 5, 4,
        
        // Top face
        3, 7, 2,
        2, 7, 6
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
    
    // Apply scale to model matrix
    model = glm::scale(model, glm::vec3(edgeLength, edgeLength, edgeLength));
    
    // Apply rotations to model matrix
    model = glm::rotate(model, eulerXYZ.x, glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, eulerXYZ.y, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, eulerXYZ.z, glm::vec3(0.0f, 0.0f, 1.0f));
    
    
    
    
    
    // Compile and load shaders
    shader = new Shader("res/shaders/main.vs", "res/shaders/main.fs");
    
}



void Cube::render(glm::mat4 view, glm::mat4 projection)
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
