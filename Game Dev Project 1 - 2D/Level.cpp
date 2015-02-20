#include "Level.h"
#include <fstream>
#include <Game Engine/Errors.h>
#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>
#include <iostream>
#include "base64.h"
#include <algorithm>
#include "Utility.h"
#include <Game Engine/GLTexture.h>
#include <Game Engine/ImageLoader.h>

Level::Level()
{

}


Level::~Level()
{
}

void Level::Init(const std::string& filePath)
{
	std::ifstream loadFile(filePath);
	if (loadFile.fail())
	{
		GameEngine::FatalError("File failed to open: " + filePath);
	}

	std::vector<char> buffer((std::istreambuf_iterator<char>(loadFile)), std::istreambuf_iterator<char>());
	_levelData = buffer;
	_levelData.push_back('\0');

	rapidxml::xml_document<> doc;
	doc.parse<0>(&_levelData[0]);

	_tileMap.Init(&doc);


	// using tileset sources, decode their pngs into memory
	GameEngine::GLTexture textureData = GameEngine::ImageLoader::LoadPNG(_tileMap.GetTileSets()[0].source);
	// texture data loaded

	// because the entire atlas is in memory, utilize the uv space to select a piece of the image
	_spriteBatch.Init();
	_spriteBatch.Begin();

	// the tile map data is stored sequentially
	// if the map is 100x100
	// that means each row is 100 nodes
	std::vector<TileLayer>::iterator iter = _tileMap.GetTileLayers()->begin();

	GameEngine::ColorRGBA8 color(255, 255, 255, 255);

	// only one tile data atm

	int tileHeight = _tileMap.GetTileHeight();
	int tileWidth = _tileMap.GetTileWidth();
	int sourceWidth = _tileMap.GetTileSets()[0].width;
	int tilesPerRow = sourceWidth / _tileMap.GetTileSets()[0].tileWidth;

	int index = 0;

	for (int i = 0; i < _tileMap.GetWidth(); i++)
	{
		for (int j = 0; j < _tileMap.GetHeight(); j++)
		{
			//to find this image i must know the texture atlas width and height
			// 2048x2048
			// if the gid is 66 - 1
			// and the tile sizes are 64x64
			// that means the first row has 32 tiles
			// so 65 would be the 3rd row 2nd column
			// the top left pixel point would be at 64 x 128
			// u = 64/2048
			// v = 128/2048
			//iter->tileData[(i+1)*j]

			int gid = iter->tileData[index];
			gid -= _tileMap.GetTileSets()[0].firstGid - 1;
			int sourceY = ceil((float)gid / tilesPerRow) - 1;
			int sourceX = gid - (tilesPerRow * sourceY) - 1;
			
			// TURN THESE into coordinates
			sourceY = sourceY * tileWidth;
			sourceX = sourceX * tileWidth;

			// first 2 values is top left
			// last 2 values is bottom right
			float uStart = (float)(sourceX) / sourceWidth;
			float vStart = (float)(sourceWidth - (sourceY + tileWidth)) / sourceWidth;

			float uEnd = (float)(sourceX + tileWidth) / sourceWidth;
			float vEnd = (float)(sourceWidth - (sourceY)) / sourceWidth;

			glm::vec4 uvSpace(uStart, vStart, uEnd, vEnd);
			glm::vec4 positionAndSize = glm::vec4(j * tileWidth, -i * tileWidth, tileWidth, tileWidth);

			GameEngine::Vertex bottomLeft;
			bottomLeft.color = color;
			bottomLeft.SetPosition(positionAndSize.x, positionAndSize.y);
			bottomLeft.SetUV(uStart, vStart);

			GameEngine::Vertex topLeft;
			topLeft.color = color;
			topLeft.SetPosition(positionAndSize.x, positionAndSize.y + positionAndSize.w);
			topLeft.SetUV(uStart, vEnd);

			GameEngine::Vertex topRight;
			topRight.color = color;
			topRight.SetPosition(positionAndSize.x + positionAndSize.z, positionAndSize.y + positionAndSize.w);
			topRight.SetUV(uEnd, vEnd);

			GameEngine::Vertex bottomRight;
			bottomRight.color = color;
			bottomRight.SetPosition(positionAndSize.x + positionAndSize.z, positionAndSize.y);
			bottomRight.SetUV(uEnd, vStart);


			_spriteBatch.Draw(bottomLeft, bottomRight, topLeft, topRight, textureData.id, 0.0f);
			index++;
		}
	}

	_spriteBatch.End();

	std::cout << "Test";
}

bool Level::CharRemoval(char c)
{
	switch (c)
	{
		case '\n':
		case ' ':
			return true;
		default:
			return false;
	}
}

void Level::Draw()
{
	_spriteBatch.RenderBatches();
}
