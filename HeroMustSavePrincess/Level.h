//
//  Level.h
//  HeroMustSavePrincess
//
//  Created by Daniel Breves on 7/11/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#ifndef __HeroMustSavePrincess__Level__
#define __HeroMustSavePrincess__Level__

#include <iostream>
#include <vector>
#include "../TmxParser/Tmx.h"
#include "Tile.h"
#include "ImageManager.h"

class SpriteManager;

class Level
{
private:
	//A 2D array of Tile pointers
	std::vector<std::vector<std::vector<Tile*>>> map;
    
	//Width and height of level (in tiles)
	int width, height, tileSize;
    
	void SetDimensions(int layers, int w, int h);
	
public:
	Level();
	~Level();
    
	void AddTile(int layer, int x, int y, Tile* tile);
	Tile* GetTile(unsigned int layer, unsigned int x, unsigned int y);
    
    void LoadMap(std::string filename, ImageManager& imageManager, SpriteManager* spriteManager);
    void LoadTilesets(Tmx::Map* map, ImageManager& imageManager);
    
    const int GetLayers() const {return (int)map.size();}
	const int GetWidth() const {return width;}
	const int GetHeight() const {return height;}
    const int GetTileSize() const {return tileSize;}
};

#endif /* defined(__HeroMustSavePrincess__Level__) */
