#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <Game Engine/Sprite.h>
#include <Game Engine/GLSLProgram.h>
#include <Game Engine/GLTexture.h>
#include <Game Engine/Window.h>
#include <vector>
#include <Game Engine/Camera2D.h>
#include <Game Engine/SpriteBatch.h>
#include <Game Engine/InputManager.h>
#include <Game Engine/Timing.h>
#include <Game Engine/Widget.h>
#include "Level.h"

class Game
{
	public:
	Game();
	~Game();
	void Run();
	private:
	void Init();
	void InitShaders();
	void Update();
	void Draw();
	void Input();

	GameEngine::Window _window;
	GameEngine::Camera2D _camera; ///< Main Camera
	GameEngine::GLSLProgram _textureProgram; ///< The shader program
	GameEngine::FpsLimiter _fpsLimiter;
	GameEngine::InputManager _inputManager; ///< Handles input

	int _screenWidth;
	int _screenHeight;
	float _maxFps;
	float _fps;
	Level _level;
};

