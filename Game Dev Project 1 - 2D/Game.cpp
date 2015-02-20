#include "Game.h"
#include <iostream>
#include <string>
#include <Game Engine/Errors.h>
#include <Game Engine/GameEngine.h>
#include <Game Engine/ResourceManager.h>
#include <Game Engine/Widget.h>

Game::Game() : _screenWidth(1080), _screenHeight(720), _maxFps(60.0f)
{
	_camera.Init(_screenWidth, _screenHeight);
}


Game::~Game()
{
}

void Game::Run()
{
	Init();
	Update();
}

void Game::Init()
{
	GameEngine::Init();
	_window.Create("Game Engine", _screenWidth, _screenHeight, 0);
	_level.Init("Maps/level1.tmx");
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
	InitShaders();
	_fpsLimiter.Init(_maxFps, _maxFps);
}

void Game::InitShaders()
{
	// Compile our color shader
	_textureProgram.CompileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	_textureProgram.AddAttributes("vertexPosition");
	_textureProgram.AddAttributes("vertexColor");
	_textureProgram.AddAttributes("vertexUV");
	_textureProgram.LinkShaders();
}

void Game::Update()
{
	_fpsLimiter.SetMaxFPS(60.0f);
	while (true)
	{
		_fpsLimiter.Begin();
		Input();
		_camera.Update();
		Draw();
		_fps = _fpsLimiter.End();

		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 100)
		{
			std::cout << _fps << std::endl;
			frameCounter = 0;
		}
	}
}

void Game::Draw()
{
	// Set the base depth to 1.0
	glClearDepth(1.0);
	// Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_textureProgram.Use();
	glActiveTexture(GL_TEXTURE0);
	GLint textureLocation = _textureProgram.GetUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);
	GLint pLocation = _textureProgram.GetUniformLocation("P");
	glm::mat4 cameraMatrix = _camera.GetCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));
	_level.Draw();
	glBindTexture(GL_TEXTURE_2D, 0);
	_textureProgram.Unuse();
	// Swap our buffer and draw everything to the screen!
	_window.Swap();
}

void Game::Input()
{
	SDL_Event evnt;
	const float CAMERA_SPEED = 10.0f;
	const float SCALE_SPEED = 0.1f;
	//Will keep looping until there are no more events to process
	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
			case SDL_QUIT:
				// Exit the game here!
				break;
			case SDL_MOUSEMOTION:
				_inputManager.SetMouseCoordinates(evnt.motion.x, evnt.motion.y);
				break;
			case SDL_KEYDOWN:
				_inputManager.KeyPress(evnt.key.keysym.sym);
				break;
			case SDL_KEYUP:
				_inputManager.KeyRelease(evnt.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				_inputManager.KeyPress(evnt.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				_inputManager.KeyRelease(evnt.button.button);
				break;
		}
	}

	if (_inputManager.IsKeyDown(SDLK_w))
	{
		_camera.SetPosition(_camera.GetPosition() + glm::vec2(0.0f, CAMERA_SPEED));
	}

	if (_inputManager.IsKeyDown(SDLK_s))
	{
		_camera.SetPosition(_camera.GetPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
	}

	if (_inputManager.IsKeyDown(SDLK_d))
	{
		_camera.SetPosition(_camera.GetPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
	}

	if (_inputManager.IsKeyDown(SDLK_a))
	{
		_camera.SetPosition(_camera.GetPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
	}

	if (_inputManager.IsKeyDown(SDLK_q))
	{
		_camera.SetScale(_camera.GetScale() + SCALE_SPEED);
	}

	if (_inputManager.IsKeyDown(SDLK_e))
	{
		_camera.SetScale(_camera.GetScale() - SCALE_SPEED);
	}
}
