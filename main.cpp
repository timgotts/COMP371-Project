#define GLEW_STATIC

#include <iostream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <GLM\gtc\type_ptr.hpp>
#include <random>
#include <time.h>
#include <string>

#include "Camera.h"
#include "Shader.h"
#include "Cube.h"
#include "Rock.h"
#include "Fish.h"
#include "Skybox.h"
#include "Terrain.h"
#include "Seaweed.h"
#include "LightSource.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Timer.h"



#define PI 3.14159265358979323846

// Global variables
const int WIDTH = 1600, HEIGHT = 900;
int SCREEN_WIDTH, SCREEN_HEIGHT;

float deltaTime, lastFrame;

double mX, mY;
GLfloat lastX = WIDTH / 2.0f;
GLfloat lastY = HEIGHT / 2.0f;
bool firstMouse = true;

bool keys[1024];

Camera camera = Camera();

std::vector<Renderable*> objects;
std::vector<Cube*> cubes;
Skybox* skybox;
DirectionalLight sun;
SpotLight spotLight;
std::vector<PointLight> pointLights;
std::vector<LightSource> lightSources; // Temp to test point lights
Terrain* terrain;
Shader* lightingShader;



// Free function signatures
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void cursorPosCallback(GLFWwindow* window, double xPos, double yPos);
void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void windowResizeCallback(GLFWwindow* window, int width, int height);
void doMovement();




// ________________________________ MAIN ________________________________
int main()
{
    srand(time(NULL));
    
    
    
    
    // ___________________________ SETTINGS ___________________________
    
    
    
    // Create GLFW window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Aquinea", nullptr, nullptr);
    glfwHideWindow(window);
    
    glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
    
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        exit(1);
    }
    
    glfwMakeContextCurrent(window);
    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    
    // Set callback functions
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetWindowSizeCallback(window, windowResizeCallback);
    glfwSetScrollCallback(window, scrollCallback);
    
    
    // Initialize GLEW and OpenGL settings
    glewExperimental = GL_TRUE;
    
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        exit(1);
    }
    
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glPointSize(3);
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    // ___________________________ END SETTINGS ___________________________
    
    
    
    
    
    // ____________________________ CREATING SCENE ____________________________
    
    
    // Generate skybox
    Timer::start("skybox");
    skybox = new Skybox();
    Timer::stop("Skybox");
    
    // Generate terrain
    Timer::start("terrain");
    terrain = new Terrain();
    Timer::stop("Terrain");
    
    // Create Shaders
    lightingShader = new Shader("res/shaders/mainlit.vs", "res/shaders/mainlit.fs");
    
    //generate some fish objects
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> u1(0, 1);
    std::uniform_real_distribution<> dis(0, 1);
    
    for (int i = 0; i < 3; ++i)
    {
        objects.push_back(new Fish(glm::vec3(u1(gen) * 300.0f, u1(gen) * 100.0f, u1(gen) * 300.0f)));
    }
    
    
    //// Create some test cubes (lit objects)
    //for (int i = 0; i < 150; ++i)
    //{
    //	cubes.push_back(new Cube(dis(gen) * 2.0f, glm::vec3(dis(gen) * PI, dis(gen) * PI, dis(gen) * PI), glm::vec3(dis(gen) * 20.0f - 10.0f, dis(gen) * 20.0f - 10.0f, dis(gen) * 20.0f - 10.0f)));
    //}
    //
    ////Create some point lights
    //for (int i=0; i<4; i++)
    //{
    //	pointLights.push_back(PointLight(glm::vec3(dis(gen) * 20.0f - 10.0f, dis(gen) * 20.0f - 10.0f, dis(gen) * 20.0f - 10.0f)));
    //	// Create white cubes to show the location of point lights
    //	lightSources.push_back(LightSource(1.f, glm::vec3(dis(gen) * PI, dis(gen) * PI, dis(gen) * PI), pointLights.at(i).position));
    //}
    
    sun = DirectionalLight();
    spotLight = SpotLight(camera.getPosition(), camera.getFront());
    
    
    float terrainSize = (terrain->getSize()) * (terrain->getPointsPerChunk()-1);    
    
    
    Timer::start("fish");
    for (int i = 0; i < 300; ++i)
    {
        objects.push_back(new Fish(glm::vec3(u1(gen) * terrainSize, u1(gen) * 100.0f + 10.0f, u1(gen) * terrainSize)));
    }
    Timer::stop("Fish");
    
  /*  Timer::start("seaweed");
    for(int i = 0; i < (int)(0.01f*(terrainSize*terrainSize)); i++)
    {
    
        float x = u1(gen) * terrainSize  - terrain->getPointsPerChunk();;
        float z = u1(gen) * terrainSize  - terrain->getPointsPerChunk();;
        float y = terrain->getHeightAt(x,z);
        
        TerrainChunk* chunk = terrain->getChunkAtReal((int)x,(int)z);
        if(chunk != nullptr)
            chunk->addEntity(new Seaweed(glm::vec3(x, y+1, z)));
    }
    Timer::stop("seaweed");*/
    
    
    
    Timer::start("rock");
    for(int i = 0; i < (int)(0.01f*terrainSize*terrainSize); i++)
    {
        float x = u1(gen) * terrainSize;
        
        float z = u1(gen) * terrainSize;
        
        float y = terrain->getHeightAt(x,z);
        
        TerrainChunk* chunk = terrain->getChunkAtReal((int)x,(int)z);
        if(chunk != nullptr)
            chunk->addEntity(new Rock(glm::vec3(-x, -y, -z)));
    }
    Timer::stop("rock");
    // ____________________________ END CREATING SCENE ____________________________
    
    
    camera.setPosition(glm::vec3(-float(terrainSize / 2), -40.0f, -float(terrainSize / 2)));
    
    
    // ___________________________ GAME LOOP ___________________________
    glfwShowWindow(window);
    while (!glfwWindowShouldClose(window)) {
        
        // Update frame deltaTime
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        // Process events
        glfwPollEvents();
        doMovement();
        spotLight.UpdatePosition(camera.getPosition(),camera.getFront());
        
        // Clear frame buffer
        glClearColor(0.01f, 0.01f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Apply camera tranformations
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.getSmoothedZoom(deltaTime)), (GLfloat)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 1000.0f);
        
        //Render skybox
        skybox->render(view, projection);
        
        // Enable lighting shader
        lightingShader->use();
        
        
        // Set up lighting uniforms
        
        // Directional light
        glUniform3f(glGetUniformLocation(lightingShader->program, "dirLight.direction"), sun.direction.x, sun.direction.y, sun.direction.z);
        glUniform3f(glGetUniformLocation(lightingShader->program, "dirLight.ambient"), sun.ambient.x, sun.ambient.y, sun.ambient.z);
        glUniform3f(glGetUniformLocation(lightingShader->program, "dirLight.diffuse"), sun.diffuse.x, sun.diffuse.y, sun.diffuse.z);
        glUniform3f(glGetUniformLocation(lightingShader->program, "dirLight.specular"), sun.specular.x, sun.specular.y, sun.specular.z);
        
        ////	// Point Lights
        //	//	// Point light 1
        //glUniform3f(glGetUniformLocation(lightingShader->program, "pointLights[0].position"), pointLights[0].position.x, pointLights[0].position.y, pointLights[0].position.z);
        //glUniform3f(glGetUniformLocation(lightingShader->program, "pointLights[0].ambient"), pointLights[0].ambient.x, pointLights[0].ambient.y, pointLights[0].ambient.z);
        //glUniform3f(glGetUniformLocation(lightingShader->program, "pointLights[0].diffuse"), pointLights[0].diffuse.x, pointLights[0].diffuse.y, pointLights[0].diffuse.z);
        //glUniform3f(glGetUniformLocation(lightingShader->program, "pointLights[0].specular"), pointLights[0].specular.x, pointLights[0].specular.y, pointLights[0].specular.z);
        //glUniform1f(glGetUniformLocation(lightingShader->program, "pointLights[0].constant"), pointLights[0].constant);
        //glUniform1f(glGetUniformLocation(lightingShader->program, "pointLights[0].linear"), pointLights[0].linear);
        //glUniform1f(glGetUniformLocation(lightingShader->program, "pointLights[0].quadratic"), pointLights[0].quadratic);
        //		//// Point light 2
        //glUniform3f(glGetUniformLocation(lightingShader->program, "pointLights[1].position"), pointLights[1].position.x, pointLights[1].position.y, pointLights[1].position.z);
        //glUniform3f(glGetUniformLocation(lightingShader->program, "pointLights[1].ambient"), pointLights[1].ambient.x, pointLights[1].ambient.y, pointLights[1].ambient.z);
        //glUniform3f(glGetUniformLocation(lightingShader->program, "pointLights[1].diffuse"), pointLights[1].diffuse.x, pointLights[1].diffuse.y, pointLights[1].diffuse.z);
        //glUniform3f(glGetUniformLocation(lightingShader->program, "pointLights[1].specular"), pointLights[1].specular.x, pointLights[1].specular.y, pointLights[1].specular.z);
        //glUniform1f(glGetUniformLocation(lightingShader->program, "pointLights[1].constant"), pointLights[1].constant);
        //glUniform1f(glGetUniformLocation(lightingShader->program, "pointLights[1].linear"), pointLights[1].linear);
        //glUniform1f(glGetUniformLocation(lightingShader->program, "pointLights[1].quadratic"), pointLights[1].quadratic);
        //		//// Point light 3
        //glUniform3f(glGetUniformLocation(lightingShader->program, "pointLights[2].position"), pointLights[2].position.x, pointLights[2].position.y, pointLights[2].position.z);
        //glUniform3f(glGetUniformLocation(lightingShader->program, "pointLights[2].ambient"), pointLights[2].ambient.x, pointLights[2].ambient.y, pointLights[2].ambient.z);
        //glUniform3f(glGetUniformLocation(lightingShader->program, "pointLights[2].diffuse"), pointLights[2].diffuse.x, pointLights[2].diffuse.y, pointLights[2].diffuse.z);
        //glUniform3f(glGetUniformLocation(lightingShader->program, "pointLights[2].specular"), pointLights[2].specular.x, pointLights[2].specular.y, pointLights[2].specular.z);
        //glUniform1f(glGetUniformLocation(lightingShader->program, "pointLights[2].constant"), pointLights[2].constant);
        //glUniform1f(glGetUniformLocation(lightingShader->program, "pointLights[2].linear"), pointLights[2].linear);
        //glUniform1f(glGetUniformLocation(lightingShader->program, "pointLights[2].quadratic"), pointLights[2].quadratic);
        //		//// Point light 4
        //glUniform3f(glGetUniformLocation(lightingShader->program, "pointLights[3].position"), pointLights[3].position.x, pointLights[3].position.y, pointLights[3].position.z);
        //glUniform3f(glGetUniformLocation(lightingShader->program, "pointLights[3].ambient"), pointLights[3].ambient.x, pointLights[3].ambient.y, pointLights[3].ambient.z);
        //glUniform3f(glGetUniformLocation(lightingShader->program, "pointLights[3].diffuse"), pointLights[3].diffuse.x, pointLights[3].diffuse.y, pointLights[3].diffuse.z);
        //glUniform3f(glGetUniformLocation(lightingShader->program, "pointLights[3].specular"), pointLights[3].specular.x, pointLights[3].specular.y, pointLights[3].specular.z);
        //glUniform1f(glGetUniformLocation(lightingShader->program, "pointLights[3].constant"), pointLights[3].constant);
        //glUniform1f(glGetUniformLocation(lightingShader->program, "pointLights[3].linear"), pointLights[3].linear);
        //glUniform1f(glGetUniformLocation(lightingShader->program, "pointLights[3].quadratic"), pointLights[3].quadratic);
        
        
        ////// SpotLight
        //glUniform3f(glGetUniformLocation(lightingShader->program, "spotLight.position"), spotLight.position.x, spotLight.position.y, spotLight.position.z);
        //glUniform3f(glGetUniformLocation(lightingShader->program, "spotLight.direction"), camera.getFront().x, camera.getFront().y, camera.getFront().z);
        //glUniform3f(glGetUniformLocation(lightingShader->program, "spotLight.ambient"), spotLight.ambient.x, spotLight.ambient.y, spotLight.ambient.z);
        //glUniform3f(glGetUniformLocation(lightingShader->program, "spotLight.diffuse"), spotLight.diffuse.x, spotLight.diffuse.y, spotLight.diffuse.z);
        //glUniform3f(glGetUniformLocation(lightingShader->program, "spotLight.specular"), spotLight.specular.x, spotLight.specular.y, spotLight.specular.z);
        //glUniform1f(glGetUniformLocation(lightingShader->program, "spotLight.constant"), spotLight.constant);
        //glUniform1f(glGetUniformLocation(lightingShader->program, "spotLight.linear"), spotLight.linear);
        //glUniform1f(glGetUniformLocation(lightingShader->program, "spotLight.quadratic"), spotLight.quadratic);
        //glUniform1f(glGetUniformLocation(lightingShader->program, "spotLight.cutOff"), spotLight.cutOff);
        //glUniform1f(glGetUniformLocation(lightingShader->program, "spotLight.outerCutOff"), spotLight.cutOff);
        
        
        GLint viewPosLoc = glGetUniformLocation(lightingShader->program, "viewPos");
        GLuint viewLoc = glGetUniformLocation(lightingShader->program, "view");
        GLuint projectionLoc = glGetUniformLocation(lightingShader->program, "projection");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniform3f(viewPosLoc, camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
        
        // Render the terrain
        terrain->render(camera.getPosition(), lightingShader);
        
        // Render objects in the scene
        for (auto obj : objects)
        {
            obj->animate(deltaTime);
            obj->render(lightingShader);
        }
        
        ////Render cubes used for lighting tests
        //for (auto cube : cubes)
        //{
        //	cube->render(view, projection, lightingShader);
        //}
        
        
        
        glfwSwapBuffers(window);
    }
    
    // ___________________________ END GAME LOOP ___________________________
    
    
    
    
    glfwDestroyWindow(window);
    //TODO: object buffer cleanup
    //glDeleteVertexArrays(1, &VAO);
    //glDeleteBuffers(1, &VBO);
    glfwTerminate();
    
    
}

// ________________________________ END MAIN ________________________________




// Free function definitions

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
        
    }
    
    
    
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            keys[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            keys[key] = false;
        }
    }
    
}


void cursorPosCallback(GLFWwindow* window, double xPos, double yPos)
{
    mX = xPos;
    mY = yPos;
    
    if (firstMouse)
    {
        lastX = xPos;
        lastY = yPos;
        
        firstMouse = false;
    }
    
    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;
    
    lastX = xPos;
    lastY = yPos;
    
    camera.processMouseMovement(xOffset, yOffset);
}




void scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
    camera.processMouseScroll(yOffset);
}



void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        // SHOOT HARPOON
        // TAKE PHOTO
    }
}



void windowResizeCallback(GLFWwindow* window, int width, int height)
{
    
    SCREEN_WIDTH = width;
    SCREEN_HEIGHT = height;
    
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    
}



void doMovement()
{
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
    {
        camera.processKeyboard(FORWARD, deltaTime);
    }
    
    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
    {
        camera.processKeyboard(BACKWARD, deltaTime);
    }
    
    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
    {
        camera.processKeyboard(LEFT, deltaTime);
    }
    
    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
    {
        camera.processKeyboard(RIGHT, deltaTime);
    }
    
    if (keys[GLFW_KEY_SPACE])
    {
        camera.processKeyboard(UP, deltaTime);
    }
    
    if (keys[GLFW_KEY_LEFT_CONTROL])
    {
        camera.processKeyboard(DOWN, deltaTime);
    }
    
    if (keys[GLFW_KEY_Q])
    {
        camera.processKeyboard(ROLL_LEFT, deltaTime);
    }
    
    if (keys[GLFW_KEY_E])
    {
        camera.processKeyboard(ROLL_RIGHT, deltaTime);
    }
    
    if (keys[GLFW_KEY_LEFT_SHIFT])
    {
        camera.processKeyboard(SPRINT, deltaTime);
    }
    
    if (keys[GLFW_KEY_LEFT_ALT])
    {
        camera.processKeyboard(CRAWL, deltaTime);
    }
    
    if (!keys[GLFW_KEY_LEFT_ALT] && !keys[GLFW_KEY_LEFT_SHIFT])
    {
        camera.processKeyboard(WALK, deltaTime);
    }
    
}