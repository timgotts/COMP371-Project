#pragma once
#include "Renderable.h"
class LightSource
{
    public:
    GLuint LightVAO;
    void render(glm::mat4 view, glm::mat4 projection);
    LightSource(float edgeLength, glm::vec3 eulerXYZ, glm::vec3 position);
    ~LightSource();
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
    
    std::vector<glm::vec3> vertices;
    std::vector<GLuint> indices;
    
    glm::mat4 model;
    
    Shader * shader;
};

