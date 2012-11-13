//
//  Camera.h
//  HeroMustSavePrincess
//
//  Created by Daniel Breves on 7/11/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#ifndef __HeroMustSavePrincess__Camera__
#define __HeroMustSavePrincess__Camera__

#include <iostream>
#include "Tile.h"

class Level;

class Camera
{
private:
	sf::IntRect video;
    
public:
    Camera() {};
	Camera(sf::IntRect video);
	~Camera();
    
	//Moves camera immediately to coordinates
	void Move(int x, int y);
	void MoveCenter(Level* level, int x, int y);
    
	sf::Vector2i GetPosition() { return sf::Vector2i(video.left, video.top); }
    
    sf::Vector2i GetSize() { return sf::Vector2i(video.width, video.height); }
	
	//Helper function for retrieving camera's offset from
	//nearest tile
	sf::Vector2i GetTileOffset(int tileSize) { return sf::Vector2i(video.left % tileSize, video.top % tileSize); }
    
	//Helper function for retrieving a rectangle defining
	//which tiles are visible through camera
	sf::IntRect GetTileBounds(int tileSize);
};

#endif /* defined(__HeroMustSavePrincess__Camera__) */
