#pragma once

#include "Hud.h"
#include "soil\soil.h"

Hud::Hud(int height, int width)
{
	vertices = { 

	};
	
	//// Compile and load shaders
	//shader = new Shader("res/shaders/hud.vs", "res/shaders/hud.fs");

	//glGenVertexArrays(1, &VAO);
	//glBindVertexArray(VAO);

	//glGenBuffers(1, &VBO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices.front(), GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	//glEnableVertexAttribArray(0);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);


	//glActiveTexture(GL_TEXTURE1);

	//glBindTexture(GL_TEXTURE_CUBE_MAP, hudTexture);
}

void Hud::render(glm::mat4 view, glm::mat4 projection)
{

}

void Hud::swapHuds()
{
}
