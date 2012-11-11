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
#include <math.h>

#define SCREEN_BPP      32
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
    currentLevel->LoadMap(resourcePath() + "tiled_test3.tmx", imageManager);
	
    tileSize = currentLevel->GetTileSize();
    
    spriteManager = new SpriteManager(currentLevel);
    
    sf::Texture* hero = new sf::Texture;
    
    hero->loadFromFile(resourcePath() + "hero.png");
    
    player = new Player(*hero, sf::Vector2i(videoSize.x/2,videoSize.y/2), 32, 32, 3);
    
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
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        player->SetAction(Player::WEST);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        player->SetAction(Player::EAST);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        player->SetAction(Player::NORTH);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        player->SetAction(Player::SOUTH);
    }
    else {
        player->SetAction(Player::STAND);
    }
}

void Engine::Update()
{
    player->Update(currentLevel);
    player->CheckCollisions(spriteManager->GetSprites());
    camera->MoveCenter(player->GetPosition().x, player->GetPosition().y);
    camera->Update();
    spriteManager->Update(camera, currentLevel);
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
    
    int layers = currentLevel->GetLayers();

    for (int i = 0; i < layers; i++) {
        for (int y = 0, tileY = bounds.top; y < bounds.height; y++, tileY++) {
            for (int x = 0, tileX = bounds.left; x < bounds.width; x++, tileX++) {
                //Get the tile we're drawing
                tile = currentLevel->GetTile(i, tileX, tileY);
                
                if (tile) {
                    tile->Draw((x * tileSize) - camOffsetX, (y * tileSize) - camOffsetY, window);
                }
            }
        }
    }

    spriteManager->Draw(window, camera);
    
    player->Draw(window, camera);
    
	window->display();
}

//bool Engine::CheckCollision(sf::IntRect A, sf::IntRect B) {
//    //Calculate the sides of rect A
//    int leftA = A.left;
//    int rightA = A.left + A.width;
//    int topA = A.top;
//    int bottomA = A.top + A.height;
//    
//    //Calculate the sides of rect B
//    int leftB = B.left;
//    int rightB = B.left + B.width;
//    int topB = B.top;
//    int bottomB = B.top + B.height;
//    
//    //If any of the sides from A are outside of B
//    if (bottomA <= topB) return false;
//    if (topA >= bottomB) return false;
//    if (rightA <= leftB) return false;
//    if (leftA >= rightB) return false;
//    
//    //If none of the sides from A are outside B
//    return true;
//}

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
