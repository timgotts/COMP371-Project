#pragma once

#include <vector>
#include <GL\glew.h>
#include <GLM\glm.hpp>
#include <vector>


#include "Shader.h"
#include "Material.h"

class Renderable 
{
    public:
    
    GLuint VAO = 0;
    GLuint VBO = 0;
    
    std::vector<glm::vec3> vertices;
    std::vector<GLuint> indices;
    
    glm::mat4 model;
    
    Material material;
    
    float radius = -1;
    
    virtual void render(Shader* shader) {};
    virtual void animate(float deltaTime) {};
    
    virtual bool load() { return true; };
    virtual void unload() {};
    
    private:
    
};
