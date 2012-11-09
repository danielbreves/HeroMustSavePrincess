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
#include <cstdio>
#include <stdlib.h>
#include "ResourcePath.hpp"
using namespace rapidxml;

Level::Level()
{
    
}

Level::~Level()
{
    
}

void Level::SetDimensions(int w, int h)
{
    this->w = w;
	this->h = h;
    
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

void Level::LoadMap(std::string filename, ImageManager& imageManager) {
    Tmx::Map *map = new Tmx::Map();
	map->ParseFile(filename);
    
    if (map->HasError()) {
		printf("error code: %d\n", map->GetErrorCode());
		printf("error text: %s\n", map->GetErrorText().c_str());
        
		exit(map->GetErrorCode());
	}
        
    SetDimensions(map->GetWidth(), map->GetHeight());
    
    LoadTilesets(map, imageManager);
}

void Level::LoadTilesets(Tmx::Map* map, ImageManager& imageManager) {
    sf::Image img;
    tileSize = map->GetTileWidth();
    
    // Iterate through the tilesets.
	for (int i = 0; i < map->GetNumTilesets(); ++i) {
		// Get a tileset.
		const Tmx::Tileset *tileset = map->GetTileset(i);
        
        //Get the image file we're parsing and load it
		img.loadFromFile(resourcePath() + tileset->GetImage()->GetSource());
        
        int rows = tileset->GetImage()->GetWidth() / tileSize;
        int cols = tileset->GetImage()->GetHeight() / tileSize;
        
        for (int y = 0, i = 1; y < cols; ++y) {
            for (int x = 0; x < rows; ++i, ++x) {
                //Copy the right tile image from tileset
                sf::Texture tileImage;
                tileImage.create(tileSize, tileSize);
                tileImage.loadFromImage(img, sf::IntRect(x * tileSize, y * tileSize, tileSize, tileSize));
                
                //Add the image to our image list
                imageManager.AddImage(tileImage, i);
            }
        }
	}
    
    const Tmx::Layer *layer = map->GetLayer(0);
    
    for (int y = 0; y < layer->GetHeight(); ++y) {
        for (int x = 0; x < layer->GetWidth(); ++x) {
            //Get all the attributes
            int id = layer->GetTileId(x, y);
            
            Tile* newTile = new Tile(imageManager.GetImage(id));
            AddTile(x, y, newTile);
        }
	}
}