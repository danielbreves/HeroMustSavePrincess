//
//  Player.cpp
//  HeroMustSavePrincess
//
//  Created by Daniel Breves on 8/11/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#include "Player.h"
#include <algorithm>

Player::Player(sf::Texture &img, sf::Vector2i p, int w, int h, int speed) : Sprite(img, p, SOUTH, w, h, speed) {
    life = 5;
    
    sf::IntRect image = {0, 128, width, height};
    int rows = 3;
    
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

void Player::CheckCollisions(vector<Sprite*>* sprites, Level* level) {
    vector<Sprite*>::iterator i;
    for (i = sprites->begin(); i < sprites->end(); i++) {
        if ((*i)->IsVisible() && (*i)->GetHealth()) {
            //The sides of the rectangles
            int leftEnemy, leftPlayer, rightEnemy, rightPlayer, topEnemy, topPlayer, bottomEnemy, bottomPlayer;
            
            //Calculate the sides of rect Player
            leftPlayer = GetPosition().x;
            rightPlayer = GetPosition().x + width;
            topPlayer = GetPosition().y;
            bottomPlayer = GetPosition().y + height;
            
            //Calculate the sides of rect Enemy
            leftEnemy = (*i)->GetPosition().x;
            rightEnemy = (*i)->GetPosition().x + (*i)->GetWidth();
            topEnemy = (*i)->GetPosition().y;
            bottomEnemy = (*i)->GetPosition().y + (*i)->GetHeight();
            
            if (bottomEnemy > topPlayer && topEnemy < bottomPlayer && rightEnemy > leftPlayer && leftEnemy < rightPlayer) {
                ActionType hitAction;
                
                if (currAction == STAND) {
                    hitAction = prevAction;
                } else {
                    hitAction = currAction;
                }
                
                if (attacking) {
                    (*i)->Hit(hitAction, level);
                }
                else {
                    Hit((*i)->GetAction(), level);
                }
            }
        }
    }
}

void Player::Move(Level* level, int x, int y) {
    int tileSize = level->GetTileSize();
    Corners tiles = DetectCollision(level, position.x + x, position.y + y);
    
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


void Player::Update(Level* level) {
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