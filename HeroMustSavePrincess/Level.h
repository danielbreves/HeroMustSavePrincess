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
#include "Tile.h"

class Level
{
private:
	//A 2D array of Tile pointers
	std::vector<std::vector<Tile*>> map;
    
	//Width and height of level (in tiles)
	int w;
	int h;
    
	void SetDimensions(int w, int h);
	
public:
	Level(int w, int h);
	~Level();
    
	void AddTile(int x, int y, Tile* tile);
	Tile* GetTile(unsigned int x, unsigned int y);
    
	void LoadLevel();
    
	int GetWidth();
	int GetHeight();
};

#endif /* defined(__HeroMustSavePrincess__Level__) */
