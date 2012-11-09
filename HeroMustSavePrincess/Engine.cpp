//
//  Engine.cpp
//  HeroMustSavePrincess
//
//  Created by Daniel Breves on 7/11/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#include "Engine.h"
#include "Animation.h"
#include "ResourcePath.hpp"

#define SCREEN_BPP      32
#define SPRITE_SPEED    2
#define SPRITE_WIDTH    32
#define SPRITE_HEIGHT   32
#define FPS             25

Engine::Engine(int w, int h)
{
    videoSize = sf::Vector2i(w, h);
}

Engine::~Engine()
{
    delete player;
    delete spriteManager;
    delete currentLevel;
    delete camera;
    delete window;
}

bool Engine::Init()
{
	window = new sf::RenderWindow(sf::VideoMode(videoSize.x, videoSize.y, SCREEN_BPP), "Hero Must Save Princess");
    camera = new Camera(videoSize.x,videoSize.y, 0.1f);
    
    mouseDown = false;
    
	if(!window)
		return false;
    
    currentLevel = new Level;
    currentLevel->LoadMap(resourcePath() + "tiled_test2.tmx", imageManager);
	
    tileSize = currentLevel->GetTileSize();
    
    spriteManager = new SpriteManager(currentLevel, tileSize);
    
    sf::Texture* hero = new sf::Texture;
    
    hero->loadFromFile(resourcePath() + "hero.png");
    
    player = new Player(*hero, sf::Vector2i(videoSize.x/2, videoSize.y/2), SPRITE_WIDTH, SPRITE_HEIGHT, SPRITE_SPEED);
    
	return true;
}

void Engine::ProcessInput()
{
	sf::Event evt;
	//Loop through all window events
	while(window->pollEvent(evt))
	{
		if(evt.type == sf::Event::Closed) {
			window->close();
		}
	}
    
    sf::IntRect bounds = camera->GetTileBounds(tileSize);
    
    cout << "player->GetPosition().x: " << player->GetPosition().x << endl;
    cout << "player->GetPosition().y: " << player->GetPosition().y << endl;
    cout << "camera->GetPosition().x: " << camera->GetPosition().x << endl;
    cout << "camera->GetPosition().y: " << camera->GetPosition().y << endl;
    cout << "bounds.left: " << bounds.left << endl;
    cout << "bounds.top: " << bounds.top << endl;
    cout << "player x?: " << ((player->GetPosition().x + SPRITE_WIDTH + camera->GetTileOffset(tileSize).x + SPRITE_SPEED) / tileSize) << endl;
    cout << "boundary x?: " << currentLevel->GetWidth() << endl;
    
        
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && player->GetPosition().x > -camera->GetPosition().x) {
        player->Action(Player::WEST);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
        (player->GetPosition().x + SPRITE_WIDTH + camera->GetTileOffset(tileSize).x + SPRITE_SPEED) / tileSize < currentLevel->GetWidth() - bounds.left) {
        player->Action(Player::EAST);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player->GetPosition().y > -camera->GetPosition().y) {
        player->Action(Player::NORTH);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
        (player->GetPosition().y + SPRITE_HEIGHT + camera->GetTileOffset(tileSize).y + SPRITE_SPEED) / tileSize < currentLevel->GetHeight() - bounds.top) {
        player->Action(Player::SOUTH);
    }
}

void Engine::Update()
{
    player->Update();
    player->CheckCollisions(spriteManager->GetSprites());
    camera->MoveCenter(player->GetPosition().x, player->GetPosition().y);
    camera->Update();
    spriteManager->Update(camera, tileSize);
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
    
    spriteManager->Draw(window, camera);
    
    player->Draw(window);
    
	window->display();
}

void Engine::MainLoop()
{
    sf::Int32 timelastcall = clock.getElapsedTime().asMilliseconds();
    
	//Loop until our window is closed
	while(window->isOpen())
	{
        if (window->isOpen() && clock.getElapsedTime().asMilliseconds() - timelastcall > 1000/FPS) {
            ProcessInput();
            Update();
            timelastcall = clock.getElapsedTime().asMilliseconds();
        }
        
        RenderFrame();
	}
}

void Engine::Go()
{
	if(!Init())
		throw "Could not initialize Engine";
    
	MainLoop();
}
