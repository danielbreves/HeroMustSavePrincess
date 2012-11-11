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
                int diffTopBottom = bottomEnemy - topPlayer;
                int diffBottomTop = bottomPlayer - topEnemy;
                int diffRightLeft = rightEnemy - leftPlayer;
                int diffLeftRight = rightPlayer - leftEnemy;
                
                int diffs[] = {diffTopBottom,diffBottomTop,diffRightLeft,diffLeftRight};
                int maxDiff = *max_element(diffs, diffs+4);
                
                if (diffTopBottom == maxDiff) {
                    (*i)->Hit(currAction, level);
                } else if (diffBottomTop == maxDiff) {
                    (*i)->Hit(currAction, level);
                } else if (diffRightLeft == maxDiff) {
                    (*i)->Hit(currAction, level);
                } else if (diffLeftRight == maxDiff) {
                    (*i)->Hit(currAction, level);
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
        
    // if moving
    if (currAction != STAND) animations[currAction]->Update();
}