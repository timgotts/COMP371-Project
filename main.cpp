#define GLEW_STATIC

#include <iostream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <GLM\gtc\type_ptr.hpp>
#include <random>
#include <time.h>
#include <string>
#include <thread>

#include "Camera.h"
#include "Shader.h"
#include "Cube.h"
#include "Rock.h"
#include "Fish.h"
#include "Skybox.h"
#include "Terrain.h"
#include "Seaweed.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Timer.h"
#include "GlowFish.h"
#include "Coral.h"
#include "Harpoon.h"


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

Camera * camera = new Camera();

std::vector<Fish*> fishes;
std::vector<GlowFish*> glowFish;
std::vector<Harpoon*> harpoons;
std::vector<Cube*> cubes;
Skybox* skybox;
DirectionalLight sun;
SpotLight spotLight;
std::vector<PointLight> pointLights;
Terrain* terrain;
Shader* lightingShader;
Shader* lightSourceShader;
Shader* skyboxShader;



// Free function signatures
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void cursorPosCallback(GLFWwindow* window, double xPos, double yPos);
void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void windowResizeCallback(GLFWwindow* window, int width, int height);
void doMovement();
void animateFish(float deltaTime);
void animateFishThread(int start, int count);
void animateHarpoon(float deltaTime);
void createTerrainThread();


// ________________________________ MAIN ________________________________
int main()
{
    srand(time(NULL));
    
    
    // ___________________________ SETTINGS ___________________________
    
    // Generate terrain
    std::thread terrainThread(createTerrainThread);
    
    
    
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
    
    
    // Create Shaders
    lightingShader = new Shader("res/shaders/mainlit.vs", "res/shaders/mainlit.fs");
    lightSourceShader = new Shader("res/shaders/lightsource.vs", "res/shaders/lightsource.fs");
    skyboxShader = new Shader("res/shaders/skybox.vs", "res/shaders/skybox.fs");
    
	sun = DirectionalLight(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.3f, 0.3f, 0.7f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-0.2f, -1.0f, -0.3f));
    //sun = DirectionalLight(glm::vec3(0.1f,0.1f,0.3f),glm::vec3(0.0f,0.0f,0.3f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(-0.2f, -1.0f, -0.3f));
    
    terrainThread.join();
    
    float terrainSize = (terrain->getSize()) * (terrain->getPointsPerChunk()-1);    
    
    
    
    //Randomize fish locations
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> u1(0, 1);
    
	// Generate fish
    Timer::start("fish");
    for (int i = 0; i < 600; ++i)
    {
        fishes.push_back(new Fish(glm::vec3(u1(gen) * terrainSize, u1(gen) * 80.0f + 15.0f, u1(gen) * terrainSize)));
    }
    Timer::stop("Fish");
    
	// Generate glowing fish
    Timer::start("GlowFish");
    for (int i = 0; i < 25; ++i)
    {
        glowFish.push_back(new GlowFish(glm::vec3(u1(gen) * terrainSize, u1(gen) * 100.0f + 10.0f, u1(gen) * terrainSize)));
    }
    Timer::stop("GlowFish");
    
    
    // Generate seaweed
    Timer::start("seaweed");
    for (int i = 0; i < (int)(0.0002f*(terrainSize*terrainSize)); i++) 
    {
         float x = u1(gen) * terrainSize;
         float z = u1(gen) * terrainSize;
         
         int patchSize = rand() % 20;
         
         for (float j = 0; j < patchSize; j++)
         {
         
             int sx = x + u1(gen) * 20;
             int sz = z + u1(gen) * 20;
             
             float y = terrain->getHeightAt(sx, sz);
             
             TerrainChunk* chunk = terrain->getChunkAtReal((int)sx, (int)sz);
             if (chunk != nullptr)
                 chunk->addEntity(new Seaweed(glm::vec3(sx, y + 1, sz)));
                 
         }
    }
    Timer::stop("seaweed");
    
    
    // Generate rocks
    Timer::start("rock");
    for(int i = 0; i < (int)(0.001f*terrainSize*terrainSize); i++)
    {
        float x = u1(gen) * terrainSize;
        
        float z = u1(gen) * terrainSize;
        
        float y = terrain->getHeightAt(x,z);
        
        TerrainChunk* chunk = terrain->getChunkAtReal((int)x,(int)z);
        if(chunk != nullptr)
            chunk->addEntity(new Rock(glm::vec3(-x, -y, -z)));
    }
    Timer::stop("rock");
    
    
    // Generate coral
    Timer::start("coral");
    for (int i = 0; i < (int)(0.0009f*terrainSize*terrainSize); i++)
    {
        float x = u1(gen) * terrainSize;
        
        float z = u1(gen) * terrainSize;
        
        float y = terrain->getHeightAt(x, z);
        
        TerrainChunk* chunk = terrain->getChunkAtReal((int)x, (int)z);
        if (chunk != nullptr)
            chunk->addEntity(new Coral(glm::vec3(-x, -y, -z)));
    }
    Timer::stop("Coral");
    
    // ____________________________ END CREATING SCENE ____________________________
    
    
    camera->setPosition(glm::vec3(-float(terrainSize / 2), -40.0f, -float(terrainSize / 2)));
    
    camera->setPosition(glm::vec3(-float(terrainSize / 2), -(terrain->getHeightAt(terrainSize / 2,terrainSize/2)+5), -float(terrainSize / 2)));
    terrain->updateChunks(camera->getPosition());
    
    spotLight = SpotLight(glm::vec3(0.5f, 0.5f, 0.2f), glm::vec3(0.3f, 0.3f, 0.05f), glm::vec3(1.0f, 1.0f, 1.0f),
                          camera->getPosition(), camera->getFront(), glm::cos(glm::radians(15.5f)), glm::cos(glm::radians(25.0f)), 1.0f, 0.0014f, 0.000007f);
    
    // ___________________________ GAME LOOP ___________________________
    glfwShowWindow(window);
    while (!glfwWindowShouldClose(window)) {
        
        float viewDistance = terrain->getRenderDistance() * terrain->getPointsPerChunk();
        
        // Update frame deltaTime
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        // Process events
        glfwPollEvents();
        doMovement();
        
        // Apply camera tranformations
        glm::mat4 view = camera->getViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera->getSmoothedZoom(deltaTime)), (GLfloat)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 1000.0f);
        
        // Clear frame buffer
        glClearColor((2.0f/255.0f), (34.0f / 255.0f), (134.0f/255.0f), 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        
        // Remove translation component of the view matrix for skybox 
        glm::mat4 skybox_view = glm::mat4(glm::mat3(view));
        
        //Skybox
        skyboxShader->use();
        
        glUniform1f(glGetUniformLocation(skyboxShader->program, "viewDistance"), viewDistance);
        glUniformMatrix4fv(glGetUniformLocation(skyboxShader->program, "view"), 1, GL_FALSE, glm::value_ptr(skybox_view));
        glUniformMatrix4fv(glGetUniformLocation(skyboxShader->program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        //skybox->render(skyboxShader);
        
        //Terrain/fish/rocks
        lightingShader->use();
        glUniform1f(glGetUniformLocation(lightingShader->program, "viewDistance"), viewDistance);
        glUniformMatrix4fv(glGetUniformLocation(lightingShader->program, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader->program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        
        // Set lighting uniforms
        // Directional light
        glUniform3f(glGetUniformLocation(lightingShader->program, "dirLight.direction"), sun.direction.x, sun.direction.y, sun.direction.z);
        glUniform3f(glGetUniformLocation(lightingShader->program, "dirLight.ambient"), sun.ambient.x, sun.ambient.y, sun.ambient.z);
        glUniform3f(glGetUniformLocation(lightingShader->program, "dirLight.diffuse"), sun.diffuse.x, sun.diffuse.y, sun.diffuse.z);
        glUniform3f(glGetUniformLocation(lightingShader->program, "dirLight.specular"), sun.specular.x, sun.specular.y, sun.specular.z);
        
        // SpotLight
        glUniform3f(glGetUniformLocation(lightingShader->program, "spotLight.position"), -camera->getPosition().x, -camera->getPosition().y, -camera->getPosition().z);
        glUniform3f(glGetUniformLocation(lightingShader->program, "spotLight.direction"), -camera->getFront().x, -camera->getFront().y, -camera->getFront().z);
        glUniform3f(glGetUniformLocation(lightingShader->program, "spotLight.ambient"), spotLight.ambient.x, spotLight.ambient.y, spotLight.ambient.z);
        glUniform3f(glGetUniformLocation(lightingShader->program, "spotLight.diffuse"), spotLight.diffuse.x, spotLight.diffuse.y, spotLight.diffuse.z);
        glUniform3f(glGetUniformLocation(lightingShader->program, "spotLight.specular"), spotLight.specular.x, spotLight.specular.y, spotLight.specular.z);
        glUniform1f(glGetUniformLocation(lightingShader->program, "spotLight.constant"), spotLight.constant);
        glUniform1f(glGetUniformLocation(lightingShader->program, "spotLight.linear"), spotLight.linear);
        glUniform1f(glGetUniformLocation(lightingShader->program, "spotLight.quadratic"), spotLight.quadratic);
        glUniform1f(glGetUniformLocation(lightingShader->program, "spotLight.cutOff"), spotLight.cutOff);
        glUniform1f(glGetUniformLocation(lightingShader->program, "spotLight.outerCutOff"), spotLight.outerCutOff);
        
        glUniform3f(glGetUniformLocation(lightingShader->program, "viewPos"), -camera->getPosition().x, -camera->getPosition().y, -camera->getPosition().z);
        
        // Point lights (glowfish)
        for (int i = 0; i < glowFish.size(); i++)
        {
            glowFish.at(i)->animate(deltaTime, terrain);
            std::string identifier = "pointLights[" + std::to_string(i) + "]";
            
            glUniform3f(glGetUniformLocation(lightingShader->program, (identifier + ".position").c_str()), glowFish.at(i)->getPosition().x, glowFish.at(i)->getPosition().y, glowFish.at(i)->getPosition().z);
            glUniform3f(glGetUniformLocation(lightingShader->program, (identifier + ".ambient").c_str()), glowFish.at(i)->ambient.x, glowFish.at(i)->ambient.y, glowFish.at(i)->ambient.z);
            glUniform3f(glGetUniformLocation(lightingShader->program, (identifier + ".diffuse").c_str()), glowFish.at(0)->diffuse.x, glowFish.at(0)->diffuse.y, glowFish.at(0)->diffuse.z);
            glUniform3f(glGetUniformLocation(lightingShader->program, (identifier + ".specular").c_str()), glowFish.at(0)->specular.x, glowFish.at(0)->specular.y, glowFish.at(0)->specular.z);
            glUniform1f(glGetUniformLocation(lightingShader->program, (identifier + ".constant").c_str()), glowFish.at(0)->constant);
            glUniform1f(glGetUniformLocation(lightingShader->program, (identifier + ".linear").c_str()), glowFish.at(0)->linear);
            glUniform1f(glGetUniformLocation(lightingShader->program, (identifier + ".quadratic").c_str()), glowFish.at(0)->quadratic);
        }
        
        // Render the terrain and scene objects
        terrain->render(camera->getPosition(), lightingShader, deltaTime);
        
        animateFish(deltaTime);
        // Render objects in the scene
        for (auto fish : fishes)
        {
            fish->render(lightingShader);
        }
        
        animateHarpoon(deltaTime);
        for (auto harpoon : harpoons)
        {
            harpoon->render(lightingShader);
        }
        
        //Glowfish
        lightSourceShader->use();
        glUniformMatrix4fv(glGetUniformLocation(lightSourceShader->program, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(lightSourceShader->program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        
        glUniform1f(glGetUniformLocation(lightSourceShader->program, "viewDistance"),  viewDistance);
        
        
        glUniform3f(glGetUniformLocation(lightingShader->program, "viewPos"), -camera->getPosition().x, -camera->getPosition().y, -camera->getPosition().z);
        
        //Render glowfish
        for (auto gf : glowFish)
        {
            gf->render(lightSourceShader);
        }
        
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
    
    camera->processMouseMovement(xOffset, yOffset);
}




void scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
    camera->processMouseScroll(yOffset);
}



void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
		glm::vec3 harpoonPos;
		harpoonPos = camera->getPosition() + camera->getUp() - 0.7f *camera->getRight();
		harpoons.push_back(new Harpoon(harpoonPos, camera->getFront()));
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
    GLfloat velocity = 2*camera->getMovementSpeed() * deltaTime;
    
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
    {
        glm::vec3 newPos = -(camera->getPosition() + velocity*(camera->getFront()));
        if(terrain->isPositionValid(newPos))
        {
            camera->processKeyboard(FORWARD, deltaTime);
            terrain->updateChunks(camera->getPosition());
        }
        
    }
    
    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
    {
        glm::vec3 newPos = -(camera->getPosition() - velocity*(camera->getFront()));
        if(terrain->isPositionValid(newPos))
        {
            camera->processKeyboard(BACKWARD, deltaTime);
            terrain->updateChunks(camera->getPosition());
        }
    }
    
    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
    {
        glm::vec3 newPos = -(camera->getPosition() + velocity*(camera->getRight()));
        if(terrain->isPositionValid(newPos))
        {
            camera->processKeyboard(LEFT, deltaTime);
            terrain->updateChunks(camera->getPosition());
        }
    }
    
    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
    {
        glm::vec3 newPos = -(camera->getPosition() - velocity*(camera->getRight()));
        if(terrain->isPositionValid(newPos))
        {
            camera->processKeyboard(RIGHT, deltaTime);
            terrain->updateChunks(camera->getPosition());
        }
    }
    
    if (keys[GLFW_KEY_SPACE])
    {
        glm::vec3 newPos = -(camera->getPosition() - velocity*(camera->getUp()));
        if(terrain->isPositionValid(newPos))
        {
            camera->processKeyboard(UP, deltaTime);
            terrain->updateChunks(camera->getPosition());
        }
    }
    
    if (keys[GLFW_KEY_LEFT_CONTROL])
    {
        glm::vec3 newPos = -(camera->getPosition() + velocity*(camera->getUp()));
        if(terrain->isPositionValid(newPos))
        {
            camera->processKeyboard(DOWN, deltaTime);
            terrain->updateChunks(camera->getPosition());
        }
    }
    
    if (keys[GLFW_KEY_Q])
    {
        glm::vec3 newPos = -(camera->getPosition() + velocity*(camera->getFront()));
        if(terrain->isPositionValid(newPos))
        {
            camera->processKeyboard(ROLL_LEFT, deltaTime);
            terrain->updateChunks(camera->getPosition());
        }
    }
    
    if (keys[GLFW_KEY_E])
    {
        camera->processKeyboard(ROLL_RIGHT, deltaTime);
    }
    
    if (keys[GLFW_KEY_LEFT_SHIFT])
    {
        camera->processKeyboard(SPRINT, deltaTime);
    }
    
    if (keys[GLFW_KEY_LEFT_ALT])
    {
        camera->processKeyboard(CRAWL, deltaTime);
    }
    
    if (!keys[GLFW_KEY_LEFT_ALT] && !keys[GLFW_KEY_LEFT_SHIFT])
    {
        camera->processKeyboard(WALK, deltaTime);
    }
    
}

void animateFish(float deltaTime)
{
    int size = fishes.size();
    
    std::thread t0(animateFishThread, 0, size / 8);
    std::thread t1(animateFishThread, size / 8, size / 8);
    std::thread t2(animateFishThread, size / 4, size / 8);
    std::thread t3(animateFishThread, 3 * size / 8, size / 8);
    std::thread t4(animateFishThread, size / 2, size / 8);
    std::thread t5(animateFishThread, 5 * size / 8, size / 8);
    std::thread t6(animateFishThread, 3 * size / 4, size / 8);
    std::thread t7(animateFishThread, 7 * size / 8, size / 8);
    t0.join();
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
}

void animateFishThread(int start, int count)
{
    for (int i = start; i < start + count; ++i)
    {
        fishes[i]->animate(deltaTime, terrain);
    }
}

void animateHarpoon(float deltaTime)
{
    for (auto harpoon : harpoons)
    {
        harpoon->animate(deltaTime, terrain);
    }
}

void createTerrainThread()
{
    Timer::start("terrain");
    terrain = new Terrain();
    Timer::stop("Terrain");
    
    float terrainSize = (terrain->getSize()) * (terrain->getPointsPerChunk()-1);
    
    
    //Randomize fish locations
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> u1(0, 1);
    
    
    
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
    
}
