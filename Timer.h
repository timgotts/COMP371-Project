#pragma once

#include <string>
#include <iostream>

#include "GLFW\glfw3.h"

class Timer
{
public:
	static float startTime, endTime, elapsedTime;

	static void start(std::string s = "")
	{
		if (!(s == ""))
		{
			std::cout << "Loading " << s << "..." << std::endl;
		}
		startTime = glfwGetTime();
	}

	static void stop(std::string s = "")
	{
		endTime = glfwGetTime();
		elapsedTime = endTime - startTime;
		if(!(s == ""))
		{
			std::cout << s << " loaded in " << elapsedTime << " seconds." << std::endl;
		}
	}
};

float Timer::startTime = 0.0f;
float Timer::endTime = 0.0f;
float Timer::elapsedTime = 0.0f;