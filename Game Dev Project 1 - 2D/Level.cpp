#include "Level.h"
#include <fstream>
#include <Game Engine/Errors.h>
#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>
#include <iostream>
#include "base64.h"
#include <algorithm>
#include "Utility.h"

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


	
	// root node
	//for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute())
	//{
	//	if (std::strcmp(attr->name(), "version") == 0)
	//	{
	//		_tileMap.map.version = atoi(attr->value());
	//	}

	//	if (std::strcmp(attr->name(), "width") == 0)
	//	{
	//		_tileMap.map.width = atoi(attr->value());
	//	}

	//	if (std::strcmp(attr->name(), "height") == 0)
	//	{
	//		_tileMap.map.height = atoi(attr->value());
	//	}

	//	if (std::strcmp(attr->name(), "tilewidth") == 0)
	//	{
	//		_tileMap.map.tileWidth = atoi(attr->value());
	//	}

	//	if (std::strcmp(attr->name(), "tileheight") == 0)
	//	{
	//		_tileMap.map.tileHeight = atoi(attr->value());
	//	}
	//}

	//rapidxml::xml_node<>* childNode = node->first_node();
	//for (rapidxml::xml_attribute<> *attr = childNode->first_attribute(); attr; attr = attr->next_attribute())
	//{
	//	if (std::strcmp(attr->name(), "firstgid") == 0)
	//	{
	//		_tileMap.tileSet.firstgid = atoi(attr->value());
	//	}

	//	if (std::strcmp(attr->name(), "name") == 0)
	//	{
	//		_tileMap.tileSet.name = std::string(attr->value());
	//	}

	//	if (std::strcmp(attr->name(), "tilewidth") == 0)
	//	{
	//		_tileMap.tileSet.tileWidth = atoi(attr->value());
	//	}

	//	if (std::strcmp(attr->name(), "tileheight") == 0)
	//	{
	//		_tileMap.tileSet.tileHeight = atoi(attr->value());
	//	}
	//}

	//childNode = childNode->first_node();
	//for (rapidxml::xml_attribute<> *attr = childNode->first_attribute(); attr; attr = attr->next_attribute())
	//{
	//	if (std::strcmp(attr->name(), "source") == 0)
	//	{
	//		_tileMap.tileSet.source.source = std::string(attr->value());
	//	}

	//	if (std::strcmp(attr->name(), "width") == 0)
	//	{
	//		_tileMap.tileSet.source.width = atoi(attr->value());
	//	}

	//	if (std::strcmp(attr->name(), "height") == 0)
	//	{
	//		_tileMap.tileSet.source.height = atoi(attr->value());
	//	}

	//}

	//TileLayer layer;

	//childNode = node->first_node();
	//childNode = childNode->next_sibling();

	//for (rapidxml::xml_attribute<> *attr = childNode->first_attribute(); attr; attr = attr->next_attribute())
	//{
	//	if (std::strcmp(attr->name(), "name") == 0)
	//	{
	//		layer.name = std::string(attr->value());
	//	}

	//	if (std::strcmp(attr->name(), "width") == 0)
	//	{
	//		layer.width = atoi(attr->value());
	//	}

	//	if (std::strcmp(attr->name(), "height") == 0)
	//	{
	//		layer.height = atoi(attr->value());
	//	}

	//}

	//childNode = childNode->first_node();

	//for (rapidxml::xml_attribute<> *attr = childNode->first_attribute(); attr; attr = attr->next_attribute())
	//{
	//	if (std::strcmp(attr->name(), "encoding") == 0)
	//	{
	//		layer.data.encoding = std::string(attr->value());
	//	}

	//	if (std::strcmp(attr->name(), "compression") == 0)
	//	{
	//		layer.data.compression = std::string(attr->value());
	//	}
	//}

	//std::string prepForDecode = std::string(childNode->value());
	//
	//

	//prepForDecode.erase(
	//	std::remove_if(prepForDecode.begin(), prepForDecode.end(), &Level::CharRemoval), 
	//	prepForDecode.end());
	//layer.data.data = prepForDecode;

	////z_stream infstream;
	//

	//// only work with one layer for now
	//// decode base 64

	//_tileMap.tileLayer.push_back(layer);

	//// only have one to work with
	//// decode base 64
	//base64 b;
	//
	//std::string decoded = b.base64_decode(layer.data.data);
	//std::string uncompressed = Utility::Decompress(decoded);
	//std::vector<char> mapData(uncompressed.begin(), uncompressed.end());

	//std::cout << "Level Data" << std::endl;


	// parse ze file
	// overallstructure
	// <map>
	//	   <tileset>
	//     </tileset>
	//	   <layer>
	//			<data> </data>
	//     </layer>
	//	   <layer>
	//			<data> </data>
	//	   </layer>
	// </map>
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
