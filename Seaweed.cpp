#include "Seaweed.h"
#include <fstream>
using namespace std;


Seaweed::Seaweed(float rotAngle, glm::vec3 position)
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
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticesVBO)*totalLength, verticesVBO, GL_STATIC_DRAW);

		//EBO Binding
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesEBO)*indexLength, indicesEBO, GL_STATIC_DRAW);

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
		model = glm::translate(model, -position);
		
		//Apply the 90 degree rotation
		model = glm::rotate(model, glm::radians(rotAngle), glm::vec3(0, 0, 1));

		//Have to add a scale matrix
		

		//Compile the seaweed's shaders and load.
		shader = new Shader("res/shaders/seaweed.vs", "res/shaders/seaweed.fs");	
}



void Seaweed::render(glm::mat4 view, glm::mat4 projection)
{
	
	//Sin functiont to move the vertices based on time.
	//GLfloat timeMove = sin(glfwGetTime());
	//enabling the shader
	shader->use();

	GLuint transformLoc = glGetUniformLocation(shader->program, "model");
	GLuint viewMatrixLoc = glGetUniformLocation(shader->program, "view");
	GLuint projectionLoc = glGetUniformLocation(shader->program, "projection");

	//model = glm::translate(model, timeMove*(glm::vec3(0, 1, 0)));

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

	ofstream out;
	out.open("TEST.txt");

	ofstream out2;
	out2.open("TEST2.txt");

	//Size, which is the profile vector size times the trajectory vect size times 6 
	totalLength = profile.size()*trajectory.size() * 6;
	verticesVBO = new GLfloat[totalLength];

	//A position which we will need to keep for the indices
	int pos = 0;
	int counterEBO = 0;

	//gets the size of the EBO
	indexLength = (profile.size() - 1)*(trajectory.size() - 1) * 6;
	indicesEBO = new int[indexLength];

	//Translating the profile and trajectory vertices
	for (int i = 0; i < profile.size(); i++)
	{
		for (int k = 0; k < trajectory.size(); k++)
		{
			float colour = (float(i) / float(profile.size()));

			verticesVBO[pos] = profile.at(i).x + trajectory.at(k).x;
			verticesVBO[pos + 1] = profile.at(i).y + trajectory.at(k).y;
			verticesVBO[pos + 2] = profile.at(i).z + trajectory.at(k).z;
			verticesVBO[pos + 3] = colour * 0.1;
			verticesVBO[pos + 4] = colour * 0.39;
			verticesVBO[pos + 5] = 0;
			//increment the pos value in order to find the next set of vertices

			out << verticesVBO[pos] << ", " << verticesVBO[pos + 1] << ", " << verticesVBO[pos + 2] << ", " << verticesVBO[pos + 3] << ", " << verticesVBO[pos + 4] << ", " << verticesVBO[pos + 5] <<"," <<endl;
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

				out2 << indicesEBO[counterEBO] << ", " << indicesEBO[counterEBO + 1] << ", " << indicesEBO[counterEBO + 2] << ", " << indicesEBO[counterEBO + 3] << ", " << indicesEBO[counterEBO + 4] << ", " << indicesEBO[counterEBO + 5] << "," << endl;
				counterEBO += 6;
			}
		}
	}
}

