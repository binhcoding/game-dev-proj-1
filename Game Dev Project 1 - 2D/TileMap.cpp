#include "TileMap.h"


TileMap::TileMap()
{
	
}

TileMap::~TileMap()
{

}

void TileMap::Init(rapidxml::xml_document<>* node)
{
	// iterate through each node
	// the first node is the root
	rapidxml::xml_node<>* rootNode = node->first_node();
	PopulateMap(rootNode);
	// afterwards iterate through each node handling based on its condition
	for (rapidxml::xml_node<> *iter = rootNode->first_node(); iter; iter = iter->next_sibling())
	{
		if (std::strcmp(iter->name(), "tileset") == 0)
		{
			// tileset
			AddTileSet(iter);
		}

		if (std::strcmp(iter->name(), "layer") == 0)
		{
			AddTileLayer(iter);
		}
	}
}

void TileMap::PopulateMap(rapidxml::xml_node<>* node)
{
	// iterate through the attributes and assign them to their proper properties
	for (rapidxml::xml_attribute<>* iter = node->first_attribute(); iter; iter = iter->next_attribute())
	{
		if (CompareAttribute(iter, "orientation"))
		{
			_orientation = std::string(iter->value());
		}

		if (CompareAttribute(iter, "renderorder"))
		{
			_renderOrder = std::string(iter->value());
		}

		if (CompareAttribute(iter, "width"))
		{
			_width = atoi(iter->value());
		}

		if (CompareAttribute(iter, "height"))
		{
			_height = atoi(iter->value());
		}

		if (CompareAttribute(iter, "tilewidth"))
		{
			_tileWidth = atoi(iter->value());
		}

		if (CompareAttribute(iter, "tileheight"))
		{
			_tileHeight = atoi(iter->value());
		}

		if (CompareAttribute(iter, "nextobjectid"))
		{
			_nextObjectId = atoi(iter->value());
		}
	}
}

void TileMap::AddTileSet(rapidxml::xml_node<>* node)
{
	TileSet tileSet;
	// parse the tileset node

	for (rapidxml::xml_attribute<>* iter = node->first_attribute(); iter; iter = iter->next_attribute())
	{
		if (CompareAttribute(iter, "firstgid"))
		{
			tileSet.firstGid = atoi(iter->value());
		}

		if (CompareAttribute(iter, "name"))
		{
			tileSet.name = std::string(iter->value());
		}

		if (CompareAttribute(iter, "tilewidth"))
		{
			tileSet.tileWidth = atoi(iter->value());
		}

		if (CompareAttribute(iter, "tileheight"))
		{
			tileSet.tileHeight = atoi(iter->value());
		}
	}

	// parse the child node, should only be 1
	node = node->first_node();
	for (rapidxml::xml_attribute<>* iter = node->first_attribute(); iter; iter = iter->next_attribute())
	{
		if (CompareAttribute(iter, "source"))
		{
			tileSet.source = std::string(iter->value());
			// need to remove the first 3 characters because
			// all assets will be prepended with ../
			tileSet.source.erase(0, 3);
		}

		if (CompareAttribute(iter, "width"))
		{
			tileSet.width = atoi(iter->value());
		}

		if (CompareAttribute(iter, "height"))
		{
			tileSet.height = atoi(iter->value());
		}
	}

	_tileSets.push_back(tileSet);
}

void TileMap::AddTileLayer(rapidxml::xml_node<>* node)
{
	TileLayer tileLayer;
	// parse the tilelayer node

	for (rapidxml::xml_attribute<>* iter = node->first_attribute(); iter; iter = iter->next_attribute())
	{
		if (CompareAttribute(iter, "name"))
		{
			tileLayer.name = std::string(iter->value());
		}

		if (CompareAttribute(iter, "width"))
		{
			tileLayer.width = atoi(iter->value());
		}

		if (CompareAttribute(iter, "height"))
		{
			tileLayer.height = atoi(iter->value());
		}
	}

	// this is the data node, parse its children to fill our tilemap data
	node = node->first_node();
	for (rapidxml::xml_node<> *iter = node->first_node(); iter; iter = iter->next_sibling())
	{
		// each tile node has only gid
		tileLayer.tileData.push_back(atoi(iter->first_attribute()->value()));
	}

	_tileLayers.push_back(tileLayer);
}

bool TileMap::CompareAttribute(const rapidxml::xml_attribute<char>* name, std::string attribute)
{
	return std::strcmp(name->name(), attribute.c_str()) == 0;
}


