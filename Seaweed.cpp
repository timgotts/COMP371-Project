#include "Seaweed.h"
#include <fstream>
using namespace std;

int Seaweed::amount = 0;
Seaweed::Seaweed( glm::vec3 position)
{
    
    calculateSweep();
    
    //VAO, VBO, and EBO initialization
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    //Binding the VAO
    glBindVertexArray(VAO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*totalLength, verticesVBO, GL_STATIC_DRAW);
    
    //EBO Binding
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*indexLength, indicesEBO, GL_STATIC_DRAW);
    
    //For the vertices (vertex shader)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    //For the colors (vertex shader)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //unbind the VAO
    glBindVertexArray(0);
    
    
    //Translate the weed to a position
    model = glm::translate(model, position);
    
    //Apply the a rotation
    model = glm::rotate(model, glm::radians(rotAngle), glm::vec3(0, 0, 1));
    
    //Have to add a scale matrix
    
    
    //Compile the seaweed's shaders and load.
    shader = new Shader("res/shaders/seaweed.vs", "res/shaders/seaweed.fs");	
    
    amount++;
}



void Seaweed::render(glm::mat4 view, glm::mat4 projection)
{
    //Sin functiont to move the vertices based on time.
    GLfloat timeMove = (sin(glfwGetTime()))/2;
    //enabling the shader
    shader->use();


	/*glm::mat4 shear = 
	{
		1, timeMove, 0, 0,
		0, 1, timeMove ,0,
		0, 0, 1, 0,
		0, 0, 0, 0

	}; */
    
    GLuint transformLoc = glGetUniformLocation(shader->program, "model");
    GLuint viewMatrixLoc = glGetUniformLocation(shader->program, "view");
    GLuint projectionLoc = glGetUniformLocation(shader->program, "projection");
    
    //model = glm::translate(model, timeMove*(glm::vec3(0, 1, 0)));
    
	//model = model*shear;

    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model)); 
    glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    
    //Draw the seaweed
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexLength, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}




void Seaweed::calculateSweep()
{
    //the Profile and trajectory curve
    vector < glm::vec3> profile;
    vector < glm::vec3> trajectory;
    
    //The colour modifiers
    float colMod1 = 0;
    float colMod2 = 0;
    
    //The Original GREEn seaweed
   // if (amount % 2 == 0)
    {
        profile =
        {
            
            glm::vec3(-0.87, 0, 0),
            glm::vec3(-0.842363, 0.0175, 0),
            glm::vec3(-0.828904, 0.0254297, 0),
            glm::vec3(-0.814844, 0.0325, 0),
            glm::vec3(-0.782402, 0.043125, 0),
            glm::vec3(-0.762761, 0.0462109, 0),
            glm::vec3(-0.74, 0.0475, 0),
            glm::vec3(-0.60875, 0.0342187, 0),
            glm::vec3(-0.4775, 0.005, 0),
            glm::vec3(-0.434746, -0.012539, 0),
            glm::vec3(-0.401719, -0.033125, 0),
            glm::vec3(-0.3475, -0.075, 0),
            glm::vec3(-0.2575, -0.1475, 0),
            glm::vec3(-0.243047, -0.156367, 0),
            glm::vec3(-0.232188, -0.16125, 0),
            glm::vec3(-0.21, -0.1675, 0),
            glm::vec3(-0.179375, -0.175313, 0),
            glm::vec3(-0.145, -0.18, 0),
            glm::vec3(-0.0675, -0.175, 0),
            glm::vec3(-0.00359374, -0.167969, 0),
            glm::vec3(0.0625, -0.155, 0),
            glm::vec3(0.0880665, -0.144512, 0),
            glm::vec3(0.110469, -0.131719, 0),
            glm::vec3(0.1575, -0.1025, 0),
            glm::vec3(0.28, -0.035, 0),
            glm::vec3(0.342969, -0.0181251, 0),
            glm::vec3(0.4, -0.00999999, 0),
            glm::vec3(0.438125, -0.00656247, 0),
            glm::vec3(0.454844, -0.00789058, 0),
            glm::vec3(0.475, -0.0125, 0),
            glm::vec3(0.531094, -0.0353125, 0),
            glm::vec3(0.585, -0.0625, 0),
            glm::vec3(0.6425, -0.1, 0),
            glm::vec3(0.659668, -0.105684, 0),
            glm::vec3(0.677969, -0.109844, 0),
            glm::vec3(0.7175, -0.115, 0),
            glm::vec3(0.762187, -0.118594, 0),
            glm::vec3(0.785352, -0.11834, 0)
        };
        
        trajectory =
        {
            
            glm::vec3(-0.8725, 0, -0.1525),
            glm::vec3(-0.7625, 0, -0.0700001),
            glm::vec3(-0.685, 0, -0.00999999),
            glm::vec3(-0.637344, 0, 0.0142187),
            glm::vec3(-0.59, 0, 0.0325),
            glm::vec3(-0.555625, 0, 0.04375),
            glm::vec3(-0.538203, 0, 0.0460938),
            glm::vec3(-0.515, 0, 0.045),
            glm::vec3(-0.442813, 0, 0.0339062),
            glm::vec3(-0.40332, 0, 0.0231445),
            glm::vec3(-0.385493, 0, 0.0159985),
            glm::vec3(-0.37, 0, 0.00749999),
            glm::vec3(-0.35665, 0, -0.00317383),
            glm::vec3(-0.344609, 0, -0.01625),
            glm::vec3(-0.32375, 0, -0.0465626),
            glm::vec3(-0.29, 0, -0.1025),
            glm::vec3(-0.269844, 0, -0.131562),
            glm::vec3(-0.260527, 0, -0.142344),
            glm::vec3(-0.245, 0, -0.155),
            glm::vec3(-0.192187, 0, -0.192188),
            glm::vec3(-0.160156, 0, -0.209609),
            glm::vec3(-0.14376, 0, -0.215977),
            glm::vec3(-0.1275, 0, -0.22),
            glm::vec3(-0.110667, 0, -0.221768),
            glm::vec3(-0.0926758, 0, -0.221875),
            glm::vec3(-0.0551562, 0, -0.217813),
            glm::vec3(-0.0188086, 0, -0.209219),
            glm::vec3(0.0125, 0, -0.1975),
            glm::vec3(0.0252856, 0, -0.190251),
            glm::vec3(0.0364258, 0, -0.181543),
            glm::vec3(0.0554688, 0, -0.161094),
            glm::vec3(0.0925, 0, -0.1175),
            glm::vec3(0.185, 0, -0.0375),
            glm::vec3(0.223438, 0, 0.0053125),
            glm::vec3(0.243242, 0, 0.0250781),
            glm::vec3(0.254624, 0, 0.0333203),
            glm::vec3(0.2675, 0, 0.04),
            glm::vec3(0.298594, 0, 0.0497265),
            glm::vec3(0.334375, 0, 0.055625),
            glm::vec3(0.371094, 0, 0.057461),
            glm::vec3(0.405, 0, 0.055),
            glm::vec3(0.420566, 0, 0.0517017),
            glm::vec3(0.435938, 0, 0.0467383),
            glm::vec3(0.465625, 0, 0.0332813),
            glm::vec3(0.5175, 0, 0.0025),
            glm::vec3(0.585, 0, -0.0549999),
            glm::vec3(0.657187, 0, -0.0864062),
            glm::vec3(0.7325, 0, -0.1125),
            glm::vec3(0.781406, 0, -0.126875),
            glm::vec3(0.802285, 0, -0.129492),
            glm::vec3(0.813215, 0, -0.129146),
        };
        rotAngle = 90.0;
        colMod1 = 0.1;
        colMod2 = 0.39;
    }
    
    //The other RED seaweed
    else
    {
        profile =
        {
            
            glm::vec3(-0.165, 0.8125, 0),
            glm::vec3(-0.195, 0.6575, 0),
            glm::vec3(-0.20125, 0.614062, 0),
            glm::vec3(-0.201797, 0.597148, 0),
            glm::vec3(-0.2, 0.5775, 0),
            glm::vec3(-0.187656, 0.528125, 0),
            glm::vec3(-0.17, 0.4775, 0),
            glm::vec3(-0.1325, 0.3875, 0),
            glm::vec3(-0.105, 0.3025, 0),
            glm::vec3(-0.0992187, 0.276875, 0),
            glm::vec3(-0.0975, 0.2525, 0),
            glm::vec3(-0.0976563, 0.216406, 0),
            glm::vec3(-0.1025, 0.1775, 0),
            glm::vec3(-0.115469, 0.140781, 0),
            glm::vec3(-0.1325, 0.105, 0),
            glm::vec3(-0.17, 0.0375, 0),
            glm::vec3(-0.185469, 0.0123438, 0),
            glm::vec3(-0.19209, 0.000644505, 0),
            glm::vec3(-0.1975, -0.0125, 0),
            glm::vec3(-0.203906, -0.04125, 0),
            glm::vec3(-0.2075, -0.0775, 0),
            glm::vec3(-0.213281, -0.13125, 0),
            glm::vec3(-0.214707, -0.160703, 0),
            glm::vec3(-0.214182, -0.174639, 0),
            glm::vec3(-0.2125, -0.1875, 0),
            glm::vec3(-0.209478, -0.199355, 0),
            glm::vec3(-0.205273, -0.210625, 0),
            glm::vec3(-0.194375, -0.231875, 0),
            glm::vec3(-0.17, -0.2725, 0),
            glm::vec3(-0.125, -0.3525, 0),
            glm::vec3(-0.105, -0.395, 0),
            glm::vec3(-0.075, -0.49, 0),
            glm::vec3(-0.0653125, -0.542344, 0),
            glm::vec3(-0.0631641, -0.568457, 0),
            glm::vec3(-0.0634815, -0.580832, 0),
            glm::vec3(-0.065, -0.5925, 0),
            glm::vec3(-0.0678394, -0.603076, 0),
            glm::vec3(-0.0718555, -0.612578, 0),
            glm::vec3(-0.0826563, -0.63, 0),
            glm::vec3(-0.11, -0.67, 0),
            glm::vec3(-0.1775, -0.7925, 0),
            glm::vec3(-0.182246, -0.804238, 0),
            glm::vec3(-0.182404, -0.805003, 0),
            glm::vec3(-0.182485, -0.805648, 0),
            glm::vec3(-0.182496, -0.806187, 0),
            glm::vec3(-0.182444, -0.806628, 0),
            glm::vec3(-0.181719, -0.807656, 0),
            glm::vec3(-0.1775, -0.8125, 0),
            glm::vec3(-0.1775, -0.8525, 0)
        };
        
        trajectory =
        {
            
            glm::vec3(-0.1325, 0, 0.825),
            glm::vec3(-0.1825, 0, 0.7925),
            glm::vec3(-0.18491, 0, 0.789998),
            glm::vec3(-0.18563, 0, 0.788954),
            glm::vec3(-0.186074, 0, 0.788027),
            glm::vec3(-0.186146, 0, 0.787812),
            glm::vec3(-0.186203, 0, 0.787602),
            glm::vec3(-0.186277, 0, 0.787201),
            glm::vec3(-0.186298, 0, 0.78682),
            glm::vec3(-0.186272, 0, 0.786458),
            glm::vec3(-0.185781, 0, 0.785156),
            glm::vec3(-0.1825, 0, 0.78),
            glm::vec3(-0.182813, 0, 0.774219),
            glm::vec3(-0.182266, 0, 0.770566),
            glm::vec3(-0.18, 0, 0.765),
            glm::vec3(-0.168906, 0, 0.744375),
            glm::vec3(-0.161777, 0, 0.733125),
            glm::vec3(-0.158279, 0, 0.728496),
            glm::vec3(-0.155, 0, 0.725),
            glm::vec3(-0.153447, 0, 0.723717),
            glm::vec3(-0.151909, 0, 0.722666),
            glm::vec3(-0.148867, 0, 0.721172),
            glm::vec3(-0.147355, 0, 0.720685),
            glm::vec3(-0.145845, 0, 0.720342),
            glm::vec3(-0.142812, 0, 0.72),
            glm::vec3(-0.13, 0, 0.72),
            glm::vec3(-0.114688, 0, 0.718594),
            glm::vec3(-0.106914, 0, 0.718652),
            glm::vec3(-0.103306, 0, 0.719128),
            glm::vec3(-0.1, 0, 0.72),
            glm::vec3(-0.0970044, 0, 0.721213),
            glm::vec3(-0.0942383, 0, 0.722676),
            glm::vec3(-0.0916577, 0, 0.724402),
            glm::vec3(-0.0892187, 0, 0.726406),
            glm::vec3(-0.0845898, 0, 0.731309),
            glm::vec3(-0.08, 0, 0.7375),
            glm::vec3(-0.07, 0, 0.756875)
        };
        rotAngle = 180.0;
        colMod1 = 0.5;
        colMod2 = 0.1;
    }
    
    //Size, which is the profile vector size times the trajectory vect size times 6 
    totalLength = profile.size()*trajectory.size() * 6;
    verticesVBO = new GLfloat[totalLength];
    
    //A position which we will need to keep for the indices
    int pos = 0;
    int counterEBO = 0;
    
    //gets the size of the EBO
    indexLength = (profile.size() - 1)*(trajectory.size() - 1) * 6;
    
    indicesEBO = new GLuint[indexLength];
    
    //Translating the profile and trajectory vertices
    for (int i = 0; i < profile.size(); i++)
    {
        for (int k = 0; k < trajectory.size(); k++)
        {
            float colour = (float(i) / float(profile.size()));
            
            verticesVBO[pos] = profile.at(i).x + trajectory.at(k).x;
            verticesVBO[pos + 1] = profile.at(i).y + trajectory.at(k).y;
            verticesVBO[pos + 2] = profile.at(i).z + trajectory.at(k).z;
            verticesVBO[pos + 3] = colour * colMod1;
            verticesVBO[pos + 4] = colour *colMod2;
            verticesVBO[pos + 5] = 0.0;
            
            //increment the pos value in order to find the next set of vertices
            
            pos += 6;
            //If we are after the first iteration of i and k, then it means we are ontop.
            //Now we have to store the indices for the EBO in order to draw the triangles
            if (i > 0 && k > 0)
            {
                //Getting the indices for the EBO
                indicesEBO[counterEBO] = pos / 6 - 1;
                indicesEBO[counterEBO + 1] = pos / 6 - 1 - 1;
                indicesEBO[counterEBO + 2] = pos / 6 - trajectory.size() - 2;
                indicesEBO[counterEBO + 3] = pos / 6 - 1;
                indicesEBO[counterEBO + 4] = pos / 6 - trajectory.size() - 1;
                indicesEBO[counterEBO + 5] = pos / 6 - trajectory.size() - 2;
                //Increment the counter in order to find the next set of indices
                
                counterEBO += 6;
            }
        }
    }
}

