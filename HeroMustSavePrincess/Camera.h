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

class Camera
{
private:
	//Absolute position of camera (number of
	//pixels from origin of level map)
	sf::Vector2f position;
    
	//Target position camera is moving towards
	sf::Vector2f target;
    
	//Size of camera
	sf::Vector2i size;
    
	//Speed of camera, a value between 0.0 and 1.0
	float speed;
    
public:
	Camera(int w, int h, float speed);
	~Camera();
    
	//Moves camera immediately to coordinates
	void Move(int x, int y);
	void MoveCenter(int x, int y);
    
	//Sets camera target
	void GoTo(int x, int y);
	void GoToCenter(int x, int y);
    
	//Updates camera position
	void Update();
    
	sf::Vector2i GetPosition() { return sf::Vector2i((int)position.x, (int)position.y); }
	
	//Helper function for retrieving camera's offset from
	//nearest tile
	sf::Vector2i GetTileOffset(int tileSize) { return sf::Vector2i((int)(position.x) % tileSize, (int)(position.y) % tileSize); }
    
	//Helper function for retrieving a rectangle defining
	//which tiles are visible through camera
	sf::IntRect GetTileBounds(int tileSize);
};

#endif /* defined(__HeroMustSavePrincess__Camera__) */
