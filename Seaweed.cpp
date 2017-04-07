#include "Seaweed.h"
using namespace std;
Seaweed::Seaweed(float rotAngle, glm::vec3 position)
{
	//Reading vertices for the profile and trajectory curve from a file
	ifstream input;

	//Text file which has a large amount of vetices
	input.open("SeaweedInput.txt");
	int curveType;
	int numPoints;
	string line;
	input >> curveType;
	cout << curveType << endl;

	float x = 0;
	float y = 0;
	float z = 0;

	GLfloat* verticesVBO;

	
	int totalLength;
	//the Profile and trajectory curve
	vector < glm::vec3*>* profile = new vector<glm::vec3*>;
	vector < glm::vec3*>* trajectory = new vector<glm::vec3*>;

	//If curveType==0 then it is a TRANSLATIONAL curve
	if (curveType == 0)
	{
		//Gets te number or rows and skips lines
		getline(input, line);
		input >> numPoints;
		cout << numPoints << endl;
		getline(input, line);

		//Getting profile the actual data
		for (int i = 0; i < numPoints; i++)
		{
			input >> x;
			input >> y;
			input >> z;
			profile->push_back(new glm::vec3(x, y, z));
			//	cout << x << ", " << y << ", " << z << std::endl;
			getline(input, line);
		}
		//Getting the trajectory data
		int numPoints2;
		input >> numPoints2;

		for (int i = 0; i < numPoints2; i++)
		{
			input >> x;
			input >> y;
			input >> z;
			trajectory->push_back(new glm::vec3(x, y, z));
			//	cout << x << ", " << y << ", " << z << std::endl;
			getline(input, line);
		}

		//Size, which is the profile vector size times the trajectory vect size times 6 
		totalLength = profile->size()*trajectory->size() * 6;
		verticesVBO = new GLfloat[totalLength];

		//A position which we will need to keep for the indices
		int pos = 0;
		int counterEBO = 0;

		//gets the size of the EBO
		indexLength = (profile->size() - 1)*(trajectory->size() - 1) * 6;
		indicesEBO = new int[indexLength];

		//Translating the profile and trajectory vertices
		for (int i = 0; i < profile->size(); i++)
		{
			for (int k = 0; k < trajectory->size(); k++)
			{
				float colour = (float(i) / float(profile->size()));

				verticesVBO[pos] = profile->at(i)->x + trajectory->at(k)->x;
				verticesVBO[pos + 1] = profile->at(i)->y + trajectory->at(k)->y;
				verticesVBO[pos + 2] = profile->at(i)->z + trajectory->at(k)->z;
				verticesVBO[pos + 3] = colour * 0.4;
				verticesVBO[pos + 4] = colour * 0.1;
				verticesVBO[pos + 5] = 0;
				//increment the pos value in order to find the next set of vertices
				pos += 6;
				//If we are after the first iteration of i and k, then it means we are ontop.
				//Now we have to store the indices for the EBO in order to draw the triangles
				if (i > 0 && k > 0)
				{
					//Getting the indices for the EBO
					indicesEBO[counterEBO] = pos / 6 - 1;
					indicesEBO[counterEBO + 1] = pos / 6 - 1 - 1;
					indicesEBO[counterEBO + 2] = pos / 6 - trajectory->size() - 2;
					indicesEBO[counterEBO + 3] = pos / 6 - 1;
					indicesEBO[counterEBO + 4] = pos / 6 - trajectory->size() - 1;
					indicesEBO[counterEBO + 5] = pos / 6 - trajectory->size() - 2;
					//Increment the counter in order to find the next set of indices
					counterEBO += 6;
				}
			}
		}
	}
	//Else, if this is a ROTATIONAL curve
	else if (curveType != 0)
	{
		int spans = 0;
		//Stores the number of spans
		input >> spans;
		getline(input, line);
		input >> numPoints;
		//Getting profile the actual data
		for (int i = 0; i < numPoints; i++)
		{
			input >> x;
			input >> z;//cuz they messed up
			input >> y;//cuz they messed up
			profile->push_back(new glm::vec3(x, y, z));
			cout << x << ", " << y << ", " << z << std::endl;
			getline(input, line);
		}
		//Our Rotation matrix
		glm::mat4x4 rotation = glm::mat4(1.0f);
		//Finding the total length
		totalLength = profile->size() *spans * 6;
		indexLength = (profile->size() - 1)*(spans) * 6;
		int pos = 0;
		int indexEBO = 0;
		verticesVBO = new GLfloat[totalLength];
		indicesEBO = new int[indexLength];
		cout << spans << endl;
		//Iterates through all spans in order store the values into the vertices VBO
		for (int i = 0; i < spans; i++)
		{
			for (int k = 0; k < numPoints; k++)
			{
				glm::vec4 profile2 = glm::vec4(*profile->at(k), 1.0);
				glm::vec4 finalVec = profile2 * glm::rotate(rotation, glm::radians(360.0f / (float)spans)*i, glm::vec3(0, 1, 0));
				//Determines our colour based on the position of the vertices
				float colour = (float(k) / float(profile->size()));

				verticesVBO[pos] = finalVec.x;
				verticesVBO[pos + 1] = finalVec.y;
				verticesVBO[pos + 2] = finalVec.z;
				verticesVBO[pos + 3] = colour;
				verticesVBO[pos + 4] = colour;
				verticesVBO[pos + 5] = 0;
				//increment the pos value in order to find the next set of vertices
				pos += 6;
				//If we are after the first iteration of i and k, then it means we are ontop.
				//We must now take the indices for the EBO in order to draw the triangles
				if (i > 0 && k > 0)
				{
					//Getting the indices for the EBO
					indicesEBO[indexEBO] = pos / 6 - 1;
					indicesEBO[indexEBO + 1] = pos / 6 - 1 - 1;
					indicesEBO[indexEBO + 2] = pos / 6 - profile->size() - 2;
					indicesEBO[indexEBO + 3] = pos / 6 - 1;
					indicesEBO[indexEBO + 4] = pos / 6 - profile->size() - 1;
					indicesEBO[indexEBO + 5] = pos / 6 - profile->size() - 2;
					//increment the pos value in order to find the next set of vertices
					indexEBO += 6;
				}
				//If not then we are at the bottom
				else if (k > 0)
				{
					indicesEBO[indexEBO] = pos / 6 - 1;
					indicesEBO[indexEBO + 1] = pos / 6 - 1 - 1;
					indicesEBO[indexEBO + 2] = totalLength / 6 - profile->size() + pos / 6 - 2;
					indicesEBO[indexEBO + 3] = pos / 6 - 1;
					indicesEBO[indexEBO + 4] = totalLength / 6 - profile->size() + pos / 6 - 1;
					indicesEBO[indexEBO + 5] = totalLength / 6 - profile->size() + pos / 6 - 2;
					//increment the counter  in order to find the next set of indices for the EBO
					indexEBO += 6;
				}
			}
		}

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
		shader = new Shader("res/shader/seaweed.vs", "res / shaders / seaweed.fs");
	}
}

void Seaweed::render(glm::mat4 view, glm::mat4 projection)
{
	//enabling the shader
	shader->use();

	GLuint transformLoc = glGetUniformLocation(shader->program, "model");
	GLuint viewMatrixLoc = glGetUniformLocation(shader->program, "view");
	GLuint projectionLoc = glGetUniformLocation(shader->program, "projection");

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model)); 
	glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	//Draw the seaweed
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indexLength, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
