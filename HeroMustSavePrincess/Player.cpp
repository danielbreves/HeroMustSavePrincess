//
//  Player.cpp
//  HeroMustSavePrincess
//
//  Created by Daniel Breves on 8/11/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#include "Player.h"
#include "Princess.h"
#include "ResourcePath.hpp"
#include <algorithm>
#include <typeinfo>

Player::Player(sf::Texture &img, sf::Vector2i p, int w, int h, int speed) : Sprite(img, p, SOUTH, w, h, speed) {
    life = 5;
    
    no.loadFromFile(resourcePath() + "no.wav");
    hit.loadFromFile(resourcePath() + "hit.wav");
    kiss.loadFromFile(resourcePath() + "kiss.wav");
    
    CreateAnimations(3);
}

void Player::CreateAnimations(int rows) {
    sf::IntRect image = {0, 128, width, height};
    
    // Create animation ATTACK_SOUTH
    Animation *south = new Animation;
    image.left = 0;
    
    for (int i = 0; i < rows; i++) {
        south->AddFrame(image, 150);
        image.left += width;
    }
    
    AddAnimation(ATTACK_SOUTH, south);
    
    image.top += height;
    
    // Create animation ATTACK_WEST
    Animation *west = new Animation;
    image.left = 0;
    
    for (int i = 0; i < rows; i++) {
        west->AddFrame(image, 150);
        image.left += width;
    }
    
    AddAnimation(ATTACK_WEST, west);
    
    image.top += height;
    
    // Create animation ATTACK_EAST
    Animation *east = new Animation;
    image.left = 0;
    
    for (int i = 0; i < rows; i++) {
        east->AddFrame(image, 150);
        image.left += width;
    }
    
    AddAnimation(ATTACK_EAST, east);
    
    image.top += height;
    
    // Create animation ATTACK_NORTH
    Animation *north = new Animation;
    image.left = 0;
    
    for (int i = 0; i < rows; i++) {
        north->AddFrame(image, 150);
        image.left += width;
    }
    
    AddAnimation(ATTACK_NORTH, north);
}

Player::~Player() {
    
}

void Player::HandleCollision(Sprite* sprite, Level* level) {
    ActionType hitAction;
    
    if (currAction == STAND) {
        hitAction = prevAction;
    } else {
        hitAction = currAction;
    }
    
    if (attacking) {
        if (dynamic_cast<Princess*>(sprite)) {
            level->SetStatus(Level::LOST);
        }
        sound.setBuffer(hit);
        sprite->Hit(hitAction, level);
    }
    else {
        if (dynamic_cast<Princess*>(sprite)) {
            sound.setBuffer(kiss);
            level->SetStatus(Level::COMPLETE);
        } else {
            sound.setBuffer(no);
            Hit(sprite->GetAction(), level);
        }
    }
    
    sound.play();
}

void Player::Move(Level* level, int x, int y) {
    int tileSize = level->GetTileSize();
    Corners tiles = GetTileCollisions(level, position.x + x, position.y + y);
    
    // WEST
    if (x < 0 && position.x > 0) {
        if (tiles.upLeft || tiles.downLeft) {
            SetAction(STAND);
            position.x = (tiles.leftX * tileSize) + width;
        } else {
            position.x += x;
        }
    }
    // EAST
    else if (x > 0 && position.x + width < level->GetWidth() * tileSize) {
        if (tiles.upRight || tiles.downRight) {
            SetAction(STAND);
            position.x = (tiles.rightX * tileSize) - width;
        } else {
            position.x += x;
        }
    }
    // NORTH
    else if (y < 0 && position.y > 0) {
        if (tiles.upLeft || tiles.upRight) {
            SetAction(STAND);
            position.y = (tiles.upY * tileSize) + height;
        } else {
            position.y += y;
        }
    }
    // SOUTH
    else if (y > 0 && position.y + height < level->GetHeight() * tileSize) {
        if (tiles.downLeft || tiles.downRight) {
            SetAction(STAND);
            position.y = (tiles.downY * tileSize) - height;
        } else {
            position.y += y;
        }
    }
}


void Player::Update(const vector<Sprite*>* sprites, Level* level) {
    CheckSpriteCollisions(sprites, level);
    
    int speed = GetSpeed();
    
    switch (currAction) {
        case WEST: Move(level, -speed, 0);
            break;
        case EAST: Move(level, speed, 0);
            break;
        case NORTH: Move(level, 0, -speed);
            break;
        case SOUTH: Move(level, 0, speed);
            break;
            
        default:
            break;
    }
    
    ActionType animation = currAction;
    
    if (life && attacking) animation = static_cast<Sprite::ActionType> ((int)animation + 5);
    
    // if moving
    if (currAction != STAND) animations[animation]->Update();
}

void Player::Draw(sf::RenderWindow* rw, Camera* camera) {
    ActionType animation;
    
    if (currAction == STAND) {
        animation = prevAction;
    } else {
        animation = currAction;
    }
    
    if (life) {
        if (attacking) {
            animation = static_cast<Sprite::ActionType> ((int)animation + 5);
        }
    
        animations[animation]->Draw(rw, image, position - camera->GetPosition());
    } else {
        animations[animation]->Draw(rw, &(*blood), position - camera->GetPosition());
    }
}