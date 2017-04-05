#include "Skybox.h"
#include <GLM\gtc\matrix_transform.hpp>
#include <soil\soil.h>

Skybox::Skybox()
{
    vertices = { glm::vec3(-1.0f,  1.0f, -1.0f),
        glm::vec3(-1.0f, -1.0f, -1.0f),
        glm::vec3(1.0f, -1.0f, -1.0f),
        glm::vec3(1.0f, -1.0f, -1.0f),
        glm::vec3(1.0f,  1.0f, -1.0f),
        glm::vec3(-1.0f,  1.0f, -1.0f),
        
        glm::vec3(-1.0f, -1.0f,  1.0f),
        glm::vec3(-1.0f, -1.0f, -1.0f),
        glm::vec3(-1.0f,  1.0f, -1.0f),
        glm::vec3(-1.0f,  1.0f, -1.0f),
        glm::vec3(-1.0f,  1.0f,  1.0f),
        glm::vec3(-1.0f, -1.0f,  1.0f),
        
        glm::vec3(1.0f, -1.0f, -1.0f),
        glm::vec3(1.0f, -1.0f,  1.0f),
        glm::vec3(1.0f,  1.0f,  1.0f),
        glm::vec3(1.0f,  1.0f,  1.0f),
        glm::vec3(1.0f,  1.0f, -1.0f),
        glm::vec3(1.0f, -1.0f, -1.0f),
        
        glm::vec3(-1.0f, -1.0f,  1.0f),
        glm::vec3(-1.0f,  1.0f,  1.0f),
        glm::vec3(1.0f,  1.0f,  1.0f),
        glm::vec3(1.0f,  1.0f,  1.0f),
        glm::vec3(1.0f, -1.0f,  1.0f),
        glm::vec3(-1.0f, -1.0f,  1.0f),
        
        glm::vec3(-1.0f,  1.0f, -1.0f),
        glm::vec3(1.0f,  1.0f, -1.0f),
        glm::vec3(1.0f,  1.0f,  1.0f),
        glm::vec3(1.0f,  1.0f,  1.0f),
        glm::vec3(-1.0f,  1.0f,  1.0f),
        glm::vec3(-1.0f,  1.0f, -1.0f),
        
        glm::vec3(-1.0f, -1.0f, -1.0f),
        glm::vec3(-1.0f, -1.0f,  1.0f),
        glm::vec3(1.0f, -1.0f, -1.0f),
        glm::vec3(1.0f, -1.0f, -1.0f),
        glm::vec3(-1.0f, -1.0f,  1.0f),
        glm::vec3(1.0f, -1.0f,  1.0f)
    };
    // Compile and load shaders
    shader = new Shader("res/shaders/skybox.vs", "res/shaders/skybox.fs");
    
    //std::vector<glm::vec3> skybox_normals;
    //std::vector<glm::vec2> skybox_UVs;
    //loadOBJ(".\\res\\models\\cube.obj", vertices, skybox_normals, skybox_UVs);
    
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices.front(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    
    // Prepare skybox cubemap
    std::vector<const GLchar*> faces;
    faces.push_back("res/textures/aqua9_ft.jpg");
    faces.push_back("res/textures/aqua9_bk.jpg");
    faces.push_back("res/textures/aqua9_up.jpg");
    faces.push_back("res/textures/aqua9_dn.jpg");
    faces.push_back("res/textures/aqua9_rt.jpg");
    faces.push_back("res/textures/aqua9_lf.jpg");
    
    glActiveTexture(GL_TEXTURE1);
    
    GLuint skyboxTexture = loadCubemap(faces);
    
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
    //glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    
}

void Skybox::render(glm::mat4 view, glm::mat4 projection)
{
    shader->use();
    
    // Remove translation component of the view matrix
    glm::mat4 skybox_view = glm::mat4(glm::mat3(view));
    
    // Broadcast the uniform values to the shaders
    GLuint projectionLoc = glGetUniformLocation(shader->program, "projection");
    GLuint viewLoc = glGetUniformLocation(shader->program, "view");
    
    
    
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(skybox_view));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    glUniform1i(glGetUniformLocation(shader->program, "skyboxTexture"), 1);
    
    glDepthMask(GL_FALSE);
    // skybox cube
    glBindVertexArray(VAO);
    
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    
    glBindVertexArray(0);
    
    glDepthMask(GL_TRUE); // Set depth function back to default
    
}

GLuint Skybox::loadCubemap(std::vector<const GLchar*> faces)
{
    GLuint textureID;
    glGenTextures(1, &textureID);
    
    int width, height;
    unsigned char* image;
    
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    for (GLuint i = 0; i < faces.size(); i++)
    {
        image = SOIL_load_image(faces[i], &width, &height, 0, SOIL_LOAD_RGB);
        glTexImage2D(
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
            GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image
            );
        
        SOIL_free_image_data(image); //free resources
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    
    return textureID;
}


