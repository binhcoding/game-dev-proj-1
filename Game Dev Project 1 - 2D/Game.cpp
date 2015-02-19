#include "Game.h"
#include <iostream>
#include <string>
#include <Game Engine/Errors.h>
#include <Game Engine/GameEngine.h>
#include <Game Engine/ResourceManager.h>
#include <Game Engine/Widget.h>

Game::Game()
{
}


Game::~Game()
{
}

void Game::Run()
{
	Init();
}

void Game::Init()
{
	GameEngine::Init();
	_window.Create("Game Engine", _screenWidth, _screenHeight, 0);
	_level.Init("Maps/level1.tmx");
}