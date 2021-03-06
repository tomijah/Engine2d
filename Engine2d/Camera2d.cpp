#include "Camera2d.h"
#include <iostream>

namespace Engine2d
{
	Camera2d::Camera2d(int screenWidth, int screenHeight) : position(0.0f, 0.0f), targetLocation(0.0f, 0.0f), projectionMatrix(1.0f), scale(1.0f), needsMatrixUpdate(1)
	{
		_screenWidth = screenWidth;
		_screenHeight = screenHeight;
		orthoMatrix = glm::ortho(0.0f, (float)_screenWidth, (float)_screenHeight, 0.0f, -1.0f, 1.0f);
	}

	Camera2d::~Camera2d()
	{
	}

	void Camera2d::setPosition(glm::vec2 & newPosition)
	{
		if (Smooth) {
			targetLocation = newPosition;
		}
		else {
			position = newPosition;
			needsMatrixUpdate = true;
		}
	}

	glm::vec2 Camera2d::getFovLeftTop()
	{
		return getPosition() - glm::vec2(_screenWidth / 2, _screenHeight / 2);
	}

	glm::mat4 Camera2d::getProjectionMatrix()
	{
		if (needsMatrixUpdate) {
			projectionMatrix = orthoMatrix;
			projectionMatrix = glm::translate(projectionMatrix, glm::vec3(_screenWidth / 2, _screenHeight / 2, 0.0f));
			projectionMatrix = glm::scale(projectionMatrix, glm::vec3(scale, scale, 0.0f));
			projectionMatrix = glm::translate(projectionMatrix, glm::vec3(-position.x, -position.y, 0.0f));
			needsMatrixUpdate = false;
		}

		return projectionMatrix;
	}

	glm::mat4 Camera2d::getTranslationAndScaleMatrix() {
		glm::mat4 result(1.0f);
		result = glm::translate(result, glm::vec3(position.x, position.y, 0.0f));
		result = glm::scale(result, glm::vec3(1/scale,1/scale, 0.0f));
		result = glm::translate(result, glm::vec3(-_screenWidth / 2, -_screenHeight / 2, 0.0f));
		return result;
	}

	void Camera2d::translatePosition(glm::vec2 vector)
	{
		if(Smooth)
		{
			targetLocation += vector;
		}
		else 
		{
			position += vector;
			needsMatrixUpdate = true;
		}
	}
	void Camera2d::Update(float deltaTime)
	{
		if (Smooth && targetLocation != position) {
			glm::vec2 dist = targetLocation - position;
			glm::vec2 speed = ((dist) / 150.0f) * deltaTime;
			if (glm::length(dist) < 0.1f) {
				position = targetLocation;
			}
			else 
			{
				position += speed;
			}

			needsMatrixUpdate = true;
		}
	}
}