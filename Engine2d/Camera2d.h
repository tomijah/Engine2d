#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
namespace Engine2d
{
	class Camera2d
	{
	public:
		Camera2d(int screenWidth, int screenHeight);
		~Camera2d();
		void setPosition(glm::vec2 & newPosition) {
			position = newPosition;
			needsMatrixUpdate = true;
		}
		glm::vec2 getPosition() { return position; }
		void setScale(float & newScale) {
			scale = newScale;
			needsMatrixUpdate = true;
		}
		float getScale() { return scale; }
		glm::mat4 getProjectionMatrix();
	private:
		int _screenWidth;
		int _screenHeight;
		bool needsMatrixUpdate;
		glm::vec2 position;
		glm::mat4 orthoMatrix;
		glm::mat4 projectionMatrix;
		float scale;
	};
}