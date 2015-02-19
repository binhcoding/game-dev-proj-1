#pragma once
#include <string>
#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>

struct TileLayer
{
	std::string name;
	int width;
	int height;
	std::vector<int> tileData;
};

struct TileSet
{
	int firstGid;
	std::string name;
	int tileWidth;
	int tileHeight;
	std::string source;
	int width;
	int height;
};

class TileMap
{
	public:
	TileMap();
	~TileMap();
	void Init(rapidxml::xml_document<>* node);
	private:
	void PopulateMap(rapidxml::xml_node<>* node);
	void AddTileSet(rapidxml::xml_node<>* node);
	void AddTileLayer(rapidxml::xml_node<>* node);
	bool CompareAttribute(const rapidxml::xml_attribute<char>* name, std::string attribute);

	std::string _orientation;
	std::string _renderOrder;
	int _width, _height, _tileWidth, _tileHeight, _nextObjectId;
	std::vector<TileSet> _tileSets;
	std::vector<TileLayer> _tileLayers;
};

