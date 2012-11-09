//
//  Level.cpp
//  HeroMustSavePrincess
//
//  Created by Daniel Breves on 7/11/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#include <fstream>
#include "Level.h"
#include "rapidxml.hpp"
#include "ResourcePath.hpp"
using namespace rapidxml;

Level::Level()
{
    
}

Level::~Level()
{
    
}

int Level::GetHeight()
{
	return h;
}

int Level::GetWidth()
{
	return w;
}

void Level::SetDimensions(int w, int h)
{
	//w rows
	map.resize(w);
    
	//Each row has h columns of null Tile pointers
	for(int i = 0; i < w; i++)
	{
		map.at(i).resize(h, 0);
	}
}

void Level::AddTile(int x, int y, Tile* tile)
{
	map[x][y] = tile;
}

Tile* Level::GetTile(unsigned int x, unsigned int y)
{
    if(x < map.capacity())
	{
		if(y < map[x].capacity())
		{
			return map[x][y];
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

void Level::LoadLevel(std::string filename, ImageManager& imageManager)
{
	//Loads a level from xml file
	//Load the file
	std::ifstream inFile(filename.c_str());
    
	if(!inFile)
		throw "Could not load tileset: " + filename;
    
	//Dump contents of file into a string
	std::string xmlContents;
    
	//Blocked out of preference
	{
		std::string line;
		while(std::getline(inFile, line))
			xmlContents += line;
	}
    
	//Convert string to rapidxml readable char*
	std::vector<char> xmlData = std::vector<char>(xmlContents.begin(), xmlContents.end());
    xmlData.push_back('\0');
    
	//Create a parsed document with &xmlData[0] which is the char*
	xml_document<> doc;
	doc.parse<parse_no_data_nodes>(&xmlData[0]);
    
	//Get the root node
	xml_node<>* root = doc.first_node();
    
	//Get level attributes
	int width = atoi(root->first_attribute("width")->value());
	int height = atoi(root->first_attribute("height")->value());
    
	//Resize level
	this->w = width;
	this->h = height;
	SetDimensions(width, height);
    
	//Load each necessary tileset
	xml_node<>* tileset = root->first_node("tileset");
	while(tileset)
	{
		std::string path = resourcePath() + tileset->first_attribute("path")->value();
		//Load tileset
		imageManager.LoadTileset(path);
		//Go to next tileset
		tileset = tileset->next_sibling("tileset");
	}
    
	//Go through each tile
	xml_node<>* tile = root->first_node("tile");
	while(tile)
	{
		//Get all the attributes
		int x = atoi(tile->first_attribute("x")->value());
		int y = atoi(tile->first_attribute("y")->value());
		int baseid = atoi(tile->first_attribute("baseid")->value());
        
		//std::string walkString = tile->first_attribute("walkable")->value();
		//bool walkable = (walkString == "true")? true : false;
        
		//Create the tile and add it to the level.
		Tile* newTile = new Tile(imageManager.GetImage(baseid));
		AddTile(x, y, newTile);
        
		//Go to the next tile
		tile = tile->next_sibling("tile");
	}
}