//
//  SpriteManager.cpp
//  HeroMustSavePrincess
//
//  Created by Daniel Breves on 21/10/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#include <SFML/Graphics.hpp>
#include <time.h>
#include "Sprite.h"
#include "SpriteManager.h"
#include "Level.h"
#include "ResourcePath.hpp"
using namespace std;

SpriteManager::SpriteManager() {

}

SpriteManager::~SpriteManager() {
    vector<Sprite*>::iterator i;
    for ( i = sprites.begin() ; i < sprites.end(); i++ ) {
        delete (*i);
    }
}

void SpriteManager::AddSprite(Sprite* sprite) {
    sprites.push_back(sprite);
}

const vector<Sprite*>* SpriteManager::GetSprites() const {
    return &sprites;
}

void SpriteManager::CheckCollisions(Player* player, Level* level) {
    unsigned long size = sprites.size();
    
    for (int i = 0; i < size; i++) {
        if (CheckCollision(sprites[i],player)) {
            player->HandleCollision(sprites[i], level);
        }
            
		for (int j = i+1; j < size; j++) {
			if (CheckCollision(sprites[i],sprites[j])) {
                sprites[i]->HandleCollision(sprites[j]);
                sprites[j]->HandleCollision(sprites[i]);
			}
		}
	}
}

bool SpriteManager::CheckCollision(Sprite* A, Sprite* B) {
    if (!A->GetHealth() || !B->GetHealth()) return false;
        
    int Ax = A->GetPosition().x;
    int Ay = A->GetPosition().y;
    int Bx = B->GetPosition().x;
    int By = B->GetPosition().y;
    int speed = B->GetSpeed();
    
    if ((Ay + A->GetHeight()) <= By) return false;
    if (Ay >= (By + B->GetHeight())) return false;
	if ((Ax + A->GetWidth() - speed) <= Bx) return false;
	if (Ax >= (Bx + B->GetWidth() - speed)) return false;
    
    return true;
}

void SpriteManager::Update(Camera* camera, Level* level) {
    vector<Sprite*>::iterator i;
    for ( i = sprites.begin() ; i < sprites.end(); i++ ) {
        (*i)->Update(camera, level);
    }
}

void SpriteManager::Draw(sf::RenderWindow* rw, Camera* camera) {
    vector<Sprite*>::iterator i;
    for ( i = sprites.begin() ; i < sprites.end(); i++ ) {
        if ((*i)->IsVisible()) {
            (*i)->Draw(rw, camera);
        }
    }
}