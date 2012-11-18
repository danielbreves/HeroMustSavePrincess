//
//  Camera.cpp
//  HeroMustSavePrincess
//
//  Created by Daniel Breves on 7/11/12.
//  Based on Tutorial by RevTorA: http://www.dreamincode.net/forums/topic/230524-c-tile-engine-from-scratch-part-1/
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#include "Camera.h"
#include "Level.h"
#include <math.h>

Camera::Camera(sf::IntRect video)
{
	this->video = video;
}

Camera::~Camera()
{
    
}

//Moves camera to coordinates
void Camera::Move(int x, int y)
{
	video.left = x;
	video.top = y;
}

//Centers camera at coordinates
void Camera::MoveCenter(Level* level, int x, int y)
{
    int tileSize = level->GetTileSize();
        
    if (video.width < level->GetWidth() * tileSize) {
        if (x < video.width / 2) {
            x = 0;
        }
        else if (x > level->GetWidth() * tileSize - video.width / 2) {
            x = level->GetWidth() * tileSize - video.width;
        }
        else {
            x = x - (video.width / 2);
        }
        
        video.left = x;
    }
    
    if (video.height < level->GetHeight() * tileSize) {
        if (y < video.height / 2) {
            y = 0;
        }
        else if (y > level->GetHeight() * tileSize - video.height / 2) {
            y = level->GetHeight() * tileSize - video.height;
        }
        else {
            y = y - (video.height / 2);
        }
        
        video.top = y;
    }
}

sf::IntRect Camera::GetTileBounds(int tileSize)
{
	int x = video.left / tileSize;
	int y = video.top / tileSize;
    
	//+1 in case camera size isn't divisible by tileSize
	//And +1 again because these values start at 0, and
	//we want them to start at one
	int w = video.width / tileSize + 2;
	int h = video.height / tileSize + 2;
    
	//And +1 again if we're offset from the tile
	if(x % tileSize != 0)
		w++;
	if(y % tileSize != 0)
		h++;
    
	return sf::IntRect(x, y, w, h);
}