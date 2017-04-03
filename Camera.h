#pragma once


#include <vector>


#include <GLM\glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>
#include <GLM\gtc\quaternion.hpp>


#define PI 3.14159265358979323846

enum CameraMovement 
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	ROLL_LEFT,
	ROLL_RIGHT,
	SPRINT,
	WALK,
	CRAWL
};


const GLfloat SPEED = 14.0f;
const GLfloat SENSITIVITY = 0.0025f;
const GLfloat ROLL_SPEED = 1.5f;
const GLfloat ZOOM = 45.0f;


class Camera 
{


public:

	Camera(glm::vec4 position = glm::vec4(0.0f, 0.0f, 30.0f, 0.0f), glm::quat cameraQuat = glm::angleAxis(float(PI), glm::vec3(0.0f, 1.0f, 0.0f)))
		: movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM), targetZoom(ZOOM)
	{

		this->position = position;
		this->cameraQuat = cameraQuat;
		this->updateView();

	}


	glm::mat4 getViewMatrix() 
	{
		return viewMatrix;

	}


	void processKeyboard(CameraMovement command, GLfloat deltaTime) 
	{

		GLfloat velocity = this->movementSpeed * deltaTime;

		if (FORWARD == command) 
		{
			this->position += this->front * velocity;
		}

		if (BACKWARD == command) 
		{
			this->position -= this->front * velocity;
		}

		if (LEFT == command) 
		{
			this->position += this->right * velocity;
		}

		if (RIGHT == command) 
		{
			this->position -= this->right * velocity;
		}

		if (UP == command) 
		{
			this->position -= this->up * velocity;
		}

		if (DOWN == command) 
		{
			this->position += this->up * velocity;
		}

		if (ROLL_LEFT == command) 
		{
			keyRoll = -ROLL_SPEED * deltaTime;
			this->updateView();
		}

		if (ROLL_RIGHT == command) 
		{
			keyRoll = +ROLL_SPEED * deltaTime;
			this->updateView();
		}


		if (SPRINT == command) 
		{
			this->movementSpeed = SPEED * 2.5;
		}


		if (WALK == command) 
		{
			this->movementSpeed = SPEED;
		}

		if (CRAWL == command) 
		{
			this->movementSpeed = SPEED / 2.5;
		}

		updateView();
	}



	void processMouseMovement(GLfloat xOffset, GLfloat yOffset) 
	{

		keyYaw = xOffset * this->mouseSensitivity;
		keyPitch = -yOffset * this->mouseSensitivity;

		this->updateView();

	}


	
	void processMouseScroll(GLfloat yOffset) 
	{
		if (yOffset > 0) 
		{
			targetZoom -= 3;
		}
		else if (yOffset < 0) 
		{
			targetZoom += 3;
		}

		if (targetZoom <= 5.0f) {
			targetZoom = 5.0f;
		}

		if (targetZoom >= 45.0f) {
			targetZoom = 45.0f;
		}
	}



	GLfloat getSmoothedZoom(float deltaTime) 
	{
		if (targetZoom > zoom) 
		{
			if (zoom >= 5.0f && zoom <= 45.0f) 
			{
				zoom += 45.0f * deltaTime;
			}

			if (zoom > targetZoom) 				
			{
				zoom = targetZoom;
			}

			if (zoom <= 5.0f) 
			{
				zoom = 5.0f;
			}

			if (zoom >= 45.0f) 
			{
				zoom = 45.0f;
			}

		}

		else if (targetZoom < zoom) 
		{
			if (zoom >= 5.0f && zoom <= 45.0f) 
			{
				zoom -= 45.0f * deltaTime;
			}

			if (zoom <= 5.0f) 
			{
				zoom = 5.0f;
			}

			if (zoom >= 45.0f) 
			{
				zoom = 45.0f;
			}

		}

		this->mouseSensitivity = SENSITIVITY * (this->zoom / 45);

		return this->zoom;
	}


private:

	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;

	glm::quat cameraQuat;
	glm::vec3 eyeVector;

	GLfloat keyPitch = 0.0f, keyYaw = 0.0f, keyRoll = 0.0f;

	glm::mat4 viewMatrix;

	GLfloat movementSpeed;
	GLfloat mouseSensitivity;

	GLfloat zoom;
	GLint targetZoom;

	void updateView() 
	{

		// Temporary frame quaternion from pitch, yaw, roll
		glm::quat yaw_quat = glm::quat(glm::vec3(0.0f, keyYaw, 0.0f));
		glm::quat pitch_quat = glm::quat(glm::vec3(keyPitch, 0.0f, 0.0f));
		glm::quat roll_quat = glm::quat(glm::vec3(0.0f, 0.0f, keyRoll));

		// Reset frame keys;
		keyPitch = 0.0f;
		keyYaw = 0.0f;
		keyRoll = 0.0f;

		cameraQuat = roll_quat * pitch_quat * cameraQuat * yaw_quat;
		cameraQuat = glm::normalize(cameraQuat);

		glm::mat4 rotation = glm::mat4_cast(cameraQuat);

		glm::mat4 translation = glm::mat4(1.0f);
		translation = glm::translate(translation, position);

		viewMatrix = rotation * translation;

		glm::mat4 mat = viewMatrix;

		front = glm::vec3(mat[0][2], mat[1][2], mat[2][2]);
		right = glm::vec3(mat[0][0], mat[1][0], mat[2][0]);
		up = glm::normalize(glm::cross(front, right));

	}
};