//
//  Camera.cpp
//  HeroMustSavePrincess
//
//  Created by Daniel Breves on 7/11/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#include "Camera.h"
#include <math.h>

Camera::Camera(int w, int h, float speed)
{
	size.x = w;
	size.y = h;
    
	if(speed < 0.0)
		speed = 0.0;
	if(speed > 1.0)
		speed = 1.0;
    
	this->speed = speed;
}

Camera::~Camera()
{
    
}

//Moves camera to coordinates
void Camera::Move(int x, int y)
{
	position.x = (float)x;
	position.y = (float)y;
	target.x = (float)x;
	target.y = (float)y;
}

//Centers camera at coordinates
void Camera::MoveCenter(int x, int y)
{
	x = x - (size.x / 2);
	y = y - (size.y / 2);
    
	position.x = (float)x;
	position.y = (float)y;
	target.x = (float)x;
	target.y = (float)y;
}

//Sets target to coordinates
void Camera::GoTo(int x, int y)
{
	target.x = (float)x;
	target.y = (float)y;
}

//Centers target at coordinates
void Camera::GoToCenter(int x, int y)
{
	x = x - (size.x / 2);
	y = y - (size.y / 2);
    
	target.x = (float)x;
	target.y = (float)y;
}

//This function allows us to do a cool camera
//scrolling effect by moving towards a target
//position over time.
void Camera::Update()
{
	//X distance to target, Y distance to target, and Euclidean distance
	float x, y, d;
    
	//Velocity magnitudes
	float vx, vy, v;
    
	//Find x and y
	x = (float)(target.x - position.x);
	y = (float)(target.y - position.y);
    
	//If we're within 1 pixel of the target already, just snap
	//to target and stay there. Otherwise, continue
	if((x*x + y*y) <= 1)
	{
		position.x = target.x;
		position.y = target.y;
	}
	else
	{
		//Distance formula
		d = sqrt((x*x + y*y));
        
		//We set our velocity to move 1/60th of the distance to
		//the target. 60 is arbitrary, I picked it because I intend
		//to run this function once every 60th of a second. We also
		//allow the user to change the camera speed via the speed member
		v = (d * speed)/60;
        
		//Keep v above 1 pixel per update, otherwise it may never get to
		//the target. v is an absolute value thanks to the squaring of x
		//and y earlier
		if(v < 1.0f)
			v = 1.0f;
		
		//Similar triangles to get vx and vy
		vx = x * (v/d);
		vy = y * (v/d);
        
		//Then update camera's position and we're done
		position.x += vx;
		position.y += vy;
	}
}

sf::IntRect Camera::GetTileBounds(int tileSize)
{
	int x = (int)(position.x / tileSize);
	int y = (int)(position.y / tileSize);
    
	//+1 in case camera size isn't divisible by tileSize
	//And +1 again because these values start at 0, and
	//we want them to start at one
	int w = (int)(size.x / tileSize + 2);
	int h = (int)(size.y / tileSize + 2);
    
	//And +1 again if we're offset from the tile
	if(x % tileSize != 0)
		w++;
	if(y % tileSize != 0)
		h++;
    
	return sf::IntRect(x, y, w, h);
}