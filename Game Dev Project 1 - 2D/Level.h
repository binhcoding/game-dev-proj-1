#pragma once
#include <string>
#include <vector>
#include <Game Engine/SpriteBatch.h>
#include "TileMap.h"

class Level
{
	public:
	Level();
	~Level();
	void Init(const std::string& filePath);
	void Draw();
	private:
	static bool CharRemoval(char c);

	std::vector<char> _levelData;
	GameEngine::SpriteBatch _spriteBatch;
	TileMap _tileMap;
};

