//
//  Level.cpp
//  HeroMustSavePrincess
//
//  Created by Daniel Breves on 7/11/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#include "Level.h"

Level::Level(int w, int h)
{
	SetDimensions(w, h);
	this->w = w;
	this->h = h;
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

void Level::LoadLevel()
{
	//Eventually we'll write code to load level data from a
	//file, but for now we'll just make it all up.
}