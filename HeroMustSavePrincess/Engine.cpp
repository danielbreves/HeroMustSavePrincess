//
//  Engine.cpp
//  HeroMustSavePrincess
//
//  Created by Daniel Breves on 7/11/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#include "Engine.h"
#include "ResourcePath.hpp"

#define SCREEN_BPP 32

Engine::Engine(int w, int h, int tSize)
{
    videoSize = sf::Vector2i(w, h);
    tileSize = tSize;
}

Engine::~Engine()
{
    
}

bool Engine::Init()
{
	window = new sf::RenderWindow(sf::VideoMode(videoSize.x, videoSize.y, SCREEN_BPP), "Hero Must Save Princess");
    camera = new Camera(videoSize.x,videoSize.y, 0.1f);
    
    mouseDown = false;
    
	if(!window)
		return false;
    
    LoadImages();
    LoadLevel();
    
	return true;
}

void Engine::RenderFrame()
{
	//Camera offsets
	int camOffsetX, camOffsetY;
    
	Tile* tile;
    
	window->clear();
	
	//Get the tile bounds we need to draw and Camera bounds
	sf::IntRect bounds = camera->GetTileBounds(tileSize);
    
	//Figure out how much to offset each tile
	camOffsetX = camera->GetTileOffset(tileSize).x;
	camOffsetY = camera->GetTileOffset(tileSize).y;
    
	//Loop through and draw each tile
	//We're keeping track of two variables in each loop. How many tiles
	//we've drawn (x and y), and which tile on the map we're drawing (tileX
	//and tileY)
	for(int y = 0, tileY = bounds.top; y < bounds.height; y++, tileY++)
	{
		for(int x = 0, tileX = bounds.left; x < bounds.width; x++, tileX++)
		{
			//Get the tile we're drawing
			tile = currentLevel->GetTile(tileX, tileY);
            
            if (tile) tile->Draw((x * tileSize) - camOffsetX, (y * tileSize) - camOffsetY, window);
		}
	}
    
	window->display();
}

void Engine::ProcessInput()
{
	sf::Event evt;
	//Loop through all window events
	while(window->pollEvent(evt))
	{
		if(evt.type == sf::Event::Closed)
			window->close();
		
		if((evt.type == sf::Event::MouseButtonPressed) && (mouseDown == false))
		{
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
			int x = camera->GetPosition().x + mousePos.x;
			int y = camera->GetPosition().y + mousePos.y;
			camera->GoToCenter(x, y);
			mouseDown = true;
		}
		if(evt.type == sf::Event::MouseButtonReleased)
			mouseDown = false;
	}
}

void Engine::Update()
{
    camera->Update();
}

void Engine::LoadImages()
{
	sf::Texture image1;
	image1.loadFromFile(resourcePath() + "tile1.gif");
	imageManager.AddImage(image1);
    
    sf::Texture image2;
    image2.loadFromFile(resourcePath() + "tile2.gif");
    imageManager.AddImage(image2);    
}

void Engine::LoadLevel()
{
	//Temporary level for testing
	currentLevel = new Level(40, 40);
    
	Tile* tile;
	for(int y = 0; y < 40; y++)
	{
		for(int x = 0; x < 40; x++)
		{
			if(y % 4 == 0)
				tile = new Tile(imageManager.GetImage(1));
			else
				tile = new Tile(imageManager.GetImage(0));
            
			currentLevel->AddTile(x, y, tile);
		}
	}
}

void Engine::MainLoop()
{
	//Loop until our window is closed
	while(window->isOpen())
	{
		ProcessInput();
		Update();
		RenderFrame();
	}
}

void Engine::Go()
{
	if(!Init())
		throw "Could not initialize Engine";
    
	MainLoop();
}
