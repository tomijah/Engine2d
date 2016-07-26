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

		void setPosition(glm::vec2 & newPosition);

		glm::vec2 getFovLeftTop();

		glm::vec2 getPosition() { return position; }

		void setScale(float & newScale) {
			scale = newScale;
			needsMatrixUpdate = true;
		}

		float getScale() { return scale; }

		glm::mat4 getProjectionMatrix();
		glm::mat4 getTranslationAndScaleMatrix();

		void translatePosition(glm::vec2 vector);
		void Update(float deltaTime);
		bool Smooth = false;

	private:
		int _screenWidth;
		int _screenHeight;
		bool needsMatrixUpdate;
		glm::vec2 position;
		glm::vec2 targetLocation;
		glm::mat4 orthoMatrix;
		glm::mat4 projectionMatrix;
		float scale;
	};
}