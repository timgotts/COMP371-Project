#pragma once

#include "Rock.h"
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.inl>
#include <random>

#define PI 3.14159265358979323846

Shader* Rock::rockShader = nullptr;

Rock::Rock(glm::vec3 position)
{
    // randomize whether colour will be shade of brown or grey
    int colorType = rand() % 10;
    // initialize placeholder for colour float value
    double color;
    
    float const X = 0.525731112119133606f;
    float const Z = 0.850650808352039932f;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    // uniform distribution for the rocks
    std::uniform_real_distribution<> dis(0, 1);
    std::uniform_real_distribution<> scaler(0.5, 0.75);
    
    // brown rock
    if (colorType >= 7) 
    {
        // pick a shade
        std::uniform_real_distribution<> colorDis(0.15, 0.5);
        color = colorDis(gen);
        
        // set vertices and color values (x,x/2,0 for brown)
        vertices = {
            glm::vec3(-X,0,Z),
            glm::vec3(color, color / 2, 0.0),
            glm::vec3(X,0,Z),
            glm::vec3(color, color / 2, 0.0),
            glm::vec3(-X,0,-Z),
            glm::vec3(color, color / 2, 0.0),
            glm::vec3(X,0,-Z),
            glm::vec3(color, color / 2, 0.0),
            glm::vec3(0,Z,X),
            glm::vec3(color, color / 2, 0.0),
            glm::vec3(0,Z,-X),
            glm::vec3(color, color / 2, 0.0),
            glm::vec3(0,-Z,X),
            glm::vec3(color, color / 2, 0.0),
            glm::vec3(0.0,-Z,-X),
            glm::vec3(color, color / 2, 0.0),
            glm::vec3(Z,X,0),
            glm::vec3(color, color / 2, 0.0),
            glm::vec3(-Z,X,0),
            glm::vec3(color, color / 2, 0.0),
            glm::vec3(Z,-X,0),
            glm::vec3(color, color / 2, 0.0),
            glm::vec3(-Z,-X,0),
            glm::vec3(color, color / 2, 0.0),
        };
    }
    else // grey rock
    {
        // pick a shade
        std::uniform_real_distribution<> colorDis(0.15, 0.4);
        color = colorDis(gen);
        
        // set vertices and color values (x=y=z for grey)
        vertices = {
            glm::vec3(-X,0,Z),
            glm::vec3(color, color, color),
            glm::vec3(X,0,Z),
            glm::vec3(color, color, color),
            glm::vec3(-X,0,-Z),
            glm::vec3(color, color, color),
            glm::vec3(X,0,-Z),
            glm::vec3(color, color, color),
            glm::vec3(0,Z,X),
            glm::vec3(color, color, color),
            glm::vec3(0,Z,-X),
            glm::vec3(color, color, color),
            glm::vec3(0,-Z,X),
            glm::vec3(color, color, color),
            glm::vec3(0.0,-Z,-X),
            glm::vec3(color, color, color),
            glm::vec3(Z,X,0),
            glm::vec3(color, color, color),
            glm::vec3(-Z,X,0),
            glm::vec3(color, color, color),
            glm::vec3(Z,-X,0),
            glm::vec3(color, color, color),
            glm::vec3(-Z,-X,0),
            glm::vec3(color, color, color)
        };
    }
    
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
    
    // nudge the vertices randomly to create rock-like shape
    std::uniform_real_distribution<> nudge(-0.3, 0.3);
    for (int i=0; i<vertices.size(); i+=2)
    {
        vertices.at(i).x += nudge(gen);
        vertices.at(i).y += nudge(gen);
        vertices.at(i).z += nudge(gen);
    }
    
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
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    // Apply translation to model matrix
    model = glm::translate(model, -position);
    
	// Apply scale to model matrix
	if (rand() % 100 == 99)
	{
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
	}
	else
	{
		float scaler = rand() % 4;
		model = glm::scale(model, glm::vec3(scaler, scaler, scaler));
	}
    
    // Apply rotations to model matrix
    glm::vec3 eulerXYZ(dis(gen) * PI, dis(gen) * PI, dis(gen) * PI);
    
    model = glm::rotate(model, eulerXYZ.x, glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, eulerXYZ.y, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, eulerXYZ.z, glm::vec3(0.0f, 0.0f, 1.0f));
    
    
    // Compile and load shaders
    if(rockShader == nullptr)
        rockShader = new Shader("res/shaders/rock.vs", "res/shaders/rock.fs"); 
    
    shader = rockShader;
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
