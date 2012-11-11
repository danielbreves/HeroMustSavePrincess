//
//  Engine.cpp
//  HeroMustSavePrincess
//
//  Created by Daniel Breves on 7/11/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#include "Engine.h"
#include "Animation.h"
#include "MenuState.h"
#include "ResourcePath.hpp"
#include <math.h>

#define SCREEN_BPP      32
#define FPS             25

Engine::Engine()
{    
}

Engine::~Engine()
{
    delete player;
    delete spriteManager;
    delete currentLevel;
    delete camera;
}

void Engine::Init(StateManager* manager)
{
    videoSize = (sf::Vector2i)manager->GetWindow()->getSize();
    
    camera = new Camera(videoSize.x,videoSize.y, 0.1f);
    
    spriteManager = new SpriteManager;
    
    currentLevel = new Level;
    currentLevel->LoadMap(resourcePath() + "tiled_test4.tmx", imageManager, spriteManager);
    
    sf::Texture* hero = new sf::Texture;
    
    hero->loadFromFile(resourcePath() + "hero_full.png");
    
    player = new Player(*hero, sf::Vector2i(videoSize.x/2,videoSize.y/2), 32, 32, 3);
}

void Engine::HandleEvents(StateManager* manager)
{
	sf::Event evt;
	//Loop through all window events
	while(manager->GetWindow()->pollEvent(evt))
	{
		if(evt.type == sf::Event::Closed) {
			manager->GetWindow()->close();
		}
        if(evt.type == sf::Event::KeyPressed && (evt.key.code == sf::Keyboard::Escape)) {
			manager->ChangeState(new MenuState);
		}
	}
    
    player->SetAction(Player::STAND);
    
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        player->SetAction(Player::ATTACK);
    }
}

void Engine::Update(StateManager* manager)
{
    if (!player->GetHealth()) {
        manager->ChangeState(new MenuState);
    } else {
        player->Update(currentLevel);
        player->CheckCollisions(spriteManager->GetSprites(), currentLevel);
        camera->MoveCenter(player->GetPosition().x, player->GetPosition().y);
        camera->Update();
        spriteManager->Update(camera, currentLevel);
    }
}

void Engine::Render(StateManager* manager)
{
    int tileSize = currentLevel->GetTileSize();
    
	//Camera offsets
	int camOffsetX, camOffsetY;
    
	Tile* tile;
    
	//Get the tile bounds we need to draw and Camera bounds
	sf::IntRect bounds = camera->GetTileBounds(tileSize);
    
	//Figure out how much to offset each tile
	camOffsetX = camera->GetTileOffset(tileSize).x;
	camOffsetY = camera->GetTileOffset(tileSize).y;
    
    int layers = currentLevel->GetLayers();
    
	//Loop through and draw each tile
    for (int i = 0; i < layers; i++) {
        for (int y = 0, tileY = bounds.top; y < bounds.height; y++, tileY++) {
            for (int x = 0, tileX = bounds.left; x < bounds.width; x++, tileX++) {
                //Get the tile we're drawing
                tile = currentLevel->GetTile(i, tileX, tileY);
                
                if (tile) {
                    tile->Draw((x * tileSize) - camOffsetX, (y * tileSize) - camOffsetY, manager->GetWindow());
                }
            }
        }
    }

    spriteManager->Draw(manager->GetWindow(), camera);
    
    player->Draw(manager->GetWindow(), camera);
}
