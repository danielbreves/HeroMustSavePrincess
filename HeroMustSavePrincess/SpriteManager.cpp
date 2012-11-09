//
//  SpriteManager.cpp
//  HeroMustSavePrincess
//
//  Created by Daniel Breves on 21/10/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#include <SFML/Graphics.hpp>
#include <time.h>
#include "SpriteManager.h"
#include "ResourcePath.hpp"
using namespace std;

#define SPRITE_SPEED    2
#define SPRITE_WIDTH    32
#define SPRITE_HEIGHT   32

SpriteManager::SpriteManager(Level* level, int tileSize) {
    srand((unsigned int)time(0));
    sf::Vector2i position;
    
    sf::Texture* badguy = new sf::Texture;
    
    badguy->loadFromFile(resourcePath() + "badguy.png");
    
    position = sf::Vector2i(rand() % ((level->GetWidth() * tileSize) - SPRITE_WIDTH), rand() % ((level->GetHeight() * tileSize) - SPRITE_HEIGHT));
    sprites.push_back(new Sprite(*badguy, position, SPRITE_WIDTH, SPRITE_HEIGHT, SPRITE_SPEED));

    position = sf::Vector2i(rand() % ((level->GetWidth() * tileSize) - SPRITE_WIDTH), rand() % ((level->GetHeight() * tileSize) - SPRITE_HEIGHT));
    sprites.push_back(new Sprite(*badguy, position, SPRITE_WIDTH, SPRITE_HEIGHT, SPRITE_SPEED));
    
    position = sf::Vector2i(rand() % ((level->GetWidth() * tileSize) - SPRITE_WIDTH), rand() % ((level->GetHeight() * tileSize) - SPRITE_HEIGHT));
    sprites.push_back(new Sprite(*badguy, position, SPRITE_WIDTH, SPRITE_HEIGHT, SPRITE_SPEED));
}

SpriteManager::~SpriteManager() {
    vector<Sprite*>::iterator i;
    for ( i = sprites.begin() ; i < sprites.end(); i++ ) {
        delete (*i);
    }
}

vector<Sprite*>* SpriteManager::GetSprites() {
    return &sprites;
}

void SpriteManager::Update(Camera* camera, int tileSize) {
    vector<Sprite*>::iterator i;
    for ( i = sprites.begin() ; i < sprites.end(); i++ ) {
        (*i)->Update(camera, tileSize);
    }
}

void SpriteManager::Draw(sf::RenderWindow* rw, Camera* camera) {
    vector<Sprite*>::iterator i;
    for ( i = sprites.begin() ; i < sprites.end(); i++ ) {
        (*i)->Draw(rw);
    }
}