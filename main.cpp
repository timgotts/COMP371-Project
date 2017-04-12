#define GLEW_STATIC

#include <iostream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <GLM\gtc\type_ptr.hpp>
#include <random>
#include <time.h>
#include "Camera.h"
#include "Shader.h"
#include "Cube.h"
#include "Rock.h"
#include "Fish.h"
#include "Skybox.h"
#include "Terrain.h"
#include "Seaweed.h"

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

Camera* camera = new Camera();

std::vector<Renderable*> objects;
Skybox* skybox;
Terrain* terrain;




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
    
    // Randomly generate some fish objects
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> u1(-1, 1);
    
    for (int i = 0; i < 1000; ++i)
    {
        objects.push_back(new Fish(glm::vec3(u1(gen) * 300.0f, u1(gen) * 100.0f, u1(gen) * 300.0f)));
    }
    
    
    // Generate skybox
    skybox = new Skybox();
    
    // Generate terrain
    terrain = new Terrain();
    
    // ____________________________ END CREATING SCENE ____________________________
    
    
    
    
    
    // ___________________________ GAME LOOP ___________________________
    
    while (!glfwWindowShouldClose(window)) {
        
        // Update frame deltaTime
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        // Process events
        glfwPollEvents();
        doMovement();
        
        // Clear frame buffer
        glClearColor(0.01f, 0.01f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Apply camera tranformations
        glm::mat4 view = camera->getViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera->getSmoothedZoom(deltaTime)), (GLfloat)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 1000.0f);
        
        //Render skybox
        skybox->render(view, projection);
        terrain->render(camera->getPosition(), view, projection);
        // Render objects
        for (auto obj : objects)
        {
            obj->animate(deltaTime);
            obj->render(view, projection);
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
        camera->processKeyboard(FORWARD, deltaTime);
    }
    
    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
    {
        camera->processKeyboard(BACKWARD, deltaTime);
    }
    
    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
    {
        camera->processKeyboard(LEFT, deltaTime);
    }
    
    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
    {
        camera->processKeyboard(RIGHT, deltaTime);
    }
    
    if (keys[GLFW_KEY_SPACE])
    {
        camera->processKeyboard(UP, deltaTime);
    }
    
    if (keys[GLFW_KEY_LEFT_CONTROL])
    {
        camera->processKeyboard(DOWN, deltaTime);
    }
    
    if (keys[GLFW_KEY_Q])
    {
        camera->processKeyboard(ROLL_LEFT, deltaTime);
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