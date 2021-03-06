#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace GameEngine
{
	class Camera2D
	{
		public:
		Camera2D();
		~Camera2D();
		void Init(int screenWidth, int screenHeight);
		void Update();

		bool IsInView(const glm::vec2& position, const glm::vec2& dimensions);

		// setters
		void SetPosition(glm::vec2& newPosition)
		{
			_position = newPosition;
			_needsMatrixUpdate = true;
		}
		void SetScale(float newScale)
		{
			_scale = newScale;
			_needsMatrixUpdate = true;
		}

		glm::vec2 ConvertScreenToWorld(glm::vec2 screenCoords);

		// getters
		glm::vec2 GetPosition() { return _position; }
		float GetScale() { return _scale; }
		glm::mat4 GetCameraMatrix() { return _cameraMatrix; }
		glm::mat4 GetCameraMatrixLocked();
		private:
		int _screenWidth, _screenHeight;
		bool _needsMatrixUpdate;
		glm::vec2 _position;
		glm::mat4 _cameraMatrix;
		glm::mat4 _orthoMatrix;
		float _scale;
	};

}