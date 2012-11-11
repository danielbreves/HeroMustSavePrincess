//
//  Player.cpp
//  HeroMustSavePrincess
//
//  Created by Daniel Breves on 8/11/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#include "Player.h"
#include <algorithm>

Player::Player(sf::Texture &img, sf::Vector2i p, int w, int h, int speed) : Sprite(img, p, w, h, speed) {
}

Player::~Player() {
    
}

void CheckCollision(sf::Sprite sprite) {
    
}

void Player::CheckCollisions(vector<Sprite*>* sprites) {
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
                    (*i)->Hit();
                    //(*i)->Move(0,20);
                } else if (diffBottomTop == maxDiff) {
                    (*i)->Hit();
                    //(*i)->Move(0,-20);
                } else if (diffRightLeft == maxDiff) {
                    (*i)->Hit();
                    //(*i)->Move(20,0);
                } else if (diffLeftRight == maxDiff) {
                    (*i)->Hit();
                    //(*i)->Move(-20,0);
                }
            }
        }
    }
}


void Player::Update(Level* level) {
    Move(level);
    
    // if moving
    if (currAction != STAND) animations[currAction]->Update();
}