#include "Camera2d.h"


namespace Engine2d
{
	Camera2d::Camera2d(int screenWidth, int screenHeight) : position(0.0f, 0.0f), projectionMatrix(1.0f), scale(1.0f), needsMatrixUpdate(1)
	{
		_screenWidth = screenWidth;
		_screenHeight = screenHeight;
		orthoMatrix = glm::ortho(0.0f, (float)_screenWidth, (float)_screenHeight, 0.0f, -1.0f, 1.0f);
	}

	Camera2d::~Camera2d()
	{
	}

	glm::vec2 Camera2d::getFovLeftTop()
	{
		return getPosition() - glm::vec2(_screenWidth / 2, _screenHeight / 2);
	}

	glm::mat4 Camera2d::getProjectionMatrix()
	{
		if (needsMatrixUpdate) {
			projectionMatrix = glm::scale(glm::translate(orthoMatrix, glm::vec3(-position.x + _screenWidth / 2, -position.y + _screenHeight / 2, 0.0f)), glm::vec3(scale, scale, 0.0f));
			needsMatrixUpdate = false;
		}

		return projectionMatrix;
	}
	void Camera2d::translatePosition(glm::vec2 vector)
	{
		position += vector;
		needsMatrixUpdate = true;
	}
}