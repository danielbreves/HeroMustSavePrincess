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
#include "MessageState.h"
#include "StateManager.h"
#include "ResourcePath.hpp"
#include <sstream>
#include <math.h>

Engine::Engine()
{
}

Engine::Engine(int width, int height) {
    camera = Camera(sf::IntRect(0,0,width,height));
    
    sf::Texture* hero = new sf::Texture;
    hero->loadFromFile(resourcePath() + "hero_full.png");
    player = new Player(*hero, 32, 32, 3);
    
    CreateLevels();
}

Engine::~Engine()
{    
    delete player;
}

void Engine::Init(StateManager* manager)
{
    sf::Vector2i videoSize = (sf::Vector2i)manager->GetWindow()->getSize();
    
    levels.front().LoadMap();
    
    int tileSize = levels.front().GetTileSize();
    int centerX = (levels.front().GetWidth() * tileSize - videoSize.x)/2;
    int centerY = (levels.front().GetHeight() * tileSize - videoSize.y)/2;
    
    camera.Move(centerX, centerY);
    
    player->SetPosition(levels.front().GetPlayerPosition());
}

void Engine::CreateLevels() {
    levels.push(Level(resourcePath() + "tiled_test6.tmx"));
    levels.push(Level(resourcePath() + "level_momo.tmx"));
}

void Engine::HandleEvents(StateManager* manager)
{
	sf::Event evt;

	while(manager->GetWindow()->pollEvent(evt))
	{
		if(evt.type == sf::Event::Closed) {
			manager->GetWindow()->close();
		}
        if(evt.type == sf::Event::KeyPressed && (evt.key.code == sf::Keyboard::Escape)) {
			manager->ChangeState(new MenuState);
		}
        
        if(evt.type == sf::Event::KeyPressed && (evt.key.code == sf::Keyboard::Num1)) {
			manager->StopMusic();
		}
        
        if(evt.type == sf::Event::KeyPressed && (evt.key.code == sf::Keyboard::Num2)) {
			manager->PlayMusic();
		}
	}
    
    player->SetAction(Player::STAND);
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        player->SetAction(Player::NORTH);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        player->SetAction(Player::SOUTH);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        player->SetAction(Player::WEST);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        player->SetAction(Player::EAST);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        player->SetAction(Player::ATTACK);
    }
}

void Engine::Update(StateManager* manager)
{
    if (!player->GetHealth() || levels.front().GetStatus() == Level::LOST) {
        sf::sleep(sf::seconds(1.2f));
        manager->ChangeState(new MessageState("Game Over", 60, new MenuState));
    }
    else if (levels.front().GetStatus() == Level::COMPLETE) {
        levels.pop();

        if (levels.empty()) {
            sf::sleep(sf::seconds(1.2f));
            manager->ChangeState(new MessageState("You won!", 60, new MenuState));
        } else {
            currLevel++;
            std::stringstream ss;
            ss << "Level " << currLevel;
            sf::sleep(sf::seconds(1.2f));
            manager->ChangeState(new MessageState(ss.str(), 60, this));
        }
    }
    else {
        player->Update(levels.front().GetSprites(), &levels.front());
        camera.MoveCenter(&levels.front(), player->GetPosition().x, player->GetPosition().y);
        levels.front().Update(&camera, player);
    }
}

void Engine::Render(StateManager* manager)
{
    levels.front().Draw(manager->GetWindow(), &camera);
    
    player->Draw(manager->GetWindow(), &camera);
}
